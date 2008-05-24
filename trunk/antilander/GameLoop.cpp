#include "Functions.h"
#include "Constants.h"
#include "SDL.h"
#include "GameWorld.h"
#include "Level.h"			//testing
#include <iostream>

int main(int argv, char *args[])
{
	GameWorld *tWorld;
	tWorld= new GameWorld();

	SDL_WM_SetCaption( kWinTitle, 0 );

    tWorld->StartGameStepper();
	tWorld->SetGameStatus(knEditMode);

	//////////////// test /////////////////////
	Level* tLevel = new Level();
	tLevel->LoadLevel();
	//////////////// test /////////////////////

	while (tWorld->GetRender()->gameRunning())
	{
		if (tWorld->GetGameStatus() == knPlayMode)
		{
			tWorld->GetRender()->doInput();

			if (tWorld->LeftMouseHeld())
			{
				std::cout << "LeftMouseHeld" << std::endl;
			}
			if (tWorld->RightMouseHeld())
			{
				std::cout << "RightMouseHeld" << std::endl;
			}

			if (tWorld->FireMissile())
			{
				tWorld->SpawnMissile();
			}
			if (tWorld->TestFireExplosion())
			{
				tWorld->TestSpawnExplosion();
			}
			if ( tWorld->CheckTick( ))
			{
				tWorld->UpdateEverything( );
			}
			tWorld->DrawEverything();
		}
		else if (tWorld->GetGameStatus() == knEditMode)
		{
			tWorld->GetRender()->doEditInput();
			if (tWorld->GetRender()->isLClicked())
			{
				tWorld->AddEditLevelPoint(tWorld->GetRender()->getMouse());
			}
			//run doEditInput


			//run EditUpdateEverything


			tWorld->EditDrawEverything();
		}
 	}

    // Delete the GameWorld, it will delete all of its members
   	delete tWorld;

	return 0;
}
