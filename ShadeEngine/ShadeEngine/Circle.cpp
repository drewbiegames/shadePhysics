#include "Circle.h"

//#include <math.h>
#include "Rectangle.h"

//Calculates the area of the circle
//Returns float - Area of circle
float Circle::Area(){ return float(M_PI * (Radius * Radius)); }

//Circle to Circle Collision Test
//	Param 1 - The circle to be tested against
bool Circle::Collide(Circle& other){
	float distance = 
		float(sqrt(
		((Position->X - other.Position->X) * (Position->X - other.Position->X)) + 
		((Position->Y - other.Position->Y) * (Position->Y - other.Position->Y))
		));

	return (distance < Radius + other.Radius);
}

//Point to circle collsion test
//	Param 1 - Float X of point to be tested
//	Param 2 - Float Y of point to be tested
bool Circle::Collide(float x, float y){
	float distance = float(sqrt(((Position->X - x) * (Position->X - x)) + ((Position->Y - y) * (Position->Y - y))));
	return (distance < Radius);
}

//Rectangle to Circle Collision Test
//	Param 1 - Rectangle to be tested against
bool Circle::Collide(MyRectangle& other){
	MyRectangle testRect;
	testRect.Position = new Vector2Df();
	testRect.Position->X = other.Position->X - Radius;
	testRect.Position->Y = other.Position->Y - Radius;
	testRect.W = other.W + Radius;
	testRect.H = other.H + Radius;
	
	bool result = testRect.Collide(float(other.Position->X), float(other.Position->Y));
	
	delete testRect.Position;
	testRect.Position = nullptr;

	return result;
}