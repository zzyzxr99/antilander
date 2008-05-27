#include "Lander.h"

// Definition

float Lander::sDescentRate = kBaseDescendRate;

void Lander::SetLocation(float x, float y)
{
	mDrawLoc.x= x;//value;
	mDrawLoc.y= y;//value;
}
Lander::Lander()
{
	//initialize all the member variables
	mDrawLoc.x= 0;
	mDrawLoc.y= 0;
	mDestination.x= 0;
	mDestination.y= 0;
	mStatus= descending;
	mDescentRate= sDescentRate;
	mDir.x= 0;
	mDir.y= 0;
}


Lander::Lander(Point sPoint, Point Dest, LanderStatusType lStatus, float DescentRate)
{
	mDrawLoc.x= sPoint.x;
	mDrawLoc.y= sPoint.y;
	mDestination.x= Dest.x;
	mDestination.y= Dest.y-14;
	mStatus= lStatus;
	mDescentRate= DescentRate;
	mDir= UnitVect(sPoint, Dest);
}

Lander::~Lander()
{
	//any new operators must have delete matches here
}

int Lander::GetDrawBankIDX()
{
	return mDrawBankIDX;
}

Point Lander::GetLoc( )
{
    return mDrawLoc;
}

Vect Lander::GetDir()
{
	return mDir;
}

float Lander::GetSpeed()
{
	return mDescentRate;
}

Point Lander::GetDest()
{
	return mDestination;
}

void Lander::SetStatus( LanderStatusType status )
{
	mStatus = status;
}

LanderStatusType Lander::GetStatus( )
{
	return mStatus;
}

void Lander::sSetDescentRate( float spd )
{
    sDescentRate = spd;
}

float Lander::sGetDescentRate( )\
{
    return sDescentRate;
}