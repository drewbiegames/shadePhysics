#pragma once 


class Colour {
public:
	float R, G, B, A;

	Colour(float r, float g, float b, float a) 
		: R(r), G(g), B(b), A(A) 
	{
		Cap();
	}
	
	Colour(double r, double g, double b, double a){
		R = float(r);
		G = float(g);
		B = float(b);
		A = float(a);

		Cap();
	}

	Colour() : R(1.0f), G(1.0f), B(1.0f), A(1.0f) {}

	Colour operator+(const Colour& rhs);
	Colour operator+(const float rhs);

	Colour& operator+=(const Colour& rhs);
	Colour& operator+=(const float rhs);

	Colour operator-(const Colour& rhs);
	Colour operator-(const float rhs);

	Colour& operator-=(const Colour& rhs);
	Colour& operator-=(const float rhs);

	Colour operator*(const Colour& rhs);
	Colour operator*(const float rhs);

	Colour& operator*=(const Colour& rhs);
	Colour& operator*=(const float rhs);

	Colour operator/(const Colour& rhs);
	Colour operator/(const float rhs);

	Colour& operator/=(const Colour& rhs);
	Colour& operator/=(const float rhs);

	void Cap();
};