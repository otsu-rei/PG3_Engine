#pragma once

//-----------------------------------------------------------------------------------------
// include
//-----------------------------------------------------------------------------------------
//* engine
#include <Engine/Module/Behavior/ModelBehavior.h>
#include <Engine/Asset/Asset.h>

//* lib
#include <Lib/Geometry/Vector2.h>

//* Task
#include <Task/ICommand.h>

////////////////////////////////////////////////////////////////////////////////////////////
// Player class
////////////////////////////////////////////////////////////////////////////////////////////
class Player
	: public ModelBehavior {
public:

	//=========================================================================================
	// public methods
	//=========================================================================================

	Player()  = default;
	~Player() = default;

	void Init();

	void Term();

	void Update();

	//* command

	void LeftMove();

	void RightMove();

private:

	//=========================================================================================
	// private variables
	//=========================================================================================

	Vector2f speed_ = kUnit2<float>;

	std::shared_ptr<AssetModel> model_;

};
