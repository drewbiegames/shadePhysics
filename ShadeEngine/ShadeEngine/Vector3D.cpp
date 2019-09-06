#include "Vector3D.h"

#include "Utils.h"
#include "Quaternion.h"

Vector3Df Vector3Df::rotate(float angle, Vector3Df axis){
	float sinHalfAngle = (float)sin(util::RadiansFromDegrees(angle / 2));
	float cosHalfAngle = (float)cos(util::RadiansFromDegrees(angle / 2));

	float rX = X * sinHalfAngle;
	float rY = Y * sinHalfAngle;
	float rZ = Z * sinHalfAngle;
	float rW = cosHalfAngle;

	Quaternion rotation(rX, rY, rZ, rW);
	Quaternion conjugate = rotation.conjugate();
	
	Quaternion w = rotation.mul(*this) * conjugate;

	return Vector3Df(w.X, w.Y, w.Z);
};