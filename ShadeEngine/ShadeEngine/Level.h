#pragma once

#include <string>
#include <vector>

#include "Factory.h"
#include "Layer.h"

struct Tileset;
class LevelParser;

/*
	Level Class

	Ref: SDL Game Development, Shaun Mitchell

	not currently implemented - tested
*/

class Level {
public:
	Level();
	~Level();

	void Update();
	void Draw();

	std::vector<Tileset>* GetTilesets(){ return &mTilesets; }
	std::vector<Layer*>* GetLayers(){ return &mLayersP; }

private:

	friend class LevelParser;

	std::vector<Tileset> mTilesets;
	std::vector<Layer*> mLayersP;
};

typedef SingletonT < FactoryT < Level > > TheLevelFactory;