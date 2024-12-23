#include "SceneClear.h"

//-----------------------------------------------------------------------------------------
// include
//-----------------------------------------------------------------------------------------
//* engine
#include <Engine/System/Runtime/Scene/SceneController.h>

////////////////////////////////////////////////////////////////////////////////////////////
// SceneClear class methods
////////////////////////////////////////////////////////////////////////////////////////////

void SceneClear::Init() {
	clear_ = std::make_unique<Clear>();
	clear_->Init();
	clear_->SetToConsole();
}

void SceneClear::Term() {
}

void SceneClear::Update() {
	if (SxavengerSystem::IsTriggerKey(KeyId::KEY_SPACE)) {
		controller_->RequestNextScene("Title");
	}
}

void SceneClear::Draw() {
}
