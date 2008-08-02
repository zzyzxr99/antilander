#include "Constants.h"
#include "Structs.h"
#include "Bomb.h"
#include <cmath>
#include <iostream>
using namespace std;

float Bomb::sMaxSpeed = kBombMaxSpeed;
float Bomb::sAcceleration = kGravity*kGravity;
float Bomb::sRadius = kBombRadius;

Bomb::Bomb()
{
	//Initilize all member variables
	float mSpeed = sMaxSpeed;
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
    mAcceleration.y= sAcceleration*sAcceleration;
	mDrawLoc.x = StartLoc.x;
	mDrawLoc.y = StartLoc.y;

	mStatus = knBombFlying;
   
    mBox.x = -Bomb::sRadius;
    mBox.y = -Bomb::sRadius;
    mBox.w = Bomb::sRadius;
    mBox.h = Bomb::sRadius;
    cout << "Add bomb";

}
Bomb::~Bomb()
{
	//any new operators must have delete matches here
    cout << "Delete bomb";
}

BBox Bomb::GetBox( )
{
    return mBox;
}

void Bomb::sSetSpeed(float speed)
{
    sMaxSpeed = speed;
}

float Bomb::sGetSpeed( )
{
    return sMaxSpeed;
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
