#include "EventHandler.h"

//	Params 1 - SDL_Event from poller
void EventHandler::HandleEvent(const SDL_Event& event){
	switch (event.type){
		case SDL_JOYAXISMOTION:
			OnJoystickAxisEvent(event.jaxis);
			break;

		case SDL_JOYBUTTONDOWN:
		case SDL_JOYBUTTONUP:
			OnJoystickButtonEvent(event.jbutton);
			break;

		case SDL_MOUSEMOTION:
			OnMouseMotionEvent(event.motion);
			break;

		case SDL_MOUSEBUTTONDOWN:
		case SDL_MOUSEBUTTONUP:
			OnMouseButtonEvent(event.button);
			break;

		case SDL_MOUSEWHEEL:
			OnMouseWheelEvent(event.wheel);
			break;

		case SDL_KEYUP:
		case SDL_KEYDOWN:
			OnKeyboardEvent(event.key);
			break;
	}
}


