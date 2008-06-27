#ifndef _LANDER_H
#define _LANDER_H

#include "Structs.h"
#include "Constants.h"

class Lander
{
private:
	Point mDrawLoc;
	Point mDestination;
	int mDrawBankIDX;
	LanderStatusType mStatus;
	float mDescentRate;
	Vect mDir;

    // static member variables
    static float sDescentRate;
    static unsigned short sLanderCount;

public:
	Lander();
	Lander(Point sPoint, Point Dest, LanderStatusType lStatus, float DescentRate);
	~Lander();
	//int GetStartLocs();
	int GetDrawBankIDX();
	void InitLanders();
	void SetLocation(float x, float y);
    Point GetLoc( );
	Vect GetDir();
	float GetSpeed();
	Point GetDest();
	void SetStatus( LanderStatusType status );
	LanderStatusType GetStatus( );

    // static member functions
    static void sSetDescentRate( float spd );
    static float sGetDescentRate( );
    static void sCountLander( );
    static unsigned short sGetLanderCount( );
    static void sResetLanderCount( );
};

#endif 
