#include "GameSceneFactory.h"

//-----------------------------------------------------------------------------------------
// include
//-----------------------------------------------------------------------------------------
//* scene
#include "SceneTitle.h"
#include "SceneGame.h"
#include "SceneClear.h"

////////////////////////////////////////////////////////////////////////////////////////////
// GameSceneFactory class methods
////////////////////////////////////////////////////////////////////////////////////////////

void GameSceneFactory::Init() {
	Register<SceneTitle>("Title");
	Register<SceneGame>("Game");
	Register<SceneClear>("Clear");
}
