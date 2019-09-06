#pragma once

#include "Singleton.h"
#include "GLShader.h"
#include <vector>
class UIElement;

class UIManager : public Uncopyable {
public:
	
	void Init();

	void Draw();
	void Render();

	void Clean();
private:
	UIManager(){}
	friend class SingletonT<UIManager>;

	std::vector<UIElement*> mUIElement;
	GLShader* mShader;
	GLuint mTexture;
	GLuint mRBO;
	GLuint mFBO;

	void genFrameBuffer();

	void loadRenderQuad();
	GLuint mQuadVAO;
	GLuint mQuadVBO;
};

typedef SingletonT<UIManager> TheUI;