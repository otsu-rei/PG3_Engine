#pragma once

//-----------------------------------------------------------------------------------------
// include
//-----------------------------------------------------------------------------------------
//* framework
#include "IFramework.h"

//* engine
#include <Engine/System/Window/GameWindow.h>
#include <Engine/System/Runtime/Scene/SceneController.h>

////////////////////////////////////////////////////////////////////////////////////////////
// GameFramework class
////////////////////////////////////////////////////////////////////////////////////////////
class GameFramework
	: public IFramework {
public:

	//=========================================================================================
	// public method
	//=========================================================================================

	void Run() override;

private:

	//=========================================================================================
	// private variables
	//=========================================================================================

	std::shared_ptr<GameWindow> mainWindow_;

	std::unique_ptr<SceneController> controller_;

	//=========================================================================================
	// private method
	//=========================================================================================

	void SystemInit();
	void Init();

	void SystemUpdate();
	void Update();

	void Draw();
	void SystemDraw();

	void SystemTerm();
	void Term();

	void BeginFrame();

	void EndFrame();

};
