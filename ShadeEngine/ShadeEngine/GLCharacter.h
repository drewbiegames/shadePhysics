#include "GLGameObject.h"
#include "EventHandler.h"

/*
	GL Character class

	for testing the third person camera
*/

class GLCharacter : public GLGameObject, public EventHandler {
public:
	GLCharacter() : GLGameObject(), 
		mIsDown(false), mIsUp(false), mIsLeft(false), mIsRight(false), mAngle(0.0f){}

	void Draw();
	void Update();
	void Clean();
	void React(GameObject* obj){}

	void Load(TiXmlElement* node);

	void OnKeyboardEvent(const SDL_KeyboardEvent&);

	float* getAngle(){ return &mAngle; }

private:

	//control bools
	//use bits?
	bool mIsUp;
	bool mIsDown;
	bool mIsRight;
	bool mIsLeft;

	void Load(Vector3Df pos);
	
	float mAngle;
};