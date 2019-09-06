#pragma once

/*
	Layer Interface

	Ensures that the level is drawn in the correct order,
	Eg. Background first, then objects

	Ref: SDL Game Developent, Shaun Mitchell

	not currently - tested
*/

class Layer {
public:
	virtual void Draw() = 0{};
	virtual void Update() = 0{};

protected:
	virtual ~Layer() = 0 {};

};