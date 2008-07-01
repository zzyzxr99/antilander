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
    mBombTimer.Mark( );
    m1stMissile = true;
    m1stBomb = true;
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
    if ( m1stMissile )
    {
        m1stMissile = false;
        mGunTimer.Mark( );
        return true;
    }
	return mGunTimer.CheckElapsedMS((unsigned long)(mReloadTime * 1000));
}

bool Gunship::CanBomb( )
{
    if ( m1stBomb )
    {
        m1stBomb = false;
        mBombTimer.Mark( );
        return true;
    }
    return mBombTimer.CheckElapsedMS((unsigned long)(mBombReloadTime * 1000));
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

float Gunship::GetBombReloadTime( )
{
    return mBombReloadTime;
}

void Gunship::SetBombReloadTime( float t )
{
    mBombReloadTime = t;
}

void Gunship::SetPad( USINT pad )
{
    mPad = pad;
}

USINT Gunship::GetPad( )
{
    return mPad;
}

void Gunship::ResetTimers( )
{
    mGunTimer.Mark( );
    mBombTimer.Mark( );
}

void Gunship::ResetShots( )
{
    m1stMissile = true;
    m1stBomb = true;
}