#ifndef BASELEVELCREATOR_H
#define BASELEVELCREATOR_H

class Level;

class BaseLevelCreator {
public:
	virtual Level* createLevel() const = 0;
	virtual ~BaseLevelCreator() {}
private:

};

#endif