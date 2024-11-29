#pragma once

//-----------------------------------------------------------------------------------------
// include
//-----------------------------------------------------------------------------------------
//* camera
#include "Camera3d.h"

////////////////////////////////////////////////////////////////////////////////////////////
// BlenderDebugCamera3d class
////////////////////////////////////////////////////////////////////////////////////////////
class BlenderDebugCamera3d
	: public Camera3d {
public:

	//=========================================================================================
	// public methods
	//=========================================================================================

	BlenderDebugCamera3d()  = default;
	~BlenderDebugCamera3d() = default;

	void Update();

private:

	//=========================================================================================
	// private variables
	//=========================================================================================



};