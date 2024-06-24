#include "MyEngine.h"

//-----------------------------------------------------------------------------------------
// include
//-----------------------------------------------------------------------------------------
#include <Logger.h>

// origin
#include <WinApp.h>
#include <DirectXCommon.h>
#include <DirectXRCommon.h>
#include <ImGuiManager.h>
#include <TextureManager.h>
#include <Input.h>

#include <ComPtr.h>

#include <Performance.h>
#include <Console.h>

////////////////////////////////////////////////////////////////////////////////////////////
// namespace -anonymouse-
////////////////////////////////////////////////////////////////////////////////////////////
namespace {

	//-----------------------------------------------------------------------------------------
	// 汎用機能
	//-----------------------------------------------------------------------------------------
	WinApp* sWinApp = nullptr;                 //!< WindowApp system
	DirectXRCommon* sDirectXRCommon = nullptr;   //!< DirectX12 system
	ImGuiManager* sImGuiManager = nullptr;     //!< ImGui system
	TextureManager* sTextureManager = nullptr; //!< TextureManager system
	Input* sInput = nullptr;
}

////////////////////////////////////////////////////////////////////////////////////////////
// MyEngine class
////////////////////////////////////////////////////////////////////////////////////////////

//-----------------------------------------------------------------------------------------
// static variables
//-----------------------------------------------------------------------------------------
Camera3D* MyEngine::camera3D_ = nullptr;
Camera2D* MyEngine::camera2D_ = nullptr;

//-----------------------------------------------------------------------------------------
// method
//-----------------------------------------------------------------------------------------

void MyEngine::Initialize(int32_t kWindowWidth, int32_t kWindowHeight, const char* kWindowTitle) {
	ExternalLogger::Open();
	CoInitializeEx(0, COINIT_MULTITHREADED);

	// ウィンドウの生成
	{
		sWinApp = WinApp::GetInstance();

		std::wstring titleString = ToWstring(kWindowTitle);

		std::string title = kWindowTitle;
		ExternalLogger::Write("[windowName]: " + title);

		sWinApp->CreateGameWindow(kWindowWidth, kWindowHeight, titleString.c_str());
		ExternalLogger::Write("Complete Initialize: sWinApp");
	}

	// DirectX12 の初期化
	{
		sDirectXRCommon = DirectXRCommon::GetInstance();
		sDirectXRCommon->Init(sWinApp, kWindowWidth, kWindowHeight);
		/*sDirectXRCommon->InitRayTracing(kWindowWidth, kWindowHeight);*/
		ExternalLogger::Write("Complete Initialize: sDirectXRCommon");

	}

	
	// ImGuiManager の初期化
	{
		sImGuiManager = ImGuiManager::GetInstaince();
		sImGuiManager->Init(sWinApp, sDirectXRCommon);
		ExternalLogger::Write("Complete Initialize: sImGuiManager");
	}
	

	// TextureManager の初期化
	{
		sTextureManager = TextureManager::GetInstance();
		sTextureManager->Init(sDirectXRCommon);
		ExternalLogger::Write("Complete Initialize: sTextureManager");

		// オフスク用のテクスチャの生成 todo: consoleに移動
		sTextureManager->CreateRenderTexture("offscreen", kWindowWidth, kWindowHeight);
	}

	// Inputの初期化
	{
		sInput = Input::GetInstance();
		sInput->Init(sWinApp->GetHinst(), sWinApp->GetHwnd());
		ExternalLogger::Write("Complete Initialize: sInput");
	}

	ExternalLogger::Close();
}

void MyEngine::Finalize() {
	sTextureManager->Term();
	sTextureManager = nullptr;

	sImGuiManager->Term();
	sImGuiManager = nullptr;

	sDirectXRCommon->TermRayTracing();
	sDirectXRCommon->Term();
	sDirectXRCommon = nullptr;

	sWinApp->Term();
	sWinApp = nullptr;

	CoUninitialize();
}

void MyEngine::BeginFrame() {
	Performance::BeginFrame();
	sInput->Update();
	sImGuiManager->Begin();
}

void MyEngine::BeginScreenDraw() {
	/*sDirectXRCommon->BeginFrame();*/
	sDirectXRCommon->BeginScreenDraw();
}

void MyEngine::BeginOffscreen(Texture* renderTexture) {
	sDirectXRCommon->BeginOffscreen(renderTexture);
}

