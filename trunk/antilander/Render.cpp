// Render.cpp

#include "Constants.h"
#include "Structs.h"
#include "Functions.h"
#include "Render.h"
#include "SDL.h"
#include "SDL_GFXprimitives.h"
#include "SDL_ttf.h"
#include <cmath>
#include <iostream>
using namespace std;

Render::Render( )
{
    mSplashAlpha = 255;
    mMissileDrawPts[0].x =   -4.0F;
    mMissileDrawPts[1].x =    4.0F;
    mMissileDrawPts[2].x =    0.0F;
    mMissileDrawPts[3].x =    0.0F;
    mMissileDrawPts[4].x =   -2.0F;
    mMissileDrawPts[5].x =    2.0F;
    mMissileDrawPts[6].x =    0.0F;
    mMissileDrawPts[0].y =    0.0F;
    mMissileDrawPts[1].y =    0.0F;
    mMissileDrawPts[2].y =   -6.0F;
    mMissileDrawPts[3].y =    0.0F;
    mMissileDrawPts[4].y =  -12.0F;
    mMissileDrawPts[5].y =  -12.0F;
    mMissileDrawPts[6].y =  -17.0F;
    mLanderDrawPts[0].x =     0.0F;
    mLanderDrawPts[1].x =    -7.0F;
    mLanderDrawPts[2].x =     7.0F;
    mLanderDrawPts[3].x =   -10.0F;
    mLanderDrawPts[4].x =    10.0F;
    mLanderDrawPts[0].y =     0.0F;
    mLanderDrawPts[1].y =    13.0F;
    mLanderDrawPts[2].y =    13.0F;
    mLanderDrawPts[3].y =    13.0F;
    mLanderDrawPts[4].y =    13.0F;
    mCrosshairDrawPts[0].x =  0.0F;
    mCrosshairDrawPts[1].x = -8.0F;
    mCrosshairDrawPts[2].x =  8.0F;
    mCrosshairDrawPts[3].x =  0.0F;
    mCrosshairDrawPts[4].x =  0.0F;
    mCrosshairDrawPts[0].y =  0.0F;
    mCrosshairDrawPts[1].y =  0.0F;
    mCrosshairDrawPts[2].y =  0.0F;
    mCrosshairDrawPts[3].y = -8.0F;
    mCrosshairDrawPts[4].y =  8.0F;
	SDL_Init( SDL_INIT_VIDEO );
    TTF_Init( );
	SDL_ShowCursor (SDL_DISABLE);
	screen = SDL_SetVideoMode( kWinWidth, kWinHeight, 0, SDL_HWSURFACE | SDL_DOUBLEBUF );
	plIn.mouseMove.x = 50;
	plIn.mouseMove.y = 50;
	gameState = true;
	mBBoxLander.x= -7;
	mBBoxLander.y= -8;
	mBBoxLander.h= 22;
	mBBoxLander.w= 16;
}

Render::~Render( )
{
    TTF_Quit( );
	SDL_Quit( );
}

void Render::DrawGunship( SDL_Surface* scrn,
                          Point* gunLoc )
{
    /*Point tempMouse;
    tempMouse.x = gunLoc->x;
    tempMouse.y = 1;*/
    ellipseRGBA( scrn,
                 Round( gunLoc->x ),
                 Round( gunLoc->y ),
                 9,9,
                 255,255,255,255 );
    /*DrawMissile( scrn,
                 gunLoc,
                 &tempMouse );*/

}

void Render::DrawMissile( SDL_Surface* scrn,
                          Point* loc,
                          Point* targ )
{
    Point pts[7];
    for ( int i = 0; i < 7; i++ )
    {
        pts[i] = mMissileDrawPts[i];
    }
    float locToTarg = atan2( (float)(targ->y - loc->y), (float)(targ->x - loc->x) );
    float rotAngle = locToTarg - kPi/2;
    for ( int i = 0; i < 7; i++ )
    {
        float dist = sqrt( pts[i].x * pts[i].x + pts[i].y * pts[i].y ); // distance from point to origin
        float pntToOrg = rotAngle - atan2( (float)(pts[i].y), (float)(pts[i].x) );
        pts[i].x = dist * cos( pntToOrg ) + (float)(loc->x);
        pts[i].y = dist * sin( pntToOrg ) + (float)(loc->y);
    }
    filledTrigonRGBA ( scrn,
                       Round(pts[0].x),
                       Round(pts[0].y),
                       Round(pts[1].x),
                       Round(pts[1].y),
                       Round(pts[2].x),
                       Round(pts[2].y),
                       0,255,0,255 );
    filledTrigonRGBA ( scrn,
                       Round(pts[3].x), 
                       Round(pts[3].y),
                       Round(pts[4].x),
                       Round(pts[4].y),
                       Round(pts[5].x),
                       Round(pts[5].y),
                       255,255,255,255 );
    filledTrigonRGBA ( scrn,
                       Round(pts[4].x),
                       Round(pts[4].y),
                       Round(pts[5].x),
                       Round(pts[5].y),
                       Round(pts[6].x),
                       Round(pts[6].y),
                       255,0,0,255 );
}

