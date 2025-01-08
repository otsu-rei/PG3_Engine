#pragma once

//-----------------------------------------------------------------------------------------
// include
//-----------------------------------------------------------------------------------------
//* actor
#include "Actor/Geometry/AGeometryActor.h"

//* c++
#include <list>

//-----------------------------------------------------------------------------------------
// forward
//-----------------------------------------------------------------------------------------
class ALightActor;

////////////////////////////////////////////////////////////////////////////////////////////
// FScene class
////////////////////////////////////////////////////////////////////////////////////////////
class FScene {
public:

	//=========================================================================================
	// public methods
	//=========================================================================================

	FScene()  = default;
	~FScene() = default;


	//* getter *//

	const std::list<AGeometryActor*>& GetGeometries() const { return geometries_; }

private:

	//=========================================================================================
	// private variables
	//=========================================================================================

	//* scene actors *//

	std::list<AGeometryActor*> geometries_;
	//* sceneに描画されるactorのリスト

	std::list<ALightActor*> lights_;
	//* sceneに描画されるactorのリスト

	


};
