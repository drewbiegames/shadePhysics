#pragma once 

#include "GameObject.h"

#include "Transform.h"
#include "GLMaterial.h"
#include "GLTexture.h"
#include "GLMesh.h"
#include "GLShader.h"
#include "RigidBody.h"

/*
	OpenGL Game Object Class
*/

class GLGameObject : public GameObject {
public:
	GLGameObject() : mTransform(), mRigidBody(), 
		mMaterial(nullptr), mTexture(nullptr) 
	{}

	virtual ~GLGameObject(){}

	virtual void Draw() = 0;
	virtual void Update() = 0;
	virtual void Clean() = 0;
	virtual void React(GameObject* obj) = 0;

	virtual void Load(TiXmlElement* node) = 0;

	Vector3Df* getPosition() { return &mTransform.position; }
	Quaternion* getRotation() { return &mTransform.rotation; }
	GLMaterial* getMaterial() { return mMaterial; }
	GLTexture* getTexture() { return mTexture; }
	GLMesh* getMesh() { return mMesh; }

protected:

	Transform mTransform;

	RigidBody mRigidBody;

	GLMaterial* mMaterial;
	GLTexture* mTexture;
	GLMesh* mMesh;
	GLShader* mShader;
	
	virtual void Load(Vector3Df pos){}
};