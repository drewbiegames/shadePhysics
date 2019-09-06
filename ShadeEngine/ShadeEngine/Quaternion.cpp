#include "Quaternion.h"

#include "Utils.h"
#include "Vector3D.h"

Quaternion::Quaternion(){
	X = Y = Z = 0.0f;
	W = 1.0f;
}

Quaternion::~Quaternion(){

}

void Quaternion::CreateFromAxisAngle(float x, float y, float z, float degrees){
	//Convert degrees to radians
	float angle = util::RadiansFromDegrees(degrees);
	//calc the sin(theta / 2)
	float thesin = (float)sin(angle / 2.0f);

	Vector3Df temp(x, y, z);
	temp.normalise();

	//W = cos(theta / 2);
	W = (float)cos(angle / 2.0f);

	X = float(temp.X * thesin);
	Y = float(temp.Y * thesin);
	Z = float(temp.Z * thesin);

	//this->normalise();

}

void Quaternion::CreateFromEuler(float x, float y, float z){
	float radianX = util::RadiansFromDegrees(x);
	float radianY = util::RadiansFromDegrees(y);
	float radianZ = util::RadiansFromDegrees(z);

	float cosX = cosf(radianX / 2.0f);
	float sinX = sinf(radianX / 2.0f);
					
	float cosY = cosf(radianY / 2.0f);
	float sinY = sinf(radianY / 2.0f);
					
	float cosZ = cosf(radianZ / 2.0f);
	float sinZ = sinf(radianZ / 2.0f);

	W = cosZ * cosY * cosX + sinZ * sinY * sinX;
	X = cosZ * cosY * sinX - sinZ * sinY * cosX;
	Y = cosZ * sinY * cosX + sinZ * cosY * sinX;
	Z = sinZ * cosY * cosX - cosZ * sinY * sinX;
}

void Quaternion::CreateMatrix(float* matrix){
	if (!matrix) return;

	//first row
	matrix[0] = 1.0f - 2.0f * (Y * Y + Z * Z);
	matrix[1] = 2.0f * (X * Y + Z * W);
	matrix[2] = 2.0f * (X * Z - Y * W);
	matrix[3] = 0.0f;

	//second row
	matrix[4] = 2.0f * (X * Y - Z * W);
	matrix[5] = 1.0f - 2.0f * (X * X + Z * Z);
	matrix[6] = 2.0f * (Z * Y + X * W);
	matrix[7] = 0.0f;

	//third row
	matrix[8] = 2.0f * (X * Z + Y * W);
	matrix[9] = 2.0f * (Y * Z - X * W);
	matrix[10] = 1.0f - 2.0f * (X * X + Y * Y);
	matrix[11] = 0.0f;

	//forth row
	matrix[12] = 0.0f;
	matrix[13] = 0.0f;
	matrix[14] = 0.0f;
	matrix[15] = 1.0f;
}

Quaternion Quaternion::operator*(Quaternion& q){
	Quaternion r;

	r.X = W * q.X + X * q.W + Y * q.Z - Z * q.Y;
	r.Y = W * q.Y - X * q.Z + Y * q.W + Z * q.X;
	r.Z = W * q.Z + X *	q.Y - Y	* q.X + Z * q.W;
	r.W = W * q.W - X *	q.X - Y	* q.Y - Z * q.Z;
	
	return r.normalise();
}

Vector3Df Quaternion::operator*(Vector3Df& v){
	Vector3Df vn(v);
	vn.normalise();

	Quaternion vecQuat, resQuat;
	vecQuat.X = vn.X;
	vecQuat.Y = vn.Y;
	vecQuat.Z = vn.Z;
	vecQuat.W = 0.0f;

	resQuat = vecQuat * -(*this);
	resQuat = *this * resQuat;

	return Vector3Df(resQuat.X, resQuat.Y, resQuat.Z);
}

Quaternion Quaternion::mul(Quaternion q){
	Quaternion R;

	R.X = W * q.X + X * q.W + Y * q.Z - Z * q.Y;
	R.Y = W * q.Y - X * q.Z + Y * q.W + Z * q.X;
	R.Z = W * q.Z + X *	q.Y - Y	* q.X + Z * q.W;
	R.W = W * q.W - X *	q.X - Y	* q.Y - Z * q.Z;

	return R.normalise();
}

Quaternion Quaternion::mul(Vector3Df r){
	float w = -X * r.X - Y * r.Y - Z * r.Z;
	float x = W * r.X + Y * r.Z - Z * r.Y;
	float y = W * r.Y + Z * r.X - X * r.Z;
	float z = W * r.Z + X * r.Y - Y * r.X;

	return Quaternion(x, y, z, w);
}

Quaternion Quaternion::operator-(){
	Quaternion c;

	c.W = W;
	c.X = -X;
	c.Y = -Y;
	c.Z = -Z;

	return c;
}

Quaternion Quaternion::Slerp(const Quaternion& from, const Quaternion& to, float t)
{
	// This is from www.gamasutra.com/features/19980703/quaternions_01.htm

	float to1[4];
	double omega, cosom, sinom, scale0, scale1;

	// calc cosine
	cosom = from.X * to.X + from.Y * to.Y + from.Z * to.Z
		+ from.W * to.W;

	// adjust signs (if necessary)
	if (cosom < 0)
	{
		cosom = -cosom;
		to1[0] = -to.X;
		to1[1] = -to.Y;
		to1[2] = -to.Z;
		to1[3] = -to.W;
	}
	else
	{
		to1[0] = to.X;
		to1[1] = to.Y;
		to1[2] = to.Z;
		to1[3] = to.W;
	}

	// calculate coefficients

	static const double DELTA = 0.001;
	if ((1.0 - cosom) > DELTA)
	{
		// standard case (slerp)
		omega = acos(cosom);
		sinom = sin(omega);
		scale0 = sin((1.0 - t) * omega) / sinom;
		scale1 = sin(t * omega) / sinom;
	}
	else
	{
		// "from" and "to" quaternions are very close 
		//  ... so we can do a linear interpolation
		scale0 = 1.0 - t;
		scale1 = t;
	}

	Quaternion res;

	// calculate final values
	res.X = (float)(scale0 * (double)from.X + scale1 * (double)to1[0]);
	res.Y = (float)(scale0 * (double)from.Y + scale1 * (double)to1[1]);
	res.Z = (float)(scale0 * (double)from.Z + scale1 * (double)to1[2]);
	res.W = (float)(scale0 * (double)from.W + scale1 * (double)to1[3]);

	return res;
}


float Quaternion::length(){
	return (float)sqrt(X * X + Y * Y + Z * Z + W * W);
}

Quaternion Quaternion::normalise(){
	float l = length();

	X /= l; 
	Y /= l;
	Z /= l;
	W /= l;

	return (*this);
}

Quaternion Quaternion::conjugate(){
	return Quaternion(-X, -Y, -Z, W);
}

void Quaternion::Output(){
	std::cout << "Q(W = " << W << "; X= " << X << "; Y= " << Y << "; Z= " << Z << ")" << std::endl;
}

//Quaternion Quaternion::operator *(Vector3Df vec){
//	Quaternion r;
//	vec.normalise();
//
//	r.W = 1.0f;
//	r.X = (float)vec.X;
//	r.Y = (float)vec.Y;
//	r.Z = (float)vec.Z;
//
//	//TODO, is this order correct?!?
//	return (*this) * r;
//};

//TODO: extract angle and axis
//angle = arccos(w) * 2;
//V.normlise()