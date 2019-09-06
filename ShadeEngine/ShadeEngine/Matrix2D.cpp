#include "Matrix2D.h"

#include <assert.h>

Matrix2D::Matrix2D(){
	mMatrix[A] = mMatrix[D] = 1.0f;
	mMatrix[B] = mMatrix[C] = 0.0f;
}

float Matrix2D::Determinant(){
	return mMatrix[A] * mMatrix[D] - mMatrix[B] * mMatrix[C];
}

Matrix2D Matrix2D::Transpose(){
	Matrix2D temp;

	temp[A] = mMatrix[A]; temp[B] = mMatrix[C];
	temp[C] = mMatrix[B]; temp[D] = mMatrix[D];

	return temp;
}

float& Matrix2D::operator[](const unsigned int rhs){

	return mMatrix[rhs];
}
Matrix2D Matrix2D::operator*(Matrix2D& rhs){
	Matrix2D temp;

	temp[A] = mMatrix[A] * rhs[A] + mMatrix[B] * rhs[C];
	temp[B] = mMatrix[A] * rhs[B] + mMatrix[B] * rhs[D];

	temp[C] = mMatrix[C] * rhs[A] + mMatrix[D] * rhs[C];
	temp[D] = mMatrix[C] * rhs[B] + mMatrix[D] * rhs[D];

	return temp;
}

Matrix2D Matrix2D::Cofactor(){
	Matrix2D temp;

	temp = *this;
	temp[B] *= -1.0f;
	temp[C] *= -1.0f;

	return temp;
}

Vector2Df Matrix2D::operator*(const Vector2Df& rhs){
	Vector2Df temp;

	temp.X = mMatrix[A] * rhs.X + mMatrix[B] * rhs.Y;
	temp.Y = mMatrix[C] * rhs.X + mMatrix[D] * rhs.Y;

	return temp;
}

Matrix2D Matrix2D::operator*(const float& rhs){
	Matrix2D temp;

	temp[A] = mMatrix[A] * rhs;
	temp[B] = mMatrix[B] * rhs;
	temp[C] = mMatrix[C] * rhs;
	temp[D] = mMatrix[D] * rhs;

	return temp;
}