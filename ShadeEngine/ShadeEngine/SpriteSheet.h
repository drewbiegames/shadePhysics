#pragma once

#include "Texture.h"
#include "tinyxml.h"

class SpriteSheet : public Texture {
public:
	SpriteSheet(){};
	virtual ~SpriteSheet(){}
	
	//Load from XML Node
	virtual bool Load(TiXmlElement* node);

	//Draw Current cell of the sprite sheet
	virtual void Draw(int x, int y, int w, int h, SDL_RendererFlip flip = SDL_FLIP_NONE);

	//Setters
	void SetCurCell(int no) { mCurCell = no; }

	//Getters
	int GetNumCells() const { return mNumCellsX * mNumCellsY; }
	int GetCellWidth() const { return mCellWidth; }
	int GetCellHeight() const { return mCellHeight; }
	int GetNumCellsX() const { return mNumCellsX; }
	int GetNumCellsY() const { return mNumCellsY; }
	std::string GetID() const { return mID; }
	SDL_Texture* GetTexture() const { return mTextureP; }

private:
	int mCurCell,
		mCellWidth,
		mCellHeight,
		mNumCellsX,
		mNumCellsY;
	
	std::string mID;
};
