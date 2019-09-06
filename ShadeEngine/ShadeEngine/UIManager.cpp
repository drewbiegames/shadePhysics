#include "UIManager.h"

#include <iostream>
#include "FrameBuffer.h"

void UIManager::Init(){
	std::string vertshader = "uishader.vert";
	std::string fragshader = "uishader.frag";

	mShader->Load("UIShader", vertshader, fragshader);

	genFrameBuffer();

	loadRenderQuad();
}


void UIManager::Draw(){
	glBindFramebuffer(GL_FRAMEBUFFER, mFBO);

	std::vector<UIElement*>::iterator it = mUIElement.begin();

	for (; it != mUIElement.end(); it++){
		//*it->Draw();
	}
	
	
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void UIManager::Render(){

	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glDisable(GL_DEPTH_TEST);

	//draw to screen;
	mShader->Enable();
	glBindVertexArray(mQuadVAO);
	glBindTexture(GL_TEXTURE_2D, mTexture);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glBindVertexArray(0);

	mShader->Disable();

}

void UIManager::Clean(){

}

void UIManager::genFrameBuffer(){
	//Generate the frame buffer
	glGenFramebuffers(1, &mFBO);
	glBindFramebuffer(GL_FRAMEBUFFER, mFBO);

	//Generate blank texure (Data is NULL)
	glGenTextures(1, &mTexture);
	glBindTexture(GL_TEXTURE_2D, mTexture);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, WINDOWWIDTH, WINDOWHEIGHT, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glBindTexture(GL_TEXTURE_2D, 0);
	//Attach the texture to the frame buffer
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, mTexture, 0);

	//Genrate render buffer object for depth and stencil
	glGenRenderbuffers(1, &mRBO);
	glBindRenderbuffer(GL_RENDERBUFFER, mRBO);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, WINDOWWIDTH, WINDOWHEIGHT);
	glBindBuffer(GL_RENDERBUFFER, 0);
	//attach RBO
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, mRBO);

	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE){
		std::cout << "Error: UI Framebuffer is not complete!" << std::endl;
		Clean();
	}

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void UIManager::loadRenderQuad(){

	mQuadVAO = TheFrameBuffer::Instance()->getQuadVAO();
	mQuadVBO = TheFrameBuffer::Instance()->getQuadVBO();
}