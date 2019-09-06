#include "StateParser.h"

#include "GameObject.h"
#include "GLGameObject.h"
#include "Texture.h"
#include "SpriteSheet.h"
#include "Animation.h"
#include "AssetManager.h"
#include "Game.h"
#include "Factory.h"
#include "GLShader.h"
#include "FrameBuffer.h"

#include "GLLight.h"

//Gets XML file and then pass relevent nodes to object, texture, animation parsers
//	Param 1 - Path to the XML File
//	Param 2 - ID of the current state
//	Param 3 - GameObjects vector
bool StateParser::ParseState(const char* stateFile, std::string stateID, std::vector<GameObject*>& objects){
	// create the XML Doc
	TiXmlDocument xmlDoc;

	//load state file
	if (!xmlDoc.LoadFile(stateFile)){
		std::cerr << xmlDoc.ErrorDesc() << std::endl;
		return false;
	}

	//get root element
	TiXmlElement* root = xmlDoc.RootElement();

	//pre declare the states
	TiXmlElement* stateRoot = 0;

	//get this states root node and assign it to stateRoot
	for (TiXmlElement* e = root->FirstChildElement(); e != nullptr; e = e->NextSiblingElement()){
		if (e->Value() == stateID){
			stateRoot = e;
			break;
		}
	}

	//pre declare texture root
	TiXmlElement* textureRoot = 0;

	for (TiXmlElement* e = stateRoot->FirstChildElement(); e != nullptr; e = e->NextSiblingElement()){
		if (e->Value() == std::string("ASSETS"))
			textureRoot = e;
	}

	//parse the textures
	parseAssets(textureRoot);

	//predeclare object root
	TiXmlElement* objectRoot = 0;

	//get the root of the texture elements
	for (TiXmlElement* e = stateRoot->FirstChildElement(); e != nullptr; e = e->NextSiblingElement()){
		if (e->Value() == std::string("OBJECTS"))
			objectRoot = e;
	}

	//parse the objects
	parseObjects(objectRoot, objects);

	return true;
}

//Parse Textures from XML Node
//	Param 1 - TiXmlElement the TEXTURE root node
void StateParser::parseAssets(TiXmlElement* root){
	for (TiXmlElement* e = root->FirstChildElement(); e != nullptr; e = e->NextSiblingElement()){
		if (e->Value() == std::string("spritesheet")){
			Asset* sheet = TheAssetFactory::Instance()->Create("SpriteSheet");
			sheet->Load(e);
			parseAnimations(e);
		}
		if (e->Value() == std::string("texture")){
			Asset* texture = TheAssetFactory::Instance()->Create("Texture");
			texture->Load(e);
		}
		if (e->Value() == std::string("gl_texture")){
			Asset* gltexture = TheAssetFactory::Instance()->Create("GLTexture");
			gltexture->Load(e);
		}
		if (e->Value() == std::string("gl_material")){
			Asset* gltexture = TheAssetFactory::Instance()->Create("GLMaterial");
			gltexture->Load(e);
		}
		if (e->Value() == std::string("gl_mesh")){
			Asset* gltexture = TheAssetFactory::Instance()->Create("Mesh");
			gltexture->Load(e);
		}
		if (e->Value() == std::string("gl_shader")){
			Asset* glShader = TheAssetFactory::Instance()->Create("GLShader");
			glShader->Load(e);
		}
		if (e->Value() == std::string("gl_light")){
			TheGLLighting::Instance()->Load(e);
		}
		if (e->Value() == std::string("gl_framebuffer")){
			TheFrameBuffer::Instance()->Load(e);
		}
	}
}

//Parse Animations from XML Node
//	Param 1 - TiXmlElement - the spritesheet root node
void StateParser::parseAnimations(TiXmlElement* root){
	for (TiXmlElement* e = root->FirstChildElement(); e != nullptr; e = e->NextSiblingElement()){
		if (e->Value() == std::string("animation")){
			Asset* animation = static_cast<Asset*>(TheAssetFactory::Instance()->Create("Animation"));
			animation->Load(e);
		}
	}
}

//Parse Objects from XML Node
//	Param 1 - TiXmlElement - the OJBECT root node
void StateParser::parseObjects(TiXmlElement* root, std::vector<GameObject*>& objects){
	for (TiXmlElement* e = root->FirstChildElement(); e != nullptr; e = e->NextSiblingElement()){
		if (e->Value() == std::string("object")){
			std::string type = e->Attribute("type");
			GameObject* gameObject = TheGameObjectFactory::Instance()->Create(type);
			if (gameObject){
				gameObject->Load(e);
				objects.push_back(gameObject);
			}
			else{
				throw("Failed to load game object!");
				//error code here
			}
		}
	}
}

