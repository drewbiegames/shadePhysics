#include "MenuButton.h"

#include "Input.h"
#include "Rectangle.h"
#include "GenericEvent.h"
#include "AssetManager.h"

MenuButton::MenuButton() : SDLGameObject(), mEventListener(nullptr), mSpriteSheetP(nullptr),mCurrentFrame(0) { }

//Draw the Menu Button
void MenuButton::Draw(){
	mSpriteSheetP->Draw(int(mPosition.X), int(mPosition.Y), mWidth, mHeight);
}

//Update the current cell of the sprite sheet
void MenuButton::Update(){
	mSpriteSheetP->SetCurCell(mCurrentFrame);
}

//Clean the object pointers and unregister from sytems
void MenuButton::Clean(){
	TheInput::Instance()->RemoveHandler(mTextureID);
	delete mEventListener;
	mEventListener = nullptr;
	SDLGameObject::Clean();
}

//Handle Mouse Button Events, send event if clicked
//	Param 1 - mouse button event
void MenuButton::OnMouseButtonEvent(const SDL_MouseButtonEvent& event){
	if (event.type == SDL_MOUSEBUTTONDOWN){ 
		if (event.button == SDL_BUTTON_LEFT){
			if (mCurrentFrame == MOUSEOVER){
				mCurrentFrame = CLICKED;
				//Changes the state
				mEventListener->SetEvent(new GenericEvent());
			}
		}
	}
}

//HandleMouse motion events, changes the current frame of the button
//	Param 1 - Mouse Motion Event
void MenuButton::OnMouseMotionEvent(const SDL_MouseMotionEvent& event){
	MyRectangle colidBox(this, mPosition, mVelocity, float(mWidth), float(mHeight));
	if (colidBox.Collide(float(event.x), float(event.y))){
		//if mouse over highlight button
		mCurrentFrame = MOUSEOVER;
	}
	else{
		mCurrentFrame = MOUSEOUT;
	}
}

//Load from hard coded variables
//	Param 1 - X Position
//	Param 2 - Y Position
//	Param 3 - Width
//	Param 4 - Height
//	Param 5 - Texture ID
void MenuButton::Load(int x, int y, int width, int height, std::string textureID){
	SDLGameObject::Load(x, y, width, height, textureID);
	mCurrentFrame = MOUSEOUT;
	
	TheInput::Instance()->AddHandler(mTextureID, this);
	mEventListener = new EventListener();
	mSpriteSheetP = TheAssetManager::Instance()->Get<SpriteSheet>(mTextureID);
}

//Load Variables with XML Node
//	Params 1 - XML Node
void MenuButton::Load(TiXmlElement* node){
	SDLGameObject::Load(node);
	mCurrentFrame = MOUSEOUT;
	TheInput::Instance()->AddHandler(mTextureID, this);
	mEventListener = new EventListener();
	mSpriteSheetP = TheAssetManager::Instance()->Get<SpriteSheet>(mTextureID);
}

static bool sgMenuButtonRegister = TheGameObjectFactory::Instance()->RegisterType("MenuButton", Create<MenuButton>);