#pragma once

#include <cmath>
#include "Defines.h"

/*
	Vector3D 
	with operator overloads +, -, +=, -=, *, / and Normalise
	cross and dot
	Modified from template to float only class
	Ref: Class Slides
*/

template <class T>
class Vector3D {
public:
	Vector3D() : X(0), Y(0), Z(0) {}
	Vector3D<T>(T x, T y, T z) : X(x), Y(y), Z(z) {}

	T X;
	T Y;
	T Z;

	bool isZero(){ 
		bool x = X == T(0);
		bool y = Y == T(0);
		bool z = Z == T(0);
		return x && y && z;
	}

	float Length() { return sqrt(X * X + Y * Y + Z * Z); }
	float SqLength() { return X * X + Y * Y + Z * Z; }

	Vector3D<T> operator+(const Vector3D<T>& v2) const {
		return Vector3D<T>(X + v2.X, Y + v2.Y, Z + v2.Z);
	}

	Vector3D<T>& operator+=(const Vector3D<T>& v2){
		this->X += v2.X;
		this->Y += v2.Y;
		this->Z += v2.Z;
		return *this;
	}

	Vector3D<T> operator-(const Vector3D<T>& v2) const {
		return Vector3D<T>(X - v2.X, Y - v2.Y, Z - v2.Z);
	}

	Vector3D<T> operator-() const {
		return Vector3D<T>(-X, -Y, -Z);
	}

	Vector3D<T>& operator-=(const Vector3D<T>& v2){
		this->X -= v2.X;
		this->Y -= v2.Y;
		this->Z -= v2.Z;
		return *this;
	}

	Vector3D<T> operator*(float scalar){
		return Vector3D<T>(X * scalar, Y * scalar, Z * scalar);
	}

	Vector3D<T>& operator*=(float scalar){
		X *= scalar;
		Y *= scalar;
		Z *= scalar;
		return *this;
	}

	Vector3D<T> operator*(Vector3D<T> other){
		Vector3D<T> result;

		result.X = X * other.X;
		result.Y = Y * other.Y;
		result.Z = Z * other.Z;

		return result;
	}

	Vector3D<T> operator/(float scalar){
		return Vector3D<T>(X / scalar, Y / scalar, Z / scalar);
	}

	Vector3D<T>& operator/=(float scalar){
		X /= scalar;
		Y /= scalar;
		Z /= scalar;
		return *this;
	}

	void normalise(){
		float l = Length();
		if (l > 0){
			(*this) *= 1 / l;
		}
	}

	Vector3D<T> normalised(){
		Vector3D<T> vec3 = *this;
		vec3.normalise();
		return vec3;
	}

	void setLength(float len){
		normalise();
		X *= len;
		Y *= len;
		Z *= len;
	}

	float dot(Vector3D<T> other){
		return float(
			X * other.X + 
			Y * other.Y + 
			Z * other.Z);
	}

	Vector3D<T> cross(Vector3D<T>& v2){
		return Vector3D<T>(
			Y * v2.Z - Z * v2.Y, 
			Z * v2.X - X * v2.Z, 
			X * v2.Y - Y * v2.X);
	}

	void Output(){
		std::cout << "(" << X << ", " << Y << ", " << Z << ")" << std::endl;
	}

};
typedef Vector3D<float> Vector3Df;
typedef Vector3D<double> Vector3Dd;
typedef Vector3D<int> Vector3Di;
typedef Vector3D<float> Vec3;

template <class T>
Vector3D<T> rotate(float angle, Vector3D<T> axis){
	float sinHalfAngle = (float)sin(util::RadiansFromDegrees(angle / 2));
	float cosHalfAngle = (float)cos(util::RadiansFromDegrees(angle / 2));

	float rX = X * sinHalfAngle;
	float rY = Y * sinHalfAngle;
	float rZ = Z * sinHalfAngle;
	float rW = cosHalfAngle;

	Quaternion rotation(rX, rY, rZ, rW);
	Quaternion conjugate = rotation.conjugate();

	Quaternion w = rotation.mul(*this) * conjugate;

	return Vector3D<T>(T(w.X), T(w.Y), T(w.Z));
};
