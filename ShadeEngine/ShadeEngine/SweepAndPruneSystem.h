#pragma once
#include "CollisionSystem.h"
#include "Singleton.h"
#include <vector>
#include "BoundingShape.h"
#include "AABB.h"
#include <set>
#include <list>

/* 
	Contianer type definitions
*/

typedef std::vector<AABB*> AABBVector;
typedef std::vector<BoundingShape*> ShapeVector;
typedef std::pair<AABB*, AABB*> AABBPair;
typedef std::list<AABBPair> PairList;

/*
	Sorting functions for the sort algorithm
*/
bool sortX(AABB* a, AABB* b);
bool sortY(AABB* a, AABB* b);
bool sortZ(AABB* a, AABB* b);

/*
	Sweep and Prune Collision system

	Sorts the AABB of each of the collidables along each axis 
	then checks collision only if the range of the AABB collides 
	along all three axis by sorting them into pairs
*/

class SweepAndPruneSystem : public CollisionSystem {
public:

	~SweepAndPruneSystem();

	virtual void RegisterCollidable(GameObject* collidable);
	virtual void UnregisterColliable(GameObject* collidable);

	void Update();

private:
	friend class Game;
	SweepAndPruneSystem();

	AABBVector mXaxis;
	AABBVector mYaxis;
	AABBVector mZaxis;

	ShapeVector mShapes;
	PairList mPossiblePairs;

	virtual void updateAABBs();
	void testRelevantCollisions();

	void addPair(AABBPair pair);
	void removePair(AABBPair pair);
	void clearPairs();
};