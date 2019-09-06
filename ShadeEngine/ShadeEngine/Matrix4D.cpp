#include "Matrix4D.h"

#include <iostream>
#include <string>
#include <assert.h>
#include "Matrix3D.h"

Matrix4D::Matrix4D(){
	mMatrix[A] = mMatrix[F] = mMatrix[K] = mMatrix[P] = 1;

	mMatrix[B] = mMatrix[C] = mMatrix[D] = 
	mMatrix[E] = mMatrix[G] = mMatrix[H] = 
	mMatrix[I] = mMatrix[J] = mMatrix[L] = 
	mMatrix[M] = mMatrix[N] = mMatrix[0] = 0.0f;
}

float* Matrix4D::getMatrix(){
	return mMatrix;
}

Matrix4D Matrix4D::Inverse(){
	Matrix4D temp;

	Matrix4D minors;

	Matrix3D mat3;

	//Row 1
	//A
	mat3[Matrix3D::A] = mMatrix[F]; mat3[Matrix3D::B] = mMatrix[G]; mat3[Matrix3D::C] = mMatrix[H];
	mat3[Matrix3D::D] = mMatrix[J]; mat3[Matrix3D::E] = mMatrix[K]; mat3[Matrix3D::F] = mMatrix[L];
	mat3[Matrix3D::G] = mMatrix[N]; mat3[Matrix3D::H] = mMatrix[O]; mat3[Matrix3D::I] = mMatrix[P];
	minors[A] = mat3.Determinant();

	//B 
	//only one column changes a long the row
	mat3[Matrix3D::A] = mMatrix[E]; 
	mat3[Matrix3D::D] = mMatrix[I];
	mat3[Matrix3D::G] = mMatrix[M];
	minors[B] = mat3.Determinant();

	//C
	mat3[Matrix3D::B] = mMatrix[F];
	mat3[Matrix3D::E] = mMatrix[J];
	mat3[Matrix3D::H] = mMatrix[N];
	minors[C] = mat3.Determinant();

	//D
	mat3[Matrix3D::C] = mMatrix[G];
	mat3[Matrix3D::F] = mMatrix[K];
	mat3[Matrix3D::I] = mMatrix[O];
	minors[D] = mat3.Determinant();

	//Row 2
	//H
	mat3[Matrix3D::A] = mMatrix[A]; mat3[Matrix3D::B] = mMatrix[B]; mat3[Matrix3D::C] = mMatrix[C];
	minors[H] = mat3.Determinant();
	
	//G
	mat3[Matrix3D::C] = mMatrix[D];
	mat3[Matrix3D::F] = mMatrix[L];
	mat3[Matrix3D::I] = mMatrix[P];
	minors[G] = mat3.Determinant();

	//F
	mat3[Matrix3D::B] = mMatrix[C];
	mat3[Matrix3D::E] = mMatrix[K];
	mat3[Matrix3D::H] = mMatrix[O];
	minors[F] = mat3.Determinant();

	//E
	mat3[Matrix3D::A] = mMatrix[B];
	mat3[Matrix3D::D] = mMatrix[J];
	mat3[Matrix3D::G] = mMatrix[N];
	minors[E] = mat3.Determinant();

	//Row 3
	//I
	mat3[Matrix3D::D] = mMatrix[F]; mat3[Matrix3D::E] = mMatrix[G]; mat3[Matrix3D::F] = mMatrix[H];
	minors[I] = mat3.Determinant();

	//J
	mat3[Matrix3D::A] = mMatrix[A];
	mat3[Matrix3D::D] = mMatrix[E];
	mat3[Matrix3D::G] = mMatrix[M];
	minors[J] = mat3.Determinant();

	//K
	mat3[Matrix3D::B] = mMatrix[B];
	mat3[Matrix3D::E] = mMatrix[F];
	mat3[Matrix3D::H] = mMatrix[N];
	minors[K] = mat3.Determinant();

	//L
	mat3[Matrix3D::C] = mMatrix[C];
	mat3[Matrix3D::F] = mMatrix[G];
	mat3[Matrix3D::I] = mMatrix[O]; 
	minors[L] = mat3.Determinant();

	//Row 4
	//P
	mat3[Matrix3D::G] = mMatrix[I]; mat3[Matrix3D::H] = mMatrix[J]; mat3[Matrix3D::I] = mMatrix[K];
	minors[P] = mat3.Determinant();

	//O
	mat3[Matrix3D::C] = mMatrix[D];
	mat3[Matrix3D::F] = mMatrix[H];
	mat3[Matrix3D::I] = mMatrix[L];
	minors[O] = mat3.Determinant();

	//N
	mat3[Matrix3D::B] = mMatrix[C];
	mat3[Matrix3D::E] = mMatrix[G];
	mat3[Matrix3D::H] = mMatrix[K];
	minors[N] = mat3.Determinant();

	//M
	mat3[Matrix3D::A] = mMatrix[B];
	mat3[Matrix3D::D] = mMatrix[F];
	mat3[Matrix3D::G] = mMatrix[J];
	minors[M] = mat3.Determinant();
	
	//Determinant - don't use Mat4.determinant function as repeats calculation of minors
	float determinat = 
		mMatrix[A] * minors[A] - 
		mMatrix[B] * minors[B] + 
		mMatrix[C] * minors[C] - 
		mMatrix[D] * minors[D];

	minors = minors.cofactor();
	minors = minors.Transpose();

	if (determinat != 0.0f){
		temp = minors * float(1 / determinat);
	}
	else{
		printf("Determinate equals zero!");
		temp[M] = -1.0f;
	}

	return temp;
}

