#pragma once

//-----------------------------------------------------------------------------------------
// include
//-----------------------------------------------------------------------------------------
//* engine
#include <Engine/Module/Behavior/ModelBehavior.h>
#include <Engine/Asset/Asset.h>
#include <Engine/Module/Collider/Collider.h>

//* lib
#include <Lib/Geometry/Vector2.h>

//* task
#include "PlayerBullet.h"

////////////////////////////////////////////////////////////////////////////////////////////
// Player class
////////////////////////////////////////////////////////////////////////////////////////////
class Player
	: public ModelBehavior {
public:

	//=========================================================================================
	// public methods
	//=========================================================================================

	Player() = default;
	~Player() = default;

	void Init();

	void Term();

	void Update();

private:

	//=========================================================================================
	// private variables
	//=========================================================================================

	Vector2f speed_ = { 0.1f, 0.1f };

	std::shared_ptr<AssetModel> model_;

	std::unique_ptr<Collider> collider_;

	std::unique_ptr<PlayerBullet> bullet_;

};
