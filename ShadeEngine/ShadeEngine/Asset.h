#pragma once

#include <string>

#include "tinyxml.h"
#include "Factory.h"

/*
	Asset Base Interface
*/

class Asset {
public:

	//Load by XML Node
	virtual bool Load(TiXmlElement* node) = 0;

	virtual ~Asset(){}
};

typedef SingletonT < FactoryT<Asset> > TheAssetFactory;

#include "AssetManager.h"