#include "Constants.h"
#include "Structs.h"
#include "Bomb.h"
#include <cmath>
using namespace std;

float Bomb::sSpeed = kBombStartSpeed;
float Bomb::sAcceleration = kGravity;
float Bomb::sRadius = kBombRadius;

//Constructor FIRST (easier for me)
Bomb::Bomb()
{
	//Initilize all member variables
	float mSpeed = sSpeed;
}
Vect Bomb::GetVelocity()
{
	return mVelocity;
}
void Bomb::SetVelocity(Vect vel)
{
    mVelocity= vel;
}
Vect Bomb::GetAcceleration()
{
	return mAcceleration;
}
Point Bomb::GetLocation()
{
	return mDrawLoc;
}
void Bomb::SetLocation(Point p)
{
	mDrawLoc.x = p.x;
	mDrawLoc.y = p.y;
}
BombStatusType Bomb::GetStatus()
{
	return mStatus;
}
void Bomb::SetStatus(BombStatusType stat)
{
	mStatus= stat;
}

Bomb::Bomb(Point StartLoc, Vect InitDir)
{
	mVelocity.x = InitDir.x;
	mVelocity.y = InitDir.y;
    mAcceleration.x= 0;
    mAcceleration.y= kGravity*kGravity;
	mDrawLoc.x = StartLoc.x;
	mDrawLoc.y = StartLoc.y;

	mStatus = knBombFlying;
   
    mBox.x = -Bomb::sRadius;
    mBox.y = -Bomb::sRadius;
    mBox.w = Bomb::sRadius;
    mBox.h = Bomb::sRadius;
}
//Deconstructor Last (easier for me)
Bomb::~Bomb()
{
	//any new operators must have delete matches here
}

BBox Bomb::GetBox( )
{
    return mBox;
}

void Bomb::sSetSpeed(float speed)
{
    sSpeed = speed;
}

float Bomb::sGetSpeed( )
{
    return sSpeed;
}
void Bomb::sSetAcceleration(float accel)
{
    sAcceleration = accel;
}

float Bomb::sGetAcceleration( )
{
    return sAcceleration;
}

float Bomb::sGetRadius()
{
    return sRadius;
}
void Bomb::sSetRadius(float radius)
{
    sRadius= radius;
}
