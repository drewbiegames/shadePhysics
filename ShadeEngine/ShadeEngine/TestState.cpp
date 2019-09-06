#include "TestState.h"

#include "Defines.h"

#include "StateParser.h"
#include "AssetManager.h"
#include "Utils.h"
#include "GenericEvent.h"

void TestState::Update(){
	for (std::vector<GameObject*>::iterator it = mGameObjects.begin(); it != mGameObjects.end(); it++){
		(*it)->Update();
	}
}

void TestState::Draw(){
	for (std::vector<GameObject*>::iterator it = mGameObjects.begin(); it != mGameObjects.end(); it++){
		(*it)->Draw();
	}
}

void TestState::OnEnter(){
	
	StateParser parser;
	parser.ParseState("Media/test.xml", GetStateID(), mGameObjects);

	if (!mReset){
		TheInput::Instance()->AddHandler("TestState", this);
		mReset = false;
	}

	mEventListener = new EventListener();
	mEventListener->AddFunction(Bind(&TestState::RESET, this));
}

void TestState::OnExit(){
	if (!mReset){
		TheInput::Instance()->RemoveHandler("TestState");
	}

	for (std::vector<GameObject*>::iterator it = mGameObjects.begin(); it != mGameObjects.end(); it++){
		delete *it;
		*it = nullptr;
	}
	mGameObjects.clear();

	

	TheAssetManager::Instance()->Clean();

	delete mEventListener;
	mEventListener = nullptr;
}

void TestState::OnKeyboardEvent(const SDL_KeyboardEvent& ev){
	if (ev.type == SDL_KEYDOWN
		&& ev.keysym.scancode == SDL_SCANCODE_F5){

		mEventListener->SetEvent(new GenericEvent());
	}
}

void TestState::RESET(Event* ev){
	mReset = true;
	OnExit();
	OnEnter();
}
