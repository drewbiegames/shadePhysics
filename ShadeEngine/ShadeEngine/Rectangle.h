#pragma once

#include "BoundingShape2D.h"

#include "Utils.h"
class Circle;

/*
	Rectangle Bounding Shape Class
	Used in collision
*/

class MyRectangle : public BoundingShape2D {
public:
	MyRectangle() : BoundingShape2D(), W(0.0f), H(0.0f) {}

	MyRectangle(GameObject* obj, Vector2Df& pos, Vector2Df& vel, float width, float height) :
		BoundingShape2D(obj, pos, vel), W(width), H(height) {}

	float W;
	float H;

	//Calculates the area
	float Area();

	//Rectangle to Rectangle collision
	bool Collide(MyRectangle& other);

	//Point to Rectangle collision
	bool Collide(float x, float y);

	//Circle to Rectangle collison
	bool Collide(Circle& other);

};