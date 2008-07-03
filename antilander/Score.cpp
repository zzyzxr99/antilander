#include "Score.h"
#include "Constants.h"
#include "Structs.h"
#include "SDL.h"
#include "SDL_GFXprimitives.h"
#include "SDL_ttf.h"
#include "GameWorld.h"

using namespace std;

extern GameWorld *tWorld;

Score::Score()
{
	TotalScore = 0;
	bombPt.x = kWinWidth-420; bombPt.y = 8;
	missPt.x = kWinWidth-485; missPt.y = 12;
	missPt2.x = missPt.x; missPt2.y = 0;
	landPt.x = kWinWidth-285; landPt.y = 7;
	
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
	stringstream SS, bomb, miss, land, landed;
	SS << Score;
	for(int j=0; j<tWorld->GetEndGamePadOcc(); j++)
	{
		landed << "__ ";
	}
	
	bomb << "!" << tWorld->GetNumBombs();
	miss << "!" << tWorld->GetNumMissiles();
	land << "!" << tWorld->GetLandToGo();
	
	DrawIcons(screen);
	
    TTF_Font* ScoreFont = TTF_OpenFont("QUERROUND.TTF", 10);
    SDL_Color txtForeColor = { 0, 254, 254 };
	SDL_Surface* textSurface = TTF_RenderText_Blended( ScoreFont, SS.str().c_str(), txtForeColor );
    SDL_Rect ScoreLoc = { kWinWidth - 365 ,0 ,
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

	//draw lander count
	SDL_Surface* landSurface = TTF_RenderText_Blended( hudFont, land.str().c_str(), txtForeColor );
	SDL_Rect LandLoc = { kWinWidth - 272 , 3,
                           0,0 };
	SDL_BlitSurface( landSurface,
                     NULL,
                     screen,
                     &LandLoc );
	
	//draw landed count
	SDL_Surface* landedSurface = TTF_RenderText_Blended( hudFont, landed.str().c_str(), txtForeColor );
	SDL_Rect LandedLoc = { kWinWidth - 240 , 4,
                           0,0 };
	SDL_BlitSurface( landedSurface,
                     NULL,
                     screen,
                     &LandedLoc );

	TTF_CloseFont( hudFont );
	SDL_FreeSurface( textSurface );
	SDL_FreeSurface( missSurface );
	SDL_FreeSurface( bombSurface );
	SDL_FreeSurface( landSurface );
    SDL_FreeSurface( landedSurface );
}
void Score::ClearScore()
{
	TotalScore = 0;
}

void Score::DrawIcons(SDL_Surface* screen)
{
	Sint16 ptX[7] = {kWinWidth-505, kWinWidth-135, kWinWidth-140, kWinWidth-500}; 
	Sint16 ptY[7] = {-1, -1, 16, 16};
	landedPt[0].x = kWinWidth-237; landedPt[0].y = 6;
	landedPt[1].x = landedPt[0].x+14; landedPt[1].y = 6;
	landedPt[2].x = landedPt[1].x+14; landedPt[2].y = 6;
	landedPt[3].x = landedPt[2].x+14; landedPt[3].y = 6;
	landedPt[4].x = landedPt[3].x+14; landedPt[4].y = 6;
	landedPt[5].x = landedPt[4].x+14; landedPt[5].y = 6;
	landedPt[6].x = landedPt[5].x+14; landedPt[6].y = 6;

	filledPolygonRGBA(   screen,
						 ptX,
						 ptY,
						 4,
						 80,80,80,125);

	tWorld->GetRender()->DrawBomb(screen,&bombPt,5);
	tWorld->GetRender()->DrawMissile(screen,&missPt,&missPt2,0.6F);
	tWorld->GetRender()->DrawLander(screen,&landPt,0.5F);
    
	switch(tWorld->GetLandLanded())
	{
	case 1:
		tWorld->GetRender()->DrawLander(screen,&landedPt[0],0.3F);
		break;
	case 2:
		tWorld->GetRender()->DrawLander(screen,&landedPt[0],0.3F);
		tWorld->GetRender()->DrawLander(screen,&landedPt[1],0.3F);
		break;
	case 3:
		tWorld->GetRender()->DrawLander(screen,&landedPt[0],0.3F);
		tWorld->GetRender()->DrawLander(screen,&landedPt[1],0.3F);
		tWorld->GetRender()->DrawLander(screen,&landedPt[2],0.3F);
		break;
	case 4:
		tWorld->GetRender()->DrawLander(screen,&landedPt[0],0.3F);
		tWorld->GetRender()->DrawLander(screen,&landedPt[1],0.3F);
		tWorld->GetRender()->DrawLander(screen,&landedPt[2],0.3F);
		tWorld->GetRender()->DrawLander(screen,&landedPt[3],0.3F);
		break;
	case 5:
		tWorld->GetRender()->DrawLander(screen,&landedPt[0],0.3F);
		tWorld->GetRender()->DrawLander(screen,&landedPt[1],0.3F);
		tWorld->GetRender()->DrawLander(screen,&landedPt[2],0.3F);
		tWorld->GetRender()->DrawLander(screen,&landedPt[3],0.3F);
		tWorld->GetRender()->DrawLander(screen,&landedPt[4],0.3F);
		break;
	case 6:
		tWorld->GetRender()->DrawLander(screen,&landedPt[0],0.3F);
		tWorld->GetRender()->DrawLander(screen,&landedPt[1],0.3F);
		tWorld->GetRender()->DrawLander(screen,&landedPt[2],0.3F);
		tWorld->GetRender()->DrawLander(screen,&landedPt[3],0.3F);
		tWorld->GetRender()->DrawLander(screen,&landedPt[4],0.3F);
		tWorld->GetRender()->DrawLander(screen,&landedPt[5],0.3F);
		break;
	case 7:
		tWorld->GetRender()->DrawLander(screen,&landedPt[0],0.3F);
		tWorld->GetRender()->DrawLander(screen,&landedPt[1],0.3F);
		tWorld->GetRender()->DrawLander(screen,&landedPt[2],0.3F);
		tWorld->GetRender()->DrawLander(screen,&landedPt[3],0.3F);
		tWorld->GetRender()->DrawLander(screen,&landedPt[4],0.3F);
		tWorld->GetRender()->DrawLander(screen,&landedPt[5],0.3F);
		tWorld->GetRender()->DrawLander(screen,&landedPt[6],0.3F);
		break;
	}
	
	aapolygonRGBA( screen, 
				 ptX, 
				 ptY, 
				 4,
                 kMenuRvalue,kMenuGvalue,kMenuBvalue,kMenuAvalue);
}