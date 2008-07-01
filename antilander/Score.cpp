#include "Score.h"
#include "Constants.h"
#include "Structs.h"
#include "SDL.h"
#include "SDL_GFXprimitives.h"
#include "SDL_ttf.h"
#include <string>
#include "string.h"
#include <sstream>
#include "GameWorld.h"

using namespace std;

extern GameWorld *tWorld;

Score::Score()
{
	TotalScore = 0;
	// init Point etc
}
Score::~Score()
{
	//Any "new" needs "delete"
}
int Score::GetTotalScore()
{
	return TotalScore;
}
void Score::AddScore(int Score, int Val)
{
	TotalScore = Score + Val;
}
void Score::DrawScore(int Score, SDL_Surface* screen)
{
	stringstream SS, bomb, miss;
	SS << "Score : " << Score;
	bomb << tWorld->GetNumBombs();
	miss << tWorld->GetNumMissiles();
    TTF_Font* ScoreFont = TTF_OpenFont("QUERROUND.TTF", 12);
    SDL_Color txtForeColor = { 0, 254, 254 };
	SDL_Surface* textSurface = TTF_RenderText_Blended( ScoreFont, SS.str().c_str(), txtForeColor );
    SDL_Rect ScoreLoc = { kWinWidth - 370 ,10 ,
                           0,0 };
    SDL_BlitSurface( textSurface,
                     NULL,
                     screen,
                     &ScoreLoc );
	TTF_CloseFont( ScoreFont );


	TTF_Font* hudFont = TTF_OpenFont("QUERROUND.TTF", 10);
	SDL_Surface* missSurface = TTF_RenderText_Blended( hudFont, miss.str().c_str(), txtForeColor );
	SDL_Rect MissLoc = { kWinWidth - 530 ,10 ,
                           0,0 };
	SDL_BlitSurface( missSurface,
                     NULL,
                     screen,
                     &MissLoc );


	SDL_Surface* bombSurface = TTF_RenderText_Blended( hudFont, bomb.str().c_str(), txtForeColor );
	SDL_Rect BombLoc = { kWinWidth - 450 ,10 ,
                           0,0 };
	SDL_BlitSurface( bombSurface,
                     NULL,
                     screen,
                     &BombLoc );
    
	TTF_CloseFont( hudFont );
	SDL_FreeSurface( textSurface );
	SDL_FreeSurface( missSurface );
	SDL_FreeSurface( bombSurface );
    
}
void Score::ClearScore()
{
	TotalScore = 0;
}