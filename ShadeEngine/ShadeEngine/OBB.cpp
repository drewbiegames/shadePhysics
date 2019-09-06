#include "OBB.h"
#include "GLGameObject.h"
#include "Utils.h"

OBB::OBB() : BoundingShape3D() {
	mAxes[0] = Vector3Df(1.0f, 0.0f, 0.0f); //X axis
	mAxes[1] = Vector3Df(0.0f, 1.0f, 0.0f); //Y axis
	mAxes[2] = Vector3Df(0.0f, 0.0f, 1.0f); //Z axis
}

OBB::OBB(GameObject* obj, Vector3Df& pos, Vector3Df& vel, Quaternion& rot, Vector3Df halfSize)
	: BoundingShape3D(obj, pos, vel, rot), mHalfSize(halfSize) {

	mAxes[0] = Vector3Df(1.0f, 0.0f, 0.0f); //X axis
	mAxes[1] = Vector3Df(0.0f, 1.0f, 0.0f); //Y axis
	mAxes[2] = Vector3Df(0.0f, 0.0f, 1.0f); //Z axis

	for (int ii = 0; ii < 8; ii++){
		mCorners[ii] = Vector3Df(0.0f, 0.0f, 0.0f);
	}
}

void OBB::CalculateOBB(){
	Vector3Df right		= *Rotation * mAxes[0];
	Vector3Df up		= *Rotation * mAxes[1];
	Vector3Df foreward	= *Rotation * mAxes[2];

	mCorners[0] = *Position - right + up - foreward; //top left front
	mCorners[1] = *Position - right - up - foreward; //bottom left front
	mCorners[2] = *Position + right - up - foreward; //bottom right front
	mCorners[3] = *Position + right + up - foreward; //top right front
				  
	mCorners[4] = *Position - right + up + foreward; //top left back
	mCorners[5] = *Position - right - up + foreward; //bottom left back
	mCorners[6] = *Position + right - up + foreward; //bottom right back
	mCorners[7] = *Position + right + up + foreward; //top right back
}

void OBB::CalculateAABB(){
	std::vector<Vector3Df> axes;

	axes.push_back(*Rotation * mAxes[0]);
	axes.push_back(*Rotation * mAxes[1]);
	axes.push_back(*Rotation * mAxes[2]);

	float x = std::max(
		mCorners[0].X, 
		std::max(mCorners[1].X, 
		std::max(mCorners[2].X, 
		std::max(mCorners[3].X, 
		std::max(mCorners[4].X, 
		std::max(mCorners[5].X, 
		std::max(mCorners[6].X, 
		mCorners[7].X
		)))))));
		
	float y = std::max(
		mCorners[0].Y,
		std::max(mCorners[1].Y,
		std::max(mCorners[2].Y,
		std::max(mCorners[3].Y,
		std::max(mCorners[4].Y,
		std::max(mCorners[5].Y,
		std::max(mCorners[6].Y,
		mCorners[7].Y
		)))))));

	float z = std::max(
		mCorners[0].Z,
		std::max(mCorners[1].Z,
		std::max(mCorners[2].Z,
		std::max(mCorners[3].Z,
		std::max(mCorners[4].Z,
		std::max(mCorners[5].Z,
		std::max(mCorners[6].Z,
		mCorners[7].Z
		)))))));

	AxisAlign.Max = Vector3Df(x, y, z);

	x = std::min(
		mCorners[0].X,
		std::min(mCorners[1].X,
		std::min(mCorners[2].X,
		std::min(mCorners[3].X,
		std::min(mCorners[4].X,
		std::min(mCorners[5].X,
		std::min(mCorners[6].X,
		mCorners[7].X
		)))))));

	y = std::min(
		mCorners[0].Y,
		std::min(mCorners[1].Y,
		std::min(mCorners[2].Y,
		std::min(mCorners[3].Y,
		std::min(mCorners[4].Y,
		std::min(mCorners[5].Y,
		std::min(mCorners[6].Y,
		mCorners[7].Y
		)))))));

	z = std::min(
		mCorners[0].Z,
		std::min(mCorners[1].Z,
		std::min(mCorners[2].Z,
		std::min(mCorners[3].Z,
		std::min(mCorners[4].Z,
		std::min(mCorners[5].Z,
		std::min(mCorners[6].Z,
		mCorners[7].Z
		)))))));

	AxisAlign.Min = Vector3Df(x, y, z);
	AxisAlign.Object = Object;
}

