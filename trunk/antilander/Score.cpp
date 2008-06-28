#include "Score.h"
#include "Constants.h"
#include "Structs.h"
#include "SDL.h"
#include "SDL_GFXprimitives.h"
#include "SDL_ttf.h"
#include <string>
#include "string.h"
#include <sstream>

using namespace std;

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
	stringstream SS;
	SS << "Score : " << Score;
    TTF_Font* ScoreFont = TTF_OpenFont("QUERROUND.TTF", 12);
    SDL_Color txtForeColor = { 0, 254, 254 };
	SDL_Surface* textSurface = TTF_RenderText_Blended( ScoreFont, SS.str().c_str(), txtForeColor );
    SDL_Rect ScoreLoc = { kWinWidth - 380 ,10 ,
                           0,0 };
    SDL_BlitSurface( textSurface,
                     NULL,
                     screen,
                     &ScoreLoc );
    SDL_FreeSurface( textSurface );
    TTF_CloseFont( ScoreFont );
}
void Score::ClearScore()
{
	TotalScore = 0;
}