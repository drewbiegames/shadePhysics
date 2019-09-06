#pragma once

#include "BoundingShape.h"
#include "Vector3D.h"

/*
	3D Axis Aligned Bounding Box
*/

class AABB : public BoundingShape {
public:
	AABB() : BoundingShape(), Max(Vector3Df()), Min(Vector3Df()) {}

	AABB(GameObject* obj, Vector3Df min, Vector3Df max, bool calc = true)
		: BoundingShape(obj), Max(min), Min(max), mCalcEachFrame(calc) {}

	Vector3Df Max, Min;

	//Draws in OpenGL
	void GLDraw();

	bool Collide(AABB& other);

	virtual AABB* getAABB(){ return this; }
	virtual void CalculateAABB();

	~AABB(){}

private:

	bool mCalcEachFrame;

	bool Collide(Sphere& other){ return false; }
	bool Collide(Vector3Df& point){ return false; }
	bool Collide(Capsule& other){ return false; }
	virtual bool Collide(Circle& other){ return false; }
	virtual bool Collide(MyRectangle& other){ return false; }
	virtual bool Collide(float x, float y){ return false; }
	virtual bool Collide(OBB& other){ return false; }

};