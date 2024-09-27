#pragma once

//-----------------------------------------------------------------------------------------
// include
//-----------------------------------------------------------------------------------------
//* base
#include <Engine/Beta/ModelBehavior.h>
#include <Engine/Game/Animation.h>

//* DxObject
#include <Engine/System/DxObject/DxMesh.h>

////////////////////////////////////////////////////////////////////////////////////////////
// Kipfel class
////////////////////////////////////////////////////////////////////////////////////////////
class Kipfel
	: public ModelBehavior {
public:

	//=========================================================================================
	// public methods
	//=========================================================================================

	Kipfel()  = default;
	~Kipfel() = default;

	void Init();

	void Term();

	void Update();

private:

	//=========================================================================================
	// private variables
	//=========================================================================================

	std::unique_ptr<Model> model_;

};