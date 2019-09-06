#include "Rectangle.h"

#include "Circle.h"

//Calcuates area of the rectangle
//Returns float - Area of the rectangle
float MyRectangle::Area(){
	return W * H;
}

//Rectnagle to Rectangle collsion test
//	Param 1 - Rectangle to be tested against
bool MyRectangle::Collide(MyRectangle& other){
	return
		util::RangeIntersect(Position->X, Position->X + W, other.Position->X, other.Position->X + other.W) &&
		util::RangeIntersect(Position->Y, Position->Y + H, other.Position->Y, other.Position->Y + other.H);
}

//Point to Rectangle collision test
//	Param 1 - Float X of point to be tested
//	Param 2 - Float Y of point to be tested
bool MyRectangle::Collide(float x, float y){
	return
		util::InRange(x, Position->X, Position->X + W) &&
		util::InRange(y, Position->Y, Position->Y + H);
}

//Circle to Rectangle Collision Test
//	Param 1 - Circle to be tested against
bool MyRectangle::Collide(Circle& other){
	MyRectangle testRect;
	testRect.Position = new Vector2Df();
	testRect.Position->X = Position->X - other.Radius;
	testRect.Position->Y = Position->Y - other.Radius;
	testRect.W = W + other.Radius;
	testRect.H = H + other.Radius;
	bool result = testRect.Collide(float(other.Position->X), float(other.Position->Y));
	delete testRect.Position;
	testRect.Position = nullptr;

	return result;
}