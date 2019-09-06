#include "SimpleCollision.h"

//Tests all registered Collidables against each other and have them react if colliding.
void SimpleCollision::Update(){
	for (CollidableMap::iterator it = mCollidables.begin(); it != mCollidables.end() && !mCollidables.empty(); ++it){
		CollidableMap::iterator jt = it;
		++jt;
		for (; jt != mCollidables.end() && !mCollidables.empty(); ++jt){
			if (it->second->GetBounds()->Collide(jt->second->GetBounds())){
				it->second->React(jt->second);
				jt->second->React(it->second);
			}
		}
	}
}