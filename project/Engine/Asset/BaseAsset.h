#pragma once

//-----------------------------------------------------------------------------------------
// forward
//-----------------------------------------------------------------------------------------
class AssetCollection;

////////////////////////////////////////////////////////////////////////////////////////////
// Base Asset class
////////////////////////////////////////////////////////////////////////////////////////////
class BaseAsset {
public:

	//=========================================================================================
	// public methods
	//=========================================================================================

	BaseAsset()          = default;
	virtual ~BaseAsset() = default;

	//* getter *//

	AssetCollection* GetCollection() const;

	//* setter *//

	void SetCollection(AssetCollection* collection) { collection_ = collection; }

private:

	//=========================================================================================
	// private variables
	//=========================================================================================

	AssetCollection* collection_ = nullptr;

};
