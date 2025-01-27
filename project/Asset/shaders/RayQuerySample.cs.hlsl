//-----------------------------------------------------------------------------------------
// include
//-----------------------------------------------------------------------------------------
#include "../../Packages/shaders/Camera.hlsli"

//=========================================================================================
// buffers
//=========================================================================================

RaytracingAccelerationStructure gScene : register(t0);
RWTexture2D<float4> gOutput : register(u0);
ConstantBuffer<Camera> gCamera : register(b0);

////////////////////////////////////////////////////////////////////////////////////////////
// static variables
////////////////////////////////////////////////////////////////////////////////////////////

static const uint2 kImageSize = uint2(1280, 720);

////////////////////////////////////////////////////////////////////////////////////////////
// main
////////////////////////////////////////////////////////////////////////////////////////////
[numthreads(16, 16, 1)]
void main(uint3 dispatchThreadId : SV_DispatchThreadID) {

	uint2 index = dispatchThreadId.xy;
	uint2 size  = kImageSize;

	if (any(index >= size)) {
		return;
	}
	
	RayQuery<RAY_FLAG_NONE> q;
	
	float2 viewport = float2(index) / float2(size) * 2.0f - 1.0f;
	float3 target = mul(float4(viewport.x, -viewport.y, 1.0f, 1.0f), gCamera.projInv).xyz;
	float3 direction = mul(float4(target.xyz, 0.0f), gCamera.world).xyz;
	
	// ���C�̒�`
	RayDesc ray;
	ray.Origin = float3(0, 0, -5);
	ray.Direction = direction;
	ray.TMax = 10000.0;
	ray.TMin = 0.001;
	
	// ���C�g���[�V���O�̎��s
	q.TraceRayInline(
		gScene, // �A�N�Z�����[�V�����\��
		RAY_FLAG_NONE, // ���C�t���O
		0xFF, // �C���X�^���X�}�X�N
		ray // ���C�̐���
	);
	
	// ���ʂ̏���
	if (q.Proceed()) {
		gOutput[index] = float4(1, 0, 0, 1);
		
	} else {
		gOutput[index] = float4(0, 0, 0, 1);

	}
	
}
