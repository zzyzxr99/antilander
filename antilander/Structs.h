#ifndef _STRUCTS_H
#define _STRUCTS_H
#include "SDL.h"
#include <cmath>

struct Vect
{
	float x;
	float y;
	Vect();
	~Vect();
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
Point MoveEntity(Point start,Vect direction,float speed,float timeelapsed);

float Angle( Point pStart,
             Point pEnd );

float Angle( Vect v );


// For input of player
struct playInput
{
	Point mouseMove;
	bool leftClick;				//if set to true - left mouse button has been clicked
	bool rightClick;			//if set to true - right mouse button has been clicked
	bool tlclicked;				//temp click variable
	bool trclicked;             //temp click variable
	SDLKey keyPress;
	SDL_MouseButtonEvent mousePress;
	playInput();
	~playInput();
};

struct BBox
{
	float x,y,w,h;
};

bool IntersectBoxes(BBox b1, BBox b2);
bool IntersectSegments(Point p1,Point p2,Point p3,Point p4);

#endif // _STRUCTS_H

