#pragma once

#include <string>

#include "Vector2D.h"
#include "SpriteSheet.h"

/*
	Animation Class
	Displays an animation
*/

class Animation : public Asset {
public:
	Animation();
	
	//Load from XML Node
	bool Load(TiXmlElement* node);

	//Animation controls
	void Start();
	void Stop();
	bool End(){ return mEndCell == (mEndCell - 1); }

	//Update the frame
	void Update();

	//Draw the current frame of the animation
	void Draw(Vector2Df pos, SDL_RendererFlip flip = SDL_FLIP_NONE);

private:
	//Sprite Sheet for the animation
	SpriteSheet* mSheetP;

	//Animation variables, used to calculate the current frame
	float mDuration;
	unsigned int mStartCell;
	unsigned int mEndCell;
	unsigned int mCurCell;
	float mTimePerCell;
	float mTimeSinceLastCellChange;

	//Control variables
	bool mLoop;
	bool mRunning;
};
