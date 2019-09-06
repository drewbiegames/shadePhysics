#include "GLThirdPersonCamera.h"

#include "Utils.h"

//Follows the point at the angle
void GLThirdPersonCamera::Update(){
	mTarget = (*mFocus);

	float X = (cos((*mAngle)) * mZoom);
	float Y = (sin((*mAngle)) * mZoom);

	float L = Vector2Df(X, Y).Length();

	mTransform.position = Vector3Df(
		mTarget.X + X,
		mTarget.Y + L,
		mTarget.Z + Y);
}

//Handle mouse wheel event - zoom
void GLThirdPersonCamera::OnMouseWheelEvent(const SDL_MouseWheelEvent& ev){
	mZoom += ev.y * 0.5f;
	util::clampValue(mZoom, mZoomMax, mZoomMin);
}

//Set zoom within clamped value
void GLThirdPersonCamera::setZoom(float zoom, float max, float min){
	mZoom = zoom;
	mZoomMax = max;
	mZoomMin = min;
	util::clampValue(mZoom, mZoomMax, mZoomMin);
}