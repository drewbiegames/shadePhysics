#include "GLCamera.h"
#include "EventHandler.h"

/*
	A camera that follows an object
*/

class GLThirdPersonCamera : public GLCamera, public EventHandler {
public:
	GLThirdPersonCamera() : GLCamera(), mAngle(nullptr), mFocus(nullptr), mZoom(6.0f), mZoomMax(10.0f), mZoomMin(6.0f) {
		TheInput::Instance()->AddHandler("Camera", this);
	}

	void Update();

	virtual void OnMouseWheelEvent(const SDL_MouseWheelEvent&);

	void setFocus(Vector3Df* focus){ mFocus = focus; }
	void setAngle(float* angle){ mAngle = angle; }
	void setZoom(float zoom, float max, float min);
private:
	Vector3Df* mFocus;
	float* mAngle;
	float mZoom, mZoomMax, mZoomMin;
};