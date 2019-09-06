#pragma once

#include <string>

/*
	Tileset structure
	Potentialy redundent (Level parser re-write required);
*/

struct Tileset{
	int firstGridID = 0;
	int	tileWidth = 0;
	int	tileHeight = 0;
	int	spacing = 0;
	int	margin = 0;
	int	width = 0;
	int	height = 0;
	int	numColumns = 0;
	std::string name;
};