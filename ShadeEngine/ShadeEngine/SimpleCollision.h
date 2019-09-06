#pragma once

#include "CollisionSystem.h"

/*
	Simple Collision System
*/

class SimpleCollision : public CollisionSystem {
public:

	void Update();
private:
	friend class Game;
	SimpleCollision() {}
};