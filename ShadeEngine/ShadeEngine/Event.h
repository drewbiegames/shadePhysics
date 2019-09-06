#pragma once

#include "Factory.h"

/*
	Event Class
	Used by Event Pollers
	A function is bound to an Event object and sent to the event poller
	Dervied class could include any paramaters for the function

	Derived from Event Handling UML Diagram, Danië Van Ophem
*/

class Event{
public:
	virtual ~Event() = 0 {};
};

typedef SingletonT<FactoryT<Event>> TheEventFactory;

//My Notes On how to use the Event Handling system
	//Event is an object you create when an event happens
	//Onclick (or similar event) will inherit from this
	//In button
		//Public variable EventListener
	//In State
		//bind a function in the state load
		//Resigter functions to the EventListener
	//call SetEvent() when triggered in button

	