//-----------------------------------------------------------------------------------------
// include
//-----------------------------------------------------------------------------------------
#include "ReflectionHitgroupCommon.hlsli"

//=========================================================================================
// buffers
//=========================================================================================
//* local buffer

//!< t0, t1 ��ReflectionHitgroupCommon.hlsli�Œ�`�ς�
Texture2D<float4> gAlbedo  : register(t2);
SamplerState      gSampler : register(s0);

////////////////////////////////////////////////////////////////////////////////////////////
// main
////////////////////////////////////////////////////////////////////////////////////////////
[shader("closesthit")]
void mainGeometryClosesthit(inout Payload payload, Attribute attribute) {
	// HACK: recrusion������ⓧ���̏ꍇ��, anyhit�ŏ������s��
	//<- anyhit�̃I�[�o�[�w�b�h�̍l��
	
	Vertex vtx = GetVertex(attribute);

	float4 color = gAlbedo.SampleLevel(gSampler, vtx.texcoord, 0.0f);
	
	payload.color = color.rgb;
}

