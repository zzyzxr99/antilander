
#include "GameWorld.h"
#include "Functions.h"
#include "Level.h"
#include <iostream>
#include "math.h"
#include <sstream>
using namespace std;

//static variables
lua_State* GameWorld::luaVM;
Level GameWorld::mCurrentLevel;
Level GameWorld::mEditLevel;
int GameWorld::command;
float GameWorld::value;


extern GameWorld *tWorld;



GameWorld::GameWorld()
{
	// initialize all the member varibles
	mStarted		= false;
	mTempLevel		= new Level();

	mGameMode		= knPlayMode;
    mGameStepper.Mark();
    mNumLndrLvl		= 10;
    mNumLndrScr		= 1;
    mLndrPersist	= false;
    mNumMissile		= kStartAmmo;
    mNumBomb		= kDefaultStartBomb;
    mGunMoves		= false;
    mGunMoveRnd		= false;
    mEndGamePadOcc	= 0;
    mFrat			= false;
	lvlCtr			= 0;
	command			= 0;
	value			= 0;
	StartLua();
	if(lvlCtr == 0)
	{
		mCurrentLevel.LoadLevel("default.txt");
	}
	else
	{
		mCurrentLevel.LoadLevel(GetLevName(lvlCtr));
	}
	InitEverything();
	/*vector<Point>::iterator fP= mGameTerrain.PadPts();
	mPlayerShip.InitGunship(fP[mCurrentLevel.GetGunStartPad()]);*/
	InitStars();
}

GameWorld::~GameWorld()
{
	// any new operators must have delete matches here
	// mLanders.capacity();
	lua_close(luaVM);
	delete mTempLevel;
}

void GameWorld::SpawnMissile()
{
    if ( mNumMissile > 0 )
    {
	    //set Missile at Gunship Location EVERYTIME
	    Point *Start;
	    Start = mPlayerShip.GetLoc();

	    //Destination
	    Point Destin;
	    Destin = mRender.getMouse();

	    //Direction
	    Vect Dir;
	    Dir = UnitVect(*Start, Destin);

	    //Add to Vector
	    Missile localMissile(*Start,Destin,Dir);
	    mMissiles.push_back(localMissile);
        mNumMissile--;
    }
}

void GameWorld::SpawnBomb()
{
    if ( mNumBomb > 0 )
    {
	    //set Missile at Gunship Location EVERYTIME
	    Point *Start;
	    Start = mPlayerShip.GetLoc();

	    //Destination
	    Point Destin;
	    Destin = mRender.getMouse();

	    //Direction
	    Vect Dir= MakeVect(*Start,Destin);
        //Add to Vector
	    Bomb localBomb(*Start, Dir);
	    mBombs.push_back(localBomb);
        mNumBomb--;
    }
}

void GameWorld::SpawnLander(Point sPoint, Point tPoint)
{
	//Lander *PtrLander;
	//PtrLander= new Lander(sPoint, tPoint, knLanderDescending, Lander::sGetDescentRate( ) );

    Lander localLander(sPoint, tPoint, knLanderDescending, Lander::sGetDescentRate( ));

	mLanders.push_back(localLander);
	_ASSERTE(mNumLndrsToGo > 0);
	mNumLndrsToGo--;
}

void GameWorld::SpawnExplosion( Point sLoc )
{
    //Explosion *newExpl;
    //newExpl= new Explosion( sLoc,
    //                        Explosion::sGetMaxRadius( ),
    //                        Explosion::sGetExpansionRate( ),
    //                        kExplosionInnerColorDefault,
    //                        kExplosionOuterColorDefault);

    Explosion localExplosion( sLoc,
                              Explosion::sGetMaxRadius( ),
                              Explosion::sGetExpansionRate( ),
                              kExplosionInnerColorDefault,
                              kExplosionOuterColorDefault );

    mExplosions.push_back(localExplosion);

    // Test setting static variables
    //Explosion::sSetMaxRadius( newExpl->GetMaxRadius( ) + 10.0F );
    //Explosion::sSetExpansionRate( newExpl->GetExpansionRate( ) + 5.0F );
}

void GameWorld::InitEverything()
{
	
	/*mTempLevel->LoadLevel("default.txt");
	mCurrentLevel.Clone(mTempLevel);*/
    InitLevel( );
	//Init all Entities
	//mGameTerrain.InitTerrain();
	//mGameTerrain.InitPadPoints();
	/*InitMissiles();*/
	//InitLanders();
	//SpawnLander();
	//int numpts= mGameTerrain.GetNumPadPts();
//	tWorld->SetGunPad(mCurrentLevel.GetGunStartPad());
	
//	vector<Point>::iterator fP= mGameTerrain.PadPts();
	//	mPlayerShip.InitGunship(fP[mCurrentLevel.GetGunStartPad()]);
    // EJR Explosions - None to init there are done during results
}

