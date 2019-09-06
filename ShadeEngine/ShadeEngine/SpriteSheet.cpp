#include "SpriteSheet.h"

#include "Game.h"
#include "AssetManager.h"
#include "tinyxml.h"
#include "SDLGame.h"

//Load from XML Node
//	Param 1 - XML Node
//Return bool - true if succeded
bool SpriteSheet::Load(TiXmlElement* node){
	std::string path;

	//get attributes of the sprite sheet
	path = node->Attribute("filename");
	mID = node->Attribute("id");
	node->Attribute("numberofcellsx", &mNumCellsX);
	node->Attribute("numberofcellsy", &mNumCellsY);	

	if (!Texture::Load(path, false)){
		return false;
	}

	mCellWidth = mWidth / mNumCellsX;
	mCellHeight = mHeight / mNumCellsY;

	TheAssetManager::Instance()->Add(mID, this);

	return true;
}

//Draw Current Cell
//	Param 1 - Destination X Position
//	Param 2 - Destination Y Position
//	Param 3 - Destination Width
//	Param 4 - Destination Height
//	Param 5 - SDL_RenderFlip
void SpriteSheet::Draw(int x, int y, int w, int h, SDL_RendererFlip flip){
	int xpos = (mCurCell % mNumCellsX) * mCellWidth;
	int ypos = (mCurCell % mNumCellsY) * mCellHeight;

	SDL_Rect srcRect = { xpos, ypos, mCellWidth, mCellHeight };
	SDL_Rect destRect = { x, y, w, h };

	SDL_RenderCopyEx(TheSDLGame::Instance()->GetRenderer(), mTextureP, &srcRect, &destRect, 0, 0, flip);
}

//Register SpriteSheet with Asset Factory
static bool sgAnimationRegister = TheAssetFactory::Instance()->RegisterType("SpriteSheet", Create<SpriteSheet>);