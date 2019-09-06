#pragma once

#include "BoundingShape3D.h"
#include "Matrix3D.h"

class OBB : public BoundingShape3D {
public:
	OBB();
	OBB(GameObject* obj, Vector3Df& pos, Vector3Df& vel, Quaternion& rot, Vector3Df halfSize);

	virtual void CalculateAABB();

	void Draw();
	virtual void CalculateOBB();

	virtual bool Collide(OBB& other);

	Vector3Df corner(unsigned int ii){ return mCorners[ii]; }

private:
	Vector3Df mAxes[3];
	Vector3Df mCorners[8];
	Vector3Df mHalfSize;

	virtual bool Collide(Circle& other) { return false; };
	virtual bool Collide(MyRectangle& other) { return false; };
	virtual bool Collide(float x, float y) { return false; };
	
	// TODO: THESE!!!
	virtual bool Collide(AABB& other) { return false; }
	virtual bool Collide(Sphere& other) { return false; }
	virtual bool Collide(Vector3Df& other) { return false; }
	virtual bool Collide(Capsule& other) { return false; }
};
