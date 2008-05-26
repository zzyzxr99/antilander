#ifndef _BOMB_H
#define _BOMB_H

#include "Structs.h"

class Bomb
{
private:
	BombStatusType mStatus;
	Point mDrawLoc; //uses GetLocation to point out the Bomb's place
    Vect mAcceleration;
    Vect mVelocity;
	BBox mBox;

    //static member variables
    static float sSpeed;
    static float sAcceleration;
    static float sRadius;

public:
	Bomb();
	Bomb ( Point StartLoc, Vect InitDir);
	~Bomb();
	//Public functions to get Private Functions
	Vect GetVelocity(); //can get the bomb's velocity
    void SetVelocity(Vect vel);
	Vect GetAcceleration(); //Gets the Direction
	Point GetLocation(); //Gets the Draw Loc
	void SetLocation(Point p);
    void SetTarget( Point targ );
    Point GetTarget( );
	BombStatusType GetStatus();
	void SetStatus(BombStatusType stat);
    BBox GetBox( );

    //static member functions
    static void sSetSpeed( float speed );
    static float sGetSpeed( );  
    static void sSetAcceleration( float accel );
    static float sGetAcceleration( );
    static float sGetRadius();
    static void sSetRadius(float radius);
};

#endif // _BOMB_H