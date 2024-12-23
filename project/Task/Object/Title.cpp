#include "Title.h"

//-----------------------------------------------------------------------------------------
// include
//-----------------------------------------------------------------------------------------
//* engine
#include <Engine/Asset/SxavengerAsset.h>

////////////////////////////////////////////////////////////////////////////////////////////
// Title class
////////////////////////////////////////////////////////////////////////////////////////////

void Title::Init() {
	SetName("title");

	model_ = SxavengerAsset::ImportModel("asset/model/text/title.obj");
	model_->AsyncLoad();
	SxavengerSystem::PushTask(model_);
	model_->WaitCompleted();

	ModelBehavior::SetRenderingFlag(BehaviorRenderingType::kSystematic);
	ModelBehavior::model_ = model_.get();
}

void Title::Term() {
}

void Title::Update() {
}