Matrix4D Matrix4D::Transpose(){
	Matrix4D temp;

	temp[A] = mMatrix[A]; temp[B] = mMatrix[E]; temp[C] = mMatrix[I]; temp[D] = mMatrix[M];
	temp[E] = mMatrix[B]; temp[F] = mMatrix[F]; temp[G] = mMatrix[J]; temp[H] = mMatrix[N];
	temp[I] = mMatrix[C]; temp[J] = mMatrix[G]; temp[K] = mMatrix[K]; temp[L] = mMatrix[O];
	temp[M] = mMatrix[D]; temp[N] = mMatrix[H]; temp[O] = mMatrix[L]; temp[P] = mMatrix[P];
	
	return temp;
}

Matrix4D Matrix4D::cofactor(){
	Matrix4D temp = *this;

	temp[B] = mMatrix[B] * -1.0f; 
	temp[D] = mMatrix[D] * -1.0f;
			  
	temp[E] = mMatrix[E] * -1.0f;
	temp[G] = mMatrix[G] * -1.0f;
			  
	temp[J] = mMatrix[J] * -1.0f;
	temp[L] = mMatrix[L] * -1.0f;
			  
	temp[M] = mMatrix[M] * -1.0f;
	temp[O] = mMatrix[O] * -1.0f;

	return temp;
}

Matrix4D Matrix4D::fudge(float fdg){
	Matrix4D temp;
	for (unsigned int ii = 0; ii < 16; ii++){
		temp[ii] = floorf(mMatrix[ii] * fdg) / fdg;
	}
	return temp;
}

void Matrix4D::operator=(float* rhs){
	mMatrix[A] = rhs[A]; mMatrix[B] = rhs[B]; mMatrix[C] = rhs[C]; mMatrix[D] = rhs[D];
	mMatrix[E] = rhs[E]; mMatrix[F] = rhs[F]; mMatrix[G] = rhs[G]; mMatrix[H] = rhs[H];
	mMatrix[I] = rhs[I]; mMatrix[J] = rhs[J]; mMatrix[K] = rhs[K]; mMatrix[L] = rhs[L];
	mMatrix[M] = rhs[M]; mMatrix[N] = rhs[N]; mMatrix[O] = rhs[O]; mMatrix[P] = rhs[P];
}

float& Matrix4D::operator[](const unsigned int rhs){
	return mMatrix[rhs];
}

