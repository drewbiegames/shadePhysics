#pragma once

#include "GLGameObject.h"

/*
	GL Static Camera Class
*/


class GLCamera : public GLGameObject {
public:
	GLCamera() : GLGameObject(), mTarget(Vector3Df(0.0f,0.0f,0.0f)), mUp(Vector3Df(0.0f,1.0f,0.0f)) {}
	virtual ~GLCamera(){}

	void Update();
	void Draw();
	void Clean();

	void React(GameObject* obj){}

	virtual void Load(TiXmlElement* node);
	virtual void Load(Vector3Df pos);
	void setLookAt(Vector3Df eye){ mTarget = eye; }

	Vector3Df getTarget(){ return mTarget; }
	Vector3Df getUp(){ return mUp; }
	Vector3Df getDirection(){ return mTransform.position - mTarget; }

protected:
	Vector3Df mTarget;
	Vector3Df mUp;
};