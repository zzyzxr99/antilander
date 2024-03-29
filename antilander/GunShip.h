#ifndef _GUNSHIP_H
#define _GUNSHIP_H

#include "Constants.h"
#include "Structs.h"
#include "ALTimer.h"

class Gunship
{
private:
	Point mDrawLoc;	//uses GetLoc to place gunship
	int mDrawBarrelIDX;  //barrell graphic??
	int mDrawGunshipIDX;  //!!gunship graphic, this is new!!
	GunshipStatusType mStatus;
	float mGunangle;  //uses GetGunangle to change turret elevation
	long mLastTimeShot;  //uses GetLastShot to ID shot interval (should count down)
	int mMissileCount;  //uses GetMCount to get missiles remaining
    float mReloadTime;
    float mBombReloadTime;
    USINT mPad;
    ALTimer mGunTimer;
    ALTimer mBombTimer;
    bool m1stMissile;
    bool m1stBomb;

public:
	Gunship();
	~Gunship();
	Point* GetLoc();  //gets location of gunship
	int GetDrawBarrelIDX();//??? is the barrel drawn separate?
	int GetDrawGunshipIDX();  //!!gets the graphic for gunship, this is new!!
	GunshipStatusType GetStatus();  //gets the status of the gunship
	float GetGunangle();  //gets the turret elevation
	long GetLastShot();  //gets the time of last shot
	int GetMCount();  //gets missile count of missiles remaining
	void InitGunship(Point P);
    void SetReloadTime( float t );
    float GetReloadTime( );
    float GetBombReloadTime( );
    void SetBombReloadTime( float t );
	bool CanShoot();
    bool CanBomb( );
    void SetPad( USINT pad );
    USINT GetPad( );
    void ResetTimers( );
    void ResetShots( );
};

#endif