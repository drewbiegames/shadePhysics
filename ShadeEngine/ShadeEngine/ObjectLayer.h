#pragma once

#include <vector>

#include "Layer.h"
#include "SDLGameObject.h"

/*
	Object Layer Class

	ref: SDL Game Development, Shaun Mitchell

	not currently implemented - tested
*/

class ObjectLayer : public Layer {
public:
	void OnEnter();

	virtual void Update();
	virtual void Draw();

	std::vector<SDLGameObject*>* GetGameObject(){ return &mGameObjectsP; }

private:
	std::vector<SDLGameObject*> mGameObjectsP;
};