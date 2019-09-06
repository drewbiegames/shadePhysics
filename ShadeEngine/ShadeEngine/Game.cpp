#include "Defines.h"
#include "Game.h"
#include "Input.h"
#include "GLGame.h"
#include "StateManager.h"
#include "Factory.h"

#include "SimpleCollision.h"
#include "SweepAndPruneSystem.h"

#include <stdio.h>

//Initilise SDL and create window
//	Param 1 - Title of the window
//	Param 2 - X position of the window
//	Param 3 - Y position of the window
//	Param 4 - Width of the window
//	Param 5 - Height of the window
//	Pamam 6 - Fullscreen bool
bool Game::Init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen, CollisionSystems collision){
	mGameHeight = height;
	mGameWidth = width;

	mGame = TheGLGame::Instance();
	mGame->Init(title, xpos, ypos, width, height, fullscreen);

	printf("Initialised successfully!\n");
	mRunning = true;

	mGameHeight = height;
	mGameWidth = width;

	initCollisionSystem(collision);

	return true;
}

//Render the game
void Game::Render(){
	mGame->Render();
}

//Clean all systems
void Game::Clean(){
	printf("Cleaning Game!\n");
	TheStateManager::Instance()->Quit();
	TheInput::Instance()->Clean();

	mGame->Clean();
	SDL_Quit();
}

//Updates input poller
void Game::HandleEvents(){
	TheInput::Instance()->Update();
}

void Game::HandleCollisions(){
	if (mCollision)	mCollision->Update();
}

//Updates current state
void Game::Update(){
	TheStateManager::Instance()->Update();
}

//Quit bool to false, quits the game
void Game::Quit(){
	mRunning = false;
	delete mCollision;
	mCollision = nullptr;
}

void Game::initCollisionSystem(CollisionSystems sys){
	switch(sys){
		case SIMPLE_COLLISION:
			mCollision = new SimpleCollision();
			break;
		case SWEEP_AND_PRUNE_COLLISION:
			mCollision = new SweepAndPruneSystem();
			break;
		default:
			break;
	}
}