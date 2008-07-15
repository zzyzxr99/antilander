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
    tWorld->InitSoundEngine();
	SDL_WM_SetCaption( kWinTitle, 0 );

    tWorld->StartGameStepper();
	tWorld->SetGameStatus(knIntroMode);
	tWorld->PlaySoundEffect(knSEIntroSound);
	tWorld->SetEditStatus(knBuildMode);

    tWorld->GetEditLevel()->ClearLevel();

	// ejr check OLD
	if (tWorld->GetGameStatus() == knPlayMode)
	{
//		Level*L= tWorld->GetLevel();
		tWorld->GetEditLevel()->ClearLevel();  //shouldn't this be set to ...GetCurrentLevel...?
	
	}
	tWorld->FadeChannel(knPlayChannel,.25);
	while (tWorld->GetRender()->gameRunning())
	{

//==================Play Mode=====================
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

			tWorld->DrawEverything();
		}
//====================Menu Mode========================
		else if (tWorld->GetGameStatus() == knMenuMode)
		{
			tWorld->GetRender()->doMenuInput();
			tWorld->DrawEverything();	
		}
//====================Edit Mode========================
		else if (tWorld->GetGameStatus() == knEditMode)
		{
			if (tWorld->GetEditStatus() == knBuildMode)
			{
				tWorld->GetRender()->doEditInput();
				
			}

			else if (tWorld->GetEditStatus() == knMoveMode)
			{
			
				tWorld->GetRender()->doMoveInput();

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
    tWorld->ShutdownSoundEngine();
   	delete tWorld;

	return 0;
}
