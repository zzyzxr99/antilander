
#include "GameWorld.h"
#include "Functions.h"
#include <iostream>
#include "math.h"
using namespace std;
// Definition

GameWorld::GameWorld()
{
	// initialize all the member varibles
	mStarted= false;
	mLastElapsedTime= 0.0F;
	InitEverything();
	mLastTimeStamp= mGameStepper.CurrentTimeMS();
}

GameWorld::~GameWorld()
{
	// any new operators must have delete matches here
	mLanders.capacity();
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
	Point *pad0;
	pad0= mGameTerrain.PadPts();
	Point sPoint;
	sPoint.x= pad0->x;
	sPoint.y= kLanderStartY;
	PtrLander= new Lander(sPoint, *pad0, descending, kBaseDescendRate);
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
    newExpl= new Explosion(sLoc,
                           kExplosionMaxRadiusDefault,
                           kExplosionExpandRateDefault,
                           kExplosionInnerColorDefault,
                           kExplosionOuterColorDefault);
    mExplosions.push_back(*newExpl);
}

void GameWorld::InitEverything()
{
	//Init all Entities
	mGameTerrain.InitTerrain();
	mGameTerrain.InitPadPoints();
	/*InitMissiles();*/
	//InitLanders();
	SpawnLander();
	int numpts= mGameTerrain.GetNumPadPts();
	Point *fP= mGameTerrain.PadPts();
	// Did not check num pad pts!
	mPlayerShip.InitGunship(fP[3]);

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

void GameWorld::Timestamp( )
{
    mGameStepper.Mark( );
}

bool GameWorld::CheckTick( )
{
	unsigned long curTime,timePassed;
    curTime= mGameStepper.CurrentTimeMS();
	timePassed= curTime - mLastTimeStamp;
	if (timePassed >= kGameStep)
	{
		mLastElapsedTime= (float)(timePassed)/1000.0F;
		mLastTimeStamp= curTime;
		return true;
	}
	return false;
}

void GameWorld::UpdateEverything( )
{

	//move all the missiles
	vector<Missile>::iterator misIter;
	for ( misIter = mMissiles.begin( ); misIter != mMissiles.end( ); misIter++ )
	{
		if (misIter->GetStatus( ) == flight)
		{
			if ( misIter->GetLocation( ).Distance(misIter->GetDestination( ) ) < 2 )
			{
				misIter->SetStatus(gone);
                SpawnExplosion( misIter->GetLocation( ) );
			}
			else
			{
				Point temp = MoveEntity(misIter->GetLocation(),misIter->GetDirection(),misIter->GetSpeed(),mLastElapsedTime);
				BBox MBoxTemp= misIter->GetBox();
				MBoxTemp.x+= temp.x;
				MBoxTemp.y+= temp.y;

				Point LanderTemp;
				vector<Lander>::iterator landIter;
				for ( landIter = mLanders.begin( ); landIter != mLanders.end( ); landIter++ )
				{
					if ( landIter->GetStatus( ) == descending )
					{
						LanderTemp= landIter->GetLoc();
						BBox LBoxTemp= mRender.GetLanderBox();
						LBoxTemp.x+= LanderTemp.x;
						LBoxTemp.y+= LanderTemp.y;

						if (IntersectBoxes(MBoxTemp, LBoxTemp))
						{
							landIter->SetStatus(dead);
							misIter->SetStatus(gone);
							SpawnExplosion( landIter->GetLoc( ) );
							SpawnExplosion( misIter->GetLocation( ) );
						}
					}

				}	
				misIter->SetLocation(temp);
				Point newtemp;
				misIter->GetDirection();
				if(this->MissileSect(mGameTerrain.TerrainPts(),misIter->GetLocation(),misIter->GetDirection()))
				{
					misIter->SetStatus(gone);	
				}
			}
		}
	}

    for ( misIter = mMissiles.begin( ); misIter != mMissiles.end( ); misIter++ )
	{
		if (misIter->GetStatus() == gone)
		{
            mMissiles.erase( misIter );
            break;
		}
	}


	Point LanderTemp;
    vector<Lander>::iterator landIter;
    for ( landIter = mLanders.begin( ); landIter != mLanders.end( ); landIter++ )
    {
		if ( landIter->GetStatus( ) == descending )
		{
			if(landIter->GetLoc().Distance(landIter->GetDest()) < 2 )
			{
				landIter->SetLocation(landIter->GetDest().x,landIter->GetDest().y);
				landIter->SetStatus( landed );
			}
			else
			{
				LanderTemp= MoveEntity( landIter->GetLoc(),landIter->GetDir(), landIter->GetSpeed(), mLastElapsedTime);
				landIter->SetLocation(LanderTemp.x,LanderTemp.y);
			}
		}

    }
    for ( landIter = mLanders.begin( ); landIter != mLanders.end( ); landIter++ )
	{
		if (landIter->GetStatus() == dead)
		{
            mLanders.erase( landIter );
            break;
		}
	}

    vector<Explosion>::iterator iterExpl;
    for (iterExpl= mExplosions.begin(); iterExpl != mExplosions.end(); iterExpl++)
    {
        if (iterExpl->GetStatus() == knExplosionOccuring)
        {
            ExplosionStatusType tStat;
            tStat= iterExpl->Update(mLastElapsedTime);
            iterExpl->SetStatus(tStat);
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
		return true;
	}
	return false;
}

// EJR only for testing explosion at right click mouse loc
bool GameWorld::TestFireExplosion()
{
	return mRender.isRClicked();
}

bool GameWorld::SplashRunning( )
{
    if ( mRender.GetSplashAlpha( ) > 0 )
    {
        return true;
    }
    return false;
}

bool GameWorld::MissileSect(Point* TerArr, Point MissNose, Vect Direction)
{
	float M = Direction.y/Direction.x;		//slope
	float offX = sqrt (289/((M * M) + 1));
	float offY = M*offX;
	
	MissNose.x += offX;
	MissNose.y -+ offY;
	int ctr = 0; 
	int rndMiss = (int)(MissNose.x);
	Point iter;
	while(MissNose.x <= TerArr[ctr].x || MissNose.x > TerArr[ctr+1].x)
	{
		ctr++;
	}
	
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
	
	float slope = diffY/diffX;
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