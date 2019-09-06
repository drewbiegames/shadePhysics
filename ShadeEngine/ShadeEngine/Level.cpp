#include "Level.h"

#include "Tileset.h"
#include "Layer.h"
#include "LevelParser.h"

Level::Level(){}

Level::~Level(){}

void Level::Draw(){
	for (int i = 0; i < int(mLayersP.size()); i++){
		mLayersP[i]->Draw();
	}
	
}

void Level::Update(){
	for (int i = 0; i < int(mLayersP.size()); i++){
		mLayersP[i]->Update();
	}
}

//Register Level type with Level Factory
static bool sgLevelRegister = TheLevelFactory::Instance()->RegisterType("Level", Create<Level>);