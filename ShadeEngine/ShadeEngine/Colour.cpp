#include "Colour.h"

Colour Colour::operator+(const Colour& rhs){
	Colour temp(*this);
	return (temp += rhs);
}

Colour Colour::operator+(const float rhs){
	Colour temp(*this);
	return (temp += rhs);
}

Colour& Colour::operator+=(const Colour& rhs){
	R += rhs.R;
	G += rhs.G;
	B += rhs.B;
	A += rhs.A;

	Cap();

	return *this;
}

Colour& Colour::operator+=(const float rhs){
	R += rhs;
	G += rhs;
	B += rhs;
	A += rhs;

	Cap();

	return *this;
}

Colour Colour::operator-(const Colour& rhs){
	Colour temp(*this);
	return (temp -= rhs);
}

Colour Colour::operator-(const float rhs){
	Colour temp(*this);
	return (temp -= rhs);
}

Colour& Colour::operator-=(const Colour& rhs){
	R -= rhs.R;
	G -= rhs.G;
	B -= rhs.B;
	A -= rhs.A;

	Cap();

	return *this;
}

Colour& Colour::operator-=(const float rhs){
	Colour temp(*this);
	return (temp -= rhs);
}

Colour Colour::operator*(const Colour& rhs){
	Colour temp(*this);
	return (temp *= rhs);
}

Colour Colour::operator*(const float rhs){
	Colour temp(*this);
	return (temp *= rhs);
}

Colour& Colour::operator*=(const Colour& rhs){
	R *= rhs.R;
	G *= rhs.G;
	B *= rhs.B;
	A *= rhs.A;

	Cap();

	return *this;
}

Colour& Colour::operator*=(const float rhs){
	R *= rhs;
	G *= rhs;
	B *= rhs;
	A *= rhs;

	Cap();

	return *this;
}

Colour Colour::operator/(const Colour& rhs){
	Colour temp(*this);
	return (temp /= rhs);
}

Colour Colour::operator/(const float rhs){
	Colour temp(*this);
	return (temp /= rhs);
}

Colour& Colour::operator/=(const Colour& rhs){
	if(rhs.R != 0.0f) R /= rhs.R;
	if(rhs.G != 0.0f) G /= rhs.G;
	if(rhs.B != 0.0f) B /= rhs.B;
	if(rhs.A != 0.0f) A /= rhs.A;

	Cap();

	return *this;
}

Colour& Colour::operator/=(const float rhs){
	if (rhs != 0.0f) R /= rhs;
	if (rhs != 0.0f) G /= rhs;
	if (rhs != 0.0f) B /= rhs;
	if (rhs != 0.0f) A /= rhs;

	Cap();

	return *this;
}

void Colour::Cap(){
	((R < 0.0f) ? R = 0.0f : (R > 1.0f) ? R = 1.0f : R = R);
	((G < 0.0f) ? G = 0.0f : (G > 1.0f) ? G = 1.0f : G = G);
	((B < 0.0f) ? B = 0.0f : (B > 1.0f) ? B = 1.0f : B = B);
	((A < 0.0f) ? A = 0.0f : (A > 1.0f) ? A = 1.0f : A = A);
}