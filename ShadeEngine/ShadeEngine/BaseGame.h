#include <SDL.h>
#include <stdio.h>

class BaseGame {
public:
	//Initilaise SDL Window
	//	Param 1 - Title of the window
	//	Param 2 - X position of the window
	//	Param 3 - Y position of the window
	//	Param 4 - Width of the window
	//	Param 5 - Height of the window
	//	Pamam 6 - Fullscreen bool
	virtual bool Init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen) = 0{
		if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS | SDL_INIT_TIMER) == 0){
			int flags = 0;

			if (fullscreen)
				flags = SDL_WINDOW_FULLSCREEN;

			mWindowP = SDL_CreateWindow(title, ypos, xpos, width, height, flags | SDL_WINDOW_OPENGL);

			if (!mWindowP){
				printf("Window initialise failure!\n");
				return false;
			}
			printf("Window initialised successfully!\n");
		}
		return true;
	}

	virtual void Render() = 0;
	virtual void Clean() = 0 { SDL_DestroyWindow(mWindowP);	}

	SDL_Window* GetWindow(){ return mWindowP; }

protected:
	SDL_Window* mWindowP;
};