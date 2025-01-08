#include "BaseAsset.h"

//-----------------------------------------------------------------------------------------
// include
//-----------------------------------------------------------------------------------------
//* engine
#include <Engine/System/Utility/Logger.h>

////////////////////////////////////////////////////////////////////////////////////////////
// Base Asset class methods
////////////////////////////////////////////////////////////////////////////////////////////

AssetCollection* BaseAsset::GetCollection() const {
	Assert(collection_ != nullptr, "asset collection is nullptr.");
	return collection_;
}
