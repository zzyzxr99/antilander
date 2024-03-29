#include <iostream>
#include "Structs.h"
#include "Render.h"
#include "GameWorld.h"

using namespace std;

extern GameWorld *tWorld;
extern GameWorld *mScore;

void Render::doInput()
{
	plIn.leftClick= false;
	plIn.rightClick= false;
	while (SDL_PollEvent(&mEvent))
	{
		if(mEvent.type == SDL_MOUSEMOTION)
		{
			plIn.mouseMove.x = mEvent.motion.x;
			plIn.mouseMove.y = mEvent.motion.y;
		}
		if (mEvent.type == SDL_QUIT)
		{
			gameState= false;
		}

		if(mEvent.type == SDL_KEYDOWN)
		{
			plIn.keyPress = mEvent.key.keysym.sym;
			if (!mConsole)
			{
			switch(plIn.keyPress)
				{
//===========Menu / Pause========================
				case SDLK_ESCAPE :
					if(mPause == false)
					{
						tWorld->SetGameStatus(knMenuMode);
						tWorld->FadeChannel(knPlayChannel,.25);
						tWorld->PlaySoundLoop(knSLMenu,knMenuChannel,.5);
						
					
						mPause = true;
					}
					else
					{
						break;
					}
					break;
#ifndef	_RELEASE				
				case SDLK_BACKQUOTE :
					if(mConsole == true)
					{
						mConsole = false;
					}
					else
					{
						mConsole = true;
					}
					break;
#endif
				}
			}
#ifndef _RELEASE
			else
			{
				switch(plIn.keyPress)
				{
				case SDLK_BACKQUOTE :
					if(mConsole == true)
					{
						mConsole = false;
					}
					else
					{
						mConsole = true;
					}
					break;
				case SDLK_a :
					plIn.keyP = 'a';
					break;
				case SDLK_b :
					plIn.keyP = 'b';
					break;
				case SDLK_c :
					plIn.keyP = 'c';
					break;
				case SDLK_d :
					plIn.keyP = 'd';
					break;
				case SDLK_e :
					plIn.keyP = 'e';
					break;
				case SDLK_f :
					plIn.keyP = 'f';
					break;
				case SDLK_g :
					plIn.keyP = 'g';
					break;
				case SDLK_h :
					plIn.keyP = 'h';
					break;
				case SDLK_i :
					plIn.keyP = 'i';
					break;
				case SDLK_j :
					plIn.keyP = 'j';
					break;
				case SDLK_k :
					plIn.keyP = 'k';
					break;
				case SDLK_l :
					plIn.keyP = 'l';
					break;
				case SDLK_m :
					plIn.keyP = 'm';
					break;
				case SDLK_n :
					plIn.keyP = 'n';
					break;
				case SDLK_o :
					plIn.keyP = 'o';
					break;
				case SDLK_p :
					plIn.keyP = 'p';
					break;
				case SDLK_q :
					plIn.keyP = 'q';
					break;
				case SDLK_r :
					plIn.keyP = 'r';
					break;
				case SDLK_s :
					plIn.keyP = 's';
					break;
				case SDLK_t :
					plIn.keyP = 't';
					break;
				case SDLK_u :
					plIn.keyP = 'u';
					break;
				case SDLK_v :
					plIn.keyP = 'v';
					break;
				case SDLK_w :
					plIn.keyP = 'w';
					break;
				case SDLK_x :
					plIn.keyP = 'x';
					break;
				case SDLK_y :
					plIn.keyP = 'y';
					break;
				case SDLK_z :
					plIn.keyP = 'z';
					break;
				case SDLK_0 :
					plIn.keyP = '0';
					break;
				case SDLK_1 :
					plIn.keyP = '1';
					break;
				case SDLK_2 :
					plIn.keyP = '2';
					break;
				case SDLK_3 :
					plIn.keyP = '3';
					break;
				case SDLK_4 :
					plIn.keyP = '4';
					break;
				case SDLK_5 :
					plIn.keyP = '5';
					break;
				case SDLK_6 :
					plIn.keyP = '6';
					break;
				case SDLK_7 :
					plIn.keyP = '7';
					break;
				case SDLK_8 :
					plIn.keyP = '8';
					break;
				case SDLK_9 :
					plIn.keyP = '9';
					break;
				case SDLK_BACKSPACE :
					plIn.keyP = '\b';
					break;
				case SDLK_RETURN :
					plIn.keyP = '\r';
					break;
				case SDLK_SPACE :
					plIn.keyP = ' ';
					break;
				case SDLK_DELETE :
					plIn.keyP = '$';
					break;
				case SDLK_PERIOD :
					plIn.keyP = '.';
					break;
				default :
					plIn.keyP = '!';
				}
			}
#endif
		}

		if(mEvent.type == SDL_MOUSEBUTTONDOWN)
		{
			plIn.mousePress.button = mEvent.button.button;
			if((plIn.mousePress.button == SDL_BUTTON_LEFT))
			{
				plIn.leftClick = true;
				plIn.tlclicked = true;
			}


			if(plIn.mousePress.button == SDL_BUTTON_RIGHT )
			{
				plIn.rightClick = true;
				plIn.trclicked = true;
			}
		}

		if(mEvent.type == SDL_MOUSEBUTTONUP)
		{
			plIn.mousePress.button = mEvent.button.button;
			if(plIn.mousePress.button == SDL_BUTTON_LEFT)
			{
				plIn.tlclicked = false;
				plIn.leftClick = false;
			}

			if(plIn.mousePress.button == SDL_BUTTON_RIGHT)
			{
				plIn.trclicked = false;
				plIn.rightClick = false;
			}
		}

		if(plIn.leftClick == 1)
			cout << "left clicked\n";
		if(plIn.rightClick == 1)
			cout << "right clicked\n";
	}
}


