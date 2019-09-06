#include "EventListener.h"

#include "Event.h"
#include "UIEventPoller.h"

//Call when event triggered
//	Param 1 - Event object
void EventListener::SetEvent(Event* event){
	if (mFunctionsP.size() > 0){
		mEventsP.push_back(event);
		TheUIEventPoller::Instance()->mEventQueueP.push(this);
		delete event;
	}
	else {
		delete event;
	}
}

//	Param 1 - Bound Event object
void EventListener::AddFunction(std::function<void(Event*)> func){
	mFunctionsP.push_back(func);
}

//	Param 1 - Bound Event object
void EventListener::RemoveFunction(std::function<void(Event*)> func){
	FunctionContainer::iterator it = mFunctionsP.begin();

	for (; it != mFunctionsP.end(); it++){
		if (*it = func){
			mFunctionsP.erase(it);
			break;
		}
	}
}
