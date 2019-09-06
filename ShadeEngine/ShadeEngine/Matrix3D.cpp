#include "Matrix3D.h"

#include "Matrix2D.h"

#include <assert.h>

Matrix3D::Matrix3D(){
	mMatrix[A] = mMatrix[E] = mMatrix[I] = 1.0f;

	mMatrix[B] = mMatrix[C] = mMatrix[D] = 0.0f;
	mMatrix[F] = mMatrix[G] = mMatrix[H] = 0.0f;
}

float Matrix3D::Determinant(){
	float a, b, c, det;

	Matrix2D temp;

	temp[0] = mMatrix[E]; temp[2] = mMatrix[F];
	temp[1] = mMatrix[H]; temp[3] = mMatrix[I];
	a = mMatrix[A] * temp.Determinant();

	temp[0] = mMatrix[D]; temp[2] = mMatrix[F];
	temp[1] = mMatrix[G]; temp[3] = mMatrix[I];
	b = mMatrix[B] * temp.Determinant();

	temp[0] = mMatrix[D]; temp[2] = mMatrix[E];
	temp[1] = mMatrix[G]; temp[3] = mMatrix[H];
	c = mMatrix[C] * temp.Determinant();

	det = a - b + c;
	return det;
}

Matrix3D Matrix3D::Transpose(){
	Matrix3D temp;
	
	temp[A] = mMatrix[A]; temp[B] = mMatrix[D]; temp[C] = mMatrix[G];
	temp[D] = mMatrix[B]; temp[E] = mMatrix[E]; temp[F] = mMatrix[H];
	temp[G] = mMatrix[C]; temp[H] = mMatrix[F]; temp[I] = mMatrix[I];

	return temp;
}

Matrix3D Matrix3D::Cofactor(){
	throw("Do this");
	assert(false);
	Matrix3D temp;
	//TODO: THIS
	return temp;
}

float& Matrix3D::operator[](const unsigned int rhs){
	return mMatrix[rhs];
}

Vector3Df Matrix3D::operator*(const Vector3Df& rhs){
	Vector3Df temp;

	temp.X = mMatrix[A] * rhs.X + mMatrix[B] * rhs.Y + mMatrix[C] * rhs.Z;
	temp.Y = mMatrix[D] * rhs.X + mMatrix[E] * rhs.Y + mMatrix[F] * rhs.Z;
	temp.Z = mMatrix[G] * rhs.X + mMatrix[H] * rhs.Y + mMatrix[I] * rhs.Z;

	return temp;
}

Matrix3D Matrix3D::operator*(Matrix3D& rhs){
	Matrix3D temp;

	temp[A] = mMatrix[A] * rhs[A] + mMatrix[B] * rhs[D] + mMatrix[C] * rhs[G];
	temp[B] = mMatrix[A] * rhs[B] + mMatrix[B] * rhs[E] + mMatrix[C] * rhs[H];
	temp[C] = mMatrix[A] * rhs[C] + mMatrix[B] * rhs[F] + mMatrix[C] * rhs[I];


	temp[D] = mMatrix[D] * rhs[A] + mMatrix[E] * rhs[D] + mMatrix[F] * rhs[G];
	temp[E] = mMatrix[D] * rhs[B] + mMatrix[E] * rhs[E] + mMatrix[F] * rhs[H];
	temp[F] = mMatrix[D] * rhs[C] + mMatrix[E] * rhs[F] + mMatrix[F] * rhs[I];

	temp[G] = mMatrix[G] * rhs[A] + mMatrix[H] * rhs[D] + mMatrix[I] * rhs[G];
	temp[H] = mMatrix[G] * rhs[B] + mMatrix[H] * rhs[E] + mMatrix[I] * rhs[H];
	temp[I] = mMatrix[G] * rhs[C] + mMatrix[H] * rhs[F] + mMatrix[I] * rhs[I];

	return temp;
}

Matrix3D Matrix3D::operator*(const float& rhs){
	Matrix3D temp;

	for (int ii = 0; ii < 9; ++ii){
		temp[ii] = mMatrix[ii] * rhs;
	}
	return temp;
}

void Matrix3D::CreateFromQuaternion(const Quaternion& quat){
	//first row
	mMatrix[0] = 1.0f - 2.0f * (quat.Y * quat.Y + quat.Z * quat.Z);
	mMatrix[1] = 2.0f * (quat.X * quat.Y + quat.Z * quat.W);
	mMatrix[2] = 2.0f * (quat.X * quat.Z - quat.Y * quat.W);

	//second row
	mMatrix[3] = 2.0f * (quat.X * quat.Y - quat.Z * quat.W);
	mMatrix[4] = 1.0f - 2.0f * (quat.X * quat.X + quat.Z * quat.Z);
	mMatrix[5] = 2.0f * (quat.Z * quat.Y + quat.X * quat.W);

	//third row
	mMatrix[6] = 2.0f * (quat.X * quat.Z + quat.Y * quat.W);
	mMatrix[7] = 2.0f * (quat.Y * quat.Z - quat.X * quat.W);
	mMatrix[8] = 1.0f - 2.0f * (quat.X * quat.X + quat.Y * quat.Y);
}