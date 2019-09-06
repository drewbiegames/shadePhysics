#include "Texture.h"
#include "SDLGame.h"
#include "AssetManager.h"

#include <cassert>

Texture::Texture() : mTextureP(nullptr) { }

//SDL Load Texture Function
//	Param 1 - path to the texture file
//	Param 2 - bool - Insert into texture map?
//		If loading from a spritesheet adding Texture causes memory freeing errors
bool Texture::Load(std::string path, bool insert){
	SDL_Surface* tempSurface = IMG_Load(path.c_str());

	if (tempSurface == 0){
		printf("Error Loading Surface: %s\n", path.c_str());
		assert(false);
		return false;
	}

	mTextureP = SDL_CreateTextureFromSurface(TheSDLGame::Instance()->GetRenderer(), tempSurface);

	mWidth = tempSurface->w;
	mHeight = tempSurface->h;

	SDL_FreeSurface(tempSurface);

	if (mTextureP != 0){
		if (insert){
			TheAssetManager::Instance()->Add(path, this);
		}
		return true;
	}

	printf("Error Loading Texture: %s\n", path.c_str());
	assert(false);
	return false;
}

//Load from XML Node
//	Params 1 - XML Node
bool Texture::Load(TiXmlElement* node){
	std::string path;
	path = node->Attribute("filename");
	mID = node->Attribute("id");
	Load(path , false);
	TheAssetManager::Instance()->Add(mID, this);
	return true;
}

//Load from generate SDL_Texture
//	Param 1 - TextureID
//	Param 2 - SDL_Texture*
bool Texture::Load(const std::string id, SDL_Texture* texture){
	mTextureP = texture;
	SDL_QueryTexture(mTextureP, 0, 0, &mWidth, &mHeight);
	TheAssetManager::Instance()->Add(id, this);
	return true;
}

//Draw Texture
//	Params 1 - Destination X
//	Params 2 - Destination Y
//	Params 3 - Destination Width
//	Params 4 - Destination Height
//	Params 5 - SDL_RenderFlip flag
void Texture::Draw(int x, int y, int width, int height, SDL_RendererFlip flip){
	SDL_Rect srcRect  = { 0, 0, mWidth, mHeight };
	SDL_Rect destRect = { x, y, width, height };
	
	SDL_RenderCopyEx(TheSDLGame::Instance()->GetRenderer(), mTextureP, &srcRect, &destRect, 0, 0, flip);
}

//Register Texture Type with Asset factory
static bool sgAnimationRegister = TheAssetFactory::Instance()->RegisterType("Texture", Create<Texture>);