void Render::DrawBomb( SDL_Surface* scrn,
                          Point* loc, float radius )
{
    aacircleRGBA(scrn,
                 Round(loc->x),
                 Round(loc->y),
                 Round(radius),
                 255,255,255,
                 0xFF);
    filledCircleRGBA(scrn,
                 Round(loc->x),
                 Round(loc->y),
                 Round(radius/2.0F),
                 128,128,128,
                 255);
    aacircleRGBA(scrn,
                 Round(loc->x),
                 Round(loc->y),
                 Round(radius/2.0F),
                 255,0,0,
                 255);

}

void Render::DrawLander( SDL_Surface* scrn,
                         Point* landerLoc )
{
        lineRGBA( scrn,
                  Round( landerLoc->x + mLanderDrawPts[0].x ),
                  Round( landerLoc->y + mLanderDrawPts[0].y ),
                  Round( landerLoc->x + mLanderDrawPts[1].x ),
                  Round( landerLoc->y + mLanderDrawPts[1].y ),
                  255,255,255,255 );
        lineRGBA( scrn,
                  Round( landerLoc->x + mLanderDrawPts[1].x ),
                  Round( landerLoc->y + mLanderDrawPts[1].y ),
                  Round( landerLoc->x + mLanderDrawPts[3].x ),
                  Round( landerLoc->y + mLanderDrawPts[3].y ),
                  255,255,255,255 );
        lineRGBA( scrn,
                  Round( landerLoc->x + mLanderDrawPts[0].x ),
                  Round( landerLoc->y + mLanderDrawPts[0].y ),
                  Round( landerLoc->x + mLanderDrawPts[2].x ),
                  Round( landerLoc->y + mLanderDrawPts[2].y ),
                  255,255,255,255 );
        lineRGBA( scrn,
                  Round( landerLoc->x + mLanderDrawPts[2].x ),
                  Round( landerLoc->y + mLanderDrawPts[2].y ),
                  Round( landerLoc->x + mLanderDrawPts[4].x ),
                  Round( landerLoc->y + mLanderDrawPts[4].y ),
                  255,255,255,255 );
        filledEllipseRGBA( scrn,
                           Round( landerLoc->x + mLanderDrawPts[0].x ),
                           Round( landerLoc->y + mLanderDrawPts[0].y ),
                           8,8,
                           0,0,0,255 );
        ellipseRGBA( scrn,
                     Round( landerLoc->x + mLanderDrawPts[0].x ),
                     Round( landerLoc->y + mLanderDrawPts[0].y ),
                     8,8,
                     255,255,255,255 );
}


void Render::DrawTerrain( SDL_Surface *scrn,
                         vector<Point>::iterator tPts,
                          int numTP,
                          vector<BBox>::iterator boxes)
{
    for ( int i = 0; i < numTP-1; i++ )
    {
        short x[4] = { Round( tPts[i].x ),
                       Round( tPts[i+1].x ),
                       Round( tPts[i+1].x ),
                       Round( tPts[i].x ) };
        short y[4] = { Round( tPts[i].y ),
                       Round( tPts[i+1].y ),
                       kWinHeight-1,
                       kWinHeight-1 };
        filledPolygonRGBA( scrn,
                           x,y,4,
                           0,0,0,255 );
        lineRGBA( scrn,
                  Round( tPts[i].x ),
                  Round( tPts[i].y ),
                  Round( tPts[i+1].x ),
                  Round( tPts[i+1].y ),
                  255,255,255,255 );
    }
    for ( int i = 0; i < numTP-1; i++ )
    {
		DrawBox(boxes[i]);
    }
}

