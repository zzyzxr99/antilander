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
	//draw score
	stringstream SS, bomb, miss;
	SS << "Score : " << Score;
	bomb << tWorld->GetNumBombs();
	miss << tWorld->GetNumMissiles();
	Point missPt, bombPt, missPt2;
	bombPt.x = kWinWidth-420; bombPt.y = 8;
	missPt.x = kWinWidth-490; missPt.y = 12;
	missPt2.x = missPt.x; missPt2.y = 0;
	Sint16 ptX[4] = {kWinWidth-505, kWinWidth-135, kWinWidth-140, kWinWidth-500}; 
	Sint16 ptY[4] = {-1, -1, 16, 16};

	filledPolygonRGBA(   screen,
						 ptX,
						 ptY,
						 4,
						 80,80,80,125);

    TTF_Font* ScoreFont = TTF_OpenFont("QUERROUND.TTF", 10);
    SDL_Color txtForeColor = { 0, 254, 254 };
	SDL_Surface* textSurface = TTF_RenderText_Blended( ScoreFont, SS.str().c_str(), txtForeColor );
    SDL_Rect ScoreLoc = { kWinWidth - 370 ,0 ,
                           0,0 };
    SDL_BlitSurface( textSurface,
                     NULL,
                     screen,
                     &ScoreLoc );
	TTF_CloseFont( ScoreFont );

	//draw missile count
	TTF_Font* hudFont = TTF_OpenFont("QUERROUND.TTF", 7);
	SDL_Surface* missSurface = TTF_RenderText_Blended( hudFont, miss.str().c_str(), txtForeColor );
	SDL_Rect MissLoc = { kWinWidth - 480 , 3,
                           0,0 };
	SDL_BlitSurface( missSurface,
                     NULL,
                     screen,
                     &MissLoc );

	//draw bomb count
	SDL_Surface* bombSurface = TTF_RenderText_Blended( hudFont, bomb.str().c_str(), txtForeColor );
	SDL_Rect BombLoc = { kWinWidth - 410 , 3,
                           0,0 };
	SDL_BlitSurface( bombSurface,
                     NULL,
                     screen,
                     &BombLoc );
	tWorld->GetRender()->DrawBomb(screen,&bombPt,5);
	tWorld->GetRender()->DrawMissile(screen,&missPt,&missPt2,0.6F);
    
	aapolygonRGBA( screen, 
				 ptX, 
				 ptY, 
				 4,
                 kMenuRvalue,kMenuGvalue,kMenuBvalue,kMenuAvalue);

	TTF_CloseFont( hudFont );
	SDL_FreeSurface( textSurface );
	SDL_FreeSurface( missSurface );
	SDL_FreeSurface( bombSurface );
    
}
void Score::ClearScore()
{
	TotalScore = 0;
}