//-----------------------------------------------------------------------------------------
// include
//-----------------------------------------------------------------------------------------
#include "ReflectionRaytracing.hlsli"

////////////////////////////////////////////////////////////////////////////////////////////
// static const variables
////////////////////////////////////////////////////////////////////////////////////////////

static const float pi = 3.1415926535897932384626433832795f;

////////////////////////////////////////////////////////////////////////////////////////////
// static const parameter variables
////////////////////////////////////////////////////////////////////////////////////////////

static const float3 kSunDir      = normalize(float3(0.0f, 1.0f, 10.0f)); //!< ���z�̕���
static const float kSunIntensity = 20.0f;                                //!< ���z�̋���

static const uint kNumSamples = 16; //!< �T���v�����O��

static const float kEarthRadius      = 6360e3; //!< �n���̔��a
static const float kAtmosphereRadius = 6420e3; //!< ��C�̔��a

static const float kG = 0.76f; //!< Henyey-Greenstein��g�W��

static const float kHr = 7994.0f; //!< Rayleigh��scale height
static const float kHm = 1200.0f; //!< Mie��scale height

static const float3 kBetaR = float3(5.8e-6, 13.5e-6, 33.1e-6); //!< Rayleigh�̎U���W��
static const float3 kBetaM = float3(21e-6, 21e-6, 21e-6);      //!< Mie�̎U���W��

////////////////////////////////////////////////////////////////////////////////////////////
// structures
////////////////////////////////////////////////////////////////////////////////////////////

struct Sphere {
	float3 center;
	float  radius;
};

struct Ray {
	float3 origin;
	float3 direction;
};

////////////////////////////////////////////////////////////////////////////////////////////
// methods
////////////////////////////////////////////////////////////////////////////////////////////

float RayleighPhaseFunction(float mu) {
	return 3.0f / (16.0f * pi) * (1.0f + mu * mu);
}

float HenyeyGreensteinPhaseFunction(float mu) {
	return 1.0f / (4.0f * pi) * (1.0f - kG * kG) / pow(1.0f + kG * kG - 2.0f * kG * mu, 1.5f);
}

bool IntersectSphere(Ray ray, Sphere sphere, out float distanceNear, out float distanceFar) {
	float3 rc     = sphere.center - ray.origin;
	float radius2 = sphere.radius * sphere.radius;
	float tca     = dot(rc, ray.direction);
	float d2      = dot(rc, rc) - tca * tca;
	
	if (d2 > radius2) {
		return false;
	}
	
	float thc = sqrt(radius2 - d2);
	
	distanceNear = tca - thc;
	distanceFar  = tca + thc;
	return true;
}

bool GetSunLight(Ray ray, Sphere sphere, out float opticalDepthR, out float opticalDepthM) {
	
	float distanceNear = 0.0f;
	float distanceFar  = 0.0f;
	
	if (!IntersectSphere(ray, sphere, distanceNear, distanceFar)) {
		return false;
	}
	
	float marchStep = distanceFar / kNumSamples;
	
	opticalDepthR = 0.0f;
	opticalDepthM = 0.0f;
	
	for (uint i = 0; i < kNumSamples; ++i) {
		
		float3 samplePoint = ray.origin + ray.direction * ((marchStep * i) + 0.5f * marchStep);
		float height = length(samplePoint) - kEarthRadius;
		
		if (height < 0.0f) {
			return false; //!< �n�\�ɓ��B
		}
		
		opticalDepthR += exp(-height / kHr) * marchStep;
		opticalDepthM += exp(-height / kHm) * marchStep;
	}
	
	return true;
}

float3 GetIncidentLight(Ray ray, Sphere atmosphere) {
	
	float distanceNear = 0.0f;
	float distanceFar  = 0.0f;

	if (!IntersectSphere(ray, atmosphere, distanceNear, distanceFar)) {
		return float3(1.0f, 0.0f, 0.0f);
	}
	
	//float marchStep = (distanceFar - distanceNear) / kNumSamples;
	float marchStep = distanceFar / kNumSamples;
	
	float mu = dot(ray.direction, kSunDir);
	
	float phaseR = RayleighPhaseFunction(mu);
	float phaseM = HenyeyGreensteinPhaseFunction(mu);
	
	float opticalDepthR = 0.0f;
	float opticalDepthM = 0.0f;
	
	float3 sumR = float3(0.0f, 0.0f, 0.0f);
	float3 sumM = float3(0.0f, 0.0f, 0.0f);
	
	for (uint i = 0; i < kNumSamples; ++i) {
		
		float3 samplePoint = ray.origin + ray.direction * ((marchStep * i) + 0.5f * marchStep);
		float height       = length(samplePoint) - kEarthRadius;
		
		float hr = exp(-height / kHr) * marchStep;
		float hm = exp(-height / kHm) * marchStep;
		
		opticalDepthR += hr;
		opticalDepthM += hm;
		
		Ray lightRay = (Ray)0;
		lightRay.origin    = samplePoint;
		lightRay.direction = kSunDir;
		
		float opticalDepthLightR = 0.0f;
		float opticalDepthLightM = 0.0f;
		
		bool isOverground = GetSunLight(lightRay, atmosphere, opticalDepthLightR, opticalDepthLightM);
		
		if (isOverground) {
			float3 tan
				= kBetaR * (opticalDepthR + opticalDepthLightR) + kBetaM * (opticalDepthM + opticalDepthLightM) * 1.1f;

			float3 attebuation = exp(-tan);
			
			sumR += attebuation * hr;
			sumM += attebuation * hm;
		}
	}
	
	return kSunIntensity * (phaseR * sumR * kBetaR + phaseM * sumM * kBetaM);
}

////////////////////////////////////////////////////////////////////////////////////////////
// main
////////////////////////////////////////////////////////////////////////////////////////////
[shader("miss")] //!< attmosphere miss shader
void mainMiss(inout Payload payload) {

	Sphere sphere = (Sphere)0;
	sphere.center = float3(0.0f, 0.0f, 0.0f);
	sphere.radius = kAtmosphereRadius;

	Ray ray = (Ray)0;
	ray.origin    = WorldRayOrigin();
	ray.origin.y += kEarthRadius;
	ray.direction = WorldRayDirection();

	float3 col = GetIncidentLight(ray, sphere);
	
	payload.color = saturate(col);
	
}
