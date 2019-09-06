#include "AssetManager.h"

//Add Asset to map
//	Param 1 - Asset ID :: std::string
//	Param 2 - Asset Pointer
void AssetManager::Add(const std::string& name, Asset* asset){
	AssetContainer::iterator it = mAssetsP.find(name);

	if (it == mAssetsP.end()){
		mAssetsP[name] = asset;
	}
}

//Erase Asset from map, calls delete
//	Param 1 - Asset ID
void AssetManager::Remove(const std::string& name){
	AssetContainer::iterator it = mAssetsP.find(name);

	if (it != mAssetsP.end()){
		printf("Nothing to remove! %s did not exist!", name.c_str());
		return;
	}

	delete it->second;
	mAssetsP.erase(it);
}

//Clear the Texture Map, calls delete
void AssetManager::Clean(){
	AssetContainer::iterator it = mAssetsP.begin();

	for (; it != mAssetsP.end(); it++){
		delete it->second;
	}
	mAssetsP.clear();
}