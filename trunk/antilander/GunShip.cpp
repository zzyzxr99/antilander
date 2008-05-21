#include "GunShip.h"

// Definition

Gunship::Gunship()
{
	mDrawLoc.x= 0;
	mDrawLoc.y= 0;
	mStatus= ready; 
	//mGunangle=?;  how do I represent gun angle?
	mLastTimeShot= 0;  
	mMissileCount= 0;  //kStartAmmo = 1000
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