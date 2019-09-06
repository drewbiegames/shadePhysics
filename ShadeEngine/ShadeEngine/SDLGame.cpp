#include "SDLGame.h"

#include "StateManager.h"

//Initialise SDL Window and Renederer
//	Param 1 - Title of the window
//	Param 2 - X position of the window
//	Param 3 - Y position of the window
//	Param 4 - Width of the window
//	Param 5 - Height of the window
//	Pamam 6 - Fullscreen bool
bool SDLGame::Init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen){
	if (BaseGame::Init(title, xpos, ypos, width, height, fullscreen)){
		if (SDL_Init(SDL_INIT_AUDIO) == 0){
			mRendererP = SDL_CreateRenderer(mWindowP, -1, 0);

			if (mRendererP != 0){
				printf("Renderer initialised successfully!\n");
				SDL_SetRenderDrawColor(mRendererP, 0, 0, 0, 255);
			}
			else
			{
				printf("Renderer initialise failure!\n");
				return false;
			}
		}
		else{
			printf("SDL Audio failed to init!");
			return false;
		}
	}
	else{
		return false;
	}

	printf("Initialised successfully!\n");

	return true;
}

//Render game objects
void SDLGame::Render(){
	SDL_RenderClear(mRendererP);

	TheStateManager::Instance()->Draw();

	SDL_RenderPresent(mRendererP);
}

//Clean renderer and base game
void SDLGame::Clean(){
	SDL_DestroyRenderer(mRendererP);
	BaseGame::Clean();
}