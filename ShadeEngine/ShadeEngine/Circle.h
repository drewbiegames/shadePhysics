#pragma once

#include <cmath>

#include "BoundingShape2D.h"
class MyRectangle;

/*
	Circle Bounding Shape
	Used for Collision
*/

class Circle : public BoundingShape2D {
public:
	Circle() : BoundingShape2D(), Radius(0.0f) {}

	Circle(GameObject* obj, Vector2Df& pos, Vector2Df& vel, float radius) :
		BoundingShape2D(obj, pos, vel), Radius(radius) {}

	float Radius;

	//Calculates area
	float Area();

	//circle collison test
	bool Collide(Circle& other);

	//point collide test
	bool Collide(float x, float y);

	//Rectangle to Circle collision test
	bool Collide(MyRectangle& other);

};