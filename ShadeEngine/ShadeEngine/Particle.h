#pragma once

#include "GLGameObject.h"

//Date created:  12th Nov 2015
//Created by: Drew Bowden
//ref: https://www.youtube.com/watch?v=EhDtJxX0sCA&index=11&list=PL7wAPgl1JVvUEb0dIygHzO4698tmcwLk9
//Youtube series Coding Math by Coding Math channel
//Coding Math is a series of youtube videos that explains 2D math
//using javascript, I have adapted the code into C++ and applied it to 3D

class Particle : public GLGameObject {
public:
	Particle(Vec3 pos, Vec3 velocity, float mass, float resistance, bool fixed = false, bool gravity = false);

	void Update();
	void Draw();
	void Clean();

	void React(GameObject* obj);

	void Load(TiXmlElement* node);

	void Accelerate(Vector3Df accel);
	void AddForce(Vector3Df force);
	void GravitateTo(Particle* other);
	void SpringTo(Particle* other, float seperation, float forceScalar);
	void ClothSpringTo(Particle* other, float seperation, float forceScalar);
	void ConstrainTo(Particle* other, float seperation);

	float getMass(){ return mRigidBody.getMass(); }
	float angleTo(Vec3 point);
	float distanceTo(Vec3 point);
	float sqDistanceTo(Vec3 point);

	void SelectedToggle(){ mSelected = !mSelected; }

private:
	bool mFixed;
	bool mSelected;
};