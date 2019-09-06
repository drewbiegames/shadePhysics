#pragma once

#include <SDL.h>
#include <string>
#include <map>

#include "Singleton.h"
//#include "EventHandler.h"
class EventHandler;
#include "Vector2D.h"

/*
	Input Poller Class

	ref: Lecture Slides
*/

class Input : public Uncopyable {
public:
	~Input(){};

	void Update();
	void Clean();

	void AddHandler(const std::string& id, EventHandler* handler);
	void RemoveHandler(const std::string& id);

	//Notify each event handler of the event
	void DistrubuteEvents(const SDL_Event& event);

private:
	Input();
	friend class SingletonT < Input > ;

	bool InitialiseJoysticks();

	typedef std::map<std::string, EventHandler*> EventHandlerContainer;
	EventHandlerContainer mEventHandlersP;
};

typedef SingletonT<Input> TheInput;