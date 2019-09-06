#include "GLCamera.h"
#include "Utils.h"

//calls gluLookAt
void GLCamera::Draw(){
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(
		mTransform.position.X, mTransform.position.Y, mTransform.position.Z,
		mTarget.X, mTarget.Y, mTarget.Z,
		mUp.X, mUp.Y, mUp.Z);
}

void GLCamera::Update(){
	//static float a = 0;
	//a += util::DegreesFromRadians(0.001f);
	//
	//mTransform.position.X = float(cos(a)) * 10;
	//mTransform.position.Z = float(sin(a)) * 10;
}

void GLCamera::Clean(){

}

//Load from XML Node
void GLCamera::Load(TiXmlElement* node){
	double x, y, z;

	node->Attribute("posX", &x);
	node->Attribute("posY", &y);
	node->Attribute("posZ", &z);

	mTransform.position = Vector3Df(float(x), float(y), float(z));

	node->Attribute("eyeX", &x);
	node->Attribute("eyeY", &y);
	node->Attribute("eyeZ", &z);

	mTarget = Vector3Df(float(x), float(y), float(z));

	node->Attribute("upX", &x);
	node->Attribute("upY", &y);
	node->Attribute("upZ", &z);

	mUp = Vector3Df(float(x), float(y), float(z));
}

//Load from hard coded variables
void GLCamera::Load(Vector3Df pos){
	mTransform.position = pos;
}

static bool sgCameraRegister = TheGameObjectFactory::Instance()->RegisterType("Camera", Create<GLCamera>);