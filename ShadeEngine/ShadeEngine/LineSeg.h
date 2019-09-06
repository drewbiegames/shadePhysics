#pragma once

#include "Vector3D.h"

/*
	3D Line Segment
*/

class LineSeg {
public:
	LineSeg() : mP0(Vector3Df()), mP1(Vector3Df()) {}
	LineSeg(Vector3Df P0, Vector3Df P1) : mP0(P0), mP1(P1) {}

	//Draws the line to the screen using OpenGL
	void GLDrawLine();

	float DistanceToLine(Vector3Df Q);
	float SqDistanceToLine(Vector3Df Q);

	Vector3Df mP0;
	Vector3Df mP1;
};