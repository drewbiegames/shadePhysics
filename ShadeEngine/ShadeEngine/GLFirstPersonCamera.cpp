#include "GLFirstPersonCamera.h"

#include "GLGame.h"

Vector3Df GLFirstPersonCamera::yAxis = Vector3Df(0.0f, 1.0f, 0.0f);

GLFirstPersonCamera::GLFirstPersonCamera() 
	: GLCamera(), mInput(CLEAR)
{
	TheInput::Instance()->AddHandler("FPCamera", this);
}

//Calls gluLookAt
void GLFirstPersonCamera::Draw(){
	GLCamera::Draw();
}

//Removes the camera from input handler
void GLFirstPersonCamera::Clean(){
	TheInput::Instance()->RemoveHandler("FPCamera");
}

//Update the camera postion and rotation
void GLFirstPersonCamera::Update(){
	float dot = mLookAt.dot(Vector3Df(0.0f, 1.0f, 0.0f));
	
	if ((dot < 0.9f && mMouseRelX < 0) || (dot > -0.9f && mMouseRelX > 0))
		rotateX(-mMouseRelX * mRotSensitivity);

	rotateY(-mMouseRelY * mRotSensitivity);
	//mTransform.rotation.Output();
	mLookAt = (mTransform.rotation * mForward).normalised();
	
	if ((mInput & FOREWARD) == FOREWARD){
		moveCamera(mTransform.rotation * mForward, mMovSensitivity);
	}
	if ((mInput & BACKWARD) == BACKWARD){
		moveCamera(mTransform.rotation * -mForward, mMovSensitivity);
	}
	if ((mInput & STFLEFT) == STFLEFT){
		moveCamera(mTransform.rotation  * -mRight, mMovSensitivity);
	}
	if ((mInput & STFRIGHT) == STFRIGHT){
		moveCamera(mTransform.rotation  * mRight, mMovSensitivity);
	}

	mTarget = mTransform.position + mLookAt;
	mMouseRelX = mMouseRelY = 0.0f;
}

//Handle mouse events
void GLFirstPersonCamera::OnMouseMotionEvent(const SDL_MouseMotionEvent& ev){
	//switch the axis
	mMouseRelX = float(ev.yrel);
	mMouseRelY = float(ev.xrel);
}

//Handle Keyboard events
void GLFirstPersonCamera::OnKeyboardEvent(const SDL_KeyboardEvent& ev){
	switch (ev.type)
	{
		case SDL_KEYDOWN:
			switch (ev.keysym.scancode)
			{
				case SDL_SCANCODE_W:
					mInput = mInput | FOREWARD;
					break;

				case SDL_SCANCODE_S:
					mInput = mInput | BACKWARD;
					break;
				
				case SDL_SCANCODE_A:
					mInput = mInput | STFLEFT;
					break;

				case SDL_SCANCODE_D:
					mInput = mInput | STFRIGHT;
					break;

				default:
					break;
			}
			break;

		case SDL_KEYUP:
			switch (ev.keysym.scancode){

				case SDL_SCANCODE_W:
					mInput = mInput & ~FOREWARD;
					break;

				case SDL_SCANCODE_S:
					mInput = mInput & ~BACKWARD;
					break;

				case SDL_SCANCODE_A:
					mInput = mInput & ~STFLEFT;
					break;

				case SDL_SCANCODE_D:
					mInput = mInput & ~STFRIGHT;
					break;

				default:
					break;
			}
	}
}

//rotate along X axis
void GLFirstPersonCamera::rotateX(float angle){
	Quaternion temp;

	temp.CreateFromAxisAngle(1.0f, 0.0f, 0.0f, angle);

	mTransform.rotation = mTransform.rotation * temp;
	mTransform.rotation.normalise();
}


//rotate along Y axis
void GLFirstPersonCamera::rotateY(float angle){
	Quaternion temp;

	temp.CreateFromAxisAngle(0.0f, 1.0f, 0.0f, angle);

	mTransform.rotation = temp * mTransform.rotation;
	mTransform.rotation.normalise();
}

//Move camera in direction
void GLFirstPersonCamera::moveCamera(Vector3Df dir, float speed){
	mTransform.position += dir * speed;
}

//Returns the Left Unit Vector
Vector3Df GLFirstPersonCamera::GetLeft(){
	Vector3Df left;

	left = mUp.cross(mForward);

	left.normalise();
	return left;
}

//Returns the Right Unit Vector
Vector3Df GLFirstPersonCamera::GetRight(){
	Vector3Df right = mForward.cross(mUp);
	right.normalise();
	return right;
}

//Load from hard coded variables
void GLFirstPersonCamera::Load(Vector3Df pos, Vector3Df up, Vector3Df forward){
	GLCamera::Load(pos);
	
	mUp = up.normalised();
	mForward = forward.normalised();

}

//Load from XML Node
void GLFirstPersonCamera::Load(TiXmlElement* node){
	GLCamera::Load(node);

	double x, y, z;
	node->Attribute("rotX", &x);
	node->Attribute("rotY", &y);
	node->Attribute("rotZ", &z);

	mTransform.rotation.CreateFromEuler(float(x), float(y), float(z));

	mUp.normalise();

	mForward = Vector3Df(0.0f, 0.0f, -1.0f);
	mLookAt = mTransform.rotation * mForward;
	mRight = GetRight();

	mRotSensitivity = 0.5f;
	mMovSensitivity = 0.1f;

	double rot, mov;
	node->Attribute("RotationSensitivity", &rot);
	node->Attribute("MovementSensitivity", &mov);
	mRotSensitivity = float(rot);
	mMovSensitivity = float(mov);

	mInput = CLEAR;
	SDL_SetRelativeMouseMode(SDL_TRUE);

	TheGLGame::Instance()->RegisterCamera(this);
}

static bool gsFPSCameraReg = TheGameObjectFactory::Instance()->RegisterType("FPSCamera", Create<GLFirstPersonCamera>);