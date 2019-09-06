#pragma once

#include <vector>

#include "Singleton.h"
#include "CollisionSystem.h"
class BaseGame;

/*
	Game Singleton
	
	Function in this class are used in the Main Game Loop
*/

class Game : public Uncopyable {
public:
	~Game(){}

	//Initilise SDL, Create Window
	virtual bool Init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen, CollisionSystems collision);

	virtual void Render();
	void Update();
	void HandleEvents();
	void HandleCollisions();
	virtual void Clean();

	//Set Running to false
	void Quit();

	//Getters
	bool Running() { return mRunning; }
	int GetGameWidth() const { return mGameWidth; }
	int GetGameHeight() const { return mGameHeight;  }
	CollisionSystem* GetCollisionSystem() { return mCollision; }

private:
	Game(){}
	friend class SingletonT<Game>;
	
	//Window size
	int mGameWidth,
		mGameHeight;

	bool mRunning;

	BaseGame* mGame;

	void initCollisionSystem(CollisionSystems sys);
	CollisionSystem* mCollision;
};

typedef SingletonT<Game> TheGame;