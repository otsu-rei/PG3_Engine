//-----------------------------------------------------------------------------------------
// include
//-----------------------------------------------------------------------------------------
//* engine
#include <Engine/System/SxavengerSystem.h>
#include <Engine/System/Runtime/GameLoop/GameLoop.h>

//* loops
#include <Engine/GameLoop/EngineGameLoop.h>
#include <Engine/GameLoop/ConsoleGameLoop.h>

////////////////////////////////////////////////////////////////////////////////////////////
// メイン関数
////////////////////////////////////////////////////////////////////////////////////////////
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	std::unique_ptr<GameLoop::Collection> collection = std::make_unique<GameLoop::Collection>();
	collection->Push<EngineGameLoop>();
	collection->Push<ConsoleGameLoop>();

	SxavengerSystem::RunFramework(std::move(collection));

	return 0;
}
