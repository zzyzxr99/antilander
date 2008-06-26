#ifndef _SCORE_H
#define _SCORE_H

#include "Structs.h"
#include "SDL.h"
#include "SDL_GFXprimitives.h"
#include "SDL_ttf.h"

class Score
{
private:
	SDL_Surface* screen;
	TTF_Font* conFont;	
	//int TotalScore;
public:
	Score();
	~Score();
	SDL_Surface* getpScreen();
	//void DrawScore(int Score);
	int GetScore();
	void AddScore(int Score, int Val);
};
#endif