Matrix4D Matrix4D::operator*(Matrix4D& rhs){
	Matrix4D temp;

	temp[A] = mMatrix[A] * rhs[A] + mMatrix[B] * rhs[E] + mMatrix[C] * rhs[I] + mMatrix[D] * rhs[M];
	temp[B] = mMatrix[A] * rhs[B] + mMatrix[B] * rhs[F] + mMatrix[C] * rhs[J] + mMatrix[D] * rhs[N];
	temp[C] = mMatrix[A] * rhs[C] + mMatrix[B] * rhs[G] + mMatrix[C] * rhs[K] + mMatrix[D] * rhs[O];
	temp[D] = mMatrix[A] * rhs[D] + mMatrix[B] * rhs[H] + mMatrix[C] * rhs[L] + mMatrix[D] * rhs[P];

	temp[E] = mMatrix[E] * rhs[A] + mMatrix[F] * rhs[E] + mMatrix[G] * rhs[I] + mMatrix[H] * rhs[M];
	temp[F] = mMatrix[E] * rhs[B] + mMatrix[F] * rhs[F] + mMatrix[G] * rhs[J] + mMatrix[H] * rhs[N];
	temp[G] = mMatrix[E] * rhs[C] + mMatrix[F] * rhs[G] + mMatrix[G] * rhs[K] + mMatrix[H] * rhs[O];
	temp[H] = mMatrix[E] * rhs[D] + mMatrix[F] * rhs[H] + mMatrix[G] * rhs[L] + mMatrix[H] * rhs[P];

	temp[I] = mMatrix[I] * rhs[A] + mMatrix[J] * rhs[E] + mMatrix[K] * rhs[I] + mMatrix[L] * rhs[M];
	temp[J] = mMatrix[I] * rhs[B] + mMatrix[J] * rhs[F] + mMatrix[K] * rhs[J] + mMatrix[L] * rhs[N];
	temp[K] = mMatrix[I] * rhs[C] + mMatrix[J] * rhs[G] + mMatrix[K] * rhs[K] + mMatrix[L] * rhs[O];
	temp[L] = mMatrix[I] * rhs[D] + mMatrix[J] * rhs[H] + mMatrix[K] * rhs[L] + mMatrix[L] * rhs[P];

	temp[M] = mMatrix[M] * rhs[A] + mMatrix[N] * rhs[E] + mMatrix[O] * rhs[I] + mMatrix[P] * rhs[M];
	temp[N] = mMatrix[M] * rhs[B] + mMatrix[N] * rhs[F] + mMatrix[O] * rhs[J] + mMatrix[P] * rhs[N];
	temp[O] = mMatrix[M] * rhs[C] + mMatrix[N] * rhs[G] + mMatrix[O] * rhs[K] + mMatrix[P] * rhs[O];
	temp[P] = mMatrix[M] * rhs[D] + mMatrix[N] * rhs[H] + mMatrix[O] * rhs[L] + mMatrix[P] * rhs[P];

	return temp;
}

Matrix4D Matrix4D::operator*(const float rhs){
	Matrix4D mat;
	for (unsigned int ii = 0; ii < 16; ii++){
		mat[ii] = mMatrix[ii] * rhs;
	}
	return mat;
}

Vector4Df Matrix4D::operator*(const Vector4Df& rhs){
	return Vector4Df(
		mMatrix[A] * rhs.X + mMatrix[B] * rhs.Y + mMatrix[C] * rhs.Z + mMatrix[D] * rhs.W,
		mMatrix[E] * rhs.X + mMatrix[F] * rhs.Y + mMatrix[G] * rhs.Z + mMatrix[H] * rhs.W,
		mMatrix[I] * rhs.X + mMatrix[J] * rhs.Y + mMatrix[K] * rhs.Z + mMatrix[L] * rhs.W,
		mMatrix[M] * rhs.X + mMatrix[N] * rhs.Y + mMatrix[O] * rhs.Z + mMatrix[P] * rhs.W);
}

Vector3Df Matrix4D::operator*(const Vector3Df& rhs){
	return Vector3Df(
		mMatrix[A] * rhs.X + mMatrix[B] * rhs.Y + mMatrix[C] * rhs.Z + mMatrix[D] * 1.0f,
		mMatrix[E] * rhs.X + mMatrix[F] * rhs.Y + mMatrix[G] * rhs.Z + mMatrix[H] * 1.0f,
		mMatrix[I] * rhs.X + mMatrix[J] * rhs.Y + mMatrix[K] * rhs.Z + mMatrix[L] * 1.0f);
}

