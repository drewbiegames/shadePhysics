#pragma once

#include "Defines.h"

#include "Vector2D.h"

class Matrix2D{
	enum accessor{
		A = 0, B = 2,
		C = 1, D = 3
	};
public:

	Matrix2D();

	float Determinant();
	Matrix2D Transpose();
	Matrix2D Cofactor();
	Matrix2D Inverse();
	//Inverse ??

	float& operator[](const unsigned int rhs);
	Vector2Df operator*(const Vector2Df& rhs);
	Matrix2D operator*(Matrix2D& rhs);
	Matrix2D operator*(const float& rhs);
	

private:
	float mMatrix[4];
};