void Render::doEditInput()
{
	plIn.leftClick= false;
	plIn.midClick= false;
	plIn.rightClick= false;
	while (SDL_PollEvent(&mEvent))
	{
		if(mEvent.type == SDL_MOUSEMOTION)
		{
			plIn.mouseMove.x = mEvent.motion.x;
			plIn.mouseMove.y = mEvent.motion.y;
		}
		if(mEvent.type == SDL_QUIT)
		{
			gameState= false;
		}

		if(mEvent.type == SDL_KEYDOWN)
		{
			plIn.keyPress = mEvent.key.keysym.sym;
			if(plIn.keyPress == SDLK_ESCAPE)
			{
				gameState = false;
			}
			if(plIn.keyPress == SDLK_e)
			{
				doneBuildmode = true;
			}
		}

		if(mEvent.type == SDL_MOUSEBUTTONDOWN)
		{
			plIn.mousePress.button = mEvent.button.button;
			if((plIn.mousePress.button == SDL_BUTTON_LEFT))
			{
				plIn.leftClick = true;
				plIn.tlclicked = true;
			}


			if(plIn.mousePress.button == SDL_BUTTON_RIGHT )
			{
				plIn.rightClick = true;
				plIn.trclicked = true;
			}

			if(plIn.mousePress.button == SDL_BUTTON_MIDDLE)
			{
				plIn.midClick = true;
				plIn.tmclicked = true;
				doneBuildmode = true;
			}
		}

		else if(mEvent.type == SDL_MOUSEBUTTONUP)
		{
			plIn.mousePress.button = mEvent.button.button;
			if(plIn.mousePress.button == SDL_BUTTON_LEFT)
			{
				plIn.tlclicked = false;
				plIn.leftClick = false;
			}
			if(plIn.mousePress.button == SDL_BUTTON_RIGHT)
			{
				plIn.trclicked = false;
				plIn.rightClick = false;
			}

			if(plIn.mousePress.button == SDL_BUTTON_MIDDLE)
			{
				plIn.midClick = false;
				plIn.tmclicked = false;
			}
		}

	}
	if (plIn.leftClick)
	{
		tWorld->AddEditLevelPoint(plIn.mouseMove);
	}

	if (plIn.rightClick)
	{
		tWorld->AddEditPadPoint(plIn.mouseMove);
	}

	if (doneBuildmode)
	{
		doneBuildmode = false;
		tWorld->EndEditLvlPts(plIn.mouseMove);
		tWorld->SetEditStatus(knMoveMode);
	}
}
void Render::doMenuInput()
{
	plIn.leftClick= false;
	plIn.rightClick= false;
	while (SDL_PollEvent(&mEvent))
	{
		if(mEvent.type == SDL_MOUSEMOTION)
		{
			plIn.mouseMove.x = mEvent.motion.x;
			plIn.mouseMove.y = mEvent.motion.y;
		}
		if(mEvent.type == SDL_QUIT)
		{
			
			gameState= false;
		}

		if(mEvent.type == SDL_KEYDOWN)
		{
			plIn.keyPress = mEvent.key.keysym.sym;
			if(plIn.keyPress == SDLK_ESCAPE)
			{
				if (mPause)
				{
					mPause = false;
					tWorld->SetGameStatus(knPlayMode);
					tWorld->FadeChannel(knMenuChannel,.5);
					tWorld->PlaySoundLoop(knSLPlay,knPlayChannel,.5);
					tWorld->ResetTimers();
				}
			}
			else if(plIn.keyPress == SDLK_q)
			{

				tWorld->PlaySoundEffect(knSEMenuClick);
				gameState = false;
			}
			else if(plIn.keyPress == SDLK_n)
			{
				mStart = true;
				mPause = false;
				tWorld->InitLevel();
				tWorld->GetScore()->ClearScore();
				tWorld->SetGameStatus(knPlayMode);
				tWorld->FadeChannel(knMenuChannel,.5);
				tWorld->PlaySoundLoop(knSLPlay,knPlayChannel,.5);
				tWorld->PlaySoundEffect(knSEMenuClick);
			}
#ifndef _RELEASE
			else if(plIn.keyPress == SDLK_e)
			{
				// needs to change gamestatus to editor mode???
				if(mEdit == false)
				{
					mEdit = true;
					mPause = false;
				}
			}
#endif
		}
		if(mEvent.type == SDL_MOUSEBUTTONDOWN)
		{
			plIn.mousePress.button = mEvent.button.button;
			if((plIn.mousePress.button == SDL_BUTTON_LEFT))
			{
				plIn.leftClick = true;
				plIn.tlclicked = true;
			}


			if(plIn.mousePress.button == SDL_BUTTON_RIGHT )
			{
				plIn.rightClick = true;
				plIn.trclicked = true;
			}
		}

		if(mEvent.type == SDL_MOUSEBUTTONUP)
		{
			plIn.mousePress.button = mEvent.button.button;
			if(plIn.mousePress.button == SDL_BUTTON_LEFT)
			{
				plIn.tlclicked = false;
				plIn.leftClick = false;
			}

			if(plIn.mousePress.button == SDL_BUTTON_RIGHT)
			{
				plIn.trclicked = false;
				plIn.rightClick = false;
			}
		}
	}
	if(mEdit)
	{
		mEdit = false;
		tWorld->GetEditLevel()->ClearLevel();
		tWorld->SetGameStatus(knEditMode);
		tWorld->SetEditStatus(knBuildMode);
	}
	if(getMouse().x > kMenuDrawX && getMouse().x < kMenuDrawX+kMenuWidth && getMouse().y > kMenuDrawY+50 && getMouse().y < kMenuDrawY+70 && plIn.leftClick == true)
	{
		cout << "Quit highlighted!!" << endl;
		tWorld->PlaySoundEffect(knSEMenuClick);
		gameState = false;
	}
#ifndef _RELEASE
	else if(getMouse().x > kMenuDrawX && getMouse().x < kMenuDrawX+kMenuWidth && getMouse().y > kMenuDrawY+75 && getMouse().y < kMenuDrawY+95 && plIn.leftClick == true)
	{
		if(mEdit == false)
		{
			mEdit = true;
			mPause = false;
		}
	}
#endif
	else if(getMouse().x > kMenuDrawX && getMouse().x < kMenuDrawX+kMenuWidth && getMouse().y > kMenuDrawY+25 && getMouse().y < kMenuDrawY+45 && plIn.leftClick == true)
	{
		cout << "Start highlighted!!" << endl;
		mStart = true;
		mPause = false;
		tWorld->GetScore()->ClearScore();
		tWorld->InitLevel();
		tWorld->SetGameStatus(knPlayMode);
		tWorld->FadeChannel(knMenuChannel,.5);
		tWorld->PlaySoundLoop(knSLPlay,knPlayChannel,.5);
		tWorld->PlaySoundEffect(knSEMenuClick);
		
	}
	
}

