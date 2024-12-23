#pragma once

//-----------------------------------------------------------------------------------------
// include
//-----------------------------------------------------------------------------------------
//* base
#include <Engine/System/Runtime/Scene/BaseScene.h>

//* task
#include <Task/Entity/Player.h>
#include <Task/Entity/Enemy.h>

////////////////////////////////////////////////////////////////////////////////////////////
// SceneGame class
////////////////////////////////////////////////////////////////////////////////////////////
class SceneGame
	: public BaseScene {
public:

	//=========================================================================================
	// public method
	//=========================================================================================

	void Init() override;

	void Term() override;

	void Update() override;

	void Draw() override;

private:

	//=========================================================================================
	// private variables
	//=========================================================================================

	std::unique_ptr<Player> player_;
	std::unique_ptr<Enemy> enemy_;

};
