#include "GLGame.h"

#include "StateManager.h"
#include "Defines.h"
#include "FrameBuffer.h"

#include <SDL_opengl.h>

//Initialise OpenGL window usig SDL
//	Param 1 - Title of the window
//	Param 2 - X position of the window
//	Param 3 - Y position of the window
//	Param 4 - Width of the window
//	Param 5 - Height of the window
//	Pamam 6 - Fullscreen bool
bool GLGame::Init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen){
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_COMPATIBILITY);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);

	if (BaseGame::Init(title, xpos, ypos, width, height, fullscreen)){
		mContext = SDL_GL_CreateContext(mWindowP);
		if (mContext != nullptr){
			if (SDL_GL_SetSwapInterval(1) < 0){
				printf("Warning: Unable to set VSync! SDL Error: %s\n", SDL_GetError());
			}

			int a = 0;
			char** s = 0;
			glutInit(&a, s);
			
			GLenum error = GL_NO_ERROR;

			glEnable(GL_DEPTH_TEST);
			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

			//Projection Matrix
			glMatrixMode(GL_PROJECTION);
			glLoadIdentity();

			error = glGetError();
			if (error != GL_NO_ERROR){
				printf("Error found! OpenGL Error: %s\n", gluErrorString(error));
				return false;
			}

			if (glewInit() != GLEW_OK){
				printf("GLEW Failed to initialise.\n");
				return false;
			}

			gluPerspective(70.0, 1.77, 0.0001, 1000.0);

			mGrid = nullptr;

#ifdef _DEBUG
			mGrid = new GLDebugGrid();
#endif

		}
		else{
			printf("Failed to create GL Context! SDL Error: %s\n", SDL_GetError());
			return false;
		}
	}
	else{
		return false;
	};
	return true;
}

//Delete GL Context and clean base game
void GLGame::Clean(){
	SDL_GL_DeleteContext(mContext);
	if (mGrid){
		delete mGrid;
		mGrid = nullptr;
	}
	BaseGame::Clean();
}

//Render game objects
void GLGame::Render(){
	glMatrixMode(GL_MODELVIEW);
	TheFrameBuffer::Instance()->Bind();
	glClearColor(0.2f, 0.2f, 0.2f, 1.0f);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);

	TheStateManager::Instance()->Draw();

	if (mGrid) mGrid->Draw();

	TheFrameBuffer::Instance()->Unbind();

	TheFrameBuffer::Instance()->Render();

	SDL_GL_SwapWindow(mWindowP);
}


GLCamera* GLGame::GetCamera(GLuint camID){
	if (camID < mCameras.size())
		return mCameras[camID];
	else
		return nullptr;
}