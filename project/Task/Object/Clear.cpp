#include "Clear.h"

//-----------------------------------------------------------------------------------------
// include
//-----------------------------------------------------------------------------------------
//* engine
#include <Engine/Asset/SxavengerAsset.h>

////////////////////////////////////////////////////////////////////////////////////////////
// Title class
////////////////////////////////////////////////////////////////////////////////////////////

void Clear::Init() {
	SetName("clear");

	model_ = SxavengerAsset::ImportModel("asset/model/text/clear.obj");
	model_->AsyncLoad();
	SxavengerSystem::PushTask(model_);
	model_->WaitCompleted();

	ModelBehavior::SetRenderingFlag(BehaviorRenderingType::kSystematic);
	ModelBehavior::model_ = model_.get();
}

void Clear::Term() {
}

void Clear::Update() {
}
