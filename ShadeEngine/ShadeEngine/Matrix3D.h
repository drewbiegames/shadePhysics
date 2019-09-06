#pragma once

#include "Defines.h"

#include "Vector3D.h"
#include "Quaternion.h"

class Matrix3D{
	
public:

	Matrix3D();

	float Determinant();
	Matrix3D Transpose();
	Matrix3D Cofactor();
	//Inverse ??

	float& operator[](const unsigned int rhs);
	Vector3Df operator*(const Vector3Df& rhs);
	Matrix3D operator*(Matrix3D& rhs);
	Matrix3D operator*(const float& rhs);

	void CreateFromQuaternion(const Quaternion& quat);

	enum accessor{
		A = 0, B = 3, C = 6,
		D = 1, E = 4, F = 7,
		G = 2, H = 5, I = 8
	};

private:
	float mMatrix[9];
};