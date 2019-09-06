#include "BaseGame.h"
#include "Singleton.h"

class SDLGame : public BaseGame, public Uncopyable {
public:
	bool Init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);

	void Render();
	void Clean();

	SDL_Renderer* GetRenderer() const { return mRendererP; }
private:
	SDLGame(){}
	friend class SingletonT<SDLGame>;

	SDL_Renderer* mRendererP;
};

typedef SingletonT<SDLGame> TheSDLGame;