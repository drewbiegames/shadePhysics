#pragma once

#include "BoundingShape.h"

/*
	Base Game Object
	Cahnge: Each GameObject will be collidable 3rd Aug 2015
*/

#include "tinyxml.h"
#include "Factory.h"

class GameObject {
public:
	GameObject() : mBounds(nullptr), mDestroy(false){}
	virtual ~GameObject(){ delete mBounds; }

	virtual void Draw() = 0;
	virtual void Update() = 0;
	virtual void Clean() = 0;
	virtual void React(GameObject*) = 0;

	virtual void Load(TiXmlElement* node) = 0;

	virtual bool FlaggedForDestruction(){ return mDestroy; }
	virtual void Destroy(){ mDestroy = true; }
	
	BoundingShape* GetBounds() { return mBounds; }

protected:
	BoundingShape* mBounds;

	bool mDestroy;
};

typedef SingletonT<FactoryT<GameObject>> TheGameObjectFactory;