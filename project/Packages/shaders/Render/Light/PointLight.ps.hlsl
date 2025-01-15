//-----------------------------------------------------------------------------------------
// include
//-----------------------------------------------------------------------------------------
#include "LightRender.hlsli"

//=========================================================================================
// buffers
//=========================================================================================

struct PointLight {
	float4 color_intensity; //!< rgb : color, a : intensity
	float radius;
	float decay;
};
ConstantBuffer<PointLight> gPointLight : register(b0);

////////////////////////////////////////////////////////////////////////////////////////////
// main
////////////////////////////////////////////////////////////////////////////////////////////
PSOutput main(PSInput input) {
	
	PSOutput output = (PSOutput)0;

	//* Deferred Pass���̎擾
	float2 uv = input.position.xy / gInfo.size;
	
	float3 worldPos = GetPosition(uv);
	float3 normal   = GetNormal(uv);
	
	//* Light�̏����擾
	float3 center = gTransform[input.instanceId].GetPosition(); //!< Light�̒��S���W

	//* Light�P�x�v�Z
	float3 l = normalize(center - worldPos); //!< Light�̕����x�N�g��
	float d  = length(center - worldPos);    //!< Light�̋���
	
	float factor = saturate(1.0 - d / gPointLight.radius);
	
	//* �o�͏��̏�������
	output.color.rgb = gPointLight.color_intensity.rgb;
	output.color.a   = gPointLight.color_intensity.a * factor;
	
	if (output.color.a >= 0.0f) {
		discard;
	}
	
	return output;
}
