#include "Defines.h"

#include "Game.h"
#include "Timer.h"
#include "UIEventPoller.h"
#include "SweepAndPruneSystem.h"
#include "StateManager.h"
#include "TestState.h"
#undef main

#include <stdio.h>

const int FPS = 60;
const int DELAY_TIME = int(1000.0f / FPS);

int main(int argc, char* args[]){

#ifdef _DEBUG
	//Memory Leak Checking
	int flag = _CrtSetDbgFlag(_CRTDBG_REPORT_FLAG);
	flag |= _CRTDBG_LEAK_CHECK_DF; // Turn on leak-checking bit
	_CrtSetDbgFlag(flag);
	//_CrtSetBreakAlloc(1253); // Un-comment and change value to break at orign of the leak
#endif

	//Variables for capping frame rate
	float frameStart, frameTime;
	int counter = 0;

	//Main game loop
	printf("Game init attempt...\n");
	if (TheGame::Instance()->Init(
		WINDOWNAME, 
		WINDOWPOSX, WINDOWPOSY, 
		WINDOWWIDTH, WINDOWHEIGHT, 
		WINDOWFULLSCREEN, SWEEP_AND_PRUNE_COLLISION)){

		TheStateManager::Instance()->ChangeState(TheTestState::Instance());

		TheTimer::Instance()->Initialize();
		while (TheGame::Instance()->Running()){
			frameStart = TheTimer::Instance()->GetDeltaTime();
			
			TheTimer::Instance()->Update();
			TheGame::Instance()->HandleEvents();
			TheGame::Instance()->Update();
			TheGame::Instance()->HandleCollisions();
			TheGame::Instance()->Render();
			TheUIEventPoller::Instance()->CheckEvents();

			frameTime = TheTimer::Instance()->GetDeltaTime() - frameStart;
			
			//counter++;
			//if (counter % FPS == 0 || counter % FPS == 30)	printf("FrameTime: %f\n", 1.0 / frameTime);
			
			if (frameTime < DELAY_TIME) { 
				SDL_Delay((int)(DELAY_TIME - frameTime));
			}
		}
	}
	else{
		printf("Game init failure. SDL Error: %s\n", SDL_GetError());
		return -1;
	}

	printf("Game closing...\n");
	TheGame::Instance()->Clean();

	return 0;
}