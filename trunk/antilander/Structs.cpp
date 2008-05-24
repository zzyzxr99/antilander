#include "Structs.h"
#include <cmath>
using namespace std;

Point::Point()
{
	x = 0;
	y = 0;
}

Point::~Point()
{
	// any allocations with new must have matching delete here
}

float Point::Distance(Point p2)
{
	float retDist;
	float xVal= x - p2.x;
	float yVal= y - p2.y;
	retDist= sqrt(xVal*xVal+yVal*yVal);

	return retDist;
}
Vect::Vect()
{
	x = 0;
	y = 0;
}

Vect::~Vect()
{
	// any allocations with new must have matching delete here
}

playInput::playInput()
{
	mouseMove.x = 0;
	mouseMove.y = 0;
	leftClick = false;	
    rightClick = false;
	midClick = false;
	tlclicked = 0;
	trclicked = 0;
}

playInput::~playInput()
{
	
}

Vect UnitVect(Point pStart, Point pEnd)
{
	float diffx,diffy,mag;
	Vect retVect;

	diffx= (pEnd.x - pStart.x);
	diffy= (pEnd.y - pStart.y);
	mag= sqrt(diffx*diffx + diffy*diffy);
	if (mag != 0.0F)
	{
		retVect.x= diffx/mag;
		retVect.y= diffy/mag;
	}

	return retVect;
}

Vect MagVect(Vect v, float m)
{
	v.x= v.x*m;
	v.y= v.y*m;

	return v;
}

Point MoveEntity(Point start,Vect direction,float speed,float timeelapsed)
{
	Point retPoint;
	Point calcStart, calcEnd;
	calcEnd.x= direction.x;
	calcEnd.y= direction.y;

	direction= UnitVect(calcStart,calcEnd);
	direction.x= direction.x*speed*timeelapsed;
	direction.y= direction.y*speed*timeelapsed;

	retPoint.x= start.x + direction.x;
	retPoint.y= start.y + direction.y;

	return retPoint;
}


float Angle( Point pStart,
             Point pEnd )
{
    float rAngle = atan2( pEnd.y - pStart.y,
                          pEnd.x - pStart.x );
    return rAngle;
}

float Angle( Vect v )
{
    float rAngle = atan2( v.y, v.x );
    return rAngle;
}

bool IntersectBoxes(BBox b1, BBox b2)
{
	bool retIntersect= true;
	if (b1.x > (b2.x + b2.w))
	{
		retIntersect= false;
	}
	else if ((b1.x + b1.w) < b2.x)
	{
		retIntersect= false;
	}
	else if (b1.y > (b2.y + b2.h))
	{
		retIntersect= false;
	}
	else if ((b1.y + b1.h) < b2.y)
	{
		retIntersect= false;
	}

	return retIntersect;
}

// EJR Not tested do not use until rechecked code
bool IntersectSegments(Point p1,Point p2,Point p3,Point p4, Point *ip)
{
	bool retIntersect= false;

	float uA,uB,uAn,uBn,uBot;

	uBot= (p4.y-p3.y)*(p2.x-p1.x) - (p4.x-p3.x)*(p2.y-p1.y);
	uAn= (p4.x-p3.x)*(p1.y-p3.y) - (p4.y-p3.y)*(p1.x-p3.x);
	uBn= (p2.x-p1.x)*(p1.y-p3.y)- (p2.y-p1.y)*(p1.x-p3.x);

	if (uBot == 0.0)
	{
		if ((uAn == 0.0) && (uBn == 0.0))
		{
			// Segments are the same
			retIntersect= true;
		}
	}
	else 
	{
		uA= uAn/uBot;
		uB= uBn/uBot;
		if ((uA >= 0.0) && (uA <= 1.0) && (uB >= 0.0) && (uB <= 1.0))
		{
			// intersect in both segments
			retIntersect= true;
		}
	}
	if (retIntersect)
	{
		(*ip).x= p1.x + (p2.x-p1.x)*uA;
		(*ip).y= p1.y + (p2.y-p1.y)*uA;
	}
	return retIntersect;
}


