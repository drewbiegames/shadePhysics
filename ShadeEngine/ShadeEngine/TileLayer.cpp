#include "TileLayer.h"

#include "Game.h"
#include "SDLGame.h"

TileLayer::TileLayer(int tileSize, const std::vector<Tileset> &tilesets) :
mTileSize(tileSize), mTilesets(tilesets), mPosition(0, 0), mVelocity(1, 0){

	mNumColumns = (TheGame::Instance()->GetGameWidth() / mTileSize) + 1;
	mNumRows = (TheGame::Instance()->GetGameHeight() / mTileSize);
}

Tileset TileLayer::GetTilesetByID(int tileID){
	for (int i = 0; i < int(mTilesets.size()); i++)
	{
		if (i + 1 <= int(mTilesets.size()) - 1)
		{
			if (tileID >= mTilesets[i].firstGridID && tileID < mTilesets[i + 1].firstGridID)
			{
				return mTilesets[i];
			}
		}
		else
		{
			return mTilesets[i];
		}
	}

	printf("did not find tileset.\n");
	Tileset t;
	return t;
}

void TileLayer::Update(){
	mPosition += mVelocity;

	if (mPosition.X == ((mTileIDs[0].size() * mTileSize) - TheGame::Instance()->GetGameWidth())) {
		mVelocity.X = -1;
	}
	else if (mPosition.X == 0){
		mVelocity.X = 1;
	}
}

void TileLayer::Draw(){
	int x, y, x2, y2 = 0;

	x = int(mPosition.X) / mTileSize;
	y = int(mPosition.Y) / mTileSize;

	x2 = int(mPosition.X) % mTileSize;
	y2 = int(mPosition.Y) % mTileSize;

	unsigned int height = mTileIDs.size();
	unsigned int width = mTileIDs[0].size();

	for (int i = 0; i < mNumRows; i++){
		if (i + y == height){
			break;
		}

		for (int j = 0; j < mNumColumns; j++){
			if (x + j == width){
				break;
			}

			int id = mTileIDs[i + y][j + x];
			if (id == 0){
				continue;
			}

			Tileset tileset = GetTilesetByID(id);

			id--;

			/*TheTextureManager::Instance()->DrawTile
				(tileset.name,
				tileset.margin,
				tileset.spacing,
				(j * mTileSize) - x2,
				(i * mTileSize) - y2,
				mTileSize, mTileSize,
				(id - (tileset.firstGridID - 1)) / tileset.numColumns,
				(id - (tileset.firstGridID - 1)) % tileset.numColumns,
				TheGame::Instance()->GetRenderer());*/

			//Replacing how levels are drawn

		}
	}
}
