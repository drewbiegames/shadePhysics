#include "RigidBody.h"

#include "Timer.h"
#include <iostream>

float RigidBody::GRAVITY = -0.987f;

RigidBody::RigidBody()
	: mObjectTransform(nullptr), mOldPos(Vec3()), mApplyGravity(false), mEnabled(true),
	mDampening(1.0f), mCentreOfMass(Vec3()), mMass(0.0f), 
	mAcceleration(Vec3()), mVelocity(Vec3()),
	mTorqueMagnitude(0.0f), mTorqueAxis(Vec3()) 
{}


void RigidBody::Update(){
	float time = TheTimer::Instance()->GetDeltaTime();

	if (mApplyGravity) 
		Accelerate(Vec3(0.0f, GRAVITY * time, 0.0f));

	switch (mIntergration)
	{
		case EULER_INTERGRATION:
		{
			Vec3 oldVel = mVelocity;
			mVelocity += mAcceleration * time;
			mObjectTransform->position += ((oldVel + mVelocity) / 2) * time;
			mVelocity *= mDampening;
		}
			break;

		case VERLET_INTERGRATION:
		{
			//broken
			Vec3 accelTime = (mAcceleration * time * time);
			Vec3 diff = ((mObjectTransform->position - mOldPos) * (mDampening)) - (accelTime);
			mOldPos = mObjectTransform->position;
			mObjectTransform->position += diff;
		}
			break;

		default:
			break;
	}

	mAcceleration = Vec3(0.0f, 0.0f, 0.0f);
}

void RigidBody::DebugDraw(){
	
}

void RigidBody::Load(TiXmlElement* node, Transform& transform){
	mObjectTransform = &transform;
	mOldPos = mObjectTransform->position;
	mOldRot = mObjectTransform->rotation;


	std::string str = node->Attribute("gravity");
	if (str == "true") mApplyGravity = true;
	else mApplyGravity = false;

	str = node->Attribute("intergration");
	if (str == "euler") mIntergration = EULER_INTERGRATION;
	else if (str == "verlet") mIntergration = VERLET_INTERGRATION;

	double num;
	node->Attribute("mcom_x", &num);
	mCentreOfMass.X = float(num);
	node->Attribute("mcom_y", &num);
	mCentreOfMass.Y = float(num);
	node->Attribute("mcom_z", &num);
	mCentreOfMass.Z = float(num);

	node->Attribute("mass", &num);
	mMass = GLfloat(num);

	mEnabled = true;
}

void RigidBody::Load(Transform* transform, Vec3 centreOfMass, GLfloat mass, INTERGRATIONTYPE inter, bool gravity){
	mObjectTransform = transform;
	mOldPos = mObjectTransform->position;
	mOldRot = mObjectTransform->rotation;

	mCentreOfMass = centreOfMass;

	mIntergration = inter;

	mApplyGravity = gravity;

	mMass = mass;

	mEnabled = true;
}

void RigidBody::Accelerate(Vec3 accel){
	mAcceleration += accel;
}

void RigidBody::AddForce(Vec3 dir){
	mAcceleration += dir / mMass;
}

void RigidBody::AddTorque(Vec3 pointofimpact, Vec3 dir){
	dir *= TheTimer::Instance()->GetDeltaTime();
	Vec3 cross = dir.cross(pointofimpact);
	mTorqueAxis += cross;
	mTorqueMagnitude += cross.Length() * mMass;
}