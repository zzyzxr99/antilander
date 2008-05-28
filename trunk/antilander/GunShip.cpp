#include "GunShip.h"

// Definition

Gunship::Gunship()
{
	mDrawLoc.x= 0;
	mDrawLoc.y= 0;
	mStatus= ready; 
	mGunangle= kPi / 2;
	mLastTimeShot= 0;  
	mMissileCount= kStartAmmo;
    mReloadTime = kReloadTime;
    mPad = kDefaultGunStartPad;
    mGunTimer.Mark();
// initialize all the member variables
}

Gunship::~Gunship()
{
	// any new operators must have delete matches here
}

int Gunship::GetDrawGunshipIDX()
{
	return mDrawGunshipIDX;
}

bool Gunship::CanShoot()
{
	return mGunTimer.CheckElapsedMS(kReloadTime * 1000);
}

int Gunship::GetDrawBarrelIDX()
{
	return mDrawBarrelIDX;
}

void Gunship::InitGunship(Point P)
{
	mDrawLoc.x = P.x;
	mDrawLoc.y = P.y;
}

Point* Gunship::GetLoc( )
{
    return &mDrawLoc;
}

void Gunship::SetReloadTime( float t )
{
    mReloadTime = t;
}

float Gunship::GetReloadTime( )
{
    return mReloadTime;
}

void Gunship::SetPad( unsigned short pad )
{
    mPad = pad;
}

unsigned short Gunship::GetPad( )
{
    return mPad;
}