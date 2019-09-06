#include "GLCharacter.h"

#include "Defines.h"


//Draw a basic character
void GLCharacter::Draw(){

	GLGameObject::Draw();
	glPushMatrix();
		//Initial position
		glTranslatef(mPosition.X,mPosition.Y, mPosition.Z);
		glRotatef(util::DegreesFromRadians(-mAngle), 0.0, 0.5, 0.0);

		glPushMatrix();
			glTranslatef(0.0, 0.5, 0.0);
			glutSolidCube(1.0);
		glPopMatrix();

		glPushMatrix();
			glutSolidSphere(0.5, 10, 10);
		glPopMatrix();

	glPopMatrix();		
}

//Update the position and rotatation
void GLCharacter::Update(){
	float speed = 0.1f;
	float angleIncrement = util::RadiansFromDegrees(5.0f);

	if (mIsRight) mAngle -= angleIncrement;
	if (mIsLeft) mAngle += angleIncrement;

	Vector2Df tempVec2 = Vector2Df();
	tempVec2.setAngle(mAngle);
	
	mVelocity = Vector3Df(tempVec2.X, 0.0, tempVec2.Y);
	if (mIsUp){ 
		mVelocity *= -speed;
	}
	if (mIsDown){ 
		mVelocity *= speed;
	}
	else if (!mIsDown && !mIsUp){
		mVelocity = Vector3Df(0.0f, 0.0f, 0.0f);
	}
	
	mPosition += mVelocity;
}

void GLCharacter::Clean(){
	
}

//Load from XML node - not parsable
//	Param 1 - XML Node
void GLCharacter::Load(TiXmlElement* node){
	GLGameObject::Load(node);

	TheInput::Instance()->AddHandler("character", this);
}

//Load from hard coded variables - for testing
void GLCharacter::Load(Vector3Df pos){ 
	TheInput::Instance()->AddHandler("character", this);
	mPosition = pos;
}

//Handle keyboard events
void GLCharacter::OnKeyboardEvent(const SDL_KeyboardEvent& ev){
	if (ev.type == SDL_KEYDOWN){
		if (ev.keysym.scancode == SDL_SCANCODE_W){
			mIsUp = true;
		}
		if (ev.keysym.scancode == SDL_SCANCODE_S){
			mIsDown = true;
		}
		if (ev.keysym.scancode == SDL_SCANCODE_A){
			mIsLeft = true;
		}
		if (ev.keysym.scancode == SDL_SCANCODE_D){
			mIsRight = true;
		}
	}

	if (ev.type == SDL_KEYUP){
		if (ev.keysym.scancode == SDL_SCANCODE_W){
			mIsUp = false;
		}
		if (ev.keysym.scancode == SDL_SCANCODE_S){
			mIsDown = false;
		}
		if (ev.keysym.scancode == SDL_SCANCODE_A){
			mIsLeft = false;
		}
		if (ev.keysym.scancode == SDL_SCANCODE_D){
			mIsRight = false;
		}
	}
}