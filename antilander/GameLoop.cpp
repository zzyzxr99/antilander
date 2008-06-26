#include "Functions.h"
#include "Constants.h"
#include "SDL.h"
#include "GameWorld.h"
#include "Level.h"			//testing
#include <iostream>
#include <ctime>

using namespace std;


GameWorld* tWorld;

int main(int argv, char *args[])
{
	srand(clock());
 
	tWorld= new GameWorld();

	SDL_WM_SetCaption( kWinTitle, 0 );

    tWorld->StartGameStepper();
	tWorld->SetGameStatus(knIntroMode);
	tWorld->SetEditStatus(knBuildMode);

    tWorld->GetEditLevel()->ClearLevel();

	if (tWorld->GetGameStatus() == knPlayMode)
	{
//		Level*L= tWorld->GetLevel();
		tWorld->GetEditLevel()->ClearLevel();
	}


	//////////////// load test /////////////////////

	while (tWorld->GetRender()->gameRunning())
	{
		if (tWorld->GetGameStatus() == knPlayMode)
		{
			tWorld->GetRender()->doInput();
			
			if (tWorld->FireMissile())
			{
				tWorld->SpawnMissile();
			}
			if (tWorld->FireBomb())
			{
				tWorld->SpawnBomb();
			}
			if ( tWorld->CheckTick( ))
			{
				tWorld->UpdateEverything( );
			}
			tWorld->CheckSpawnLander();

            tWorld->CheckWinLose( );

			if (*tWorld->GetRender()->IsPause())
			{
				tWorld->SetGameStatus(knMenuMode);
			}

			tWorld->DrawEverything();
		}
//====================Menu Mode========================
		else if (tWorld->GetGameStatus() == knMenuMode)
		{
			tWorld->GetRender()->DrawMenu();
			tWorld->GetRender()->doMenuInput();
			if (*tWorld->GetRender()->IsStart())
			{
				tWorld->SetGameStatus(knPlayMode);
			}
		}
//====================Edit Mode========================
		else if (tWorld->GetGameStatus() == knEditMode)
		{
			if (tWorld->GetEditStatus() == knBuildMode)
			{
				tWorld->GetRender()->doEditInput();
				if (tWorld->GetRender()->isLClicked())
				{
					tWorld->AddEditLevelPoint(tWorld->GetRender()->getMouse());
				}

				if (tWorld->GetRender()->isRClicked())
				{
					tWorld->AddEditPadPoint(tWorld->GetRender()->getMouse());
				}

				if (tWorld->GetRender()->EndDraw())
				{
					tWorld->EndEditLvlPts(tWorld->GetRender()->getMouse());
					tWorld->SetEditStatus(knMoveMode);
				}
			}

			else if (tWorld->GetEditStatus() == knMoveMode)
			{
				/*if(tWorld->GetRender()->isRClicked())
				{
					tWorld->SetEditStatus(knBuildMode);
				}*/

				tWorld->GetRender()->doMoveInput();
				if (tWorld->GetRender()->isLClicked())
				{
					Point mp= (tWorld->GetRender()->getMouse());
					
				}
				if(tWorld->GetRender()->EndEdit())
				{	
					tWorld->GetEditLevel()->MakePadPtsFromTerrainPts();
				//	tWorld->GetEditLevel()->SaveLevel(tWorld->GetLevName(tWorld->GetRender()->GetLevelNum()));
				//	tWorld->GetEditLevel()->LoadLevel(tWorld->GetLevName(tWorld->GetRender()->GetLevelNum()));
					tWorld->InitEditLvl();
					tWorld->SetGameStatus(knPlayMode);
				}

			}

			tWorld->EditDrawEverything();
		}

//=================End Mode===========================//
        if ( tWorld->GetGameStatus( ) == knEndMode )
        {
            if ( tWorld->CheckTick( ) )
			{
				tWorld->UpdateEverything( );
			}
            tWorld->DrawEverything( );
        }
//=============Level Transition mode=================//
        if ( tWorld->GetGameStatus( ) == knLevTransMode )
        {
            if ( tWorld->CheckTick( ) )
			{
				tWorld->UpdateEverything( );
			}
            tWorld->DrawEverything( );
        }
//===================Intro Mode======================//
        if ( tWorld->GetGameStatus( ) == knIntroMode )
        {
            if ( tWorld->CheckTick( ) )
			{
				tWorld->UpdateEverything( );
			}
            tWorld->DrawEverything( );
        }
	}


//    tWorld->TestSaveLoadLevel();
    // Delete the GameWorld, it will delete all of its members
   	delete tWorld;

	return 0;
}
