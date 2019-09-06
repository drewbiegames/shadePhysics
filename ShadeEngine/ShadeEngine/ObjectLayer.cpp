#include "ObjectLayer.h"

#include "SDLGameObject.h"
#include "Input.h"

void ObjectLayer::OnEnter(){
	
}

void ObjectLayer::Update(){
	for (int i = 0; i < (int)mGameObjectsP.size(); i++){
		mGameObjectsP[i]->Update();
	}
}

void ObjectLayer::Draw(){
	for (int i = 0; i < (int)mGameObjectsP.size(); i++){
		mGameObjectsP[i]->Draw();
	}
}

