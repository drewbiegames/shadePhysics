#include "Sphere.h"

#include "Capsule.h"
#include "AABB.h"

bool Sphere::Collide(Sphere& other){
	Vector3Df V1, V2;

	V1 = Vector3Df(Position->X, Position->Y, Position->Z);
	V2 = Vector3Df(other.Position->X, other.Position->Y, other.Position->Z);

	float distanceSq = (V2 - V1).SqLength();
	float combineRadiusSq = (Radius + other.Radius) * (Radius + other.Radius);

	return (distanceSq < combineRadiusSq);
}

bool Sphere::Collide(Vector3Df& point){
	float distSq = (point - Vector3Df(Position->X, Position->Y, Position->Z)).SqLength();
	float radSq = Radius * Radius;

	return (distSq < radSq);
}

bool Sphere::Collide(Capsule& other){
	Vector3Df sp = Vector3Df(Position->X, Position->Y, Position->Z);
	float rad = Radius + other.R;

	return (other.L.DistanceToLine(sp) < rad);
}

void Sphere::CalculateAABB(){
	AxisAlign.Min.X = Position->X - Radius;
	AxisAlign.Min.Y = Position->Y - Radius;
	AxisAlign.Min.Z = Position->Z - Radius;
			 
	AxisAlign.Max.X = Position->X + Radius;
	AxisAlign.Max.Y = Position->Y + Radius;
	AxisAlign.Max.Z = Position->Z + Radius;
}