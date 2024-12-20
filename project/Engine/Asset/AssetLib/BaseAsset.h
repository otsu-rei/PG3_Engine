#pragma once

//-----------------------------------------------------------------------------------------
// include
//-----------------------------------------------------------------------------------------
//* c++
#include <filesystem>

////////////////////////////////////////////////////////////////////////////////////////////
// Base Asset class
////////////////////////////////////////////////////////////////////////////////////////////
class BaseAsset {
public:

	//=========================================================================================
	// public methods
	//=========================================================================================

	virtual void SetInspectorImGui() = 0;

	void SetFilepath(const std::filesystem::path& filepath) { filepath_ = filepath; }

protected:

	//=========================================================================================
	// protected variables
	//=========================================================================================

	std::filesystem::path filepath_;

	bool isLoaded_ = false;

};
