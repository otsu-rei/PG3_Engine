#include "PlayerBullet.h"

//-----------------------------------------------------------------------------------------
// include
//-----------------------------------------------------------------------------------------
//* engine
#include <Engine/Asset/SxavengerAsset.h>

////////////////////////////////////////////////////////////////////////////////////////////
// PlayerBullet class methods
////////////////////////////////////////////////////////////////////////////////////////////

void PlayerBullet::Init(const Vector3f& position) {
	SetName("player bullet");

	model_ = SxavengerAsset::ImportModel("asset/model/demo/teapot.obj");
	model_->AsyncLoad();
	SxavengerSystem::PushTask(model_);
	model_->WaitCompleted();

	ModelBehavior::SetRenderingFlag(BehaviorRenderingType::kSystematic);
	ModelBehavior::model_ = model_.get();

	collider_ = std::make_unique<Collider>();
	collider_->SetToCollection();
	collider_->SetColliderBoundingCapsule();
	collider_->SetTypeId(kColliderType_PlayerBullet);
	collider_->SetParent(this);

	ModelBehavior::GetTransform().translate = position;
	ModelBehavior::GetTransform().scale = { 0.4f, 0.4f, 0.4f };

	ModelBehavior::UpdateMatrix();
	collider_->UpdateMatrix();
}

void PlayerBullet::Term() {
}

void PlayerBullet::Update() {
	ModelBehavior::GetTransform().translate.z += 1.0f;
	ModelBehavior::UpdateMatrix();
	collider_->UpdateMatrix();

	time_.AddDeltaTime();
}
