#include "Input.h"

#include <cassert>

#include "Game.h"
#include "MouseButtons.h"
#include "EventHandler.h"

Input::Input(){
	InitialiseJoysticks();
}

//Polls Events, quits on SDL_QUIT event
void Input::Update(){
	SDL_Event event;

	while (SDL_PollEvent(&event)){
		switch (event.type){
			case SDL_QUIT:
				TheGame::Instance()->Quit();
				break;
			case 512:
				break;
			default:
				DistrubuteEvents(event);
				break;
		}
	}
}

//Clears the EventHandler Container
void Input::Clean(){
	//GameState responsible for deleting handlers
	mEventHandlersP.clear();
}

//Adds an EventHandler
//	Param 1 - ID of the EventHandler
//	Param 2 - EventHandler
void Input::AddHandler(const std::string& id, EventHandler* handler){
	EventHandlerContainer::iterator it = mEventHandlersP.find(id);

	if (it == mEventHandlersP.end()){
		mEventHandlersP[id] = handler;
	}
}


//Remove an EventHandler
//	Param 1 - ID of EvenHandler
void Input::RemoveHandler(const std::string& id){
	EventHandlerContainer::iterator it = mEventHandlersP.find(id);

	if (it != mEventHandlersP.end()){
		mEventHandlersP.erase(it);
	}
}

//Notify each subscriber of events
//	Param 1 - SDL_Event - Polled event
void Input::DistrubuteEvents(const SDL_Event& event){
	EventHandlerContainer::iterator it = mEventHandlersP.begin();

	for (; it != mEventHandlersP.end() && !mEventHandlersP.empty(); it++){
		it->second->HandleEvent(event);
	}
}

//Return bool - true if succeded, false if error
bool Input::InitialiseJoysticks(){
	if (SDL_WasInit(SDL_INIT_JOYSTICK) == 0)
		SDL_InitSubSystem(SDL_INIT_JOYSTICK);

	if (SDL_NumJoysticks() > 0){
		for (int i = 0; i < SDL_NumJoysticks(); i++){
			SDL_JoystickOpen(i);
		}
		SDL_JoystickEventState(SDL_ENABLE);

		printf("Initialised joystick\n");
		return true;
	}
	return false;
}