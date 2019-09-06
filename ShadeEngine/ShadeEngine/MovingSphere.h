#pragma once

#include "GLGameObject.h"

#include "Particle.h"

class MovingSphere : public GLGameObject {
public:
	
	void Update();
	void Draw();
	void Clean();

	void Load(TiXmlElement* node);

	void React(GameObject* other);

	GLfloat getRadius();

private:

};