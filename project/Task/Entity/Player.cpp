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

	collider_ = std::make_unique<Collider>();
	collider_->SetToCollection();
	collider_->SetColliderBoundingCapsule();
	collider_->SetTypeId(kColliderType_Player);
	collider_->SetParent(this);
}

void Player::Term() {
}

void Player::Update() {

	if (SxavengerSystem::IsPressKey(KeyId::KEY_A)) {
		ModelBehavior::GetTransform().translate.x -= speed_.x;
	}

	if (SxavengerSystem::IsPressKey(KeyId::KEY_D)) {
		ModelBehavior::GetTransform().translate.x += speed_.x;
	}

	if (SxavengerSystem::IsPressKey(KeyId::KEY_W)) {
		ModelBehavior::GetTransform().translate.y += speed_.y;
	}

	if (SxavengerSystem::IsPressKey(KeyId::KEY_S)) {
		ModelBehavior::GetTransform().translate.y -= speed_.y;
	}

	UpdateMatrix();
	collider_->UpdateMatrix();

	if (SxavengerSystem::IsTriggerKey(KeyId::KEY_SPACE)) {
		bullet_ = std::make_unique<PlayerBullet>();
		bullet_->Init(GetPosition());
		SetChild(bullet_.get());
	}

	if (bullet_ != nullptr) {
		bullet_->Update();

		if (bullet_->IsDelete()) {
			bullet_.reset();
		}
	}
}
