#include "SceneGame.h"

//-----------------------------------------------------------------------------------------
// include
//-----------------------------------------------------------------------------------------
//* engine
#include <Engine/System/Runtime/Scene/SceneController.h>
#include <Engine/System/SxavengerSystem.h>
#include <Engine/Module/SxavengerModule.h>

////////////////////////////////////////////////////////////////////////////////////////////
// SceneGame class methods
////////////////////////////////////////////////////////////////////////////////////////////

void SceneGame::Init() {
	player_ = std::make_unique<Player>();
	player_->Init();
	player_->SetToConsole();

	enemy_ = std::make_unique<Enemy>();
	enemy_->Init();
	enemy_->SetToConsole();
}

void SceneGame::Term() {
}

void SceneGame::Update() {
	player_->Update();
	enemy_->Update();

	if (enemy_->IsHit()) {
		controller_->RequestNextScene("Clear");
	}

	SxavengerModule::CheckCollision();
}

void SceneGame::Draw() {
}
