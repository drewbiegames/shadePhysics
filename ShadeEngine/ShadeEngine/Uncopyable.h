#pragma once

/*
	Uncopyable base class

	To Use:
		Include "Singleton.h"
		Inherit from Uncopyable
		Friend class Singleton<T>
		Typedef Singleton<T>

	Help from Marco Dias
*/

class Uncopyable {
private:
	Uncopyable& operator= (const Uncopyable& uc);	//assignment operator
	Uncopyable(const Uncopyable& uc);				//copy construtor

protected:
	Uncopyable(){}
};