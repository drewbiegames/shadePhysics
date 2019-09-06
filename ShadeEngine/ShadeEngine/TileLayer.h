#pragma once

#include <vector>

#include "Vector2D.h"
#include "Layer.h"
#include "Tileset.h"

/*
	Tile Layer Class

	ref: SDL Game Development, Shaun Mitchell

	not currently implemented - tested
	Changes to be made:
		Use SpriteSheet to draw tiles
*/

class TileLayer : public Layer {
public:
	TileLayer(int tileSize, const std::vector<Tileset> &tilesets);

	virtual void Update();
	virtual void Draw();

	void setTileIDs(const std::vector<std::vector<int>>& data){ mTileIDs = data; }

	void setTileSize(int tileSize){ mTileSize = tileSize; }

	Tileset GetTilesetByID(int tileID);

private:
	int mNumColumns;
	int mNumRows;
	int mTileSize;

	Vector2Df mPosition,
		mVelocity;

	const std::vector<Tileset> &mTilesets;

	std::vector<std::vector<int>> mTileIDs;
};