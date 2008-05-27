#include "Structs.h"
#include "Constants.h"
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

float Vect::Mag()
{
    return x*x + y*y;
}

Vect MakeVect(Point p1, Point p2)
{
    Vect retV;
    retV.x= p2.x - p1.x;
    retV.y= p2.y - p1.y;
    return retV;
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

IntersectStruct::IntersectStruct()
{
    mLeft= 0;
    mTop= 0;
    mRight= 0;
    mBottom= 0;

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
	//Point calcStart, calcEnd;
	//calcEnd.x= direction.x;
	//calcEnd.y= direction.y;

	//direction= UnitVect(calcStart,calcEnd);
	direction.x= direction.x*speed*timeelapsed;
	direction.y= direction.y*speed*timeelapsed;

	retPoint.x= start.x + direction.x;
	retPoint.y= start.y + direction.y;

	return retPoint;
}

Point MoveEntityAccel(Point start,Vect vel,Vect acc,float timeelapsed)
{
	Point retPoint;
	Point calcStart, calcEnd;
	//calcEnd.x= direction.x;
	//calcEnd.y= direction.y;

	//direction= UnitVect(calcStart,calcEnd);
	vel.x= (vel.x + .5F*acc.x*timeelapsed)*timeelapsed;
	vel.y= (vel.y +  .5F*acc.y*timeelapsed)*timeelapsed;

	retPoint.x= start.x + vel.x;
	retPoint.y= start.y + vel.y;

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

// Returns information about two bound boxes that do not intersect
// if retIntersect members are all zero than there is intersect - logically OPPOSITE of IntersectBoxes
IntersectStruct OutsideBoxes(BBox b1, BBox b2)
{
    IntersectStruct retIntersect;
	if (b1.x > (b2.x + b2.w))
	{
		retIntersect.mRight= 1;
	}
	if ((b1.x + b1.w) < b2.x)
	{
		retIntersect.mLeft= 1;
	}
	if (b1.y > (b2.y + b2.h))
	{
		retIntersect.mBottom= 1;
	}
	else if ((b1.y + b1.h) < b2.y)
	{
		retIntersect.mTop= 1;
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

// EJR calucate the Y intercept *yinter for Point p on the line made by lp1 and lp2

bool CalcYIntercept(Point p, Point lp1, Point lp2, float *yinter)
{
    bool isYinter= true;
    // Point x value is left of pts or right of points - out of segment 
    if (((p.x < lp1.x) && (p.x < lp2.x)) || ((p.x > lp1.x) && (p.x > lp2.x)))
    {
        isYinter= false;
    }
    else
    {
        float ldiffx= lp2.x-lp1.x;
        if (fabsf(ldiffx) < kSlopeRunTolerance)
        {
            // there is no Y intercept line is vertical   return false;
            isYinter= false;
        }
        else
        {
            float ldiffy= lp2.y-lp1.y;
            // y = Mx + b
            // M is rise/run which is diffy/diffx
            // Find b which is x=0 intercept for slope M line with point lp1
            // b = y - Mx - plug in lp1.x and lp1.y for x and y
            float slope = ldiffy/ldiffx;
            float xInter= lp1.y - slope*lp1.x;
            // now we have M and b - plug in x value of Point p and we get the y value on the line where for the x.
            // y= Mx + b - use Point p x
            // *yinter= slope*p.x + xInter
            *yinter= slope*p.x + xInter;
        }
    }
    return isYinter;
}

