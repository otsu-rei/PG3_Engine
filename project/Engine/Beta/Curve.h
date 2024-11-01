#pragma once

//-----------------------------------------------------------------------------------------
// include
//-----------------------------------------------------------------------------------------
//* lib
#include <Lib/Geometry/Vector2.h>

//* c++
#include <vector>
#include <string>

////////////////////////////////////////////////////////////////////////////////////////////
// Curve class
////////////////////////////////////////////////////////////////////////////////////////////
class Curve { // todo: template化
public:

	//=========================================================================================
	// public methds
	//=========================================================================================

	Curve()  = default;
	~Curve() = default;

	void TEST_Create();

	float GetOutput(float inputT);

	void SetImGuiCommand();

	void OutputJson(const std::string& filename);

private:

	////////////////////////////////////////////////////////////////////////////////////////////
	// CurvePoint structure
	////////////////////////////////////////////////////////////////////////////////////////////
	struct CurvePoint {
		float input, output;
	};

	//=========================================================================================
	// private variables
	//=========================================================================================

	std::vector<CurvePoint> points_;
	//* pointはinputTで昇順sortされる.

	static float CatmullRomInterpolation(float p0, float p1, float p2, float p3, float t);

};