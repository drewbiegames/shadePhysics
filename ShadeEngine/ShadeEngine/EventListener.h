#pragma once

#include <functional>
#include <vector>

class Event;

/*
	Event Listener Class

	Derived from Event Handling UML Diagram, Danië Van Ophem
*/

class EventListener{
public:
	typedef std::vector<std::function<void(Event*)>> FunctionContainer;
	typedef std::vector<Event*> EventConatianer;

	EventListener(){};
	
	//Bind a Function to a class
	//	Param 1 - Function name preceded by the class name
	//	Param 2 - Class name the funtion is a member of
	//Example call: Bind<Class>(&class::function, this);
	template < class FunctionClass >
	static friend std::function<void(Event*)> Bind(void(FunctionClass::*function)(Event*), FunctionClass* instance){
		return std::bind(function, instance, std::placeholders::_1);
	}

	//Call when event triggered
	void SetEvent(Event* event); 

	void AddFunction(std::function<void(Event*)> func);		// operator += ?
	void RemoveFunction(std::function<void(Event*)> func);	// operator -= ?

private:
	//Friend UI EventPoller - exclusive to this system
	friend class UIEventPoller;
	
	FunctionContainer mFunctionsP;
	EventConatianer mEventsP;
};