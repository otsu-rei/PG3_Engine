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

////////////////////////////////////////////////////////////////////////////////////////////
// Enemy class
////////////////////////////////////////////////////////////////////////////////////////////
class Enemy
	: public ModelBehavior {
public:
	//=========================================================================================
	// public methods
	//=========================================================================================

	Enemy()  = default;
	~Enemy() = default;

	void Init();

	void Term();

	void Update();

	bool IsHit() const { return isHit_; }

private:

	//=========================================================================================
	// private variables
	//=========================================================================================

	Vector2f speed_ = { 0.1f, 0.1f };

	std::shared_ptr<AssetModel> model_;

	std::unique_ptr<Collider> collider_;

	bool isHit_ = false;

	
};
