//-----------------------------------------------------------------------------------------
// include
//-----------------------------------------------------------------------------------------
#include "PostProcess.hlsli"
#include "../../Camera.hlsli"

//=========================================================================================
// buffers
//=========================================================================================

RWTexture2D<float4> gInput : register(u0); //!< input texture
RWTexture2D<float4> gIntermediate : register(u1); //!< intermediate texture
RWTexture2D<float4> gOutput : register(u2); //!< output texture

SamplerState gSampler : register(s0);

ConstantBuffer<Camera> gCamera : register(b0);

struct Parameter {
	float radius;
	float maxRadius;
	float angleBias;
	float stregth;
	float filter;
	float2 scale;
};
ConstantBuffer<Parameter> gParameter : register(b1);


////////////////////////////////////////////////////////////////////////////////////////////
// variables
////////////////////////////////////////////////////////////////////////////////////////////

static const float pi_v = 3.14159265359f;
static const int kKernelRadius = 15;

////////////////////////////////////////////////////////////////////////////////////////////
// methods
////////////////////////////////////////////////////////////////////////////////////////////

float Gaussian2d(float2 diff, float sigma) {
	float a = 1.0f / (2.0f * pi_v * sigma * sigma);
	float b = exp(-(diff.x * diff.x + diff.y * diff.y) / (2.0f * sigma * sigma));
	return a * b;
}

////////////////////////////////////////////////////////////////////////////////////////////
// main
////////////////////////////////////////////////////////////////////////////////////////////
[numthreads(_NUM_THREADS_X, _NUM_THREADS_Y, 1)]
void main(uint3 dispatchThreadId : SV_DispatchThreadID) {

	uint2 index = dispatchThreadId.xy;
	uint2 size = gConfig.size;
	
	if (any(index >= size)) {
		return; //!< texture size over
	}
	
	float2 texcoord = float2(index) / float2(size);
	
	float4 input = gInput[index];
	float4 intermediate = gIntermediate[index];
	
	static const int2 kScale = int2(gParameter.scale);
	
	float sum = 0.0f;
	float weightSum = 0.0f;
	
	for (int x = -kScale.x; x <= kScale.x; ++x) {
		for (int y = -kScale.y; y <= kScale.y; ++y) {

			int2 ind = int2(index) + int2(x, y);
			
			float weight = Gaussian2d(float2(x, y), 2.0f);
			sum += weight * gIntermediate[ind].r;
			weightSum += weight;
		}
	}
	
	float ao = saturate(sum / weightSum);
	
	gOutput[index] = float4(input.rgb * ao, input.a);
	
}
