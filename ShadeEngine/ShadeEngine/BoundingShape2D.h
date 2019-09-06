#pragma once

#include "BoundingShape.h"
#include "Vector2D.h"


/*
	Base Bounding Shape
	Used for collision
*/

class BoundingShape2D : public BoundingShape {
public:
	BoundingShape2D() {}
	BoundingShape2D(GameObject* obj, Vector2Df& pos, Vector2Df& vel) 
		: BoundingShape(obj), Position(&pos), Velocity(&vel) {}

	virtual ~BoundingShape2D(){};

	Vector2Df* Position;
	Vector2Df* Velocity;
	
	virtual bool Collide(Circle& other) = 0;
	virtual bool Collide(MyRectangle& other) = 0;
	virtual bool Collide(float x, float y) = 0;


private:

	virtual bool Collide(AABB& other) { return false; }
	virtual bool Collide(Sphere& other) { return false; }
	virtual bool Collide(Vector3Df& point) { return false; }
	virtual bool Collide(Capsule& other) { return false; }
	virtual bool Collide(OBB& other){ return false; }
	
	AABB* getAABB(){ return nullptr; }
	void CalculateAABB(){}
};