#pragma once

#include <cmath>
#include "Defines.h"

/*
	Vector4D Template Class
*/

template <class T>
class Vector4D {
public:
	Vector4D() : X(0), Y(0), Z(0), W(0) {}
	Vector4D<T>(T x, T y, T z, T w) : X(x), Y(y), Z(z), W(w) {}

	T X;
	T Y;
	T Z;
	T W;

	float Length() { return sqrt(X * X + Y * Y + Z * Z + W * W); }
	float SqLength() { return X * X + Y * Y + Z * Z + W * W; }

	Vector4D<T> operator+(const Vector4D<T>& v2) const {
		return Vector4D<T>(X + v2.X, Y + v2.Y, Z + v2.Z, W + v2.W);
	}

	Vector4D<T> operator+=(const Vector4D<T>& v2){
		this->X += v2.X;
		this->Y += v2.Y;
		this->Z += v2.Z;
		this->W += v2.W;
		return *this;
	}

	Vector4D<T> operator-(const Vector4D<T>& v2) const {
		return Vector4D<T>(X - v2.X, Y - v2.Y, Z - v2.Z, W - v2.W);
	}

	Vector4D<T> operator-=(const Vector4D<T>& v2){
		this->X -= v2.X;
		this->Y -= v2.Y;
		this->Z -= v2.Z;
		this->W -= v2.W;
		return *this;
	}

	Vector4D<T> operator*(float scalar){
		return Vector4D<T>(X * scalar, Y * scalar, Z * scalar, W * scalar);
	}

	Vector4D<T>& operator*=(float scalar){
		X *= scalar;
		Y *= scalar;
		Z *= scalar;
		W *= scalar;
		return *this;
	}

	Vector4D<T> operator/(float scalar){
		return Vector4D<T>(X / scalar, Y / scalar, Z / scalar, W / scalar);
	}

	Vector4D<T>& operator/=(float scalar){
		X /= scalar;
		Y /= scalar;
		Z /= scalar;
		W /= scalar;
		return *this;
	}

	void normalise(){
		float l = Length();
		if (l > 0){
			(*this) *= 1 / l;
		}
	}

	Vector4D<T> normalised(){
		Vector3D<T> temp = *this;
		temp.normalise();
		return temp;
	}

	float dot(Vector4D<T> other){
		return float(
			X * other.X +
			Y * other.Y +
			Z * other.Z +
			W * other.W);
	}
};

typedef Vector4D<float> Vector4Df;
typedef Vector4D<double> Vector4Dd;
typedef Vector4D<int> Vector4Di;