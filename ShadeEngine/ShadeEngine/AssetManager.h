#pragma once

#include <string>
#include <map>

#include "Singleton.h"
#include "Asset.h"

/*
	Asset Manager Class
*/

class AssetManager : public Uncopyable {
public:
	typedef std::map<std::string, Asset*> AssetContainer;

	//Add Asset to map
	void Add(const std::string& name, Asset* asset);

	//Erase Asset from map, calls delete
	void Remove(const std::string& name);

	//Clear the Texture Map
	void Clean();

	//Template Get Function
	//Returns Templated pointer to an Asset in the map
	//	Param 1 - Asset ID
	template<class T> T* Get(const std::string& name){
		AssetContainer::iterator it = mAssetsP.find(name);

		if (it != mAssetsP.end()){
			if (it->second){
				return dynamic_cast<T*>(it->second);
			}
		}
		return nullptr;
	}
	
private:
	AssetManager(){}
	friend class SingletonT < AssetManager > ;

	AssetContainer mAssetsP;
};

typedef SingletonT<AssetManager> TheAssetManager;