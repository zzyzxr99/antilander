
#include "GameWorld.h"
#include "Functions.h"
#include "Level.h"
#include <iostream>
#include "math.h"
#include <sstream>
using namespace std;

//static variables
lua_State* GameWorld::luaVM;
unsigned short GameWorld::mNumMissile;
unsigned short GameWorld::mNumBomb;

int GameWorld::command;
float GameWorld::value;

GameWorld::GameWorld()
{
	// initialize all the member varibles
	mStarted		= false;
	mTempLevel = new Level();
	InitEverything();
	mGameMode		= knPlayMode;
    mGameStepper.Mark();
    mNumLndrLvl		= 0;
    mNumLndrScr		= 1;
    mLndrPersist	= false;
    mNumMissile		= 2;
    mNumBomb		= kDefaultStartBomb;
    mGunMoves		= false;
    mGunMoveRnd		= false;
    mEndGamePadOcc	= 0;
    mFrat			= false;
	lvlCtr			= 1;
	command			= 0;
	value			= 0;
	StartLua();
	
}

GameWorld::~GameWorld()
{
	// any new operators must have delete matches here
	// mLanders.capacity();
	lua_close(luaVM);
	delete mTempLevel;
}

void GameWorld::TestSaveLoadLevel()
{
    mEditLevel.EJRTestSaveLevel("TestLevel.LEV");
    mEditLevel.EJRTestLoadLevel("TestLevel.LEV");
}
void GameWorld::InitMissiles()
{
	Missile* PtrMissile;
    Point* loc ;
	loc	= mPlayerShip.GetLoc();
    loc->x = 50.0F;
    loc->y = 300.0F;
    Point targ;
    targ.x = 100.0F;
    targ.y = 108.0F;
	PtrMissile = new Missile( *loc,
                              targ );
	mMissiles.push_back(*PtrMissile);
/////////////// extra to test multi-missile render //////////////////////
 /*   loc.x = 50.0F;
    loc.y = 200.0F;
    targ.x = 200.0F;
    targ.y = 100.0F;
	PtrMissile = new Missile( loc,
                              targ );
	mMissiles.push_back(*PtrMissile);*/
/////////////// extra to test multi-missile render //////////////////////
	SpawnMissile();

}

void GameWorld::SpawnMissile()
{
    if ( mNumMissile > 0 )
    {
	    //set Missile at Gunship Location EVERYTIME
	    Missile *PtrMissile;
	    Point *Start;
	    Start = mPlayerShip.GetLoc();

	    //Destination
	    Point Destin;
	    Destin = mRender.getMouse();

	    //Direction
	    Vect Dir;
	    Dir = UnitVect(*Start, Destin);

	    //Add to Vector
	    PtrMissile = new Missile(*Start, Destin, Dir);
	    mMissiles.push_back(*PtrMissile);
        mNumMissile--;
    }
}

void GameWorld::SpawnBomb()
{
    if ( mNumBomb > 0 )
    {
	    //set Missile at Gunship Location EVERYTIME
	    Bomb *PtrBomb;
	    Point *Start;
	    Start = mPlayerShip.GetLoc();

	    //Destination
	    Point Destin;
	    Destin = mRender.getMouse();

	    //Direction
	    Vect Dir= MakeVect(*Start,Destin);
        //Add to Vector
	    PtrBomb = new Bomb(*Start, Dir);
	    mBombs.push_back(*PtrBomb);
        mNumBomb--;
    }
}

void GameWorld::InitLanders()
{
	Lander *PtrLander;
	PtrLander= new Lander();
    PtrLander->SetLocation( 100,100 );
	mLanders.push_back(*PtrLander);
/////////////// extra to test multi-lander render //////////////////////
    PtrLander= new Lander();
    PtrLander->SetLocation( 300,50 );
	mLanders.push_back(*PtrLander);
/////////////// extra to test multi-lander render //////////////////////
}

void GameWorld::SpawnLander()
{
	Lander *PtrLander;
    vector<Point>::iterator pad0;
	pad0= mGameTerrain.PadPts();
	Point sPoint,tPoint;
	sPoint.x= pad0[2].x;	    //magic number - needs to DIE!
	sPoint.y= kLanderStartY;
    tPoint.x= pad0[2].x;
    tPoint.y= pad0[2].y;
    PtrLander= new Lander(sPoint, tPoint, knLanderDescending, Lander::sGetDescentRate( ) );
	mLanders.push_back(*PtrLander);
}

