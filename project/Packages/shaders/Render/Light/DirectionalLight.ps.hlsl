//-----------------------------------------------------------------------------------------
// include
//-----------------------------------------------------------------------------------------
#include "LightRender.hlsli"

//=========================================================================================
// buffer
//=========================================================================================

struct DirectionalLight {
	float4 color_intencity; //!< rgb : color, a : intensity
	float3 direction;
};
ConstantBuffer<DirectionalLight> gDirectionalLight : register(b0);

////////////////////////////////////////////////////////////////////////////////////////////
// main
////////////////////////////////////////////////////////////////////////////////////////////
PSOutput main(PSInput input) {

	PSOutput output = (PSOutput)0;
	
	// Object�����݂��Ȃ��ꍇ�͉������Ȃ�
	if (GetDepth(input.position.xy) == 1.0f) {
		discard;
	}
	
	//* Deferred Pass���̎擾
	Surface surface;
	surface.GetSurface(input.position.xy);
	
	//* Light�̏����擾
	float3 l       = -gDirectionalLight.direction;                                                //!< surface����light�ւ̕����x�N�g��
	float3 c_light = gDirectionalLight.color_intencity.rgb * gDirectionalLight.color_intencity.a; //!< light��color
	
	//* �v�Z
	float diffuse = CalculateDiffuseLambert(surface.normal, l);
	
	//* �o��
	output.color.rgb = diffuse * c_light * surface.albedo;
	// func_unlit() = float3(0.0f, 0.0f, 0.0f), func_lit() = c_surface
	
	output.color.a = 1.0f;
	
	return output;
}
