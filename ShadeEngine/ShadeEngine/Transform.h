#pragma once

#include "Vector3D.h"
#include "Quaternion.h"

/*
	Transform Class

	TODO: Make Template
		Prerequisite: Make Quaternion a Template

*/

class Transform {
public:
	Transform();
	Transform(Vector3Df pos, Quaternion rot);

	void CreateTransformMatrix(float* matrix);

	Vector3Df position;
	Quaternion rotation;
};