void GameWorld::TestSpawnExplosion()
{
    Explosion *newExpl;
    Point sLoc= mRender.getMouse();
    newExpl= new Explosion(sLoc,
                           kExplosionMaxRadiusDefault,
                           kExplosionExpandRateDefault,
                           kExplosionInnerColorDefault,
                           kExplosionOuterColorDefault);
    mExplosions.push_back(*newExpl);
}

void GameWorld::SpawnExplosion( Point sLoc )
{
    Explosion *newExpl;
    newExpl= new Explosion( sLoc,
                            Explosion::sGetMaxRadius( ),
                            Explosion::sGetExpansionRate( ),
                            kExplosionInnerColorDefault,
                            kExplosionOuterColorDefault);
    mExplosions.push_back(*newExpl);

    // Test setting static variables
    //Explosion::sSetMaxRadius( newExpl->GetMaxRadius( ) + 10.0F );
    //Explosion::sSetExpansionRate( newExpl->GetExpansionRate( ) + 5.0F );

}

void GameWorld::InitEverything()
{
	mTempLevel->LoadLevel("LEVEL1.TXT");
	mCurrentLevel.Clone(mTempLevel);
    InitLevel( );
	//Init all Entities
	//mGameTerrain.InitTerrain();
	//mGameTerrain.InitPadPoints();
	/*InitMissiles();*/
	//InitLanders();
	//SpawnLander();
	int numpts= mGameTerrain.GetNumPadPts();
    //vector<Point>::iterator fP= mGameTerrain.PadPts();
	// Did not check num pad pts!
	//mPlayerShip.InitGunship(fP[3]);
    // EJR Explosions - None to init there are done during results
}

void GameWorld::DrawEverything( )
{
    SDL_FillRect( mRender.getpScreen( ),
                  NULL,
                  SDL_MapRGB( mRender.getpScreen( )->format,
                              0,0,0 ));

    mRender.DrawGunship( mRender.getpScreen( ),
                         mPlayerShip.GetLoc( ));

    mRender.DrawTerrain( mRender.getpScreen( ),
                         mGameTerrain.TerrainPts( ),
                         mGameTerrain.GetTPts( ),
						 mGameTerrain.TerBox());

    if ( mRender.GetSplashAlpha( ) > 0 )
    {
        mRender.DrawSplash( );
        mRender.DecSplashAlpha( 1 );
    }

    vector<Lander>::iterator landIter;
    for ( landIter = mLanders.begin( ); landIter != mLanders.end( ); landIter++ )
    {
        mRender.DrawLander( mRender.getpScreen( ),
                            &(landIter->GetLoc( )));
		mRender.DrawBox(landIter->GetLoc(), mRender.GetLanderBox());
    }

    vector<Missile>::iterator misIter;
    for ( misIter = mMissiles.begin( ); misIter != mMissiles.end( ); misIter++ )
    {
        mRender.DrawMissile( mRender.getpScreen( ),
                             &(misIter->GetLocation( )),
                             &(misIter->GetTarget( )));
        mRender.DrawCrosshair( mRender.getpScreen( ),
                               &(misIter->GetTarget( )),
                               255,0,0 );
        mRender.DrawBox( misIter->GetLocation( ),
                         misIter->GetBox( ) );
    }

    vector<Bomb>::iterator bombIter;
    for ( bombIter = mBombs.begin( ); bombIter != mBombs.end( ); bombIter++ )
    {
        mRender.DrawBomb( mRender.getpScreen( ),
                             &(bombIter->GetLocation( )),
                             bombIter->sGetRadius());
    }

    mRender.DrawMissile( mRender.getpScreen( ),
					     mPlayerShip.GetLoc( ),
					     &(mRender.getMouse( )));

    mRender.DrawCrosshair( mRender.getpScreen( ),
					       &mRender.getMouse( ),
					       0,255,0);

    vector<Explosion>::iterator iterExpl;
    for (iterExpl= mExplosions.begin(); iterExpl != mExplosions.end(); iterExpl++)
    {
        if (iterExpl->GetStatus() == knExplosionOccuring)
        {
            mRender.DrawExplosion(mRender.getpScreen(),
                                  iterExpl->GetLocation(),
                                  0,
                                  iterExpl->GetCurrentRadius(),
                                  iterExpl->GetOuterColor(),
                                  iterExpl->GetInnerColor());
        }
    }

	// Temp test for IntersectSegments
	Point *p1= mPlayerShip.GetLoc();
	Point p2= mRender.getMouse();

	lineRGBA( mRender.getpScreen(),
                  Round( (*p1).x ),
                  Round( (*p1).y),
                  Round( p2.x),
                  Round( p2.y),
                  255,255,255,255 );

	Point p3,p4;
	p3.x= 150.0;
	p3.y= 128.0;
	p4.x= 151.0;
	p4.y= 200.0;

	lineRGBA( mRender.getpScreen(),
              Round( p3.x ),
              Round( p3.y),
              Round( p4.x),
              Round( p4.y),
              255,255,255,255 );

	Point p5;
	if (IntersectSegments(*p1,p2,p3,p4,&p5))
	{
			lineRGBA( mRender.getpScreen(),
              Round( p5.x-5 ),
              Round( p5.y-5),
              Round( p5.x+5),
              Round( p5.y+5),
              0,255,255,255 );
			lineRGBA( mRender.getpScreen(),
              Round( p5.x+5 ),
              Round( p5.y-5),
              Round( p5.x-5),
              Round( p5.y+5),
              0,255,255,255 );
	}
	// end test code for IntersectSegments
	
	// do console stuff
	if(IsConsole())
	{
		//do console key detection
		//Draw Console
		mRender.DrawConsole(DoConsoleIn());
	}
	
    SDL_Flip( mRender.getpScreen( ));
}

