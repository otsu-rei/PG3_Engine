#include "SceneTitle.h"

//-----------------------------------------------------------------------------------------
// include
//-----------------------------------------------------------------------------------------
//* engine
#include <Engine/System/Runtime/Scene/SceneController.h>

////////////////////////////////////////////////////////////////////////////////////////////
// SceneTitle class methods
////////////////////////////////////////////////////////////////////////////////////////////

void SceneTitle::Init() {
	title_ = std::make_unique<Title>();
	title_->Init();
	title_->SetToConsole();
}

void SceneTitle::Term() {
	title_.reset();
}

void SceneTitle::Update() {
	if (SxavengerSystem::IsTriggerKey(KeyId::KEY_SPACE)) {
		controller_->RequestNextScene("Game");
	}
}

void SceneTitle::Draw() {
}
