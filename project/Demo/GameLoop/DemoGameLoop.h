#pragma once

//-----------------------------------------------------------------------------------------
// include
//-----------------------------------------------------------------------------------------
//* base
#include <Engine/System/Runtime/GameLoop/GameLoop.h>

//* demo
#include "../DemoModelRender.h"
#include "../Objects/ChessBoard.h"

////////////////////////////////////////////////////////////////////////////////////////////
// DemoGameLoop class
////////////////////////////////////////////////////////////////////////////////////////////
class DemoGameLoop
	: public GameLoop::Interface {
public:

	//=========================================================================================
	// public method
	//=========================================================================================

	void Init(GameLoop::Context* context) override;

	void Term() override;

private:

	//=========================================================================================
	// private variables
	//=========================================================================================

	std::unique_ptr<DemoModelRender> demo_;

	//=========================================================================================
	// private method
	//=========================================================================================

	void InitGame();

	void TermGame();

	void UpdateGame();

	void RenderGame();

};
