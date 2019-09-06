#pragma once

#include "Singleton.h"
#include "Defines.h"
#include "GLShader.h"

class FrameBuffer : public Uncopyable {
public:
	void Render();

	void Bind();
	void Unbind();

	void Load(TiXmlElement* node);

	void setShaderVariables(GLfloat offset, GLint divisor);
	void setShaderVariables(GLint offset_divisor, GLint divisor);

	void Clean();

	GLuint getQuadVBO(){ return mQuadVBO; }
	GLuint getQuadVAO(){ return mQuadVAO; }

private:
	FrameBuffer() : mFBO(0), mShader(nullptr) {}
	friend class SingletonT<FrameBuffer>;

	GLShader* mShader;

	void genFrameBuffer();
	GLuint mFBO;
	GLuint mTexture;

	GLuint mRBO;

	void loadRenderQuad();
	GLuint mQuadVAO;
	GLuint mQuadVBO;

	//Shader variables;
	GLfloat fOffset;
	GLint fDivisor;
};

typedef SingletonT<FrameBuffer> TheFrameBuffer;