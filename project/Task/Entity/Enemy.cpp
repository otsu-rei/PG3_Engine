#include "Enemy.h"

//-----------------------------------------------------------------------------------------
// include
//-----------------------------------------------------------------------------------------
//* engine
#include <Engine/Asset/SxavengerAsset.h>

////////////////////////////////////////////////////////////////////////////////////////////
// Enemy class methods
////////////////////////////////////////////////////////////////////////////////////////////

void Enemy::Init() {
	SetName("enemy");

	model_ = SxavengerAsset::ImportModel("asset/model/demo/cube.obj");
	model_->AsyncLoad();
	SxavengerSystem::PushTask(model_);
	model_->WaitCompleted();

	ModelBehavior::SetRenderingFlag(BehaviorRenderingType::kSystematic);
	ModelBehavior::model_ = model_.get();

	collider_ = std::make_unique<Collider>();
	collider_->SetToCollection();
	collider_->SetColliderBoundingCapsule();
	collider_->SetTypeId(kColliderType_Enemy);
	collider_->SetTargetId(kColliderType_PlayerBullet);
	collider_->SetParent(this);

	collider_->SetOnCollisionEnter([this](_MAYBE_UNUSED Collider* const collider) {
		isHit_ = true;
	});

	ModelBehavior::GetTransform().translate.z = 8.0f;

	ModelBehavior::UpdateMatrix();
	collider_->UpdateMatrix();
}

void Enemy::Term() {
}

void Enemy::Update() {
}
