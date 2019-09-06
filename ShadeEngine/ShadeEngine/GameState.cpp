#include "GameState.h"
#include "AssetManager.h"

void GameState::Update(){
	for (unsigned int ii = 0; ii < mGameObjects.size(); ii++){
		if (mGameObjects[ii] != nullptr){
			mGameObjects[ii]->Update();
		}
	}

	bool check = true;
	while (check){
		check = false;
		std::vector<GameObject*>::iterator it = mGameObjects.begin();
		for (; it != mGameObjects.end(); it++){
			if ((*it)->FlaggedForDestruction()){
				(*it)->Clean();
				delete *it;
				*it = nullptr;
				mGameObjects.erase(it);
				check = true;
				break;
			}
		}
		if (!check) break;
	}
}

void GameState::Draw(){
	for (unsigned int ii = 0; ii < mGameObjects.size(); ii++){
		if (mGameObjects[ii] != nullptr){
			mGameObjects[ii]->Draw();
		}
	}
}

void GameState::OnExit(){
	for (std::vector<GameObject*>::iterator it = mGameObjects.begin(); it != mGameObjects.end(); it++){
		(*it)->Clean();
		delete *it;
		*it = nullptr;
	}
	mGameObjects.clear();

	TheAssetManager::Instance()->Clean();
}