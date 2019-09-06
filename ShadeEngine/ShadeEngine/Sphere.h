#pragma once

#include "BoundingShape3D.h"
/*
	3D Sphere Collider
*/

class Sphere : public BoundingShape3D {

public:
	Sphere() : BoundingShape3D(), Radius(0.0f) {}
	Sphere(GameObject* obj, Vector3Df& pos, Vector3Df& vel, Quaternion& rot, float radius) 
		: BoundingShape3D(obj, pos, vel, rot), Radius(radius) {}

	float Radius;

	virtual bool Collide(Sphere& other);
	virtual bool Collide(Vector3Df& other);
	virtual bool Collide(Capsule& other);

	virtual void CalculateAABB();
	
private:
	virtual bool Collide(AABB& other) { return false; }
	virtual bool Collide(OBB& other) { return false; }
};