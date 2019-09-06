#pragma once

#include "BaseGame.h"
#include "Singleton.h"

#include "GLDebugGrid.h"

#include "GLCamera.h"

/*
	GL Game class

	Initilises an Open GL window through SDL
*/

class GLGame : public BaseGame, public Uncopyable {
public:
	bool Init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);

	void Render();
	void Clean();

	SDL_GLContext* GetContext(){ return &mContext; }

	void RegisterCamera(GLCamera* cam){ mCameras.push_back(cam); }
	GLCamera* GetCamera(GLuint camID); 

private:
	GLGame(){}
	friend class SingletonT < GLGame > ;

	SDL_GLContext mContext;

	GLDebugGrid* mGrid;

	std::vector<GLCamera*> mCameras;
};

typedef SingletonT<GLGame> TheGLGame;