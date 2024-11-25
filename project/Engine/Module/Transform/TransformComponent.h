#pragma once

//-----------------------------------------------------------------------------------------
// include
//-----------------------------------------------------------------------------------------
//* transform
#include "Transform.h"

//* engine
#include <Engine/System/DirectX/DxObject/DxDimensionBuffer.h>

//* lib
#include <Lib/Adapter/Json/IJsonSerializer.h>

//* c++
#include <memory>

////////////////////////////////////////////////////////////////////////////////////////////
// BaseTransformComponent class
////////////////////////////////////////////////////////////////////////////////////////////
class BaseTransformComponent {
public:

	//=========================================================================================
	// public methods
	//=========================================================================================

	BaseTransformComponent()  = default;
	~BaseTransformComponent() = default;

	void CreateBuffer();

	void Transfer();

	//* getter *//

	const D3D12_GPU_VIRTUAL_ADDRESS& GetGPUVirtualAddress() const;

	const Vector3f GetPosition() const;

	//* setter *//

	void SetParent(const BaseTransformComponent* component) { parent_ = component; }

	//=========================================================================================
	// public variables
	//=========================================================================================

	Matrix4x4 mat = Matrix4x4::Identity();

protected:

	//=========================================================================================
	// protected variables
	//=========================================================================================

	const BaseTransformComponent* parent_ = nullptr;

	std::unique_ptr<DxObject::DimensionBuffer<TransformationMatrix>> buffer_;

};

////////////////////////////////////////////////////////////////////////////////////////////
// TransformComponent class
////////////////////////////////////////////////////////////////////////////////////////////
class TransformComponent
	: public BaseTransformComponent, public IJsonSerializer {
public:

	//=========================================================================================
	// public methods
	//=========================================================================================

	TransformComponent()  = default;
	~TransformComponent() = default;

	void UpdateMatrix();

	void SetImGuiCommand();

	json OutputJson() override;

	void InputJson(const json& data) override;

	//=========================================================================================
	// public variables
	//=========================================================================================

	QuaternionTransform transform;

private:
};

