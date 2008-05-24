#include "Functions.h"
#include "Constants.h"
#include "SDL.h"
#include "GameWorld.h"

#include <iostream>

int main(int argv, char *args[])
{
	GameWorld *tWorld;
	tWorld= new GameWorld();

	SDL_WM_SetCaption( kWinTitle, 0 );

    tWorld->StartGameStepper();
	tWorld->SetGameStatus(knEditMode);

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
			//run doEditInput


			//run EditUpdateEverything


			//run editDrawEverything
		}
 	}

    // Delete the GameWorld, it will delete all of its members
   	delete tWorld;

	return 0;
}
