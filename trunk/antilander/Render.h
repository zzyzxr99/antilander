// Render.h

#ifndef _RENDER_H
#define _RENDER_H



#include "Structs.h"
#include "SDL.h"
#include "SDL_GFXprimitives.h"
#include "SDL_ttf.h"
#include "level.h"
#include <string>

class Render
{
private:
    Point mMissileDrawPts[7];
    Point mLanderDrawPts[5];
    Point mCrosshairDrawPts[5];
	SDL_Surface* screen;
	SDL_Event mEvent;
	SDL_KeyboardEvent mKeyEvent;
	playInput plIn;				//player input
	//bool shiftKey;
	bool gameState;
	bool playState;  //for checking if a level is started
	bool doneBuildmode;
	bool exitEditmode;
    short int mSplashAlpha;
    FadeType mSplashFade;
	BBox mBBoxLander;
	BBox mGameScreen;
	TTF_Font* conFont;	
	bool mConsole;
	int mLevelNum;
	bool mPause;
	bool mStart;
	bool mEdit;

public:
    Render( );
    ~Render( );
    void DrawGunship( SDL_Surface* scrn,
                      Point* gunLoc );
    void DrawMissile( SDL_Surface* scrn,
                      Point* loc,
                      Point* targ );
    void DrawBomb( SDL_Surface* scrn,
                      Point* loc, float radius);
    void DrawLander( SDL_Surface* scrn,
                     Point* landerLoc );
    void DrawTerrain( SDL_Surface* scrn,
        vector<Point>::iterator tPts,
                      int numTP,
                      vector<BBox>::iterator boxes);
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
	void doMenuInput();
	void doMoveInput();
	bool gameRunning();					//gets current gamestate
	bool arePlaying();
	bool EndDraw();
	bool EndEdit();
	void SetEndEdit(bool num);
	void SetEndDraw(bool num);
	Point getMouse();					//gets cursor position
	//bool shiftHeld();
	bool isLClicked();					//check whether mouse is clicked
	bool isRClicked();
	bool isMClicked();
	bool isLeftHeld();
	bool isRightHeld();
	bool isMidHeld();
	short int GetSplashAlpha( );
    void StepSplashAlpha(short amt);
    FadeType GetSplashFade( );
    void SetSplashFade(FadeType fade);
    void DrawSplash(GameStatusType status);
	void DrawMenu();
	
//    void DrawBox( Point loc,
//                  BBox box );
//	void DrawBox(BBox box);
	BBox GetLanderBox();
	void DrawLevel(Level* l,bool DrawGreen);
    BBox GetGameScreen();
	int GetLevelNum();
	void DrawConsole(string str);
	playInput* GetInput();
	bool GetConsole();
	void DrawScore(int Score);
	bool* IsPause();
	bool* IsStart();
	bool* IsEdit();
    void Start( );
    void Stop( );
	void SetGameState(bool state);
};

#endif // _RENDER_H;
