#pragma once

#include <cmath>
#include "Defines.h"
#include "Vector4D.h"
#include "Vector3D.h"

/*
	Matrix4D
*/

class Matrix4D {
	enum accessor {
		A = 0, B = 4, C = 8, D = 12,
		E = 1, F = 5, G = 9, H = 13,
		I = 2, J = 6, K = 10, L = 14,
		M = 3, N = 7, O = 11, P = 15
	};
public:
	Matrix4D();

	float* getMatrix();

	Matrix4D Inverse();
	Matrix4D Transpose();
	float Determinant();

	void operator=(float* rhs);
	float& operator[](const unsigned int rhs);

	Matrix4D operator*(Matrix4D& rhs);
	Matrix4D operator*(const float rhs);
	Vector4Df operator*(const Vector4Df& rhs);
	Vector3Df operator*(const Vector3Df& rhs);
	Matrix4D& operator=(const Vector3Df& rhs);

	void Output();

private:
	float mMatrix[16];

	Matrix4D fudge(float fdg);

	Matrix4D cofactor();
};