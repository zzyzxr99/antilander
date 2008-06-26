#ifndef _SCORE_H
#define _SCORE_H

#include "Structs.h"
#include "ALTimer.h"
#include "SDL.h"

class Score
{
private:
	Point mDrawLoc;
	ALTimer mScoreTime;
	int mScoreValue;
	SDL_Color mScoreColor;

public:
	Score();
	// Score( parameters )
	~Score();
	//void DrawScore(int Score);
};
#endif