#include "Constants.h"
#include "Structs.h"
#include "Missile.h"
#include <cmath>
using namespace std;

float Missile::sSpeed = kMissileStartSpeed;

//Constructor FIRST (easier for me)
Missile::Missile()
{
	//Initilize all member variables
	int mDrawBankIDX = 0;
	float mSpeed = sSpeed;
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
	mSpeed = sSpeed;
	mStatus = knMissileFlying;
    Point pts[5];
    pts[0].x =  -4.0F;
    pts[1].x =  -2.0F;
    pts[2].x =   0.0F;
    pts[3].x =   2.0F;
    pts[4].x =   4.0F;
    pts[0].y =   0.0F;
    pts[1].y = -12.0F;
    pts[2].y = -17.0F;
    pts[3].y = -12.0F;
    pts[4].y =   0.0F;
    float locToTarg = atan2( mDirection.y,
                             mDirection.x );
    float rotAngle = locToTarg - kPi/2;
    for ( int i = 0; i < 5; i++ )
    {
        float dist = sqrt( pts[i].x * pts[i].x + pts[i].y * pts[i].y ); // distance from point to origin
        float pntToOrg = rotAngle - atan2( pts[i].y,
                                           pts[i].x );
        pts[i].x = dist * cos( pntToOrg );
        pts[i].y = dist * sin( pntToOrg );
    }
    float minX = pts[0].x;
    float minY = pts[0].y;
    for ( int i = 1; i < 5; i++ )
    {
        if ( pts[i].x < minX)
        {
            minX = pts[i].x;
        }
        if ( pts[i].y < minY)
        {
            minY = pts[i].y;
        }
    }
    float maxX = pts[0].x;
    float maxY = pts[0].y;
    for ( int i = 1; i < 5; i++ )
    {
        if ( pts[i].x > maxX)
        {
            maxX = pts[i].x;
        }
        if ( pts[i].y > maxY)
        {
            maxY = pts[i].y;
        }
    }
    mBox.x = minX;
    mBox.y = minY;
    mBox.w = maxX - minX;
    mBox.h = maxY - minY;
}
//Deconstructor Last (easier for me)
Missile::~Missile()
{
	//any new operators must have delete matches here
}

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
	float mSpeed = sSpeed;
}

BBox Missile::GetBox( )
{
    return mBox;
}

void Missile::sSetSpeed(float speed)
{
    sSpeed = speed;
}

float Missile::sGetSpeed( )
{
    return sSpeed;
}