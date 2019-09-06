#include "SDLGameObject.h"

#include "Game.h"
#include "Timer.h"

Vector2Df SDLGameObject::sGravity = Vector2Df(0.0f, 9.8f);

void SDLGameObject::Update(){
	if (mIsAffectedByGravity){
		mVelocity += sGravity * TheTimer::Instance()->GetDeltaTime();
	}

	mPosition += mVelocity;
}

//Load Varables, used in testing
void SDLGameObject::Load(int x, int y, int width, int height, std::string textureID){
	mPosition = Vector2Df(float(x), float(y));
	mVelocity = Vector2Df(0, 0);
	mAcceleration = Vector2Df(0, 0);
	mWidth = width;
	mHeight = height;
	mTextureID = textureID;
	
}

//Load File from XML Node
//	Param 1 - XML Node
void SDLGameObject::Load(TiXmlElement* node){
	int x, y;
	node->Attribute("x", &x);
	node->Attribute("y", &y);
	node->Attribute("width", &mWidth);
	node->Attribute("height", &mHeight);

	mPosition = Vector2Df(float(x), float(y));

	mTextureID = node->Attribute("textureID");
}