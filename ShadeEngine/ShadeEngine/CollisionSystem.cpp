#include "CollisionSystem.h"

//Adds Collidable to the container
void CollisionSystem::RegisterCollidable(GameObject* collidable){
	int id = (int)(collidable);

	CollidableMap::iterator it = mCollidables.find(id);

	if (it == mCollidables.end()){
		mCollidables[id] = collidable;
	}
}

//Removes Collidable to the container
void CollisionSystem::UnregisterColliable(GameObject* collidable){
	int id = (int)(collidable);

	CollidableMap::iterator it = mCollidables.find(id);

	if (it != mCollidables.end()){
		mCollidables.erase(it);
	}
}