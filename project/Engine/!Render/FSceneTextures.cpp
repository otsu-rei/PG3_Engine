#include "FSceneTextures.h"
_DXOBJECT_USING

//-----------------------------------------------------------------------------------------
// include
//-----------------------------------------------------------------------------------------
//* engine
#include <Engine/System/SxavengerSystem.h>

//=========================================================================================
// static const variables
//=========================================================================================

const std::array<DXGI_FORMAT, FSceneTextures::kGBufferLayoutCount> FSceneTextures::kGBufferFormats = {
	DXGI_FORMAT_R8G8B8A8_UNORM,     //!< Normal
	DXGI_FORMAT_R8G8B8A8_UNORM,     //!< Material
	DXGI_FORMAT_R32G32B32A32_FLOAT, //!< Albedo_AO
	DXGI_FORMAT_R32G32B32A32_FLOAT, //!< Position
	DXGI_FORMAT_R32G32B32A32_FLOAT, //!< Lighting
};

////////////////////////////////////////////////////////////////////////////////////////////
// Framework SceneTextures class methods
////////////////////////////////////////////////////////////////////////////////////////////

void FSceneTextures::Create(const Vector2ui& size) {
	for (uint8_t i = 0; i < kGBufferLayoutCount; ++i) {
		gBuffers_[i] = std::make_unique<FTexture>();
		gBuffers_[i]->Create(size, kGBufferFormats[i]);
	}

	depth_ = std::make_unique<FSceneDepth>();
	depth_->Create(size);

	parameterBuffer_ = std::make_unique<DxObject::DimensionBuffer<TexturesParameter>>();
	parameterBuffer_->Create(SxavengerSystem::GetDxDevice(), 1);
	parameterBuffer_->At(0).size = size;

}

void FSceneTextures::BeginBasePass(const DirectXThreadContext* context) const {
	gBuffers_[static_cast<uint8_t>(GBufferLayout::Normal)]->TransitionBeginRenderTarget(context);
	gBuffers_[static_cast<uint8_t>(GBufferLayout::Material)]->TransitionBeginRenderTarget(context);
	gBuffers_[static_cast<uint8_t>(GBufferLayout::Albedo_AO)]->TransitionBeginRenderTarget(context);
	gBuffers_[static_cast<uint8_t>(GBufferLayout::Position)]->TransitionBeginRenderTarget(context);

	depth_->TransitionBeginRasterizer(context);

	static const uint8_t kGBufferCount = 4;
	std::array<D3D12_CPU_DESCRIPTOR_HANDLE, kGBufferCount> handles = {};
	handles[0] = gBuffers_[static_cast<uint8_t>(GBufferLayout::Normal)]->GetCPUHandleRTV();
	handles[1] = gBuffers_[static_cast<uint8_t>(GBufferLayout::Material)]->GetCPUHandleRTV();
	handles[2] = gBuffers_[static_cast<uint8_t>(GBufferLayout::Albedo_AO)]->GetCPUHandleRTV();
	handles[3] = gBuffers_[static_cast<uint8_t>(GBufferLayout::Position)]->GetCPUHandleRTV();

	context->GetCommandList()->OMSetRenderTargets(
		kGBufferCount, handles.data(), false, &depth_->GetRasterizerCPUHandleDSV()
	);

	gBuffers_[static_cast<uint8_t>(GBufferLayout::Normal)]->ClearRenderTarget(context);
	gBuffers_[static_cast<uint8_t>(GBufferLayout::Material)]->ClearRenderTarget(context);
	gBuffers_[static_cast<uint8_t>(GBufferLayout::Albedo_AO)]->ClearRenderTarget(context);
	gBuffers_[static_cast<uint8_t>(GBufferLayout::Position)]->ClearRenderTarget(context);

	depth_->ClearRasterizerDepth(context);
}

void FSceneTextures::EndBasePass(const DirectXThreadContext* context) const {
	gBuffers_[static_cast<uint8_t>(GBufferLayout::Normal)]->TransitionEndRenderTarget(context);
	gBuffers_[static_cast<uint8_t>(GBufferLayout::Material)]->TransitionEndRenderTarget(context);
	gBuffers_[static_cast<uint8_t>(GBufferLayout::Albedo_AO)]->TransitionEndRenderTarget(context);
	gBuffers_[static_cast<uint8_t>(GBufferLayout::Position)]->TransitionEndRenderTarget(context);

	depth_->TransitionEndRasterizer(context);
}
