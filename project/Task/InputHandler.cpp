#include "InputHandler.h"

//-----------------------------------------------------------------------------------------
// include
//-----------------------------------------------------------------------------------------
//* engine
#include <Engine/System/SxavengerSystem.h>
#include <Engine/Console/Console.h>

////////////////////////////////////////////////////////////////////////////////////////////
// InputHandler class methods
////////////////////////////////////////////////////////////////////////////////////////////

void InputHandler::Init() {
	//!< commandの設定
	commandKeyA_ = std::make_unique<MoveLeftCommand>();
	commandKeyD_ = std::make_unique<MoveRightCommand>();
}

ICommand* InputHandler::HandleInput() {
	auto keyboardInput = SxavengerSystem::GetInput()->GetKeyboardInput();

	//!< 対応したkeybindのcommandを返す
	
	if (keyboardInput->IsPress(KeyId::KEY_D)) {
		sConsole->Log("D key is pressed", Color4f{ 0.0f, 1.0f, 0.0f, 1.0f });
		return commandKeyD_.get();
	}

	if (keyboardInput->IsPress(KeyId::KEY_A)) {
		sConsole->Log("A key is pressed", Color4f{ 0.0f, 1.0f, 0.0f, 1.0f });
		return commandKeyA_.get();
	}

	//!< 対応したkeybindがない場合はnullptrを返す
	return nullptr;
}
