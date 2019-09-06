#pragma once

#include <cmath>
//#include "Utils.h"

/*
	Vector2D Template
	with operator overloads +, -, +=, -=, *, / and Normalise

	Ref: SDL Game Development, Shaun Mitchell
*/

template<class T>
class Vector2DT{
public:
	Vector2DT() : X(0), Y(0) {}
	Vector2DT(T x, T y) : X(x), Y(y) {}

	T X;
	T Y;

	T Length() { return sqrt(X * X + Y * Y); }

	Vector2DT operator+(const Vector2DT& v2) const {
		return Vector2DT(X + v2.X, Y + v2.Y);
	}

	Vector2DT& operator+=(const Vector2DT& v2){
		this->X += v2.X;
		this->Y += v2.Y;
		return *this;
	}

	Vector2DT operator-(const Vector2DT& v2) const {
		return Vector2DT(X - v2.X, Y - v2.Y);
	}

	Vector2DT operator-() const {
		return Vector2DT(-X, -Y);
	}

	Vector2DT& operator-=(const Vector2DT& v2){
		this->X -= v2.X;
		this->Y -= v2.Y;
		return *this;
	}

	Vector2DT operator*(T scalar){
		return Vector2DT(X * scalar, Y * scalar);
	}

	Vector2DT& operator*=(T scalar){
		X *= scalar;
		Y *= scalar;
		return *this;
	}

	Vector2DT operator/(T scalar){
		return Vector2DT(X / scalar, Y / scalar);
	}

	Vector2DT& operator/=(T scalar){
		X /= scalar;
		Y /= scalar;
		return *this;
	}

	void normalise(){
		float l = Length();
		if (l > 0){
			(*this) *= 1 / l;
		}
	}

	void setLength(float len){
			normalise();
			X *= len;
			Y *= len;
	}

	void setAngle(float angle){
		X = cos(angle);
		Y = sin(angle);
	}

	float getRadians(){
		return atan2f(Y, X);
	}

	float dot(Vector2DT<T> other){
		return float(X * other.X + Y * other.Y);
	}
	
};

typedef Vector2DT<float> Vec2;
typedef Vector2DT<float> Vector2Df;
typedef Vector2DT<int> Vector2Di;