#include "GLTexture.h"

#include <SDL_image.h>

//Apply the texture
void GLTexture::ApplyTexture(){
	glBindTexture(GL_TEXTURE_2D, mTextureID);
}

//Load from file path
bool GLTexture::Load(std::string path){
	
	SDL_Surface* tempSurface = IMG_Load(path.c_str());

	if (tempSurface == 0){
		printf("Failed to load SDL Surface. Path: %s", path.c_str());
		return false;
	}

	unsigned char* textureArr = (unsigned char*)tempSurface->pixels;

	mWidth = tempSurface->w;
	mHeight = tempSurface->h;
	int bpp = tempSurface->format->BytesPerPixel;

	mFormat = GL_RGB;
	if (bpp == 4){
		mFormat = GL_RGBA;
	}

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glGenTextures(1, &mTextureID);
	glBindTexture(GL_TEXTURE_2D, mTextureID);

	glTexImage2D(GL_TEXTURE_2D, 0, mFormat, mWidth, mHeight, 0, mFormat, GL_UNSIGNED_BYTE, textureArr);
	glGenerateMipmap(GL_TEXTURE_2D);
	gluBuild2DMipmaps(GL_TEXTURE_2D, mFormat, mWidth, mHeight, mFormat, GL_UNSIGNED_BYTE, textureArr);

	SDL_FreeSurface(tempSurface);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	glEnable(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, 0);

	return true;

}

//Load from XML Node
bool GLTexture::Load(TiXmlElement* node){

	std::string path = node->Attribute("path");

	std::string texID = node->Attribute("textureID");

	if (!Load(path)){
		return false;
	}

	TheAssetManager::Instance()->Add(texID, this);
	
	return true;
}

static bool sgGLTextureRegister = TheAssetFactory::Instance()->RegisterType("GLTexture", Create<GLTexture>);