#include "Timer.h"

#include <SDL.h>

void Timer::Initialize(){
	mOldTicks = SDL_GetTicks();
}

//Gets called every frame, keeps constant time
void Timer::Update(){
	unsigned int newTicks = SDL_GetTicks();
	unsigned int difference = newTicks - mOldTicks;

	mDeltaTime = static_cast<float>(difference);
	mDeltaTime /= 1000;

	mOldTicks = newTicks;
}