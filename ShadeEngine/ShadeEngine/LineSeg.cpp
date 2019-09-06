#include "LineSeg.h"

#include "Utils.h"

void LineSeg::GLDrawLine(){
	util::GLRenderVec3(mP1, mP0, Vector3Df(1.0f,1.0f,1.0f));
}

float LineSeg::DistanceToLine(Vector3Df Q){

	Vector3Df M = mP1 - mP0;
	Vector3Df QP0 = Q - mP0;

	auto t = M.dot(QP0) / M.dot(M);

	if (t < 0){
		return (Q - mP0).Length();
	}
	if (t > 1){
		return (Q - mP1).Length();
	}

	Vector3Df P = mP0 + (M * t);

	Vector3Df PQ = P - Q;

	return PQ.Length();
}

float LineSeg::SqDistanceToLine(Vector3Df Q){
	Vector3Df M = mP1 - mP0;
	Vector3Df QP0 = Q - mP0;

	auto t = M.dot(QP0) / M.dot(M);

	if (t < 0){
		return (Q - mP0).SqLength();
	}
	if (t > 1){
		return (Q - mP1).SqLength();
	}

	Vector3Df P = mP0 + (M * t);

	Vector3Df PQ = P - Q;

	return PQ.SqLength();
}