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
// PlayerBullet class
////////////////////////////////////////////////////////////////////////////////////////////
class PlayerBullet
	: public ModelBehavior {
public:

	//=========================================================================================
	// public methods
	//=========================================================================================

	PlayerBullet()  = default;
	~PlayerBullet() = default;

	void Init(const Vector3f& position);

	void Term();

	void Update();

	bool IsDelete() const { return time_.time >= 2.0f; }

private:

	//=========================================================================================
	// private variables
	//=========================================================================================

	std::shared_ptr<AssetModel> model_;
	std::shared_ptr<Collider> collider_;

	DeltaTimePoint<TimeUnit::s> time_;

};
