#include "SphereTest.h"

#include "Sphere.h"
#include "SimpleCollision.h"

void SphereTest::Update(){}

void SphereTest::Draw(){
	glPushMatrix();
		glTranslatef(mPosition.X, mPosition.Y, mPosition.Z);
		
		glutWireSphere(mRadius, 12, 12);

	glPopMatrix();
}

void SphereTest::Clean(){
	TheSimpleCollision::Instance()->UnregisterColliable(this);
}

void SphereTest::Load(TiXmlElement* node){
	GLGameObject::Load(node);

	double rad;
	node->Attribute("radius", &rad);
	mBounds = new Sphere(this, mPosition,mVelocity, mRotation, float(rad));
	mRadius = float(rad);

	TheSimpleCollision::Instance()->RegisterCollidable(this);
}

void SphereTest::React(GameObject* obj){

}

void SphereTest::Load(Vector3Df pos){}

static bool sgSphereReg = TheGameObjectFactory::Instance()->RegisterType("SphereTest", Create<SphereTest>);

