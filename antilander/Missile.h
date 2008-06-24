#ifndef _MISSILE_H
#define _MISSILE_H

#include "Structs.h"

class Missile
{
private:
	MissileStatusType mStatus;
	Point mDrawLoc; //uses GetLocation to point out the missile's place
	Point mDestination; //X and Y cord for where the missile was told to go by clicking the mouse
	Point mNose;
	float mSpeed; //uses GetSpeed to change its firing speed
	Vect mDirection; //Uses Vect GetDirection to find its direction
	int mDrawBankIDX; //Graphic for the missile
    BBox mBox;

    //static member variables
    static float sSpeed;

public:
	Missile();
	Missile ( Point StartLoc, Point Dest, Vect InitDir);
	Missile ( Point loc,Point targ );
	~Missile();
	//Public functions to get Private Functions
	float GetSpeed(); //can get the missle's speed
	Vect GetDirection(); //Gets the Direction
	Point GetLocation(); //Gets the Draw Loc
	int GetBankIDX(); //Gets DrawBankIDX
	Point GetDestination(); //Gets the Destination
	void SetLocation(Point p);
    void SetTarget( Point targ );
    Point GetTarget( );
	MissileStatusType GetStatus();
	void SetStatus(MissileStatusType stat);
    BBox GetBox( );
	Point GetNoseLoc();
    //static member functions
    static void sSetSpeed( float speed );
    static float sGetSpeed( );
};

#endif 