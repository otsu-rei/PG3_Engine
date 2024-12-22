#pragma once

//-----------------------------------------------------------------------------------------
// include
//-----------------------------------------------------------------------------------------
//* scene
#include "IScene.h"

//* c++
#include <memory>
#include <unordered_map>
#include <functional>
#include <string>

////////////////////////////////////////////////////////////////////////////////////////////
// Base SceneFactory class
////////////////////////////////////////////////////////////////////////////////////////////
class BaseSceneFactory {
public:

	//=========================================================================================
	// public method
	//=========================================================================================

	virtual ~BaseSceneFactory() = default;

	std::unique_ptr<IScene> CreateScene(const std::string& key) const;

	void Register(const std::string& key, std::function<std::unique_ptr<IScene>()> function) {
		factory_[key] = function;
	}

	template <DerivedFromScene T>
	void Register(const std::string& key);

protected:

	//=========================================================================================
	// protected variables
	//=========================================================================================

	std::unordered_map<std::string, std::function<std::unique_ptr<IScene>()>> factory_;

};

template<DerivedFromScene T>
inline void BaseSceneFactory::Register(const std::string& key) {
	factory_[key] = []() { return std::make_unique<T>(); };
}
