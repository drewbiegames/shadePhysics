#include "GameState.h"
#include "Singleton.h"
#include "EventHandler.h"

#include "GameObject.h"
#include "Vector3D.h"
#include "EventListener.h"

/*
	Test State
*/

class TestState : public GameState, public Uncopyable, public EventHandler {
public:

	void Update();
	void Draw();

	void OnEnter();
	void OnExit();

	std::string GetStateID() const { return "TEST"; }

	EventListener* mEventListener;

private:
	friend class SingletonT < TestState > ;
	TestState() : mReset(false) {}

	std::vector<GameObject*> mGameObjects;

	void OnKeyboardEvent(const SDL_KeyboardEvent&);

	void RESET(Event*);

	bool mReset;
};

typedef SingletonT<TestState> TheTestState;