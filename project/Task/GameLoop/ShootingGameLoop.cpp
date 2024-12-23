#include "ShootingGameLoop.h"

////////////////////////////////////////////////////////////////////////////////////////////
// ShootingGameLoop class methods
////////////////////////////////////////////////////////////////////////////////////////////

void ShootingGameLoop::Init(GameLoop::Context* context) {

	context->SetState(
		GameLoop::State::Init, std::nullopt, [this]() {
			InitGame();
		}
	);

	context->SetState(
		GameLoop::State::Term, std::nullopt, [this]() {
			TermGame();
		}
	);

	context->SetState(
		GameLoop::State::Update, std::nullopt, [this]() {
			UpdateGame();
		}
	);

	context->SetState(
		GameLoop::State::Render, std::nullopt, [this]() {
			DrawGame();
		}
	);

	context->SetState(
		GameLoop::State::Begin, std::nullopt, [this]() {
			controller_->ActivateNextScene();
		}
	);
}

void ShootingGameLoop::Term() {
}

void ShootingGameLoop::InitGame() {

	controller_ = std::make_unique<SceneController>();

	std::unique_ptr<GameSceneFactory> factory = std::make_unique<GameSceneFactory>();
	factory->Init();

	controller_->SetSceneFactory(std::move(factory));
	controller_->Init("Title");
}

void ShootingGameLoop::TermGame() {
	controller_->TermScene();
	controller_.reset();
}

void ShootingGameLoop::UpdateGame() {
	controller_->UpdateScene();
}

void ShootingGameLoop::DrawGame() {
	controller_->DrawScene();
}
