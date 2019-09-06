#include "StateManager.h"

#include "Timer.h"

//Removes current state, changes state
//	Param 1 - GameState* - State to change to
//Will quit on failer
void StateManager::ChangeState(GameState* state){
	if (state){
		if (!mStateStack.empty()){
			mStateStack.back()->OnExit();
			mStateStack.pop_back();
		}
		mStateStack.push_back(state);
		mStateStack.back()->OnEnter();
	}
	else
		Quit();
}

//Change State, without removing current state
//	Param 1 - GameState* - State to change to
void StateManager::PushState(GameState* state){
	if (state){
		mStateStack.push_back(state);
		mStateStack.back()->OnEnter();
	}
	else
		Quit();
}

//Remove Current State, switches back to previous state
void StateManager::PopState(){
	mStateStack.back()->OnExit();
	mStateStack.pop_back();
}

// Calls top states Update()
void StateManager::Update(){
	if (mStateStack.size() < 1){
		//error
		throw("Add Error Codes Here! No State on stack!");
		Quit();
	}
	else{
		mStateStack.back()->Update();
	}
}

// Calls top states Draw()
void StateManager::Draw(){
	if (mStateStack.size() < 1){
		//error
		throw("Add Error Codes Here! No State on stack!");
		Quit();
	}
	else{
		mStateStack.back()->Draw();
	}
}

//Sets Running to false, cleaning the current states exiting the game
void StateManager::Quit(){
	for (unsigned int ii = 0; mStateStack.size(); ii++){
		mStateStack.back()->OnExit();
		mStateStack.pop_back();
	}
}