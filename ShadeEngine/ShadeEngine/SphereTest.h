#pragma once

#include "GLGameObject.h"

class SphereTest : public GLGameObject{
public:
	SphereTest() : GLGameObject() {}

	void Update();
	void Draw();
	void Clean();
	void React(GameObject* obj);

	void Load(TiXmlElement* node);
	void Load(Vector3Df pos);

	~SphereTest(){ Clean(); }
private:
	float mRadius;
};