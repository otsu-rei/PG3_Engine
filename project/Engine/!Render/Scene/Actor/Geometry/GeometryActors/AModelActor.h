#pragma once

//-----------------------------------------------------------------------------------------
// include
//-----------------------------------------------------------------------------------------
//* actor
#include "../AGeometryActor.h"

//* engine
#include <Engine/Asset/Model/AssetModel.h>
#include <Engine/Asset/Observer/AssetObserver.h>

////////////////////////////////////////////////////////////////////////////////////////////
// AModelActor class
////////////////////////////////////////////////////////////////////////////////////////////
class AModelActor
	: public AGeometryActor {
public:

	//=========================================================================================
	// public methods
	//=========================================================================================

	AModelActor()          = default;
	virtual ~AModelActor() = default;

	void Init();

	//* render *//

	virtual void RenderOpaque(const RendererContext& context) override;

	virtual void RenderTransparent(const RendererContext& context) override;

	//* raytracing option *//

	virtual void SetupToplevelAS(const SetupContext& context) override;

	//* setter *//

	void SetModel(const AssetObserver<AssetModel>& model) { model_ = model; }

	void SetRenderWait(bool isRenderWait) { isRenderWait_ = isRenderWait; }

protected:

	//=========================================================================================
	// protected variables
	//=========================================================================================

	//* asset *//

	AssetObserver<AssetModel> model_;

	//* option *//

	bool isRenderWait_ = true;

};
