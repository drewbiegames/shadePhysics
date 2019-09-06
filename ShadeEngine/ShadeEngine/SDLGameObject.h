#pragma once

#include <string>

#include "tinyxml.h"
#include "Vector2D.h"
#include "GameObject.h"

/*
	SDLGameObject Abstract Class
*/

class SDLGameObject : public GameObject {
public:
	SDLGameObject() : mPosition(0.0f,0.0f), mWidth(0), mHeight(0), mIsAffectedByGravity(false) {}
	virtual ~SDLGameObject(){}

	virtual void Draw() = 0;
	virtual void Update() = 0;
	virtual void Clean() = 0 {};
	virtual void React(GameObject* obj) = 0;

	//Load from XML Node
	virtual void Load(TiXmlElement* node);

	//Getters
	Vector2Df GetPosition(){ return mPosition; }
	Vector2Df GetVelocity(){ return mVelocity; }
	int GetWidth(){ return mWidth; }
	int GetHeight(){ return mHeight; }
	std::string getTextureID() const { return mTextureID; }

protected:
	//Load function, used in testing and previous versions
	virtual void Load(int x, int y, int width, int height, std::string textureID);

	Vector2Df mPosition;
	int mWidth;
	int mHeight;

	std::string mTextureID;

	Vector2Df mVelocity;
	Vector2Df mAcceleration;

	static Vector2Df sGravity;
	bool mIsAffectedByGravity;
};