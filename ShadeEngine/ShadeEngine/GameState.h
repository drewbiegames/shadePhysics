#pragma once

#include <string>
#include <vector>

#include "GameObject.h"

/*
	Game State Interface
*/

class GameState{
public:
	
	virtual void Update() = 0;
	virtual void Draw() = 0;

	virtual void OnEnter() = 0;
	virtual void OnExit() = 0;

	virtual std::string GetStateID() const = 0;

protected:
	std::vector<GameObject*> mGameObjects;
private:

};