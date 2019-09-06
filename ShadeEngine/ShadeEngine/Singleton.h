#pragma once

#include "Uncopyable.h"

/*
	Singleton Template
	Singleton Pattern

	To Use:
		Include "Singleton.h"
		Inherit from Uncopyable
		Friend class Singleton<T>
		Typedef Singleton<T>

	Help from Marco Dias
*/

template <class T>
class SingletonT : public Uncopyable {
public:
	static T* Instance(){
		static T t;
		return &t;
	}
};