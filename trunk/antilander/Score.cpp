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
	SDL_ShowCursor (SDL_DISABLE);
	screen = SDL_SetVideoMode( kWinWidth, kWinHeight, 0, SDL_HWSURFACE | SDL_DOUBLEBUF );
	conFont = TTF_OpenFont("Compact_Mono.TTF", 15);
	//TotalScore = 0;

}
Score::~Score()
{
	//Any "new" needs "delete"
}
SDL_Surface* Score::getpScreen()
{
	return screen;
}
//int Score::GetScore()
//{
//	return TotalScore;
//}
//void Score::DrawScore(int Score)
//{
//	stringstream SS;
//	SS << "Score : " << Score;
//    TTF_Font* ScoreFont = TTF_OpenFont("QUERROUND.TTF", 12);
//    SDL_Color txtForeColor = { 0, 254, 254 };
//	SDL_Surface* textSurface = TTF_RenderText_Blended( ScoreFont, SS.str().c_str(), txtForeColor );
//    SDL_Rect ScoreLoc = { 15,kWinHeight - 70,
//                           0,0 };
//    SDL_BlitSurface( textSurface,
//                     NULL,
//                     screen,
//                     &ScoreLoc );
//    SDL_FreeSurface( textSurface );
//    TTF_CloseFont( ScoreFont );
//}