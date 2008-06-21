#include "Functions.h"
#include "Constants.h"
#include "SDL.h"
#include "GameWorld.h"
#include "Level.h"			//testing
#include <iostream>
#include <ctime>


using namespace std;

int main(int argv, char *args[])
{
	srand(clock());
	GameWorld* tWorld; 
	tWorld= new GameWorld();

	SDL_WM_SetCaption( kWinTitle, 0 );

    tWorld->StartGameStepper();
	tWorld->SetGameStatus(knPlayMode);
	tWorld->SetEditStatus(knBuildMode);

    tWorld->GetLevel()->ClearLevel();

	if (tWorld->GetGameStatus() == knPlayMode)
	{
//		Level*L= tWorld->GetLevel();
		tWorld->GetLevel()->ClearLevel();
	}

	


	//////////////// load test /////////////////////

	while (tWorld->GetRender()->gameRunning())
	{
		if (tWorld->GetGameStatus() == knPlayMode)
		{
			tWorld->GetRender()->doInput();

            if ( tWorld->GetLanders( )->size( ) < tWorld->GetNumLndrScr( ) )
            {
                tWorld->SpawnLander( );
            }
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
			tWorld->DrawEverything();
			
			
				


		}
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
				//////////////////////////	Load Level Test  //////////////////////////
				tWorld->GetLevel()->SaveLevel(tWorld->GetLevName(tWorld->GetRender()->GetLevelNum()));
				///////////////////////////////////////////////////////////////////////
				if(tWorld->GetRender()->EndEdit())
				{	
					tWorld->GetLevel()->MakePadPtsFromTerrainPts();
				//	tWorld->GetLevel()->SaveLevel(tWorld->GetLevName(tWorld->GetRender()->GetLevelNum()));
				//	tWorld->GetLevel()->LoadLevel(tWorld->GetLevName(tWorld->GetRender()->GetLevelNum()));
					tWorld->InitEditLvl();
					tWorld->SetGameStatus(knPlayMode);
				}

			}

			tWorld->EditDrawEverything();
		}
	}


//    tWorld->TestSaveLoadLevel();
    // Delete the GameWorld, it will delete all of its members
   	delete tWorld;

	return 0;
}