void GameWorld::EditDrawEverything()
{
    SDL_FillRect( mRender.getpScreen( ),
                  NULL,
                  SDL_MapRGB( mRender.getpScreen( )->format,
                              0,0,0 ));
	bool DrawGreen= (mEditMode == knBuildMode);
	mRender.DrawLevel(&mEditLevel,DrawGreen);

    //mRender.DrawGunship( mRender.getpScreen( ),
    //                     mPlayerShip.GetLoc( ));

    //mRender.DrawTerrain( mRender.getpScreen( ),
    //                     mGameTerrain.TerrainPts( ),
    //                     mGameTerrain.GetTPts( ),
	//					 mGameTerrain.TerBox());

    /*if ( mRender.GetSplashAlpha( ) > 0 )
    {
        mRender.DrawSplash( );
        mRender.DecSplashAlpha( 1 );
    }*/
 
 /*   mRender.DrawMissile( mRender.getpScreen( ),
					     mPlayerShip.GetLoc( ),
					     &(mRender.getMouse( )));*/

    mRender.DrawCrosshair( mRender.getpScreen( ),
					       &mRender.getMouse( ),
					       0,255,0);

	// Temp test for IntersectSegments
	/*Point *p1= mPlayerShip.GetLoc();
	Point p2= mRender.getMouse();

	lineRGBA( mRender.getpScreen(),
                  Round( (*p1).x ),
                  Round( (*p1).y),
                  Round( p2.x),
                  Round( p2.y),
                  255,255,255,255 );

	Point p3,p4;
	p3.x= 150.0;
	p3.y= 128.0;
	p4.x= 151.0;
	p4.y= 200.0;

	lineRGBA( mRender.getpScreen(),
              Round( p3.x ),
              Round( p3.y),
              Round( p4.x),
              Round( p4.y),
              255,255,255,255 );

	Point p5;
	if (IntersectSegments(*p1,p2,p3,p4,&p5))
	{
			lineRGBA( mRender.getpScreen(),
              Round( p5.x-5 ),
              Round( p5.y-5),
              Round( p5.x+5),
              Round( p5.y+5),
              0,255,255,255 );
			lineRGBA( mRender.getpScreen(),
              Round( p5.x+5 ),
              Round( p5.y-5),
              Round( p5.x-5),
              Round( p5.y+5),
              0,255,255,255 );
	}*/
	// end test code for IntersectSegments

	
    SDL_Flip( mRender.getpScreen( ));
}