void Render::DrawCrosshair( SDL_Surface* scrn,
                     Point* loc,
                     int r,
                     int g,
                     int b )
{
    ellipseRGBA( scrn,
                 Round( loc->x + mCrosshairDrawPts[0].x ),
                 Round( loc->y + mCrosshairDrawPts[0].y ),
                 6,6,
                 r,g,b,191 );
    lineRGBA( scrn,
              Round( loc->x + mCrosshairDrawPts[1].x ),
              Round( loc->y + mCrosshairDrawPts[1].y ),
              Round( loc->x + mCrosshairDrawPts[2].x ),
              Round( loc->y + mCrosshairDrawPts[2].y ),
              r,g,b,191 );
    lineRGBA( scrn,
              Round( loc->x + mCrosshairDrawPts[3].x ),
              Round( loc->y + mCrosshairDrawPts[3].y ),
              Round( loc->x + mCrosshairDrawPts[4].x ),
              Round( loc->y + mCrosshairDrawPts[4].y ),
              r,g,b,191 );
}

void Render::DrawExplosion( SDL_Surface* scrn,
                         Point loc,
                         float frameIDX,
                         float radius,
                         SDL_Color colorOuter,
                         SDL_Color colorInner)
{
    filledCircleRGBA(scrn,
                 Round(loc.x),
                 Round(loc.y),
                 Round(radius),
                 colorOuter.r,
                 colorOuter.g,
                 colorOuter.b,
                 0xFF);
    aacircleRGBA(scrn,
                 Round(loc.x),
                 Round(loc.y),
                 Round(radius),
                 colorOuter.r,
                 colorOuter.g,
                 colorOuter.b,
                 0xFF);
    if (radius > kExplosionSecondRadiusDefault)
    {
        filledCircleRGBA(scrn,
                     Round(loc.x),
                     Round(loc.y),
                     Round(radius - kExplosionSecondRadiusDefault),
                     colorInner.r,
                     colorInner.g,
                     colorInner.b,
                     0xFF);
            aacircleRGBA(scrn,
                     Round(loc.x),
                     Round(loc.y),
                     Round(radius - kExplosionSecondRadiusDefault),
                     colorInner.r,
                     colorInner.g,
                     colorInner.b,
                     0xFF);
    }
}

void Render::DrawLevel(Level* l)
{
	vector<Point> *vPts;
	vector<Point>::iterator iterPoint;
	vPts= l->GetTerPt();
	unsigned short numPts= l->GetNumTerPt();
	if (numPts > 0)
	{
		iterPoint= vPts->begin();
		if (numPts > 1)
		{
			for (int tp = 0; tp < (numPts -1); tp++)
			{
				Point pt1= *iterPoint;
				iterPoint++;
				lineRGBA(screen,
					Round(pt1.x),
					Round(pt1.y),
					Round(iterPoint->x),
					Round(iterPoint->y),
					255,255,255,255 );
			}
			
		}
			lineRGBA(screen,
			Round(iterPoint->x),
			Round(iterPoint->y),
			Round(getMouse().x),
			Round(getMouse().y),
			0,255,0,255 );
	}

}

SDL_Surface* Render::getpScreen()
{
	return screen;
}

void Render::doInput()
{
    plIn.leftClick= false;
    plIn.rightClick= false;
    while (SDL_PollEvent(&mEvent))
    {
	    if(mEvent.type == SDL_MOUSEMOTION)
	    {
		    plIn.mouseMove.x = mEvent.motion.x;
		    plIn.mouseMove.y = mEvent.motion.y;
	    }
		if (mEvent.type == SDL_QUIT)
		{
			gameState= false;
		}

	    if(mEvent.type == SDL_KEYDOWN)
	    {
		    plIn.keyPress = mEvent.key.keysym.sym;
		    if(plIn.keyPress == SDLK_ESCAPE)
		    {
			    gameState = false;
		    }
	    }

	    if(mEvent.type == SDL_MOUSEBUTTONDOWN)
	    {
		    plIn.mousePress.button = mEvent.button.button;
		    if((plIn.mousePress.button == SDL_BUTTON_LEFT))
		    {
			    plIn.leftClick = true;
			    plIn.tlclicked = true;
		    }
		   

		    if(plIn.mousePress.button == SDL_BUTTON_RIGHT )
		    {
			    plIn.rightClick = true;
			    plIn.trclicked = true;
		    }
	    }

		if(mEvent.type == SDL_MOUSEBUTTONUP)
	    {
		    plIn.mousePress.button = mEvent.button.button;
		    if(plIn.mousePress.button == SDL_BUTTON_LEFT)
		    {
			    plIn.tlclicked = false;
                plIn.leftClick = false;
		    }

			if(plIn.mousePress.button == SDL_BUTTON_RIGHT)
		    {
			    plIn.trclicked = false;
                plIn.rightClick = false;
		    }
	    }
    	
	    if(plIn.leftClick == 1)
		    cout << "left clicked\n";
	    if(plIn.rightClick == 1)
		    cout << "right clicked\n";
    }
}

