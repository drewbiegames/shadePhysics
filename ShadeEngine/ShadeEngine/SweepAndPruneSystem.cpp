#include "SweepAndPruneSystem.h"
#include "Utils.h"
#include <algorithm>

SweepAndPruneSystem::SweepAndPruneSystem(){
}


SweepAndPruneSystem::~SweepAndPruneSystem(){

}

void SweepAndPruneSystem::RegisterCollidable(GameObject* collidable){
	if (BoundingShape* shape = dynamic_cast<BoundingShape*>(collidable->GetBounds())){
		mShapes.push_back(shape);
		mXaxis.push_back(shape->getAABB());
		mYaxis.push_back(shape->getAABB());
		mZaxis.push_back(shape->getAABB());
	}
}

void SweepAndPruneSystem::UnregisterColliable(GameObject* collidable){
	ShapeVector::iterator it = mShapes.begin();

	for (; it != mShapes.end(); it++){
		if ((*it)->Object == collidable){
			mShapes.erase(it);
			break;
		}
	}

	AABBVector::iterator jt = mXaxis.begin();

	for (; jt != mXaxis.end(); jt++){
		if ((*jt)->Object == collidable){
			mXaxis.erase(jt);
			break;
		}
	}

	jt = mYaxis.begin();

	for (; jt != mYaxis.end(); jt++){
		if ((*jt)->Object == collidable){
			mYaxis.erase(jt);
			break;
		}
	}

	jt = mZaxis.begin();

	for (; jt != mZaxis.end(); jt++){
		if ((*jt)->Object == collidable){
			mZaxis.erase(jt);
			break;
		}
	}
}

void SweepAndPruneSystem::updateAABBs(){
	for (ShapeVector::iterator it = mShapes.begin(); it != mShapes.end(); it++){
		if ((*it) != nullptr){
			(*it)->CalculateAABB();
		}
	}
}

void SweepAndPruneSystem::Update(){
	if (mShapes.size() > 1){
		updateAABBs();

		std::sort(mXaxis.begin(), mXaxis.end(), sortX);
		std::sort(mYaxis.begin(), mYaxis.end(), sortY);
		std::sort(mZaxis.begin(), mZaxis.end(), sortZ);

		AABBVector::iterator it = mXaxis.begin();
		for (; it != mXaxis.end() - 1; it++){
			AABBVector::iterator jt = it + 1;
			for (; jt != mXaxis.end(); jt++){
				AABBPair pair(*it, *jt);
				if (util::RangeIntersect((*it)->Max.X, (*it)->Min.X, (*jt)->Max.X, (*jt)->Min.X)){
					addPair(pair);
				}
				else {
					removePair(pair);
				}
			}
		}

		it = mYaxis.begin();
		for (; it != mYaxis.end() - 1; it++){
			AABBVector::iterator jt = it + 1;
			for (; jt != mYaxis.end(); jt++){
				AABBPair pair(*it, *jt);
				if (util::RangeIntersect((*it)->Max.Y, (*it)->Min.Y, (*jt)->Max.Y, (*jt)->Min.Y)){
					addPair(pair);
				}
				else {
					removePair(pair);
				}
			}
		}

		it = mZaxis.begin();
		for (; it != mZaxis.end() - 1; it++){
			AABBVector::iterator jt = it + 1;
			for (; jt != mZaxis.end(); jt++){
				AABBPair pair(*it, *jt);
				if (util::RangeIntersect((*it)->Max.Z, (*it)->Min.Z, (*jt)->Max.Z, (*jt)->Min.Z)){
					addPair(pair);
				}
				else {
					removePair(pair);
				}
			}
		}

		testRelevantCollisions();
		clearPairs();
	}
}

void SweepAndPruneSystem::testRelevantCollisions(){
	if (mPossiblePairs.size() >= 1){
		PairList::iterator it = mPossiblePairs.begin();

		for (; it != mPossiblePairs.end(); it++){
			BoundingShape* oneBounds = it->first->Object->GetBounds();
			BoundingShape* twoBounds = it->second->Object->GetBounds();
			if (oneBounds->Collide(twoBounds)){
				oneBounds->Object->React(twoBounds->Object);
				twoBounds->Object->React(oneBounds->Object);
			}
		}

	}
}

void SweepAndPruneSystem::addPair(AABBPair pair){
	PairList::iterator it = std::find(mPossiblePairs.begin(), mPossiblePairs.end(), pair);

	if (it == mPossiblePairs.end()){
		mPossiblePairs.push_back(pair);
	}
}

void SweepAndPruneSystem::removePair(AABBPair pair){
	PairList::iterator it = std::find(mPossiblePairs.begin(), mPossiblePairs.end(), pair);

	if (it != mPossiblePairs.end()){
		mPossiblePairs.remove(*it);
	}
}

void SweepAndPruneSystem::clearPairs(){
	mPossiblePairs.clear();
}

bool sortX(AABB* a, AABB* b){
	return (a->Min.X) < (b->Min.X);
};

bool sortY(AABB* a, AABB* b){
	return (a->Min.Y) < (b->Min.Y);
};

bool sortZ(AABB* a, AABB* b){
	return (a->Min.Z) < (b->Min.Z);
};