void GameWorld::StartGameStepper()
{
	mStarted= true;
	mGameStepper.Mark();
}

Render* GameWorld::GetRender( )
{
	return &mRender;
}

bool GameWorld::CheckTick( )
{
/*	unsigned long curTime,timePassed;
    curTime= mGameStepper.CurrentTimeMS();
	timePassed= curTime - mLastTimeStamp;
	if (timePassed >= kGameStep)
	{
		mLastElapsedTime= (float)(timePassed)/1000.0F;
		mLastTimeStamp= curTime;
		return true;
	}
	*/
    if (mGameStepper.CheckElapsedMS(kGameStep))
    {
        return true;
    }
    return false;
}

void GameWorld::UpdateEverything( )
{

    float elapsedTime= mGameStepper.LastInterval();
	//move all the missiles
	vector<Missile>::iterator misIter;
	for ( misIter = mMissiles.begin( ); misIter != mMissiles.end( ); misIter++ )
	{
		MissileStatusType tStatus= misIter->GetStatus();
		if (tStatus == knMissileFlying)
		{
			if ( misIter->GetLocation( ).Distance(misIter->GetDestination( ) ) < 2 )
			{
				misIter->SetStatus(knMissileExplode);
                //SpawnExplosion( misIter->GetLocation( ) );
			}
			else
			{
				Point temp = MoveEntity(misIter->GetLocation(),misIter->GetDirection(),misIter->GetSpeed(),elapsedTime);
				BBox MBoxTemp= misIter->GetBox();
				MBoxTemp.x+= temp.x;
				MBoxTemp.y+= temp.y;

				Point LanderTemp;
				vector<Lander>::iterator landIter;
				for ( landIter = mLanders.begin( ); landIter != mLanders.end( ); landIter++ )
				{
					if ( landIter->GetStatus( ) == knLanderDescending )
					{
						LanderTemp= landIter->GetLoc();
						BBox LBoxTemp= mRender.GetLanderBox();
						LBoxTemp.x+= LanderTemp.x;
						LBoxTemp.y+= LanderTemp.y;

						if (IntersectBoxes(MBoxTemp, LBoxTemp))
						{
							landIter->SetStatus(knLanderExplode);
							misIter->SetStatus(knMissileExplode);
						}
					}

				}	
				misIter->SetLocation(temp);
				Point newtemp;
				misIter->GetDirection();
				if(this->MissileSect(mGameTerrain.TerrainPts(),misIter->GetLocation(),misIter->GetDirection()))
				{
					misIter->SetStatus(knMissileExplode);	
				}
			}
		}
		else if (tStatus == knMissileExplode)
		{
			misIter->SetStatus(knMissileDead);
			SpawnExplosion(misIter->GetLocation());
		}

	}
	// Remove a Missile from vector if status is gone
    for ( misIter = mMissiles.begin( ); misIter != mMissiles.end( ); misIter++ )
	{
		if (misIter->GetStatus() == knMissileDead)
		{
            mMissiles.erase( misIter );
            break;
		}
	}

    //move all the Bombs
	vector<Bomb>::iterator bombIter;
	for ( bombIter = mBombs.begin( ); bombIter != mBombs.end( ); bombIter++ )
	{
		BombStatusType bStatus= bombIter->GetStatus();
		if (bStatus == knBombFlying)
		{
			    Vect bombVel= bombIter->GetVelocity();
                Vect bombAcc= bombIter->GetAcceleration();
			    Point temp = MoveEntityAccel(bombIter->GetLocation(),bombVel,bombAcc,elapsedTime);
				BBox BBoxTemp= bombIter->GetBox();
				BBoxTemp.x+= temp.x;
				BBoxTemp.y+= temp.y;

				Point LanderTemp;
				vector<Lander>::iterator landIter;
				for ( landIter = mLanders.begin( ); landIter != mLanders.end( ); landIter++ )
				{
					if ( landIter->GetStatus( ) == knLanderDescending )
					{
						LanderTemp= landIter->GetLoc();
						BBox LBoxTemp= mRender.GetLanderBox();
						LBoxTemp.x+= LanderTemp.x;
						LBoxTemp.y+= LanderTemp.y;

						if (IntersectBoxes(BBoxTemp, LBoxTemp))
						{
							landIter->SetStatus(knLanderExplode);
							bombIter->SetStatus(knBombExplode);
						}
					}

				}	
               
				IntersectStruct isOut;
                isOut= OutsideBoxes(BBoxTemp,mRender.GetGameScreen());
                if ((isOut.mLeft == 1) || (isOut.mRight == 1) || (isOut.mBottom == 1))
                {
                    bombIter->SetStatus(knBombDead);
                }
                else
                {
                    float yInter;
                    bool hitTerrain= false;
                    // Check if bombs is below terrain
                    int numtps= mGameTerrain.GetTPts();
                    vector<Point>::iterator landIter= mGameTerrain.TerrainPts();
                    for (int tps= 0; tps < (numtps-1); tps++)
                    {
                        if (CalcYIntercept(temp,landIter[tps],landIter[tps+1],&yInter))
                        {
                            if (temp.y >= yInter)
                            {
                                // intercept is below or equal to line - boom!
                                bombIter->SetStatus(knBombExplode);
                                hitTerrain= true;
                                break;
                            }
                        }
                    }
                    if (!hitTerrain)
                    {
                        bombIter->SetLocation(temp);

                        // Velocity changes based on acceleration
                        bombVel.x+= bombAcc.x*elapsedTime;
                        bombVel.y+= bombAcc.y*elapsedTime;
                        bombIter->SetVelocity(bombVel);
                    }
                }
		}
		else if (bStatus == knBombExplode)
		{
			bombIter->SetStatus(knBombDead);
			SpawnExplosion(bombIter->GetLocation());
		}
	}
	// Remove a Bomb from vector if status is gone
    for ( bombIter = mBombs.begin( ); bombIter != mBombs.end( ); bombIter++ )
	{
		if (bombIter->GetStatus() == knBombDead)
		{
            mBombs.erase( bombIter );
            break;
		}
	}

	// Update all Landers
	Point LanderTemp;
    vector<Lander>::iterator landIter;
    for ( landIter = mLanders.begin( ); landIter != mLanders.end( ); landIter++ )
    {
		LanderStatusType lStatus= landIter->GetStatus();
		if ( lStatus == knLanderDescending )
		{
			if(landIter->GetLoc().Distance(landIter->GetDest()) < 2 )
			{
				landIter->SetLocation(landIter->GetDest().x,landIter->GetDest().y);
				landIter->SetStatus( knLanderLanded );
			}
			else
			{
				LanderTemp= MoveEntity( landIter->GetLoc(),landIter->GetDir(), landIter->GetSpeed(), elapsedTime);
				landIter->SetLocation(LanderTemp.x,LanderTemp.y);
			}
		}
		else if ( lStatus == knLanderExplode )
		{
			landIter->SetStatus(knLanderDead);
			SpawnExplosion(landIter->GetLoc());
		}

    }
	// Remove a Lander from vector if dead
    for ( landIter = mLanders.begin( ); landIter != mLanders.end( ); landIter++ )
	{
		if (landIter->GetStatus() == knLanderDead)
		{
            mLanders.erase( landIter );
            break;
		}
	}
	// Update all Explosions
    vector<Explosion>::iterator iterExpl;
    for (iterExpl= mExplosions.begin(); iterExpl != mExplosions.end(); iterExpl++)
    {
        if (iterExpl->GetStatus() == knExplosionOccuring)
        {
            ExplosionStatusType eStatus;
            eStatus= iterExpl->Update(elapsedTime);

			// Fratricide - did I spell it right?
			// Check if explosion radius hits missile, bomb, lander
			// Need current radius, current location of Explosion
			float curRadius= iterExpl->GetCurrentRadius();
			Point locExpl= iterExpl->GetLocation();
			Point locCheck;
			float calcDist;
			// Landers check
			vector<Lander>::iterator iterLander;
			for (iterLander= mLanders.begin(); iterLander != mLanders.end(); iterLander++)
			{
				if (iterLander->GetStatus() == knLanderDescending)
				{
					locCheck= iterLander->GetLoc();
					calcDist= locExpl.Distance(locCheck);
					if (calcDist <= curRadius)
					{
						iterLander->SetStatus(knLanderExplode);
					}
				}
			}
			// Missiles check
			vector<Missile>::iterator iterMissile;
			for (iterMissile= mMissiles.begin(); iterMissile != mMissiles.end(); iterMissile++)
			{
				if (iterMissile->GetStatus() == knMissileFlying)
				{
					locCheck= iterMissile->GetLocation();
					calcDist= locExpl.Distance(locCheck);
					if (calcDist <= curRadius)
					{
						iterMissile->SetStatus(knMissileExplode);
					}
				}
			}
			vector<Bomb>::iterator iterBomb;
			for (iterBomb= mBombs.begin(); iterBomb != mBombs.end(); iterBomb++)
			{
				if (iterBomb->GetStatus() == knBombFlying)
				{
					locCheck= iterBomb->GetLocation();
					calcDist= locExpl.Distance(locCheck);
					if (calcDist <= curRadius)
					{
						iterBomb->SetStatus(knBombExplode);
					}
				}
			}
            iterExpl->SetStatus(eStatus);
        }
    }
    // Remove an Explosion from the vector - do not have to remove all at once
    for (iterExpl= mExplosions.begin(); iterExpl != mExplosions.end(); iterExpl++)
    {
        if (iterExpl->GetStatus() == knExplosionDone)
        {
            mExplosions.erase(iterExpl);
            cout << "Explosion Count=" << mExplosions.size() << endl;
            break; // break out of loop - iterator is invalid after erase - only delete one each update cycle
        }
    }

}

