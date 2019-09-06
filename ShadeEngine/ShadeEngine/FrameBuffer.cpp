#include "FrameBuffer.h"

#include <iostream>

void FrameBuffer::Render(){
	//clear the screen
	glClearColor(0.75f, 0.75f, 0.75f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	glDisable(GL_DEPTH_TEST);

	//draw screen;
	mShader->Enable();
	glBindVertexArray(mQuadVAO);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, mTexture);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glBindVertexArray(0);

	mShader->Disable();
}

void FrameBuffer::Bind(){
	glBindFramebuffer(GL_FRAMEBUFFER, mFBO);
}

void FrameBuffer::Unbind(){
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void FrameBuffer::Load(TiXmlElement* node){
	std::string shader = node->Attribute("shader");

	mShader = TheAssetManager::Instance()->Get<GLShader>(shader);

	int offset;
	node->Attribute("offset", &offset);
	fOffset = float(1.0 / offset);

	int divisor;
	node->Attribute("divisor", &divisor);
	fDivisor = divisor;

	setShaderVariables(fOffset, fDivisor);
	
	genFrameBuffer();

	loadRenderQuad();
}

void FrameBuffer::setShaderVariables(GLfloat offset, GLint divisor){
	fOffset = offset;

	mShader->Enable();
	
	GLuint offsetID = mShader->getUniform("fOffset");
	glUniform1f(offsetID, fOffset);

	GLuint divisorID = mShader->getUniform("fDivisor");
	glUniform1i(divisorID, divisor);
	
	mShader->Disable();
}

void FrameBuffer::setShaderVariables(GLint offset_divisor, GLint divisor){
	fOffset = float(1.0 / divisor);
	setShaderVariables(fOffset, divisor);
}

void FrameBuffer::Clean(){
	glDeleteBuffers(1, &mFBO);
	mFBO = 0;

	mShader = nullptr;
}

void FrameBuffer::genFrameBuffer(){
	//Generate the frame buffer
	glGenFramebuffers(1, &mFBO);
	glBindFramebuffer(GL_FRAMEBUFFER, mFBO);

	//Generate blank texture (Data is NULL so that it is dynamic)
	glGenTextures(1, &mTexture);
	glBindTexture(GL_TEXTURE_2D, mTexture);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, WINDOWWIDTH, WINDOWHEIGHT, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glBindTexture(GL_TEXTURE_2D, 0);

	//Attach the textures to the frame buffer
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, mTexture, 0);

	//Genrate render buffer object for depth and stencil
	glGenRenderbuffers(1, &mRBO);
	glBindRenderbuffer(GL_RENDERBUFFER, mRBO);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, WINDOWWIDTH, WINDOWHEIGHT);
	glBindBuffer(GL_RENDERBUFFER, 0);
	//attach RBO
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, mRBO);

	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE){
		std::cout << "Error: Framebuffer is not complete!" << std::endl;
		Clean();
	}

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void FrameBuffer::loadRenderQuad(){

	//ref: http://learnopengl.com/#!Advanced-OpenGL/Framebuffers
	GLfloat quadVerts[] = {
		//positions	  //texcoords
		-1.0f,  1.0f, 0.0f, 1.0f,
		-1.0f, -1.0f, 0.0f, 0.0f,
		 1.0f, -1.0f, 1.0f, 0.0f,

		-1.0f,  1.0f, 0.0f, 1.0f,
		 1.0f, -1.0f, 1.0f, 0.0f,
		 1.0f,  1.0f, 1.0f, 1.0f
	};

	GLuint vertAtrrib = mShader->getAttribute("vVertex");
	GLuint texcoordAttrib = mShader->getAttribute("vTexCoord");

	glGenVertexArrays(1, &mQuadVAO);
	glGenBuffers(1, &mQuadVBO);
	glBindVertexArray(mQuadVAO);
	glBindBuffer(GL_ARRAY_BUFFER, mQuadVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(quadVerts), &quadVerts, GL_STATIC_DRAW);
	glEnableVertexAttribArray(vertAtrrib);
	glVertexAttribPointer(vertAtrrib, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(texcoordAttrib);
	glVertexAttribPointer(texcoordAttrib, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*)(2 * sizeof(GLfloat)));
	glBindVertexArray(0);
}