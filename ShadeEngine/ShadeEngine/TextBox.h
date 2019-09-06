#pragma once

#include "SDLGameObject.h"
#include "Text.h"

/*
	Text Box Game Object Class
	Display's text to the screen
*/

class TextBox : public SDLGameObject {
public:
	virtual ~TextBox(){}

	//Update the text box
	virtual void Update(){};
	//Draw the text box
	virtual void Draw();
	//Clean the object pointers
	virtual void Clean();

	virtual void React(GameObject* obj){}

	//Load from XML Node
	virtual void Load(TiXmlElement* node);

	//Operator overload to change text
	virtual void operator=(const std::string& newText);

protected:
	std::string mText;
	Text* mTextureP;
};