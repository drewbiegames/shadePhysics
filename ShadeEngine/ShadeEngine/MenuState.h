#pragma once

#include <vector>
#include <functional>
#include "GameState.h"

/*
	MenuState Interface

	Each menu state will need to setCallbacks for button clicks
*/

class MenuState : public GameState {

protected:
	virtual void setCallbacks() = 0;

};