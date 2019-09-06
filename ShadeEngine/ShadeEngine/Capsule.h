#pragma once

#include "BoundingShape3D.h"
#include "LineSeg.h"

/*
	3D Capsule collider
*/

class Capsule : public BoundingShape3D {
public:
	Capsule() : BoundingShape3D(), L(), R(0.0f) {}
	Capsule(GameObject* obj, Vector3Df& pos, Vector3Df& vel, Quaternion& rot, 
			Vector3Df P0, Vector3Df P1, float radius) 
		: BoundingShape3D(obj, pos, vel, rot), L(P0, P1), R(radius) {}

	LineSeg L;
	float R;

	void CalculateAABB();

	bool Collide(AABB& other){ return false; }
	bool Collide(Sphere& other);
	bool Collide(Vector3Df& other);
	bool Collide(Capsule& other) { /*TO DO*/return false; }
	bool Collide(OBB& other){ /*TO DO*/return false; }
};