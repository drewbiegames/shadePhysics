#pragma once

#include  "GLGameObject.h"

/*
	Cube Game Object class
*/

class Cube : public GLGameObject{
public:
	
	void Update();
	void Draw();
	void Clean();
	void React(GameObject* obj){}

	void Load(TiXmlElement* node);
	

private:
	GLfloat mSize;

	void Load(Vector3Df pos);
};