void GameWorld::DrawEverything( )
{
    SDL_FillRect( mRender.getpScreen( ),
                  NULL,
                  SDL_MapRGB( mRender.getpScreen( )->format,
                              0,0,0 ));

	mRender.DrawStars( mRender.getpScreen( ),
                                 mStars, sizeof(mStars)/8,
                                 2);

    mRender.DrawGunship( mRender.getpScreen( ),
                         mPlayerShip.GetLoc( ));

    mRender.DrawTerrain( mRender.getpScreen( ),
                         mGameTerrain.TerrainPts( ),
                         mGameTerrain.GetTPts( ),
						 mGameTerrain.TerBox());

    if ( mGameMode == knIntroMode ||
         mGameMode == knLevTransMode ||
         mGameMode == knEndMode )
    {
        mRender.DrawSplash( mGameMode );
    }

    vector<Lander>::iterator landIter;
    for ( landIter = mLanders.begin( ); landIter != mLanders.end( ); landIter++ )
    {
        mRender.DrawLander( mRender.getpScreen( ),
                            &(landIter->GetLoc( )));
//		mRender.DrawBox(landIter->GetLoc(), mRender.GetLanderBox());
    }

    // DWL draw missiles and bombs only in knPlayMode
    if ( mGameMode == knPlayMode )
    {
        vector<Missile>::iterator misIter;
        for ( misIter = mMissiles.begin( ); misIter != mMissiles.end( ); misIter++ )
        {
            mRender.DrawMissile( mRender.getpScreen( ),
                                 &(misIter->GetLocation( )),
                                 &(misIter->GetTarget( )));
            mRender.DrawCrosshair( mRender.getpScreen( ),
                                   &(misIter->GetTarget( )),
                                   255,0,0 );
         // mRender.DrawBox( misIter->GetLocation( ),
         //                  misIter->GetBox( ) );
        }
        vector<Bomb>::iterator bombIter;
        for ( bombIter = mBombs.begin( ); bombIter != mBombs.end( ); bombIter++ )
        {
            mRender.DrawBomb( mRender.getpScreen( ),
                                 &(bombIter->GetLocation( )),
                                 bombIter->sGetRadius());
        }
    }

    mRender.DrawMissile( mRender.getpScreen( ),
					     mPlayerShip.GetLoc( ),
					     &(mRender.getMouse( )));

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
	
	// do console stuff
	if(IsConsole())
	{
		//do console key detection
		//Draw Console
		mRender.DrawConsole(DoConsoleIn());
	}

	//this is temp draw menu
	
	//mRender.DrawScore(TotalScore);
	mScore.DrawScore(mScore.GetTotalScore(), mRender.getpScreen());
	//mRender.DrawMenu();
			
	if (mGameMode == knMenuMode)
	{
		mRender.DrawMenu();
		mRender.DrawCrosshair( mRender.getpScreen( ),
					       &mRender.getMouse( ),
					       0,255,0);
	}

    if ( mGameMode == knPlayMode
         ||
         mGameMode == knEditMode )
    {
        mRender.DrawCrosshair( mRender.getpScreen( ),
					           &mRender.getMouse( ),
					           0,255,0);
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
    if (mGameStepper.CheckElapsedMS(kGameStep))
    {
        return true;
    }
    return false;
}

void GameWorld::UpdateEverything( )
{
	int TotalScore = mScore.GetTotalScore();
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
							mScore.AddScore(TotalScore, knMKill);
						//AddScore(TotalScore, knMKill);
						}
					}
				}
				IntersectStruct isOut;
				isOut= OutsideBoxes(MBoxTemp,mRender.GetGameScreen());
				if ((isOut.mLeft == 1) || (isOut.mRight == 1) || (isOut.mBottom == 1) ||
					(isOut.mTop == 1))
				{
					misIter->SetStatus(knMissileDead);
				} 
				else
				{
					float yInter;
					bool hitTerrain= false;
					// Check if Missle is below terrain
					int numtps= mGameTerrain.GetTPts();
					Point testPt= misIter->GetNoseLoc();
					testPt.x+= temp.x;
					testPt.y+= temp.y;
					vector<Point>::iterator terrIter= mGameTerrain.TerrainPts();
					for (int tps= 0; tps < (numtps-1); tps++)
					{
						if (CalcYIntercept(testPt,terrIter[tps],terrIter[tps+1],&yInter))
						{
							if (testPt.y >= yInter)
							{
								// intercept is below or equal to line - boom!
								misIter->SetStatus(knMissileExplode);
								hitTerrain= true;
								break;
							}
						}
					}
					if (!hitTerrain)
					{
						misIter->SetLocation(temp);
					}
				}
			}
		}
		else if (tStatus == knMissileExplode)
		{
			Point explPt= misIter->GetLocation();
			Point nosePt= misIter->GetNoseLoc();
			explPt.x+= nosePt.x;
			explPt.y+= nosePt.y;
			misIter->SetStatus(knMissileDead);
			SpawnExplosion(explPt);
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
						//AddScore(TotalScore, knBKill);
						mScore.AddScore(TotalScore, knBKill);
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
				LanderLanded();
				cout << mNumLndrsLanded << " lander(s) have landed" << endl;
			}
			else
			{
				LanderTemp= MoveEntity( landIter->GetLoc(),landIter->GetDir(), landIter->GetSpeed(), elapsedTime);
				landIter->SetLocation(LanderTemp.x,LanderTemp.y);
                // EJR Lander watcher
 //               cout << "Lander x,y: " << LanderTemp.x << " " << LanderTemp.y << endl;
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
						mScore.AddScore(TotalScore, knFKill);
						//AddScore(TotalScore, knFKill);
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
	//update all values
	// Lander
    //Lander::sSetDescentRate( mCurrentLevel.GetLndrDescRate( ) );

    //// Missile
    //Missile::sSetSpeed( mCurrentLevel.GetMissileSpd( ) );

    //// Gunship
    //mPlayerShip.SetPad( mCurrentLevel.GetGunStartPad( ) );
    //mPlayerShip.SetReloadTime( mCurrentLevel.GetGunReload( ) );
    //mPlayerShip.SetBombReloadTime( mCurrentLevel.GetBombReloadTime( ) );

    //// Explosion
    ///*Explosion::sSetMaxRadius( mCurrentLevel.GetExpRad( ) );
    //Explosion::sSetExpansionRate( mCurrentLevel.GetExplRate( ) );*/

    //// Bomb
    //Bomb::sSetSpeed( mCurrentLevel.GetBombMxSpd( ) );
    //Bomb::sSetAcceleration( mCurrentLevel.GetBombAcc( ) );
    //Bomb::sSetRadius( mCurrentLevel.GetBombRad( ) );
	//CheckPause();

    // Splash
    if ( mGameMode == knIntroMode ||
         mGameMode == knLevTransMode ||
         mGameMode == knEndMode )
    {
        bool levelExist;
        if ( mRender.GetSplashFade( ) == knFadeIn )
        {
            mRender.StepSplashAlpha(1);
        }
        else if ( mRender.GetSplashFade( ) == knFadeOut )
        {
            mRender.StepSplashAlpha(-1);
        }
        else if ( mRender.GetSplashFade( ) == knFadeDone
                  &&
                  mGameMode == knIntroMode )
        {
            for ( lvlCtr = 1; lvlCtr <= 50; lvlCtr++ )
            {
			    levelExist = mCurrentLevel.LoadLevel(GetLevName(lvlCtr));
                if(levelExist)
                {
                    break;
                }
            }
            mGameMode = knMenuMode;
            mRender.SetSplashFade(knFadeIn);
            StopRender( );
        }
        else if ( mRender.GetSplashFade( ) == knFadeDone
                  &&
                  mGameMode == knEndMode )
        {
            for ( lvlCtr = 1; lvlCtr <= 50; lvlCtr++ )
            {
			    levelExist = mCurrentLevel.LoadLevel(GetLevName(lvlCtr));
                if(levelExist)
                {
                    break;
                }
            }
            mGameMode = knMenuMode;
         // mCurrentLevel.ClearLevel( );
            InitLevel( );
			mScore.ClearScore();
            mRender.SetSplashFade(knFadeIn);
            StopRender( );
        }
        else if ( mRender.GetSplashFade( ) == knFadeDone
                  &&
                  mGameMode == knLevTransMode )
        {
            bool search1_50 = false;
            do
            {
                levelExist = mCurrentLevel.LoadLevel(GetLevName(++lvlCtr));
                if(levelExist)
                {
                    break;
                }
                if ( lvlCtr >= 50 )
                {
                    if ( search1_50 == true )
                    {
                        break;
                    }
                    else
                    {
                        lvlCtr = 0;
                        search1_50 = true;
                        continue;
                    }
                }
            } while ( lvlCtr <= 50 );
            mGameMode = knPlayMode;
            InitLevel( );
            mRender.SetSplashFade(knFadeIn);
            StopRender( );
        }

    }

	//update gunship location
	
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
	float offX = sqrt (256/((M * M) + 1));
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

void GameWorld::LanderLanded ()
{
	mNumLndrsLanded++;
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


void GameWorld::AddEditPadPoint(Point p)
{
	//Identify the last point in the vector
	vector<Point> *ptrTer;
	ptrTer=	mEditLevel.GetTerPt();
	if (ptrTer->size() > 0)
	{
		vector<Point>::reference end= ptrTer->back();
		//retriev the Y axis
		p.y = ptrTer->back().y;
		//add 22 to the x axis
		p.x = ptrTer->back().x+30;


		//insert that point when right mouse is clicked
		mEditLevel.AddPoint(p);
	}
	
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
	mNumLndrsToGo = mNumLndrLvl;
	mNumLndrsLanded = 0;
    mNumLndrScr = mCurrentLevel.GetNumLndrScr( );
    mLndrPersist = mCurrentLevel.GetLndrPersist( );
    mNumMissile = mCurrentLevel.GetNumMissile( );
    mGunMoves = mCurrentLevel.GetGunMoves( );
    mGunMoveRnd = mCurrentLevel.GetGunMoveRnd( );
    mEndGamePadOcc = mCurrentLevel.GetEndGamePadOcc( );
    mFrat = mCurrentLevel.GetFrat( );
    mLanders.clear( );
    mMissiles.clear( );
    mBombs.clear( );
    mExplosions.clear( );

    // Terrain
    mGameTerrain.SetNumPadPts( mCurrentLevel.GetNumPad( ) );
    mGameTerrain.InitPadPoints( mCurrentLevel.GetPadpt( ) );
    mGameTerrain.SetNumTPts( mCurrentLevel.GetNumTerPt( ) );
    mGameTerrain.InitTerrain( mCurrentLevel.GetTerPt( ) );

    // Lander
    Lander::sSetDescentRate( mCurrentLevel.GetLndrDescRate( ) );
    Lander::sResetLanderCount( );

    // Missile
    Missile::sSetSpeed( mCurrentLevel.GetMissileSpd( ) );

    // Gunship
    mPlayerShip.SetPad( mCurrentLevel.GetGunStartPad( ) );
    mPlayerShip.SetReloadTime( mCurrentLevel.GetGunReload( ) );
    mPlayerShip.SetBombReloadTime( mCurrentLevel.GetBombReloadTime( ) );
    mPlayerShip.ResetShots( );
	vector<Point>::iterator fP= mGameTerrain.PadPts();
	mPlayerShip.InitGunship(fP[mCurrentLevel.GetGunStartPad()]);

    // Explosion
    Explosion::sSetMaxRadius( mCurrentLevel.GetExpRad( ) );
    Explosion::sSetExpansionRate( mCurrentLevel.GetExplRate( ) );

    // Bomb
    mNumBomb = mCurrentLevel.GetNumBomb( );
    Bomb::sSetSpeed( mCurrentLevel.GetBombMxSpd( ) );
    Bomb::sSetAcceleration( mCurrentLevel.GetBombAcc( ) );
    Bomb::sSetRadius( mCurrentLevel.GetBombRad( ) );

    // GameWorld
    ResetTimers( );


}

void GameWorld::ResetTimers( )
{
    mPlayerShip.ResetTimers( );
    mGameStepper.Mark( );
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


	mCurrentLevel.Clone(&mEditLevel);

}

vector<Lander>* GameWorld::GetLanders( )
{
    return &mLanders;
}

USINT GameWorld::GetNumLndrScr( )
{
    return mNumLndrScr;
}

int GameWorld::PointCheck()
{
	//for (int tp = 1; tp < (numPts); tp++)
	return 0;
}

void GameWorld::CheckSpawnLander()
{
	if (mNumLndrsToGo > 0)
	{
		vector<Lander>::iterator iterLander;
		int curLanders = 0;
		for (iterLander = mLanders.begin() ; iterLander != mLanders.end() ; iterLander++)
		{
			if (iterLander->GetStatus() == knLanderDescending)
			{
				curLanders++;
			}
		}

		if ( ( curLanders < mNumLndrScr) )
		{

			vector<Point>::iterator pad0;
			bool doSpawn = true;
			pad0= mGameTerrain.PadPts();
			Point sPoint,tPoint;
			int spawnLoc = rand()%mGameTerrain.GetNumPadPts();
			sPoint.x= pad0[spawnLoc].x;
			sPoint.y= kLanderStartY;
			tPoint.x= pad0[spawnLoc].x;
			tPoint.y= pad0[spawnLoc].y;
			
			if(spawnLoc == mPlayerShip.GetPad( ))// gunship location
			{
				doSpawn = false;
			}
			else
			{
				for (iterLander = mLanders.begin(); iterLander != mLanders.end(); iterLander++)
				{
					if ((iterLander->GetStatus() == knLanderDescending || iterLander->GetStatus() == knLanderLanded)
						&& iterLander->GetLoc().x == tPoint.x)
					{
						doSpawn = false;
					}
				}
			}

			if (doSpawn == true)
			{
				tWorld->SpawnLander(sPoint, tPoint);
			}

		}
	}
}

void GameWorld::CheckWinLose( )
{
    if ( mNumLndrsLanded >= mEndGamePadOcc )
    {
        mGameMode = knEndMode;
    }
    else if ( Lander::sGetLanderCount( ) >= mNumLndrLvl )
    {
        mGameMode = knLevTransMode;
    }
}

string GameWorld::GetLevName(int num)
{
	string name;
	stringstream out;
	out << num;
	name = out.str();
	return ("LEVEL" + name + ".txt");
}

Level* GameWorld::GetEditLevel()
{
	return &mEditLevel;
}

Level* GameWorld::GetCurrentLevel()
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
		mCurrentLevel.SetNumMissile((int)value);
		break;
	case 2 :
		mCurrentLevel.SetNumBomb((int)value);
		break;
		break;
	case 3 :
		mCurrentLevel.SetGunReload(value);
		break;
	case 4 : 	
		mCurrentLevel.SetNumLndrLvl((int)value);
		break;
	case 5 :
		mCurrentLevel.SetNumLndrScr((int)value); 
		break;
	case 6 :
		mCurrentLevel.SetLndrPersist((bool)value);
		break;
	case 7 : 
		mCurrentLevel.SetLndrDescRate(value);
		break;
	case 8 :
		mCurrentLevel.SetMissileSpd(value);
		break;
	case 9 :
		tWorld->SetGunPad((USINT)value);
		break;
	case 10 :
		mCurrentLevel.SetBombReloadTime(value);
		break;
	case 11 :
		mCurrentLevel.SetBombAcc(value);
		break;
	case 12 :
		mCurrentLevel.SetBombMxSpd(value);
		break;
	case 13 :
		mCurrentLevel.SetBombRad(value);
		break;
	case 14 :
		mCurrentLevel.SetExpRad(value);
		break;
	case 15 :
		mCurrentLevel.SetExpRate(value);
		break;
	case 90 :
		tWorld->GetCurrentLevel()->SaveLevel(tWorld->GetLevName((int)value));
		*tWorld->GetLvlCtr() = (USINT)value;
		break;
	case 91 :
		tWorld->GetCurrentLevel()->LoadLevel(tWorld->GetLevName((int)value));
		*tWorld->GetLvlCtr() = (USINT)value;
		break;
	case 92 :
		//restart - by default all the cases restart the level
		break;
	case 93 :
		tWorld->GetRender()->SetGameState(false);
		break;
	//case 100 :
	//	tWorld->SpawnBomb();
	//	break;
	//case 101 :
	//	tWorld->SpawnMissile();
	//	break;
	//case 102 :
	//	tWorld->SpawnLander();
	//	break;
	}
	if(command != 0)
	{
		tWorld->InitEverything();
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


//int GameWorld::GetScore()
//{
//	return TotalScore;
//}

Gunship* GameWorld::GetGunship()
{
	return &mPlayerShip;
}
void GameWorld::CheckPause()
{
	while(*mRender.IsPause())
	{
		mRender.doMenuInput();
		ResetTimers();
	}
}

void GameWorld::StartRender( )
{
    mRender.Start( );
}

void GameWorld::StopRender( )
{
    mRender.Stop( );
}

USINT* GameWorld::GetLvlCtr( )
{
	return &lvlCtr;
}

void GameWorld::SetGunPad(USINT num)
{
	if(num > GetCurrentLevel()->GetPadpt()->size()-1)
	{
		cout << "Non existant pad point - using default '0' " << endl;
		mCurrentLevel.SetGunStartPad(0);
	}
	else
	{
		mCurrentLevel.SetGunStartPad(num);
	}
}
Score* GameWorld::GetScore()
{
	return &mScore;
}

void GameWorld::InitStars()
{
	srand(1532);
	for(int j=0; j<125; j++)
	{
		Point temp;
		temp.x = rand() % (kWinWidth-1);
		temp.y = rand() % (kWinHeight-1);
		mStars[j] = temp;
	}
}