#include "constants.h"
#include "Missile.h"


//Constructor FIRST (easier for me)
Missile::Missile()
{
	//Initilize all member variables
	int mDrawBankIDX = 0;
	float mSpeed = kMissileStartSpeed;
}
float Missile::GetSpeed()
{
	return mSpeed;
}
Vect Missile::GetDirection()
{
	return mDirection;
}
Point Missile::GetLocation()
{
	return mDrawLoc;
}
int Missile::GetBankIDX()
{
	return mDrawBankIDX;
}
void Missile::SetLocation(Point p)
{
	mDrawLoc.x = p.x;
	mDrawLoc.y = p.y;
}
MissileStatusType Missile::GetStatus()
{
	return mStatus;
}
void Missile::SetStatus(MissileStatusType stat)
{
	mStatus= stat;
}
Point Missile::GetDestination()
{
	return mDestination;
}
Missile::Missile(Point StartLoc, Point Dest, Vect InitDir)
{
	mDestination.x = Dest.x; // Spawned Missile Param = Member Var 
	mDestination.y = Dest.y; // Spawned Missile Param = Member Var
	mDirection.x = InitDir.x;
	mDirection.y = InitDir.y;
	mDrawLoc.x = StartLoc.x;
	mDrawLoc.y = StartLoc.y;
   	mDrawBankIDX = 0; //does nothing
	mSpeed = kMissileStartSpeed;
	mStatus = flight;
}
//Deconstructor Last (easier for me)
Missile::~Missile()
{
	//any new operators must have delete matches here
}

////////////////// Dave's added functions ////////////////////
void Missile::SetTarget( Point targ )
{
    mDestination.x = targ.x;
    mDestination.y = targ.y;
}
Point Missile::GetTarget( )
{
    return mDestination;
}
Missile::Missile ( Point loc,Point targ )
{
    mDrawLoc.x = loc.x;
    mDrawLoc.y = loc.y;
    mDestination.x = targ.x;
    mDestination.y = targ.y;
    int mDrawBankIDX = 0;
	float mSpeed = kMissileStartSpeed;
}
////////////////// Dave's added functions ////////////////////