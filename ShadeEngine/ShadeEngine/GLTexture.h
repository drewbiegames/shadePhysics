#pragma once

#include "Asset.h"

#include "Defines.h"

/*
	GLTexture Class

	Loads in a texture from a file
*/

class GLTexture : public Asset {

public:

	void ApplyTexture();

	bool Load(TiXmlElement* node);

	bool Load(std::string path);

	GLuint GetID() { return mTextureID; }

	~GLTexture(){ glDeleteTextures(1,&mTextureID);	}

private:

	GLuint mTextureID;

	GLenum mFormat;
	GLuint mWidth;
	GLuint mHeight;

};