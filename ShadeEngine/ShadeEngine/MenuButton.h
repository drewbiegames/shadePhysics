#pragma once

#include <functional>

#include "SDLGameObject.h"
#include "EventHandler.h"
#include "EventListener.h"
#include "SpriteSheet.h"

/*
	Menu Button Class

	SDL Game Object for display
	Event Handler for game event handleing
*/

class MenuButton : public SDLGameObject, public EventHandler {
public:
	MenuButton();

	//Draw Menu Button
	virtual void Draw();
	//Update current frame
	virtual void Update();
	//Clean object pointers and unregister from systems
	virtual void Clean();

	virtual void React(GameObject*){}

	//Event Handling for mouse buttons - on click call event
	virtual void OnMouseButtonEvent(const SDL_MouseButtonEvent& event);
	//Event Handling for mouse motion - on mouse over change frame
	virtual void OnMouseMotionEvent(const SDL_MouseMotionEvent& event);

	//Public as easy of access from any state
	EventListener* mEventListener;

	//Load from hard coded variables
	virtual void Load(int x, int y, int width, int height, std::string textureID);

	//Load from XML Node
	virtual void Load(TiXmlElement* node);

private:

	enum buttonState{
		MOUSEOUT = 0,
		MOUSEOVER = 1,
		CLICKED = 2
	};

	int mCurrentFrame;

	SpriteSheet* mSpriteSheetP;
};