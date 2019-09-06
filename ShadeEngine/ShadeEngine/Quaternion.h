#pragma once

#include "Vector3D.h"

/*
	Quaternion Class

	ref: http://content.gpwiki.org/index.php/OpenGL:Tutorials:Using_Quaternions_to_represent_rotation
	ref: SAE Portal download

	TODO: Make a template
*/

class Quaternion {

public:
	Quaternion();
	Quaternion(float x, float y, float z, float w) : X(x), Y(y), Z(z), W(w) {}
	~Quaternion();

	Quaternion operator*(Quaternion& q);

	Vector3Df operator*(Vector3Df& vec);

	Quaternion operator-();

	void CreateFromAxisAngle(float x, float y, float z, float degrees);

	void CreateFromEuler(float x, float y, float z);

	static Quaternion Slerp(const Quaternion& q1, const Quaternion& q2, float between);

	float length();

	Quaternion normalise();

	Quaternion conjugate();

	Quaternion mul(Vector3Df vec);

	Quaternion mul(Quaternion q);

	void CreateMatrix(float* pMatrix);

	float W, X, Y, Z;

	void Output();
	//Quaternion operator *(Vector3Df vec);
};