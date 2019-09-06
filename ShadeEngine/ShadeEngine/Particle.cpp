#include "Particle.h"
#include "Timer.h"

Particle::Particle(Vec3 pos, Vec3 velocity, float mass, float resistance, bool fixed, bool gravity){
	mTransform.position = pos;
	mRigidBody.setVelocity(velocity);
	mRigidBody.setDampening(resistance);
	mRigidBody.Load(&mTransform, Vec3(0.0f,0.0f,0.0f), mass, EULER_INTERGRATION, gravity);
	mFixed = fixed;
	mSelected = false;
}


void Particle::Update(){
	if(!mFixed) mRigidBody.Update();
}

void Particle::Draw(){
	glPushMatrix();
		glTranslatef(mTransform.position.X, mTransform.position.Y, mTransform.position.Z);
		if (mSelected) glColor3f(1.0f, 0.0f, 0.0f);
		glutSolidSphere(0.1, 10, 10);
		if (mSelected) glColor3f(1.0f, 1.0f, 1.0f);
	glPopMatrix();
}

void Particle::Clean(){

}

void Particle::Load(TiXmlElement* node){

}

void Particle::React(GameObject* obj){

}

void Particle::Accelerate(Vector3Df accel){
	if (!mFixed) mRigidBody.Accelerate(accel);
}

void Particle::AddForce(Vector3Df force){
	if(!mFixed) mRigidBody.AddForce(force);
}

void Particle::GravitateTo(Particle* other){
	Vec3 grav = *other->getPosition() - mTransform.position;
	float distSq = sqDistanceTo(*other->getPosition());

	grav.setLength(other->getMass() / distSq);

	Accelerate(grav);
}

void Particle::SpringTo(Particle* other, float seperation, float scalar){
	Vec3 direction = *other->getPosition() - mTransform.position;
	direction.setLength(direction.Length() - seperation);

	Vec3 spring = (direction * scalar);
	
	this->AddForce(spring);
	other->AddForce(-spring);
}

void Particle::ClothSpringTo(Particle* other, float seperation, float scalar){
	Vec3 direction = *other->getPosition() - mTransform.position;
	direction.setLength((direction.Length() - seperation) * 0.5f);

	Vec3 spring = (direction * scalar);

	this->AddForce(spring);
	other->AddForce(-spring);
}

void Particle::ConstrainTo(Particle* other, float rest){
	//Ref: http://cg.alexandra.dk/?p=147

	Vec3 dir = *other->getPosition() - *this->getPosition();
	float cur = dir.Length() - rest; //current lentgh
	//dir.normalise();
	Vec3 correction = dir * (1 - rest / cur);
	correction = (correction * 0.5);
	this->AddForce(correction);
	other->AddForce(-correction);
}

float Particle::angleTo(Vec3 point){
	return acosf(mTransform.position.normalised().dot(point));
}

float Particle::distanceTo(Vec3 point){
	return (mTransform.position - point).Length();
}

float Particle::sqDistanceTo(Vec3 point){
	return (mTransform.position - point).SqLength();
}

