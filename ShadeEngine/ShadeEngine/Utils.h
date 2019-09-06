#pragma once

#include <math.h>
//Warning C4005: 'M_PI': macro definition error
//Aware of warning, when _USE_MATH_DEFINES used
#ifndef M_PI
#define M_PI        3.14159265358979323846264338327950288
#endif
#include <algorithm>

#include "Vector2D.h"
#include "Vector3D.h"
#include <iostream>
#include <sstream>

namespace util {

	template <class T>
	bool InRange(T value, T min, T max){
		return value <= std::max(max, min) && value >= std::min(min, max);
	}

	template <class T>
	bool RangeIntersect(T minA, T maxA, T minB, T maxB){
		return std::max(minA, maxA) >= std::min(minB, maxB) &&
			   std::min(minA, maxA) <= std::max(minB, maxB);
	}

	float DegreesFromRadians(float radians);

	float RadiansFromDegrees(float degrees);

	void GLRenderVec3(Vector3Df vec, Vector3Df origin, Vector3Df colour);

	void GLTexturedCube(GLfloat size);

	void GLPrintMatrix4(float* matrix);

	template<class T>
	void clampValue(T& value, T max, T min){
		if (value > max) value = max;
		if (value < min) value = min;
	}

	template<class T>
	void wrapValue(T& value, T max, T min){
		value = value > min ? max - (min - value) :
				value < max ? min + (value - max) : 
				value;
	}

	float toFloat(const std::string& str);

	int toInt(const std::string& str);

	unsigned int toUInt(const std::string& str);

	bool contains(std::istringstream& str, char ch);

	Vector2Df PixelToScreen(GLint x, GLint y);
	
};