bool GameWorld::FireMissile()
{
	if(mRender.isLClicked())
	{
		if(mPlayerShip.CanShoot())
		{
		return true;
		}
	}
	return false;
}

// EJR only for testing explosion at right click mouse loc
bool GameWorld::FireBomb()
{
	if ( mRender.isRClicked() )
    {
        if ( mPlayerShip.CanBomb( ) )
        {
            return true;
        }
    }
    return false;
}

bool GameWorld::SplashRunning( )
{
    if ( mRender.GetSplashAlpha( ) > 0 )
    {
        return true;
    }
    return false;
}

bool GameWorld::MissileSect(vector<Point>::iterator TerArr, Point MissNose, Vect Direction)
{
	///////// calculate missile nose in relation to base //////////////
	float M = Direction.y/Direction.x;		
	float offX = sqrt (289/((M * M) + 1));
//	float offX = 17/sqrt((M * M) + 1);    works as well
	float offY = M*offX;
	MissNose.x += offX;
	int numTps= mGameTerrain.GetTPts();
	
	//missile off screen
	if(MissNose.x < -10 || MissNose.x > kWinWidth + 10 || MissNose.y < -10 || MissNose.y > kWinHeight + 10)
	{
		cout << "Missile offscreen" << endl;
		return true;
	}

	int ctr = 0; 
	int rndMiss = (int)(MissNose.x);
	Point iter;
	
	while ((ctr < (numTps - 1) && ((MissNose.x <= TerArr[ctr].x) || (MissNose.x > TerArr[ctr+1].x))))
	{
		ctr++;
	}

	if (ctr < (numTps - 1))
	{
		//in case of similar y values
		if(TerArr[ctr].y == TerArr[ctr+1].y && MissNose.y >= TerArr[ctr].y)
		{
			return true;
		}

		float diffX = TerArr[ctr+1].x - TerArr[ctr].x;
		float diffY = TerArr[ctr].y - TerArr[ctr+1].y;

		if(diffX == 0)
		{
			diffX = 0.00001F;
		}

		float slope = diffY/diffX;				//terrain slope
		float misVect = MissNose.x - TerArr[ctr].x;


		iter.x = TerArr[ctr].x;
		iter.y = TerArr[ctr].y;

		//move iterator
		for(int i=0; i<misVect+1; i++)
		{
			iter.x = iter.x + 1;
			iter.y = iter.y - slope;
			if(iter.x == rndMiss)
			{
				if(MissNose.y >= iter.y)
				{
					return true;
					cout << "Intersection!!!";
				}
			}
		}
	}
	return false;
}

