#pragma once

#include <map>

#include "GameObject.h"

/*
	Collision System Interface
*/

typedef std::map<int, GameObject*> CollidableMap;

class CollisionSystem {
public:
	//Checks all the objects against one another
	virtual void Update() = 0;
	virtual ~CollisionSystem(){}

	//Add collidable to the list
	virtual void RegisterCollidable(GameObject* collidable);
	//Remove colliable from the list
	virtual void UnregisterColliable(GameObject* collidable);
	
protected:
	
	CollidableMap mCollidables;
};

enum CollisionSystems{
	SIMPLE_COLLISION,
	SWEEP_AND_PRUNE_COLLISION,
	SAT3D_COLLISION
};