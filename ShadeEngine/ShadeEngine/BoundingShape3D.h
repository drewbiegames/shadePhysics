#pragma once

#include "BoundingShape.h"
#include "Vector3D.h"
#include "Quaternion.h"
#include "AABB.h"


class BoundingShape3D : public BoundingShape {
public:
	BoundingShape3D() : Position(nullptr), Velocity(nullptr), Rotation(nullptr), AxisAlign() {}

	BoundingShape3D(GameObject* obj, Vector3Df& pos, Vector3Df& vel, Quaternion& rot)
		: BoundingShape(obj), Position(&pos), Velocity(&vel), Rotation(&rot) {}

	virtual ~BoundingShape3D(){	}

	Vector3Df* Position;
	Vector3Df* Velocity;
	Quaternion* Rotation;

	AABB AxisAlign;
	
	virtual void CalculateAABB() = 0;
	AABB* getAABB(){ return &AxisAlign; }

	virtual bool Collide(AABB& other) = 0;
	virtual bool Collide(OBB& other) = 0;
	virtual bool Collide(Sphere& other) = 0;
	virtual bool Collide(Vector3Df& other) = 0;
	virtual bool Collide(Capsule& other) = 0;

private:
	virtual bool Collide(Circle& other){ return false; }
	virtual bool Collide(MyRectangle& other){ return false; }
	virtual bool Collide(float x, float y){ return false; }
};