#pragma once

class GameObject;
class Circle;
class MyRectangle;
class AABB;
class OBB;
class Sphere;
class Capsule;
#include "Vector3D.h"

class BoundingShape {
public:
	BoundingShape() : Object(nullptr) {}
	BoundingShape(GameObject* obj) : Object(obj) {}
	virtual ~BoundingShape(){}

	GameObject* Object;

	bool Collide(BoundingShape* other);
	virtual AABB* getAABB() = 0;
	virtual void CalculateAABB() = 0;

	virtual bool Collide(Circle& other) = 0;
	virtual bool Collide(MyRectangle& other) = 0;
	virtual bool Collide(float x, float y) = 0;

	virtual bool Collide(AABB& other) = 0;
	virtual bool Collide(OBB& other) = 0;
	virtual bool Collide(Sphere& other) = 0;
	virtual bool Collide(Vector3Df& point) = 0;
	virtual bool Collide(Capsule& other) = 0;
private:

};