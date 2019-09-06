#pragma once

#include "GLGameObject.h"
#include "Particle.h"

class ClothTest : public GLGameObject {
public:
	~ClothTest(){ Clean(); }

	void Draw();	
	void Update();

	void Clean();

	void Load(TiXmlElement* node);

	void React(GameObject* object);

	void AddWindForce(Vec3 direction);

private:

	//Particles in the cloth
	std::vector<std::vector<Particle*>> mParticles;

	//Variables for springs
	float mSeperationStruct;
	float mForceScalarStruct;
	float mSeperationShear;
	float mForceScalarShear;
	float mSeperationBend;
	float mForceScalarBend;

	Vec3 mWind;
	
	//Mesh variables - exposed due to the dynamic drawing of cloth
	GLuint mVAO;
	GLuint mVBO_vert;
	GLuint mVBO_norm;
	GLuint mVBO_uvs;

	//Normals for each particle
	std::vector<std::vector<Vec3>> mAccumulatedNormals;

	//Data for vertex buffers
	std::vector<GLfloat> mVertices;
	std::vector<GLfloat> mNormals;
	std::vector<GLfloat> mUVs;

	//Mesh functions - for dynamic drawing
	void makeVAO();
	void createArrays();
	void updateVAO();

	//for applying a wind force to a triangle
	void triangleWindForce(Particle* p1, Particle* p2, Particle* p3, Vec3 direction);
	

	Vec3 calculateTriangleNormal(Particle* p1, Particle* p2, Particle* p3);
	Vec3 calcNormal(GLuint w, GLuint h, GLuint width, GLuint height);

	void sphereCollisionReaction(Vec3 centre, GLfloat radius);
	
	//For when collisions are implemented.
	void calcAABB();
};