Matrix4D& Matrix4D::operator=(const Vector3Df& rhs){
	mMatrix[D] = rhs.X;
	mMatrix[H] = rhs.Y;
	mMatrix[L] = rhs.Z;
	return *this;
}

float Matrix4D::Determinant(){
	float a, b, c, d;
	Matrix3D mat3;

	//Row 1
	//A
	mat3[Matrix3D::A] = mMatrix[F]; mat3[Matrix3D::B] = mMatrix[G]; mat3[Matrix3D::C] = mMatrix[H];
	mat3[Matrix3D::D] = mMatrix[J]; mat3[Matrix3D::E] = mMatrix[K]; mat3[Matrix3D::F] = mMatrix[L];
	mat3[Matrix3D::G] = mMatrix[N]; mat3[Matrix3D::H] = mMatrix[O]; mat3[Matrix3D::I] = mMatrix[P];
	a = mat3.Determinant();

	//B 
	//only one column changes a long the row
	mat3[Matrix3D::A] = mMatrix[E];
	mat3[Matrix3D::D] = mMatrix[I];
	mat3[Matrix3D::G] = mMatrix[M];
	b = mat3.Determinant();

	//C
	mat3[Matrix3D::B] = mMatrix[F];
	mat3[Matrix3D::E] = mMatrix[J];
	mat3[Matrix3D::H] = mMatrix[N];
	c = mat3.Determinant();

	//D
	mat3[Matrix3D::C] = mMatrix[G];
	mat3[Matrix3D::F] = mMatrix[K];
	mat3[Matrix3D::I] = mMatrix[O];
	d = mat3.Determinant();

	return mMatrix[A] * a - mMatrix[B] * b + mMatrix[C] * c - mMatrix[D] * d;
}

void Matrix4D::Output(){
	std::string line1, line2, line3, line4;

	if (mMatrix[A] >= 0.0f) line1 += " ";
	line1 += std::to_string(mMatrix[A]) + ", ";
	if (mMatrix[B] >= 0.0f) line1 += " ";
	line1 += std::to_string(mMatrix[B]) + ", ";
	if (mMatrix[C] >= 0.0f) line1 += " ";
	line1 += std::to_string(mMatrix[C]) + ", ";
	if (mMatrix[D] >= 0.0f) line1 += " ";
	line1 += std::to_string(mMatrix[D]);


	if (mMatrix[E] >= 0.0f) line2 += " ";
	line2 += std::to_string(mMatrix[E]) + ", ";
	if (mMatrix[F] >= 0.0f) line2 += " ";
	line2 += std::to_string(mMatrix[F]) + ", ";
	if (mMatrix[G] >= 0.0f) line2 += " ";
	line2 += std::to_string(mMatrix[G]) + ", ";
	if (mMatrix[H] >= 0.0f) line2 += " ";
	line2 += std::to_string(mMatrix[H]);

	if (mMatrix[I] >= 0.0f) line3 += " ";
	line3 += std::to_string(mMatrix[I]) + ", ";
	if (mMatrix[J] >= 0.0f) line3 += " ";
	line3 += std::to_string(mMatrix[J]) + ", ";
	if (mMatrix[K] >= 0.0f) line3 += " ";
	line3 += std::to_string(mMatrix[K]) + ", ";
	if (mMatrix[L] >= 0.0f) line3 += " ";
	line3 += std::to_string(mMatrix[L]);

	if (mMatrix[M] >= 0.0f) line4 += " ";
	line4 += std::to_string(mMatrix[M]) + ", ";
	if (mMatrix[N] >= 0.0f) line4 += " ";
	line4 += std::to_string(mMatrix[N]) + ", ";
	if (mMatrix[O] >= 0.0f) line4 += " ";
	line4 += std::to_string(mMatrix[O]) + ", ";
	if (mMatrix[P] >= 0.0f) line4 += " ";
	line4 += std::to_string(mMatrix[P]);

	std::cout << "-------------------Matrix-------------------" << std::endl;
	std::cout << line1 << std::endl;
	std::cout << line2 << std::endl;
	std::cout << line3 << std::endl;
	std::cout << line4 << std::endl;
	std::cout << "--------------------------------------------" << std::endl;
}