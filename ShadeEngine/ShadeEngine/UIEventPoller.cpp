#include "UIEventPoller.h"

#include "Event.h"
#include "EventListener.h"

//	Param 1 - EventListener to be added
void UIEventPoller::RegisterEventListener(EventListener* event){
	int id = reinterpret_cast<int>(event);
	ListenerMap::iterator it = mEventListenersP.find(id);

	if (it == mEventListenersP.end()){
		mEventListenersP[id] = event;
	}
}

//	Param 1 - EventListener to be removed
void UIEventPoller::RemoveEventListener(EventListener* event){
	int id = reinterpret_cast<int>(event);
	ListenerMap::iterator it = mEventListenersP.find(id);

	if (it != mEventListenersP.end()){
		delete it->second;
		mEventListenersP.erase(it);
	}
}

//For each Event in the queue calls the function
void UIEventPoller::CheckEvents(){
	while (!mEventQueueP.empty()){

		EventListener* front = mEventQueueP.front();

		mEventQueueP.pop();

		//In debug default to zero, could make problem on release, line 39 may have issues
		int size = front->mEventsP.size();
		 
		for (int ee = 0; ee < size; ee++){

			int funcSize = front->mFunctionsP.size();
			for (int ii = 0; ii < funcSize; ii++){
				front->mFunctionsP[ii](front->mEventsP[ee]);
			}
		}
	}

}
