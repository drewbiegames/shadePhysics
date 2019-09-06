#include "LevelParser.h"

#include "Game.h"
#include "TileLayer.h"
#include "base64.h"
#include <zconf.h>
#include <zlib.h>

#include "ObjectLayer.h"
#include "Level.h"
#include "Layer.h"

Level* LevelParser::ParseLevel(const char* levelFile){
	//Create TinyXML Doc and load
	TiXmlDocument levelDocument;
	if (!levelDocument.LoadFile(levelFile)){
		printf("Loading %s XML file failed!", levelFile);
	}

	//get root node
	TiXmlElement* rootP = levelDocument.FirstChildElement();

	std::string levelName;

	rootP->Attribute("tilewidth", &mTileSize);
	rootP->Attribute("width", &mWidth);
	rootP->Attribute("height", &mHeight);

	//we know that properties is the first child of the root
	TiXmlElement* propertiesP = rootP->FirstChildElement();

	// we must parse the textures needed for this level, which have been added to properties
	for (TiXmlElement* e = propertiesP->FirstChildElement(); e != nullptr; e = e->NextSiblingElement())
	{
		if (e->Value() == std::string("property"))
		{
			if (e->Attribute("name") == std::string("levelName")){
				levelName = e->Attribute("value");
			}
			parseTextures(e);
		}
	}

	//create level object
	Level* levelP = TheLevelFactory::Instance()->Create(levelName);

	//parse any object layers
	for (TiXmlElement* e = rootP->FirstChildElement(); e != nullptr; e = e->NextSiblingElement()){
		if (e->Value() == std::string("layer")){
			parseTileLayer(e, levelP->GetLayers(), levelP->GetTilesets());
		}
	}

	//parse the tilesets
	for (TiXmlElement* e = rootP->FirstChildElement(); e != nullptr; e = e->NextSiblingElement()){
		if (e->Value() == std::string("tileset"))
			parseTilesets(e, levelP->GetTilesets());
	}

	// parse any object layers
	for (TiXmlElement* e = rootP->FirstChildElement(); e != nullptr; e = e->NextSiblingElement())
	{
		if (e->Value() == std::string("objectgroup") || e->Value() == std::string("layer"))
		{
			if (e->FirstChildElement()->Value() == std::string("object"))
			{
				parseObjectLayer(e, levelP->GetLayers());
			}
			else if (e->FirstChildElement()->Value() == std::string("data"))
			{
				parseTileLayer(e, levelP->GetLayers(), levelP->GetTilesets());
			}
		}
	}
	return levelP;
}

void LevelParser::parseTilesets(TiXmlElement* tilesetRootP, std::vector<Tileset>* tilesetsP){
	//add the tileset to texture manager
	/*TheTextureManager::Instance()->Load(
		mAssetTag + tilesetRootP->FirstChildElement()->Attribute("source"),
		tilesetRootP->Attribute("name"),
		TheGame::Instance()->GetRenderer());*/

	//Replacing how textures are loaded

	//create a tileset object
	Tileset tileset;
	tilesetRootP->FirstChildElement()->Attribute("width", &tileset.width);
	tilesetRootP->FirstChildElement()->Attribute("height", &tileset.height);
	tilesetRootP->Attribute("firstgid", &tileset.firstGridID);
	tilesetRootP->Attribute("tilewidth", &tileset.tileWidth);
	tilesetRootP->Attribute("tileheight", &tileset.tileHeight);
	tilesetRootP->Attribute("spacing", &tileset.spacing);
	tilesetRootP->Attribute("margin", &tileset.margin);
	tileset.name = tilesetRootP->Attribute("name");

	tileset.numColumns = tileset.width / (tileset.tileWidth + tileset.spacing);

	tilesetsP->push_back(tileset);
}

void LevelParser::parseTileLayer(TiXmlElement* tileElementP, std::vector<Layer*> *layersP, const std::vector<Tileset>* tilesetsP){
	TileLayer* tileLayerP;
	tileLayerP = new TileLayer(mTileSize, *tilesetsP);

	//tile data
	std::vector<std::vector<int>> data;

	std::string decodedIDs;
	TiXmlElement* dataNodeP = nullptr;

	for (TiXmlElement* e = tileElementP->FirstChildElement(); e != nullptr; e = e->NextSiblingElement()){
		if (e->Value() == std::string("data"))
			dataNodeP = e;
	}

	for (TiXmlNode* e = dataNodeP->FirstChild(); e != nullptr; e = e->NextSibling()){
		TiXmlText* text = e->ToText();
		std::string t = text->Value();
		decodedIDs = base64_decode(t);
	}

	//uncompress zlib compression
	uLongf numGids = mWidth * mHeight * sizeof(int);
	std::vector<int> ids(numGids);
	uncompress((Bytef*)&ids[0], &numGids, (const Bytef*)decodedIDs.c_str(), decodedIDs.size());

	std::vector<int> layerRow(mWidth, 0);

	for (int j = 0; j < mHeight; j++){
		data.push_back(layerRow);
	}

	for (int rows = 0; rows < mHeight; rows++){
		for (int cols = 0; cols < mWidth; cols++){
			data[rows][cols] = ids[rows*mWidth + cols];
		}
	}

	tileLayerP->setTileIDs(data);

	layersP->push_back(tileLayerP);
}

void LevelParser::parseTextures(TiXmlElement* textureRootP){
	//TheTextureManager::Instance()->Load(mAssetTag + textureRootP->Attribute("value"), textureRootP->Attribute("name"), TheGame::Instance()->GetRenderer());
	//Replacing how textures are parsed
}

void LevelParser::parseObjectLayer(TiXmlElement* objectElementP, std::vector<Layer*> *layerP){
	ObjectLayer* objectLayerP;
	objectLayerP = new ObjectLayer();

	for (TiXmlElement* e = objectElementP->FirstChildElement(); e != nullptr; e = e->NextSiblingElement()){
		if (e->Value() == std::string("object")){
			int x, y, width, height, numFrames, callbackID, animSpeed;
			std::string textureID;

			e->Attribute("x", &x);
			e->Attribute("y", &y);
			GameObject* gameObjectP = TheGameObjectFactory::Instance()->Create(e->Attribute("type"));

			for (TiXmlElement* properties = e->FirstChildElement(); properties != nullptr; properties = properties->NextSiblingElement()){
				if (properties->Value() == std::string("properties")){
					for (TiXmlElement* property = properties->FirstChildElement(); property != nullptr; property = property->NextSiblingElement()){

						if (property->Attribute("name") == std::string("numFrames"))
						{
							property->Attribute("value", &numFrames);
						}
						else if (property->Attribute("name") == std::string("textureHeight"))
						{
							property->Attribute("value", &height);
						}
						else if (property->Attribute("name") == std::string("textureID"))
						{
							textureID = property->Attribute("value");
						}
						else if (property->Attribute("name") == std::string("textureWidth"))
						{
							property->Attribute("value", &width);
						}
						else if (property->Attribute("name") == std::string("callbackID"))
						{
							property->Attribute("value", &callbackID);
						}
						else if (property->Attribute("name") == std::string("animSpeed"))
						{
							property->Attribute("value", &animSpeed);
						}
					}
				}
				//gameObjectP->Load(new LoaderParams(x, y, width, height, textureID)); Changing when new object parser complete

				throw "When level's parser implemented fix this game object vector";
				assert(false);
				//objectLayerP->GetGameObject()->push_back((GameObject*)gameObjectP);
			}
			static_cast<ObjectLayer*>(objectLayerP)->OnEnter();
		}
	}
	layerP->push_back(objectLayerP);
	
}