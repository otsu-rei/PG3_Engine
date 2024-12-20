#include "GameScene.h"

//-----------------------------------------------------------------------------------------
// include
//-----------------------------------------------------------------------------------------
//* engine
#include <Engine/System/SxavengerSystem.h>
#include <Engine/System/Runtime/Performance/Performance.h>
#include <Engine/Console/Console.h>
#include <Engine/Content/SxavengerContent.h>
#include <Engine/Module/SxavengerModule.h>

//* lib
#include <Lib/Environment.h>

////////////////////////////////////////////////////////////////////////////////////////////
// GameScene class methods
////////////////////////////////////////////////////////////////////////////////////////////

void GameScene::Run() {

	//-----------------------------------------------------------------------------------------
	// init process.
	//-----------------------------------------------------------------------------------------
	sConsole->Init();
	SystemInit();
	Init();
	SxavengerSystem::ExecuteAllAllocator();

	//-----------------------------------------------------------------------------------------
	// game loop.
	//-----------------------------------------------------------------------------------------
	while (SxavengerSystem::ProcessMessage()) {

		Performance::BeginFrame();
		SxavengerSystem::BeginImGuiFrame();

		//-----------------------------------------------------------------------------------------
		// update process
		//-----------------------------------------------------------------------------------------

		SxavengerSystem::GetInput()->Update();
		sConsole->UpdateConsole();

		if (sConsole->IsUpdateRequired()) {
			Update();
		}

		SxavengerSystem::EndImGuiFrame();
		SxavengerSystem::TransitionAllocator();

		//-----------------------------------------------------------------------------------------
		// draw process.
		//-----------------------------------------------------------------------------------------

		Draw();
		sConsole->Draw();
		DrawScreen();
		sConsole->DrawConsole();

		SxavengerSystem::PresentAllWindow();
		SxavengerSystem::ExecuteAllAllocator();
		//!< sub window delete時に死ぬ
		//!< shader hot reload 時に死ぬ

		SxavengerModule::ResetPrimtive();

		Performance::EndFrame();

		if (SxavengerSystem::IsTriggerKey(KeyId::KEY_F4)) {
			break;
		}
	}

	//-----------------------------------------------------------------------------------------
	// term process
	//-----------------------------------------------------------------------------------------

	Term();

	sConsole->Term();

}

void GameScene::SystemInit() {

	mainWindow_ = SxavengerSystem::CreateMainWindow(kMainWindowSize, kMainWindowTitle).lock();
	mainWindow_->SetIcon("packages/icon/SxavengerEngineIcon.ico", { 32, 32 });

	sConsole->SetWindow(mainWindow_);

	{
		std::unique_ptr<DxObject::ReflectionComputePipelineState> compute = std::make_unique<DxObject::ReflectionComputePipelineState>();
		compute->CreateBlob("common/white1x1.cs.hlsl");
		compute->ReflectionPipeline(SxavengerSystem::GetDxDevice());

		std::shared_ptr<UnorderedTexture> white1x1 = SxavengerContent::TryCreateUnorderedTexture("white1x1", { 1, 1 });
		white1x1->TransitionBeginUnordered(SxavengerSystem::GetMainThreadContext());
		compute->SetPipeline(SxavengerSystem::GetMainThreadContext()->GetDxCommand());

		DxObject::BindBufferDesc bind = {};
		bind.SetHandle("gOutput", white1x1->GetGPUHandleUAV());
		compute->BindComputeBuffer(SxavengerSystem::GetMainThreadContext()->GetDxCommand(), bind);

		compute->Dispatch(SxavengerSystem::GetMainThreadContext()->GetDxCommand(), 1, 1, 1);

		white1x1->TransitionEndUnordered(SxavengerSystem::GetMainThreadContext());
		SxavengerSystem::TransitionAllocator();
	}
}

void GameScene::Init() {
	player_ = std::make_unique<Player>();
	player_->Init();
	player_->SetToConsole();

	inputHandler_ = std::make_unique<InputHandler>();
	inputHandler_->Init();
}

void GameScene::Update() {
	command_ = inputHandler_->HandleInput();

	if (command_ != nullptr) {
		command_->Execute(player_.get());
	}

	player_->Update();
}

void GameScene::Draw() {
}

void GameScene::DrawScreen() {
}

void GameScene::Term() {
	player_.reset();
	SxavengerSystem::ExecuteAllAllocator();
}