void OBB::Draw(){
	glPushMatrix();

	glBegin(GL_LINES);
		//Front face
		glVertex3f(mCorners[0].X, mCorners[0].Y, mCorners[0].Z);
		glVertex3f(mCorners[1].X, mCorners[1].Y, mCorners[1].Z);

		glVertex3f(mCorners[1].X, mCorners[1].Y, mCorners[1].Z);
		glVertex3f(mCorners[2].X, mCorners[2].Y, mCorners[2].Z);

		glVertex3f(mCorners[2].X, mCorners[2].Y, mCorners[2].Z);
		glVertex3f(mCorners[3].X, mCorners[3].Y, mCorners[3].Z);

		glVertex3f(mCorners[3].X, mCorners[3].Y, mCorners[3].Z);
		glVertex3f(mCorners[0].X, mCorners[0].Y, mCorners[0].Z);

		//Back Face
		glVertex3f(mCorners[4].X, mCorners[4].Y, mCorners[4].Z);
		glVertex3f(mCorners[5].X, mCorners[5].Y, mCorners[5].Z);
		
		glVertex3f(mCorners[5].X, mCorners[5].Y, mCorners[5].Z);
		glVertex3f(mCorners[6].X, mCorners[6].Y, mCorners[6].Z);
		
		glVertex3f(mCorners[6].X, mCorners[6].Y, mCorners[6].Z);
		glVertex3f(mCorners[7].X, mCorners[7].Y, mCorners[7].Z);
		
		glVertex3f(mCorners[7].X, mCorners[7].Y, mCorners[7].Z);
		glVertex3f(mCorners[4].X, mCorners[4].Y, mCorners[4].Z);
		
		//Right Face
		glVertex3f(mCorners[3].X, mCorners[3].Y, mCorners[3].Z);
		glVertex3f(mCorners[7].X, mCorners[7].Y, mCorners[7].Z);
		
		glVertex3f(mCorners[2].X, mCorners[2].Y, mCorners[2].Z);
		glVertex3f(mCorners[6].X, mCorners[6].Y, mCorners[6].Z);
		
		//Left face
		glVertex3f(mCorners[0].X, mCorners[0].Y, mCorners[0].Z);
		glVertex3f(mCorners[4].X, mCorners[4].Y, mCorners[4].Z);
		
		glVertex3f(mCorners[1].X, mCorners[1].Y, mCorners[1].Z);
		glVertex3f(mCorners[5].X, mCorners[5].Y, mCorners[5].Z);

	glEnd();


	glPopMatrix();
}

bool OBB::Collide(OBB& other){
	CalculateOBB();
	other.CalculateOBB();
	bool result = true;
	std::vector<Vector3Df> axes;

	axes.push_back(*Rotation * mAxes[0]);
	axes.push_back(*Rotation * mAxes[1]);
	axes.push_back(*Rotation * mAxes[2]);

	axes.push_back(*other.Rotation * mAxes[0]);
	axes.push_back(*other.Rotation * mAxes[1]);
	axes.push_back(*other.Rotation * mAxes[2]);

	axes.push_back(axes[0].cross(axes[3]));
	axes.push_back(axes[0].cross(axes[4]));
	axes.push_back(axes[0].cross(axes[5]));

	axes.push_back(axes[1].cross(axes[3]));
	axes.push_back(axes[1].cross(axes[4]));
	axes.push_back(axes[1].cross(axes[5]));

	axes.push_back(axes[2].cross(axes[3]));
	axes.push_back(axes[2].cross(axes[4]));
	axes.push_back(axes[2].cross(axes[5]));

	//loop of axes
	for (unsigned int ii = 0; ii < axes.size(); ++ii){
		if (axes[ii].isZero()) continue;
		axes[ii].normalise();
		float min[2] = { 0.0f, 0.0f }; //0 = this; 1 = other
		float max[2] = { 0.0f, 0.0f };
		//loop of corners
		for (unsigned int cc = 0; cc < 8; ++cc){
			//this box
			float value = mCorners[cc].dot(axes[ii]);
			min[0] = std::min(value, min[0]);
			max[0] = std::max(value, max[0]);
			//other box
			value = other.corner(cc).dot(axes[ii]);
			min[1] = std::min(value, min[1]);
			max[1] = std::max(value, max[1]);
		}
		if (!util::RangeIntersect(min[0], max[0], min[1], max[1])){
			result = false;
			break;
		}
	}
	return result;
}