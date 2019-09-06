#pragma once

#include "Transform.h"
#include "tinyxml.h"

/*
	Rigid Body Class

	Created: 27th Nov 2015
	by: Andrew Bowden

	ref: Class slides "Physics 101" by Karsten Vermeulen
*/

enum INTERGRATIONTYPE{
	EULER_INTERGRATION,
	VERLET_INTERGRATION
};

class RigidBody {
public:
	RigidBody();

	void Update();
	void DebugDraw();

	void Load(TiXmlElement* node, Transform& transform);
	void Load(Transform* transform, Vec3 centreOfMass, GLfloat mMass, INTERGRATIONTYPE inter = EULER_INTERGRATION, bool gravity = false);

	void Accelerate(Vec3 accel);
	void AddForce(Vec3 dir);
	void AddTorque(Vec3 pointofimpact, Vec3 dir);

	void ToggleGravity(){ mApplyGravity = !mApplyGravity; }
	bool Enabled(){ return mEnabled; }

	void setGravity(const bool grav){ mApplyGravity = grav; }
	void setMass(const GLfloat mass){ mMass = mass; }
	void setCentreOfMass(const Vec3 com){ mCentreOfMass = com; }
	void setDampening(const GLfloat damp){ mDampening = damp; }
	void setIntergration(const INTERGRATIONTYPE type){ mIntergration = type; }
	void setVelocity(const Vec3 vel){ mVelocity = vel; }

	Vec3 getCentreOfMass(){ return mCentreOfMass; }
	GLfloat getMass(){ return mMass; }
	Vec3 getAcceleration(){ return mAcceleration; }
	Vec3 getVelocity(){ return mVelocity; }


	Vec3& getVelocityPtr(){ return mVelocity; }
	
	
private:
	bool mEnabled;

	Transform* mObjectTransform;
	Vec3 mOldPos;
	Quaternion mOldRot;

	bool mApplyGravity;
	GLfloat mDampening;

	Vec3 mCentreOfMass;
	GLfloat mMass;

	Vec3 mAcceleration;
	Vec3 mVelocity;
	
	float mTorqueMagnitude;
	Vec3 mTorqueAxis;

	INTERGRATIONTYPE mIntergration;
	
	static float GRAVITY;
};