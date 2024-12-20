#include "Player.h"

//-----------------------------------------------------------------------------------------
// include
//-----------------------------------------------------------------------------------------
//* engine
#include <Engine/Asset/SxavengerAsset.h>

////////////////////////////////////////////////////////////////////////////////////////////
// Player class methods
////////////////////////////////////////////////////////////////////////////////////////////

void Player::Init() {
	SetName("Player");

	model_ = SxavengerAsset::ImportModel("asset/model/demo/cube.obj");
	model_->AsyncLoad();
	SxavengerSystem::PushTask(model_);
	model_->WaitCompleted();

	ModelBehavior::SetRenderingFlag(BehaviorRenderingType::kSystematic);
	ModelBehavior::model_ = model_.get();
}

void Player::Term() {
}

void Player::Update() {
	UpdateMatrix();
}

void Player::LeftMove() {
	ModelBehavior::GetTransform().translate.x -= speed_.x;
}

void Player::RightMove() {
	ModelBehavior::GetTransform().translate.x += speed_.x;
}
