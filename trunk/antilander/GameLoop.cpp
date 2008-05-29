#include "Functions.h"
#include "Constants.h"
#include "SDL.h"
#include "GameWorld.h"
#include "Level.h"			//testing
#include <iostream>
#include <sstream>
using namespace std;

int main(int argv, char *args[])
{
	GameWorld *tWorld;
	tWorld= new GameWorld();

	SDL_WM_SetCaption( kWinTitle, 0 );

    tWorld->StartGameStepper();
	tWorld->SetGameStatus(knEditMode);
	tWorld->SetEditStatus(knBuildMode);

	//////////////// load test /////////////////////
	Level* tLevel = new Level();
	int lvlCtr = 1;
	
	//if (conditions are met to advance level)
	string name;
	stringstream out;
	out << lvlCtr;
	name = out.str();
	tLevel->SaveLevel ( "LEVEL" + name + ".txt" );
	tLevel->LoadLevel ( "LEVEL" + name + ".txt" );


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

			}

			tWorld->EditDrawEverything();
		}
	}


    tWorld->TestSaveLoadLevel();
    // Delete the GameWorld, it will delete all of its members
   	delete tWorld;

	return 0;
}
