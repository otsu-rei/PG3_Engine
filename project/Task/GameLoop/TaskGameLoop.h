#pragma once

//-----------------------------------------------------------------------------------------
// include
//-----------------------------------------------------------------------------------------
//* base
#include <Engine/System/Runtime/GameLoop/GameLoop.h>

//* engine
#include <Engine/!Render/FPresenter.h>
#include <Engine/!Render/FSceneTextures.h>
#include <Engine/!Render/Scene/FSceneRenderer.h>
#include <Engine/!Render/Scene/FScene.h>


//* task
#include "../Field.h"

//* c++
#include <bitset>
#include <array>

////////////////////////////////////////////////////////////////////////////////////////////
// TaskGameLoop class
////////////////////////////////////////////////////////////////////////////////////////////
class TaskGameLoop
	: public GameLoop::Interface {
public:

	//=========================================================================================
	// public method
	//=========================================================================================

	void Init(GameLoop::Context* context) override;

	void Term() override;

private:

	//=========================================================================================
	// private variables
	//=========================================================================================

	std::shared_ptr<GameWindow> window_;

	//* render *//

	std::unique_ptr<FSceneTextures> textures_;
	std::unique_ptr<FScene>  scene_;
	std::unique_ptr<FCanvas> canvas_;

	std::unique_ptr<FSceneRenderer> renderer_;

	FPresenter presenter_;

	//* field *//

	std::unique_ptr<Field> field_;

	//=========================================================================================
	// private methods
	//=========================================================================================

	void InitSystem();

	void TermSystem();

	void UpdateSystem();

	void DrawSystem();
};
