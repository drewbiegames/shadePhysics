#pragma once

#include <map>
#include <string>
#include <functional>

#include "Singleton.h"

/*
	Template Factory
*/

template<class T>
class FactoryT : public Uncopyable{
public:

	//	Param 1 - Type ID
	//	Param 2 - Creation Function
	//Return bool true on success, false on fail
	bool RegisterType(std::string typeID, std::function<T*()> creator){
		auto it = mCreators.find(typeID);

		if (it != mCreators.end()){
			printf("I cannot create the %s factory!\n", typeID.c_str());
			return false;
		}

		mCreators[typeID] = creator;

		return true;
	};

	//	Param 1 - Type ID
	//Return nullptr if not found, return T* if found
	T* Create(std::string typeID){
		auto it = mCreators.find(typeID);
		if (it == mCreators.end()){
			printf("Could not find type: %s\n", typeID.c_str());
			return nullptr;
		}
		return (it->second());
	};

private:
	friend class SingletonT<FactoryT<T>>;
	FactoryT(){}

	std::map < std::string, std::function<T*()> > mCreators;
};

//Template Creation Function
template <class T>
T* Create(){
	return new T();
}