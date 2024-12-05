//-----------------------------------------------------------------------------------------
// include
//-----------------------------------------------------------------------------------------
//* engine
#include <Engine/System/SxavengerSystem.h>
#include <Engine/System/Runtime/Scene/GameScene.h>
#include <Engine/Asset/SxavengerAsset.h>
#include <Engine/Content/SxavengerContent.h>

#include "Demo/GuizmoScene.h"


// c++
#include <memory>

////////////////////////////////////////////////////////////////////////////////////////////
// メイン関数
////////////////////////////////////////////////////////////////////////////////////////////
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	//=========================================================================================
	// sxavenger engine initalize.
	//=========================================================================================
	SxavengerSystem::Init();
	SxavengerAsset::Init();
	SxavengerContent::Init();

	//=========================================================================================
	// game scene run.
	//=========================================================================================
	{
		std::unique_ptr<GuizmoScene> scene = std::make_unique<GuizmoScene>();
		scene->Run();
	}

	//=========================================================================================
	// sxavenger engine term.
	//=========================================================================================
	SxavengerSystem::TermThreadCollection();

	SxavengerContent::Term();
	SxavengerAsset::Term();
	SxavengerSystem::Term();

	return 0;
}