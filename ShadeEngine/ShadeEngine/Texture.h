#pragma once

#include <SDL_image.h>
#include <string>

#include "Asset.h"

/*
	Texture Asset Class
*/

class Texture : public Asset {
public:
	Texture();
	virtual ~Texture(){}
	
	//Load variables from XML
	virtual bool Load(const std::string path, bool insert);
	virtual bool Load(TiXmlElement* node);
	virtual bool Load(const std::string id, SDL_Texture* texture);

	//Draw the texture
	virtual void Draw(int x, int y, int width, int height, SDL_RendererFlip = SDL_FLIP_NONE);

	//Getters
	SDL_Texture* GetTexture() const { return mTextureP; }
	int getWidth() const { return mWidth; }
	int getHeight() const { return mHeight; }

	//Setters
	void setWidth(int w) { mWidth = w; }
	void setHeight(int h) { mHeight = h; }
protected:
	SDL_Texture* mTextureP;
	int mWidth;
	int mHeight;
	std::string mID;
};
