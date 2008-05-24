// Render.h

#ifndef _RENDER_H
#define _RENDER_H

#include "Structs.h"
#include "SDL.h"
#include "SDL_GFXprimitives.h"
#include "SDL_ttf.h"

class Render
{
private:
    Point mMissileDrawPts[7];
    Point mLanderDrawPts[5];
    Point mCrosshairDrawPts[5];
	SDL_Surface* screen;
	SDL_Event mEvent;
	playInput plIn;				//player input
	bool gameState;
    short int mSplashAlpha;
	BBox mBBoxLander;

public:
    Render( );
    ~Render( );
    void DrawGunship( SDL_Surface* scrn,
                      Point* gunLoc );
    void DrawMissile( SDL_Surface* scrn,
                      Point* loc,
                      Point* targ );
    void DrawLander( SDL_Surface* scrn,
                     Point* landerLoc );
    void DrawTerrain( SDL_Surface* scrn,
                      Point* tPts,
                      int numTP,
					  BBox* boxes);
    void DrawCrosshair( SDL_Surface* scrn,
                         Point* loc,
                         int r,
                         int g,
                         int b );
    void DrawExplosion( SDL_Surface* scrn,
                         Point loc,
                         float frameIDX,
                         float radius,
                         SDL_Color colorOuter,
                         SDL_Color colorInner);
	SDL_Surface* getpScreen();			//gets a pointer to the surface (screen)
	void doInput();						//gets, processes input
	void doEditInput();					//gets, processes editor input
	bool gameRunning();					//gets current gamestate
	Point getMouse();					//gets cursor position
	bool isLClicked();					//check whether mouse is clicked
	bool isRClicked();
	bool isLeftHeld();
	bool isRightHeld();
    short int GetSplashAlpha( );
    void DecSplashAlpha( short int amt );
    void DrawSplash( );
    void DrawBox( Point loc,
                  BBox box );
	void DrawBox(BBox box);
	BBox GetLanderBox();
};

#endif // _RENDER_H;