bool GameWorld::LeftMouseHeld()
{
	return mRender.isLeftHeld();
}

bool GameWorld::RightMouseHeld()
{
	return mRender.isRightHeld();
}

void GameWorld::SetGameStatus(GameStatusType status)
{
	mGameMode= status;
}

void GameWorld::SetEditStatus(EditStatusType status)
{
	mEditMode= status;
}

GameStatusType GameWorld::GetGameStatus()
{
	return mGameMode;
}

EditStatusType GameWorld::GetEditStatus()
{
	return mEditMode;
}

void GameWorld::AddEditLevelPoint(Point p)
{	
	if (mEditLevel.GetNumTerPt() == 0)
	{
		p.x= 0;
	}
	mEditLevel.AddPoint(p);
}

void GameWorld::EndEditLvlPts(Point p)
{
	if (mEditLevel.GetNumTerPt() > 0)
	{
		p.x= 639;
	}
	mEditLevel.AddPoint(p);
}

void GameWorld::InitLevel( )
{
    // GameWorld
    mNumLndrLvl = mCurrentLevel.GetNumLndrLvl( );
    mNumLndrScr = mCurrentLevel.GetNumLndrScr( );
    mLndrPersist = mCurrentLevel.GetLndrPersist( );
    mNumMissile = mCurrentLevel.GetNumMissile( );
    mGunMoves = mCurrentLevel.GetGunMoves( );
    mGunMoveRnd = mCurrentLevel.GetGunMoveRnd( );
    mEndGamePadOcc = mCurrentLevel.GetEndGamePadOcc( );
    mFrat = mCurrentLevel.GetFrat( );

    // Terrain
    mGameTerrain.SetNumPadPts( mCurrentLevel.GetNumPad( ) );
    mGameTerrain.InitPadPoints( mCurrentLevel.GetPadpt( ) );
    mGameTerrain.SetNumTPts( mCurrentLevel.GetNumTerPt( ) );
    mGameTerrain.InitTerrain( mCurrentLevel.GetTerPt( ) );

    // Lander
    Lander::sSetDescentRate( mCurrentLevel.GetLndrDescRate( ) );

    // Missile
    Missile::sSetSpeed( mCurrentLevel.GetMissileSpd( ) );

    // Gunship
    mPlayerShip.SetPad( mCurrentLevel.GetGunStartPad( ) );
    mPlayerShip.SetReloadTime( mCurrentLevel.GetGunReload( ) );
    mPlayerShip.SetBombReloadTime( mCurrentLevel.GetBombReloadTime( ) );

    // Explosion
    Explosion::sSetMaxRadius( mCurrentLevel.GetExpRad( ) );
    Explosion::sSetExpansionRate( mCurrentLevel.GetExplRate( ) );

    // Bomb
    mNumBomb = mCurrentLevel.GetNumBomb( );
    Bomb::sSetSpeed( mCurrentLevel.GetBombMxSpd( ) );
    Bomb::sSetAcceleration( mCurrentLevel.GetBombAcc( ) );
    Bomb::sSetRadius( mCurrentLevel.GetBombRad( ) );
}

