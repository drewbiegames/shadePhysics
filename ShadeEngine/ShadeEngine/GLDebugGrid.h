#pragma once
#include "GLGameObject.h"
class GLDebugGrid :	public GLGameObject{
public:
	GLDebugGrid();

	void Update();
	void Draw();
	void Clean();

	void Load(TiXmlElement* node);

	void React(GameObject* other);

	void Init(GLuint size);

	~GLDebugGrid(){ delete mShader; mShader = nullptr; }

private:
	void Load(Vector3Df* other){}

	GLfloat mHalfedLength;
	GLint mLinesPerAxis;
	GLfloat mSpaceBetweenLines;


	GLuint mVAO;
	GLuint mVBO_color;
	GLuint mEBO_color;

	GLuint mVBO_verts;
	GLuint mEBO_verts;

	GLuint mCount;
};

