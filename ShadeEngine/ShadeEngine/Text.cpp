#include "Text.h"
#include "SDLGame.h"

//Destroys current texture
void Text::Free(){
	if (mTextureP != nullptr){
		SDL_DestroyTexture(mTextureP);
		mTextureP = nullptr;
		mWidth = 0;
		mHeight = 0;
	}
}

//Loads variables from XML Node
//Return bool - true on success
//	Param 1 - XML Text node
bool Text::Load(TiXmlElement* node){
	if (!TTF_WasInit()){
		TTF_Init();
	}

	Free();

	std::string text;
	text = node->Attribute("text");

	std::string fontPath;
	int size;
	fontPath = node->Attribute("fontpath");
	node->Attribute("size", &size);
	LoadFont(fontPath, size);


	int r, g, b, a;
	node->Attribute("red", &r);
	node->Attribute("green", &g);
	node->Attribute("blue", &b);
	node->Attribute("alpha", &a);
	SetColor(Uint8(r), Uint8(g), Uint8(b), Uint8(a));
	
	SDL_Surface* textSurface = TTF_RenderText_Solid(mFont, text.c_str(), mColour);
	if (textSurface != nullptr){
		mTextureP = SDL_CreateTextureFromSurface(TheSDLGame::Instance()->GetRenderer(), textSurface);
		if (mTextureP != nullptr){
			mWidth = textSurface->w;
			mHeight = textSurface->h;
		}
		else{
			printf("Surface to Texture conversion failed! SDL Error: %s\n", SDL_GetError());
			return false;
		}

		SDL_FreeSurface(textSurface);
	}
	else{
		printf("Text surface render failed! SDL_ttf Error: %s\n", SDL_GetError());
		return false;
	}
	return true;
}

//Changes text on the texture
//	Param 1 - string to be changed to
void Text::ChangeText(const std::string newText){
	Free();

	SDL_Surface* textSurface = TTF_RenderText_Solid(mFont, newText.c_str(), mColour);
	if (textSurface != nullptr){
		mTextureP = SDL_CreateTextureFromSurface(TheSDLGame::Instance()->GetRenderer(), textSurface);
		if (mTextureP != nullptr){
			mWidth = textSurface->w;
			mHeight = textSurface->h;
		}
		else{
			printf("Surface to Texture conversion failed! SDL Error: %s\n", SDL_GetError());
		}

		SDL_FreeSurface(textSurface);
	}
	else{
		printf("Text surface render failed! SDL_ttf Error: %s\n", SDL_GetError());
	}
}

//Loads a font from a file
//	Param 1 - File path to font
//	Param 2 - Size of the font
bool Text::LoadFont(const std::string path, int size){
	mFont = TTF_OpenFont(path.c_str(), size);
	if (mFont != nullptr){
		return true;
	}
	return false;
}

//Set Colour
//	Param 1 - 0 to 255 red
//	Param 2 - 0 to 255 green
//	Param 3 - 0 to 255 blue
//	Param 4 - 0 to 255 alpha
void Text::SetColor(Uint8 red, Uint8 green, Uint8 blue, Uint8 alpha){
	mColour.r = red;
	mColour.g = green;
	mColour.b = blue;
	mColour.a = alpha;
}