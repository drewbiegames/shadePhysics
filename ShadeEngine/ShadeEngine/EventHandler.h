#pragma once

/*
	Base Class EventHandler

	ref: Class Slides
*/

#include "Input.h"

class EventHandler {
public:
	virtual ~EventHandler(){};

	//Distributes Events to correct function for the type
	void HandleEvent(const SDL_Event& event);
	
protected:

	//To be overridden when used by base class
	virtual void OnKeyboardEvent(const SDL_KeyboardEvent&){}
	virtual void OnMouseMotionEvent(const SDL_MouseMotionEvent&){}
	virtual void OnMouseButtonEvent(const SDL_MouseButtonEvent&){}
	virtual void OnMouseWheelEvent(const SDL_MouseWheelEvent&){}
	virtual void OnJoystickAxisEvent(const SDL_JoyAxisEvent&){}
	virtual void OnJoystickButtonEvent(const SDL_JoyButtonEvent&){}
};