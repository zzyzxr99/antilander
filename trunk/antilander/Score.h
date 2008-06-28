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
	int TotalScore;

public:
	Score();
	// Score( parameters )
	~Score();
	int GetTotalScore();
	void AddScore(int Score, int Val);
	void DrawScore(int Score, SDL_Surface* screen);
	void ClearScore();
};
#endif