void Render::doEditInput()
{
    plIn.leftClick= false;
    plIn.rightClick= false;
    while (SDL_PollEvent(&mEvent))
    {
	    if(mEvent.type == SDL_MOUSEMOTION)
	    {
		    plIn.mouseMove.x = mEvent.motion.x;
		    plIn.mouseMove.y = mEvent.motion.y;
	    }
		if (mEvent.type == SDL_QUIT)
		{
			gameState= false;
		}

	    if(mEvent.type == SDL_KEYDOWN)
	    {
		    plIn.keyPress = mEvent.key.keysym.sym;
		    if(plIn.keyPress == SDLK_ESCAPE)
		    {
			    gameState = false;
		    }
	    }

	    if(mEvent.type == SDL_MOUSEBUTTONDOWN)
	    {
		    plIn.mousePress.button = mEvent.button.button;
		    if((plIn.mousePress.button == SDL_BUTTON_LEFT))
		    {
			    plIn.leftClick = true;
			    plIn.tlclicked = true;
		    }
		   

		    if(plIn.mousePress.button == SDL_BUTTON_RIGHT )
		    {
			    plIn.rightClick = true;
			    plIn.trclicked = true;
		    }

			if(plIn.mousePress.button == SDL_BUTTON_MIDDLE)
			{
				plIn.midClick = true;
			}
		 
	    }
	    if(mEvent.type == SDL_MOUSEBUTTONUP)
	    {
		    plIn.mousePress.button = mEvent.button.button;
		    if(plIn.mousePress.button == SDL_BUTTON_LEFT)
		    {
			    plIn.tlclicked = false;
                plIn.leftClick = false;
		    }
		    if(plIn.mousePress.button == SDL_BUTTON_RIGHT)
		    {
			    plIn.trclicked = false;
                plIn.rightClick = false;
		    }

			if(plIn.mousePress.button == SDL_BUTTON_MIDDLE)
			{
				plIn.midClick = false;
			}
	    }
    	
    }
}

bool Render::gameRunning()
{
	return gameState;
}

Point Render::getMouse()
{
	return plIn.mouseMove;
}

bool Render::isLClicked()
{
	return plIn.leftClick;
}

bool Render::isRClicked()
{
	return plIn.rightClick;
}

bool Render::isMClicked()
{
	return plIn.midClick;
}

bool Render::isLeftHeld()
{
	return plIn.tlclicked;
}

bool Render::isRightHeld()
{
	return plIn.trclicked;
}

short int Render::GetSplashAlpha( )
{
    return mSplashAlpha;
}

void Render::DecSplashAlpha( short amt )
{
    if ( amt < 0 )
    {
        amt = 0;
    }
    else if ( amt > 255 )
    {
        amt = 255;
    }
    mSplashAlpha -= amt;
    if ( mSplashAlpha < 0 )
    {
        mSplashAlpha = 0;
    }
    else if ( mSplashAlpha > 255 )
    {
        mSplashAlpha = 255;
    }
}

void Render::DrawSplash( )
{
    TTF_Font* splashFont = TTF_OpenFont("QUERROUND.TTF", 24);
    SDL_Color txtForeColor = { 0,
                               mSplashAlpha,
                               mSplashAlpha };
    SDL_Surface* textSurface = TTF_RenderText_Blended( splashFont,
                                                       "anti lander",
                                                       txtForeColor );
    SDL_Rect splashLoc = { 200,100,
                           0,0 };
    SDL_BlitSurface( textSurface,
                     NULL,
                     screen,
                     &splashLoc );
    SDL_FreeSurface( textSurface );
    TTF_CloseFont( splashFont );
}

void Render::DrawBox( Point loc,
                      BBox box )
{
    rectangleRGBA( screen,
                   (int)(loc.x + box.x),
                   (int)(loc.y + box.y),
                   (int)(loc.x + box.x + box.w),
                   (int)(loc.y + box.y + box.h),
                   255,255,255,127 );
}

void Render::DrawBox(BBox box)
{
    rectangleRGBA( screen,
                   (int)(box.x),
                   (int)(box.y),
                   (int)(box.x + box.w),
                   (int)(box.y + box.h),
                   255,255,255,127 );
}
BBox Render::GetLanderBox()
{
	return mBBoxLander;
}
