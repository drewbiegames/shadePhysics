#pragma once

#include "Singleton.h"

/*
	Timer Class

	ref: Tutorial with Marco Dias
*/

class Timer : public Uncopyable {
public:
		
	void Initialize();
	float GetDeltaTime() const { return mDeltaTime; };
	void Update();

private:
	Timer() : mDeltaTime(0.0f), mOldTicks(0) {};
	friend class SingletonT < Timer > ;

	//stores delta time
	float mDeltaTime;
	//time since initalized
	unsigned int mOldTicks;
};

typedef SingletonT< Timer > TheTimer;