void GameWorld::InitEditLvl( )
{
    // GameWorld
    mNumLndrLvl = mEditLevel.GetNumLndrLvl( );
    mNumLndrScr = mEditLevel.GetNumLndrScr( );
    mLndrPersist = mEditLevel.GetLndrPersist( );
    mNumMissile = mEditLevel.GetNumMissile( );
    mGunMoves = mEditLevel.GetGunMoves( );
    mGunMoveRnd = mEditLevel.GetGunMoveRnd( );
    mEndGamePadOcc = mEditLevel.GetEndGamePadOcc( );
    mFrat = mEditLevel.GetFrat( );

    // Terrain
    mGameTerrain.SetNumPadPts( mEditLevel.GetNumPad( ) );
    mGameTerrain.InitPadPoints( mEditLevel.GetPadpt( ) );
    mGameTerrain.SetNumTPts( mEditLevel.GetNumTerPt( ) );
    mGameTerrain.InitTerrain( mEditLevel.GetTerPt( ) );

    // Lander
    Lander::sSetDescentRate( mEditLevel.GetLndrDescRate( ) );

    // Missile
    Missile::sSetSpeed( mEditLevel.GetMissileSpd( ) );

    // Gunship
    mPlayerShip.SetPad( mEditLevel.GetGunStartPad( ) );
    mPlayerShip.SetReloadTime( mEditLevel.GetGunReload( ) );

    // Explosion
    Explosion::sSetMaxRadius( mEditLevel.GetExpRad( ) );
    Explosion::sSetExpansionRate( mEditLevel.GetExplRate( ) );

    // Bomb
    mNumBomb = mEditLevel.GetNumBomb( );
    Bomb::sSetSpeed( mEditLevel.GetBombMxSpd( ) );
    Bomb::sSetAcceleration( mEditLevel.GetBombAcc( ) );
    Bomb::sSetRadius( mEditLevel.GetBombRad( ) );
}

