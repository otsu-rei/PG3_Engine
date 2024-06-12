#include "RayTracingCamera.h"

//-----------------------------------------------------------------------------------------
// include
//-----------------------------------------------------------------------------------------
#include <Environment.h>
#include <MyEngine.h>
#include <Console.h>

////////////////////////////////////////////////////////////////////////////////////////////
// RayTracingCamera class methods
////////////////////////////////////////////////////////////////////////////////////////////

void RayTracingCamera::Init() {

	SetTransform(unitVector, {0.5f, 0.0f, 0.0f}, {0.0f, 20.0f, -40.0f});
	SetProjection(0.45f, static_cast<float>(kWindowWidth) / static_cast<float>(kWindowHeight), 0.1f, 100.0f);

	constantBuffer_ = std::make_unique<DxObject::BufferPtrResource<CameraForGPU>>(MyEngine::GetDevicesObj(), 1);
	constantBuffer_->SetPtr(0, &cameraForGpu_);

	SetThisAttribute("raytracingCamera");
}

void RayTracingCamera::Term() {
	constantBuffer_.reset();
}

void RayTracingCamera::Update(const Matrix4x4& viewerWorldMatrix) {

	if (isViewCamera_) {
		cameraForGpu_.world = viewerWorldMatrix;
	}
}

void RayTracingCamera::SetAttributeImGui() {

	ImGui::Checkbox("isPlayerView", &isViewCamera_);

	if (isViewCamera_) {
		ImGui::Text("player view...");

	} else {
		ImGui::DragFloat3("scale",     &transform_.scale.x,     0.01f);
		ImGui::DragFloat3("rotate",    &transform_.rotate.x,    0.01f);
		ImGui::DragFloat3("translate", &transform_.translate.x, 0.01f);
	}

	RecalculateCamera();
}

void RayTracingCamera::SetTransform(const Vector3f& scale, const Vector3f& rotate, const Vector3f& translate) {

	transform_ = { scale, rotate, translate };
	cameraForGpu_.world = Matrix::MakeAffine(transform_.scale, transform_.rotate, transform_.translate);

}

void RayTracingCamera::SetProjection(float fovY, float aspectRatio, float nearClip, float farClip) {

	projectionMatrix_ = Matrix::MakePerspectiveFov(fovY, aspectRatio, nearClip, farClip);

	cameraForGpu_.projInverse
		= Matrix::Inverse(projectionMatrix_);
}

void RayTracingCamera::RecalculateCamera() {
	cameraForGpu_.world = Matrix::MakeAffine(transform_.scale, transform_.rotate, transform_.translate);
}
