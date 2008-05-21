#ifndef _VECT_H
#define _VECT_H
#include "SDL.h"
#include <cmath>

struct Vect
{
	float x;
	float y;
	Vect();
	~Vect();
};



#endif // _VECT_H

#ifndef _POINT_H
#define _POINT_H

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



#endif // _POINT_H

