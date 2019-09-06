#pragma once


#include "Vector2D.h"
#include "Circle.h"
#include "Rectangle.h"

/*
	Collidable Interface
	Allows object to react to collision
*/

class Collidable {
public:
	Collidable() : mBounds(nullptr) {}
	virtual ~Collidable(){ 
		delete mBounds;
	}

	virtual void React(Collidable*) = 0;
	BoundingShape* GetBounds() { return mBounds; }

protected:
	BoundingShape* mBounds;
};