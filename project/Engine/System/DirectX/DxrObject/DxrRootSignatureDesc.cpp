#include "DxrRootSignatureDesc.h"
_DXROBJECT_USING

////////////////////////////////////////////////////////////////////////////////////////////
// GlobalRootSignatureDesc structure methods
////////////////////////////////////////////////////////////////////////////////////////////

void GlobalRootSignatureDesc::SetVirtualCBV(uint32_t index, uint32_t shaderRegister) {
	BaseRootSignatureDesc::SetVirtual(index, DxObject::ShaderVisibility::VISIBILITY_ALL, D3D12_ROOT_PARAMETER_TYPE_CBV, shaderRegister);
}

void GlobalRootSignatureDesc::SetVirtualSRV(uint32_t index, uint32_t shaderRegister) {
	BaseRootSignatureDesc::SetVirtual(index, DxObject::ShaderVisibility::VISIBILITY_ALL, D3D12_ROOT_PARAMETER_TYPE_SRV, shaderRegister);
}

void GlobalRootSignatureDesc::SetVirtualUAV(uint32_t index, uint32_t shaderRegister) {
	BaseRootSignatureDesc::SetVirtual(index, DxObject::ShaderVisibility::VISIBILITY_ALL, D3D12_ROOT_PARAMETER_TYPE_UAV, shaderRegister);
}

void GlobalRootSignatureDesc::SetHandleSRV(uint32_t index, uint32_t shaderRegister) {
	BaseRootSignatureDesc::SetHandle(index, DxObject::ShaderVisibility::VISIBILITY_ALL, D3D12_DESCRIPTOR_RANGE_TYPE_SRV, shaderRegister);
}

void GlobalRootSignatureDesc::SetHandleUAV(uint32_t index, uint32_t shaderRegister) {
	BaseRootSignatureDesc::SetHandle(index, DxObject::ShaderVisibility::VISIBILITY_ALL, D3D12_DESCRIPTOR_RANGE_TYPE_UAV, shaderRegister);
}

ComPtr<ID3D12RootSignature> GlobalRootSignatureDesc::CreateGlobalRootSignature(ID3D12Device* device) const {
	return BaseRootSignatureDesc::CreateRootSignature(device, D3D12_ROOT_SIGNATURE_FLAG_NONE);
}

////////////////////////////////////////////////////////////////////////////////////////////
// LocalRootSignatureDesc structure methods
////////////////////////////////////////////////////////////////////////////////////////////

void LocalRootSignatureDesc::SetVirtualCBV(uint32_t index, uint32_t shaderRegister) {
	BaseRootSignatureDesc::SetVirtual(index, DxObject::ShaderVisibility::VISIBILITY_ALL, D3D12_ROOT_PARAMETER_TYPE_CBV, shaderRegister);
}

void LocalRootSignatureDesc::SetVirtualSRV(uint32_t index, uint32_t shaderRegister) {
	BaseRootSignatureDesc::SetVirtual(index, DxObject::ShaderVisibility::VISIBILITY_ALL, D3D12_ROOT_PARAMETER_TYPE_SRV, shaderRegister);
}

void LocalRootSignatureDesc::SetVirtualUAV(uint32_t index, uint32_t shaderRegister) {
	BaseRootSignatureDesc::SetVirtual(index, DxObject::ShaderVisibility::VISIBILITY_ALL, D3D12_ROOT_PARAMETER_TYPE_UAV, shaderRegister);
}

void LocalRootSignatureDesc::SetHandleSRV(uint32_t index, uint32_t shaderRegister) {
	BaseRootSignatureDesc::SetHandle(index, DxObject::ShaderVisibility::VISIBILITY_ALL, D3D12_DESCRIPTOR_RANGE_TYPE_SRV, shaderRegister);
}

void LocalRootSignatureDesc::SetHandleUAV(uint32_t index, uint32_t shaderRegister) {
	BaseRootSignatureDesc::SetHandle(index, DxObject::ShaderVisibility::VISIBILITY_ALL, D3D12_DESCRIPTOR_RANGE_TYPE_UAV, shaderRegister);
}

ComPtr<ID3D12RootSignature> LocalRootSignatureDesc::CreateLocalRootSignature(ID3D12Device* device) const {
	return BaseRootSignatureDesc::CreateRootSignature(device, D3D12_ROOT_SIGNATURE_FLAG_LOCAL_ROOT_SIGNATURE);
}
