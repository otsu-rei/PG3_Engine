#include "GameFramework.h"

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
// GameFramework class methods
////////////////////////////////////////////////////////////////////////////////////////////

void GameFramework::Run() {

	//-----------------------------------------------------------------------------------------
	// init process.
	//-----------------------------------------------------------------------------------------
	SystemInit();
	Init();
	SxavengerSystem::ExecuteAllAllocator();

	//-----------------------------------------------------------------------------------------
	// game loop.
	//-----------------------------------------------------------------------------------------
	while (SxavengerSystem::ProcessMessage()) {

		BeginFrame();

		//-----------------------------------------------------------------------------------------
		// update process
		//-----------------------------------------------------------------------------------------

		SystemUpdate();

		if (sConsole->IsUpdateRequired()) {
			Update();
		}

		SxavengerSystem::EndImGuiFrame();
		SxavengerSystem::TransitionAllocator();

		//-----------------------------------------------------------------------------------------
		// draw process.
		//-----------------------------------------------------------------------------------------

		Draw();
		SystemDraw();

		EndFrame();

		if (SxavengerSystem::IsTriggerKey(KeyId::KEY_F4)) {
			break;
		}
	}

	//-----------------------------------------------------------------------------------------
	// term process
	//-----------------------------------------------------------------------------------------

	Term();
	SystemTerm();
}

void GameFramework::SystemInit() {
	sConsole->Init();

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

void GameFramework::Init() {
	std::unique_ptr<BaseSceneFactory> factory = std::make_unique<BaseSceneFactory>(); //!< HACK: factoryの作成をuserに任せる
	//factory->Register<GameScene>("GameScene");
	
	controller_ = std::make_unique<SceneController>();
	controller_->Init("");
}

void GameFramework::SystemUpdate() {
	SxavengerSystem::GetInput()->Update();
	sConsole->UpdateConsole();
}

void GameFramework::Update() {
	controller_->UpdateScene();
}

void GameFramework::Draw() {
	controller_->DrawScene();
}

void GameFramework::SystemDraw() {
	sConsole->Draw();
	sConsole->DrawConsole();
}

void GameFramework::SystemTerm() {
	sConsole->Term();
}

void GameFramework::Term() {
	controller_->Term();
}

void GameFramework::BeginFrame() {
	Performance::BeginFrame();
	SxavengerSystem::BeginImGuiFrame();
}

void GameFramework::EndFrame() {
	SxavengerSystem::PresentAllWindow();
	SxavengerSystem::ExecuteAllAllocator();
	//!< sub window delete時に死ぬ
	//!< shader hot reload 時に死ぬ

	SxavengerModule::ResetPrimtive();

	controller_->ActivateNextScene();

	Performance::EndFrame();
}