vector<Lander>* GameWorld::GetLanders( )
{
    return &mLanders;
}

unsigned short GameWorld::GetNumLndrScr( )
{
    return mNumLndrScr;
}

int GameWorld::PointCheck()
{
	//for (int tp = 1; tp < (numPts); tp++)
	return 0;
}

string GameWorld::GetLevName(int num)
{
	string name;
	stringstream out;
	out << num;
	name = out.str();
	return ("LEVEL" + name + ".txt");
}

Level* GameWorld::GetLevel()
{
	return &mEditLevel;
}

Level* GameWorld::GetCurLevel()
{
	return &mCurrentLevel;
}

bool GameWorld::IsConsole()
{
	return GetRender()->GetConsole();
}

string GameWorld::DoConsoleIn()			//if '!' returned = stop stream
{
	char cnt = GetRender()->GetInput()->current;
	string str;
	cnt = '!';
	if(GetRender()->GetInput()->keyP != '!') 
	{
		cnt = GetRender()->GetInput()->keyP;
		GetRender()->GetInput()->keyP = '!';
	}
	GetRender()->GetInput()->current = cnt;
	
	if(cnt != '!' && cnt != '\b' && cnt != '\r')
	{
		GetRender()->GetInput()->conString = GetRender()->GetInput()->conString + cnt;	
	}
	if(cnt == '\b')		
	{
		if(!GetRender()->GetInput()->conString.empty())
		{
			GetRender()->GetInput()->conString.erase(GetRender()->GetInput()->conString.end()-1);
		}
	}
	else if(cnt == '$')
	{
		if(!GetRender()->GetInput()->conString.empty())
		{
			GetRender()->GetInput()->conString.clear();
		}
	}
	str = ">" + GetRender()->GetInput()->conString; 
	if(cnt == '\r')
	{
		str.erase(str.begin());
		GetRender()->GetInput()->luaString = str;
		DoLua();
//		str = GetRender()->GetInput()->conString;
		GetRender()->GetInput()->conString.clear();
	}
	return str;
}

//use this to send command
void GameWorld::DoLua()
{
	int err = luaL_dofile(luaVM, "lua.lua");

	if (err)
	{
		cout << lua_tostring(luaVM, -1) << endl;
	}
	lua_getfield(luaVM, LUA_GLOBALSINDEX, "conInput");				//call lua function conInput
	lua_pushstring(luaVM, GetRender()->GetInput()->luaString.c_str());

	if (lua_pcall(luaVM, 1, 1, 0) != 0)
	{    
		cout << "Error sending string to Lua" << endl;
	}
	lua_pop(luaVM, 1); 
}

int GameWorld::l_Action(lua_State* LVM)
{
	if(lua_gettop(LVM) !=2)
	{
		cout << "Incorrect number of parameters passed from Lua" << endl;
	}
	else
	{
		command = (int)lua_tonumber(LVM, -2);
		value = (float)lua_tonumber(LVM, -1);
	//	lua_pushnumber(LVM, 0);
	}
	switch(command)
	{
	case 1 :
		SetMissiles((int)value);
		break;
	case 2 :
		SetBombs((float)value);
		break;
	}
	return 0;
}

void GameWorld::StartLua()
{
	luaVM = lua_open();
	if (luaVM == NULL)
	{
		cout << "Lua VM not created!" << endl;
	}
	else
	{
		luaL_openlibs(luaVM);
	}
	lua_register(luaVM,"Action", l_Action);

}

void GameWorld::SetMissiles(int num)
{
	mNumMissile = num; 
}

void GameWorld::SetBombs(int num)
{
	mNumBomb = num; 
}