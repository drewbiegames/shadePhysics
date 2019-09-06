#pragma once

#include "GLCamera.h"
#include "EventHandler.h"
#include "InputEnum.h"

/*
	First Person Camera Class

	Currently uses WS to move forward and backwards
	QE to move from side to side
	AD to rotate arond the Y axis
*/

class GLFirstPersonCamera : public GLCamera, public EventHandler {
public:
	GLFirstPersonCamera();

	void Update();
	void Draw();
	void Clean();

	void React(GameObject* obj){}

	void OnMouseMotionEvent(const SDL_MouseMotionEvent&);
	void OnKeyboardEvent(const SDL_KeyboardEvent&);

	Vector3Df GetLeft();
	Vector3Df GetRight();

	virtual void Load(TiXmlElement* node);

	~GLFirstPersonCamera(){ Clean(); }
	
private:
	float mRotSensitivity;
	float mMovSensitivity;

	Vector3Df mForward;
	Vector3Df mRight;
	Vector3Df mLookAt;

	InputEnum mInput;

	float mMouseRelX;
	float mMouseRelY;
	
	virtual void Load(Vector3Df pos, Vector3Df up, Vector3Df forward);

	void rotateX(float angle);
	void rotateY(float angle);
	void moveCamera(Vector3Df dir, float speed);

	static Vector3Df yAxis;
};