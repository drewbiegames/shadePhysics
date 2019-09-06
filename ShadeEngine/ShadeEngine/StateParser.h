#pragma once

#include <iostream>
#include <vector>
#include <string>

#include "tinyxml.h"
#include "GameObject.h"
#include "Factory.h"

/*
	State Parser

	Parse states from an XML file
*/

class StateParser {
public:
	//Gets XML file and then pass relevent nodes to object, texture, animation parsers
	bool ParseState(const char* stateFile, std::string stateID, std::vector<GameObject*>& objects);

private:
	//Parse objects from XML File
	void parseObjects(TiXmlElement* root, std::vector<GameObject*>& objects);

	//Parse Assets from XML File
	void parseAssets(TiXmlElement* root);

	//Parse Animation from XML File
	void parseAnimations(TiXmlElement* root);

};