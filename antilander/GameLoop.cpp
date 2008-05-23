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

	while (tWorld->GetRender()->gameRunning())
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

    // Delete the GameWorld, it will delete all of its members
   	delete tWorld;

	return 0;
}
