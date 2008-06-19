#ifndef _STRUCTS_H
#define _STRUCTS_H
#include "SDL.h"
#include <cmath>
#include <string>

using namespace std;

struct Vect
{
	float x;
	float y;
	Vect();
	~Vect();
    float Mag();
};

struct Point
{
	float x;
	float y;
	Point();
	~Point();
	float Distance(Point p2);
};

Vect UnitVect(Point pStart, Point pEnd);
Vect MagVect(Vect v,float m);
Vect MakeVect(Point p1, Point p2);

Point MoveEntity(Point start,Vect direction,float speed,float timeelapsed);
Point MoveEntityAccel(Point start,Vect vel,Vect acc,float timeelapsed);

float Angle( Point pStart,
             Point pEnd );

float Angle( Vect v );

// For input of player
struct playInput
{
	Point mouseMove;
	bool leftClick;				//if set to true - left mouse button has been clicked
	bool rightClick;			//if set to true - right mouse button has been clicked
	bool midClick;				//if set to true - middle mouse button has been clicked
	bool tlclicked;				//temp click variable
	bool trclicked;             //temp click variable
	bool tmclicked;
	char keyP;
	string conString;
	string luaString;
	char conCur;
	char current;
	SDLKey keyPress;
	SDL_MouseButtonEvent mousePress;
	playInput();
	~playInput();
};


struct IntersectStruct
{
    unsigned int mLeft:1;
    unsigned int mTop:1;
    unsigned int mRight:1;
    unsigned int mBottom:1;
    IntersectStruct();
};

struct BBox
{
	float x,y,w,h;
};

bool IntersectBoxes(BBox b1, BBox b2);
IntersectStruct OutsideBoxes(BBox b1, BBox b2);
bool IntersectSegments(Point p1,Point p2,Point p3,Point p4,Point *ip);
bool CalcYIntercept(Point p, Point lp1, Point lp2, float *yinter);

#endif // _STRUCTS_H

