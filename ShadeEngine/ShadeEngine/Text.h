#pragma once

#include <SDL_ttf.h>

#include "Texture.h"
/*
	Text Asset
	Displays text on the screen
*/

class Text : public Texture{
public:
	Text() : Texture(), mFont(nullptr) {}

	//Load from XML Node
	bool Load(TiXmlElement* node);

	//Free the current texture
	void Free();

	//Load font file
	bool LoadFont(const std::string path, int size);

	//Sets the colour of the font
	void SetColor(Uint8 red, Uint8 green, Uint8 blue, Uint8 alpha);

	//Changes the text
	void ChangeText(const std::string newText);

private:

	TTF_Font* mFont;
	SDL_Color mColour;
};