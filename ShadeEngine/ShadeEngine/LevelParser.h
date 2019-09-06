#pragma once

#include "tinyxml.h"
#include "Tileset.h"
#include "Level.h"
#include "Layer.h"

#include <vector>

/*
	Level Parser

	for parsing levels from Tiled - 
		third-party freeware level editor

	ref: SDL Game Development, Shaun Mitchell

	not currently implemented - tested

	changes to be made:
		SpriteSheet implemention
*/

class LevelParser {
public:
	LevelParser() :
	mAssetTag("Media/")
	{}

	Level* ParseLevel(const char* levelFile);

private:
	void parseTilesets(TiXmlElement* tilesetRootP, std::vector<Tileset>* pTilesets);
	void parseTileLayer(TiXmlElement* tileElementP, std::vector<Layer*> *layersP, const std::vector<Tileset>* tilesetP);
	void parseTextures(TiXmlElement* textureRootP);
	void parseObjectLayer(TiXmlElement* objectElementP, std::vector<Layer*> *layerP);

	int mTileSize,
		mWidth,
		mHeight;

	std::string mAssetTag;
};