void Render::doMoveInput()
{
	plIn.leftClick= false;
	plIn.midClick= false;
	plIn.rightClick= false;
	while (SDL_PollEvent(&mEvent))
	{
		if(mEvent.type == SDL_MOUSEMOTION)
		{
			plIn.mouseMove.x = mEvent.motion.x;
			plIn.mouseMove.y = mEvent.motion.y;
		}
		if (mEvent.type == SDL_QUIT)
		{
			gameState= false;
		}

		if(mEvent.type == SDL_KEYDOWN)
		{
			plIn.keyPress = mEvent.key.keysym.sym;
			if(plIn.keyPress == SDLK_ESCAPE)
			{
				gameState = false;
			}
			if(plIn.keyPress == SDLK_x)
			{
				exitEditmode = true;
			}
		}

		if(mEvent.type == SDL_MOUSEBUTTONDOWN)
		{
			plIn.mousePress.button = mEvent.button.button;
			if((plIn.mousePress.button == SDL_BUTTON_LEFT))
			{
				plIn.leftClick = true;
				plIn.tlclicked = true;
			}


			if(plIn.mousePress.button == SDL_BUTTON_RIGHT )
			{
				plIn.rightClick = true;
				plIn.trclicked = true;
			}

			if(plIn.mousePress.button == SDL_BUTTON_MIDDLE)
			{
				plIn.midClick = true;
				plIn.tmclicked = true;
			}

		}
		if(mEvent.type == SDL_MOUSEBUTTONUP)
		{
			plIn.mousePress.button = mEvent.button.button;
			if(plIn.mousePress.button == SDL_BUTTON_LEFT)
			{
				plIn.tlclicked = false;
				plIn.leftClick = false;
			}
			if(plIn.mousePress.button == SDL_BUTTON_RIGHT)
			{
				plIn.trclicked = false;
				plIn.rightClick = false;
			}

			if(plIn.mousePress.button == SDL_BUTTON_MIDDLE)
			{
				plIn.midClick = false;
				plIn.tmclicked = false;
			}
		}
	}

	if(exitEditmode)
	{	
		exitEditmode = false;
		tWorld->GetEditLevel()->MakePadPtsFromTerrainPts();
		Level *curLevel = tWorld->GetCurrentLevel();
		Level *editLevel = tWorld->GetEditLevel();
		editLevel->SetGunStartPad(0);
		curLevel->Clone(editLevel);
		tWorld->InitLevel();
		tWorld->SetGameStatus(knPlayMode);
	}
}