#pragma once

#include <vector>

#include "GameState.h"
#include "Singleton.h"

/*
	StateManager Singleton
*/

class StateManager : public Uncopyable {
public:
	//Removes current state then adds new state
	void ChangeState(GameState* state);
	//Adds new state without removing old state
	void PushState(GameState* state);
	//Removes current state
	void PopState();					 

	//Calls Current Class Functions of same name
	void Update();
	void Draw();

	//Set running to flase, cleans current state and quits
	void Quit();

	std::string GetStateID(){ return mStateStack.back()->GetStateID(); }

private:
	StateManager(){}
	friend class SingletonT < StateManager >;

	std::vector<GameState*> mStateStack;
};

typedef SingletonT<StateManager> TheStateManager;