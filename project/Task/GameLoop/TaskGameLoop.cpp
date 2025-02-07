#include "TaskGameLoop.h"

//-----------------------------------------------------------------------------------------
// include
//-----------------------------------------------------------------------------------------
//* engine
#include <Engine/System/SxavengerSystem.h>
#include <Engine/Asset/SxavengerAsset.h>
#include <Engine/Editor/EditorEngine.h>
#include <Engine/Editor/Editors/EngineDeveloperEditor.h>
#include <Engine/Editor/Editors/RenderSceneEditor.h>

////////////////////////////////////////////////////////////////////////////////////////////
// TaskGameLoop class methods
////////////////////////////////////////////////////////////////////////////////////////////

void TaskGameLoop::Init(GameLoop::Context* context) {
	context->SetState(GameLoop::State::Init, std::nullopt, [this]() { InitSystem(); });
	context->SetState(GameLoop::State::Term, std::nullopt, [this]() { TermSystem(); });
	context->SetState(GameLoop::State::Update, std::nullopt, [this]() {
		if (auto developer = sEditorEngine->TryGetEditor<EngineDeveloperEditor>()) {
			if (!developer->IsProcessRequired()) {
				return;
			}
		}

		UpdateSystem();
	});
	context->SetState(GameLoop::State::Draw, std::nullopt, [this]() { DrawSystem(); });

	context->SetCondition(
		[this]() { return !SxavengerSystem::ProcessMessage(); }
	);
}

void TaskGameLoop::Term() {
}

void TaskGameLoop::InitSystem() {

	window_ = SxavengerSystem::CreateMainWindow(kMainWindowSize, kMainWindowTitle).lock();

	//* render *//

	textures_ = std::make_unique<FSceneTextures>();
	textures_->Create(window_->GetSize());

	scene_  = std::make_unique<FScene>();

	renderer_ = std::make_unique<FSceneRenderer>();
	renderer_->SetTextures(textures_.get());
	renderer_->SetScene(scene_.get());

	canvas_ = std::make_unique<FCanvas>();
	canvas_->SetTextures(textures_.get());

	presenter_.Init();

	//* field *//

	field_ = std::make_unique<Field>();
	field_->Init();
	field_->SetToOutliner();

	canvas_->AddLayer(field_.get());

	//* editors *//

	sEditorEngine->ExecuteEditorFunction<RenderSceneEditor>([this](RenderSceneEditor* editor) {
		editor->SetGameRenderer(renderer_.get());
	});

}

void TaskGameLoop::TermSystem() {
	field_.reset();
}

void TaskGameLoop::UpdateSystem() {
}

void TaskGameLoop::DrawSystem() {

	renderer_->Render(SxavengerSystem::GetMainThreadContext());
	canvas_->Render(SxavengerSystem::GetMainThreadContext());

	sEditorEngine->ExecuteEditorFunction<RenderSceneEditor>([](RenderSceneEditor* editor) {
		editor->Draw();
	});

	window_->BeginRendering();
	window_->ClearWindow();

	presenter_.Present(SxavengerSystem::GetMainThreadContext(), textures_->GetSize(), textures_->GetGBuffer(FSceneTextures::GBufferLayout::Main)->GetGPUHandleSRV());

	SxavengerSystem::RenderImGui();

	window_->EndRendering();

}
