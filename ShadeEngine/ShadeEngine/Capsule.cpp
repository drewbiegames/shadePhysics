#include "Capsule.h"
#include "Sphere.h"
#include "AABB.h"

bool Capsule::Collide(Vector3Df& point){
	float distSq = L.SqDistanceToLine(point);
	return (distSq < R * R);
}

bool Capsule::Collide(Sphere& other){
	Vector3Df sp = Vector3Df(other.Position->X, other.Position->Y, other.Position->Z);
	float rad = other.Radius + R;
	rad = rad * rad;

	return (L.SqDistanceToLine(sp) < rad);
}

void Capsule::CalculateAABB(){
	AxisAlign.Min.X = std::fminf(L.mP0.X, L.mP1.X) - R;
	AxisAlign.Max.X = std::fmaxf(L.mP0.X, L.mP1.X) + R;
			 
	AxisAlign.Min.Y = std::fminf(L.mP0.Y, L.mP1.Y) - R;
	AxisAlign.Max.Y = std::fmaxf(L.mP0.Y, L.mP1.Y) + R;
			 
	AxisAlign.Min.Z = std::fminf(L.mP0.Z, L.mP1.Z) - R;
	AxisAlign.Max.Z = std::fmaxf(L.mP0.Z, L.mP1.Z) + R;
}