void MyEngine::EndOffscreen(Texture* renderTexture) {
	sDirectXRCommon->EndOffscreen(renderTexture);
}

void MyEngine::BeginOffscreens(Texture* renderTextures[D3D12_SIMULTANEOUS_RENDER_TARGET_COUNT]) {
	sDirectXRCommon->BeginOffscreens(renderTextures);
}

void MyEngine::EndOffscreens(Texture* renderTextures[D3D12_SIMULTANEOUS_RENDER_TARGET_COUNT]) {
	sDirectXRCommon->EndOffscreens(renderTextures);
}

void MyEngine::TransitionProcess() {
	sDirectXRCommon->TransitionProcess();
}

void MyEngine::TransitionProcessSingle() {
	sDirectXRCommon->TransitionSingleAllocator();
}

void MyEngine::EndFrame() {
	sImGuiManager->End();
	sDirectXRCommon->EndFrame();
	Performance::EndFrame();
}

void MyEngine::BeginDraw() {
}

int MyEngine::ProcessMessage() {
	return sWinApp->ProcessMessage() ? 1 : 0;
}

DxObject::Descriptor MyEngine::GetCurrentDescripor(DxObject::DescriptorType type) {
	assert(sDirectXRCommon != nullptr);
	return sDirectXRCommon->GetDescriptorsObj()->GetCurrentDescriptor(type);
}

void MyEngine::EraseDescriptor(DxObject::Descriptor& descriptor) {
	assert(sDirectXRCommon != nullptr);
	sDirectXRCommon->GetDescriptorsObj()->Erase(descriptor);
}

ID3D12Device8* MyEngine::GetDevice() {
	assert(sDirectXRCommon != nullptr);
	return sDirectXRCommon->GetDeviceObj()->GetDevice();
}

ID3D12GraphicsCommandList6* MyEngine::GetCommandList() {
	assert(sDirectXRCommon != nullptr);
	return sDirectXRCommon->GetCommandList();
}

DxObject::Devices* MyEngine::GetDevicesObj() {
	assert(sDirectXRCommon != nullptr);
	return sDirectXRCommon->GetDeviceObj();
}

DirectXCommon* MyEngine::GetDxCommon() {
	assert(sDirectXRCommon != nullptr);
	return sDirectXRCommon;
}

TextureManager* MyEngine::GetTextureManager() {
	assert(sTextureManager != nullptr);
	return sTextureManager;
}

Texture* MyEngine::CreateRenderTexture(const std::string& key, int32_t textureWidth, int32_t textureHeight, const Vector4f& clearColor) {
	assert(sTextureManager != nullptr);
	return sTextureManager->CreateRenderTexture(key, textureWidth, textureHeight, clearColor);
}

Texture* MyEngine::LoadTexture(const std::string& filePath) {
	assert(sTextureManager != nullptr);
	return sTextureManager->LoadTexture(filePath);
}

const D3D12_GPU_DESCRIPTOR_HANDLE& MyEngine::GetTextureHandleGPU(const std::string& textureKey) {
	assert(sTextureManager != nullptr);
	return sTextureManager->GetGPUHandle(textureKey);
}

Texture* MyEngine::GetTexture(const std::string& textureKey) {
	assert(sTextureManager != nullptr);
	return sTextureManager->GetTexture(textureKey);
}

bool MyEngine::IsPressKey(uint8_t dik) {
	assert(sInput != nullptr);
	return sInput->IsPressKey(dik);
}

bool MyEngine::IsTriggerKey(uint8_t dik) {
	assert(sInput != nullptr);
	return sInput->IsTriggerKey(dik);
}

bool MyEngine::IsReleaseKey(uint8_t dik) {
	assert(sInput != nullptr);
	return sInput->IsReleaseKey(dik);
}

////////////////////////////////////////////////////////////////////////////////////////////
// RayTracingEngine class methods
////////////////////////////////////////////////////////////////////////////////////////////

void RayTracingEngine::BeginRayTracing(DxrObject::TopLevelAS* tlas) {
	assert(sDirectXRCommon != nullptr);
	sDirectXRCommon->BeginRayTracing(tlas);
}

void RayTracingEngine::EndRayTracing() {
	assert(sDirectXRCommon != nullptr);
	sDirectXRCommon->EndRayTracing();
}

DirectXRCommon* RayTracingEngine::GetDxrCommon() {
	assert(sDirectXRCommon != nullptr);
	return sDirectXRCommon;
}
