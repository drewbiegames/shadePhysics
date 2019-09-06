#pragma once

#include <queue>
#include <map>
#include <functional>

#include "Singleton.h"

class Event;
class EventListener;

/*
	UI Event Poller

	Derived from Event Handling UML Diagram, Danië Van Ophem
*/

class UIEventPoller : public Uncopyable {
public:
	typedef std::queue<EventListener*> EventQueue;
	typedef std::map<int, EventListener*> ListenerMap;
	
	void RegisterEventListener(EventListener* listenerP);
	void RemoveEventListener(EventListener* lisenerP);

	//Polls Events and Calls assigned functions
	void CheckEvents();
private:
	UIEventPoller(){};
	friend class SingletonT < UIEventPoller >;

	//Friend class - access to the event queue
	friend class EventListener;
	
	EventQueue mEventQueueP;
	ListenerMap mEventListenersP;
};

typedef SingletonT<UIEventPoller> TheUIEventPoller;

