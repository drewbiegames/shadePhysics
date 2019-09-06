#include "Animation.h"

#include "Timer.h"
#include "Game.h"
#include "AssetManager.h"
#include "SDLGame.h"

Animation::Animation() 
	: mSheetP(nullptr), mDuration(0.0f), mStartCell(0), mEndCell(0), 
	mCurCell(0), mTimePerCell(0.0f), mTimeSinceLastCellChange(0),
	mLoop(false), mRunning(false) {

}

//Load from XML Node
//	Param 1 - XML Node
bool Animation::Load(TiXmlElement* node){
	std::string id, sheetid;
	int duration, startcell, endcell;

	//get attributes of animation
	id = node->Attribute("id");
	node->Attribute("duration", &duration);
	node->Attribute("startcell", &startcell);
	node->Attribute("endcell", &endcell);
	sheetid = node->Attribute("sheetid");

	mDuration = float(duration / 1000);
	mStartCell = mCurCell = startcell;
	mEndCell = endcell;
	mTimePerCell = float(duration / (endcell - 1 - startcell)) / 1000;

	mSheetP = TheAssetManager::Instance()->Get<SpriteSheet>(sheetid);

	TheAssetManager::Instance()->Add(id, this);

	return true;
}

//Play Animation
void Animation::Start(){
	mRunning = true;
	mCurCell = mStartCell;
	mTimeSinceLastCellChange = 0;
}

//Stop Animation
void Animation::Stop(){
	mRunning = false;
}

//Update curret cell
void Animation::Update(){
	if (mRunning){
		mTimeSinceLastCellChange += TheTimer::Instance()->GetDeltaTime();

		if (mTimeSinceLastCellChange >= mTimePerCell){
			mTimeSinceLastCellChange = 0;
			++mCurCell;
		}

		if (mCurCell >= mEndCell){
			mCurCell = mStartCell;
		}
	}
}

//Draw the current frame of the animation
//	Param 1 - Position to draw the animation
//	Param 2 - SDL_RenderFlip flag
void Animation::Draw(const Vector2Df pos, SDL_RendererFlip flip){
	int xpos = (mCurCell % mSheetP->GetNumCellsX()) * mSheetP->GetCellWidth();
	int ypos = (mCurCell / mSheetP->GetNumCellsX()) * mSheetP->GetCellHeight();

	SDL_Rect srcRect = { xpos, ypos, mSheetP->GetCellWidth(), mSheetP->GetCellHeight() };
	SDL_Rect destRect = { int(pos.X), int(pos.Y), mSheetP->GetCellWidth(), mSheetP->GetCellHeight() };

	SDL_RenderCopyEx(TheSDLGame::Instance()->GetRenderer(), mSheetP->GetTexture(), &srcRect, &destRect, 0, 0, flip);
}

//Register Animation with the Asset Factory
static bool sgAnimationRegister = TheAssetFactory::Instance()->RegisterType("Animation", Create<Animation>);