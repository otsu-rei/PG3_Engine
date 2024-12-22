#pragma once

//-----------------------------------------------------------------------------------------
// include
//-----------------------------------------------------------------------------------------
//* scene
#include "IScene.h"
#include "BaseSceneFactory.h"

////////////////////////////////////////////////////////////////////////////////////////////
// SceneController class
////////////////////////////////////////////////////////////////////////////////////////////
class SceneController {
public:

	//=========================================================================================
	// public method
	//=========================================================================================

	SceneController()  = default;
	~SceneController() = default;

	void Init(const std::string& startSceneKey);

	void Term();

	//* scene factory option *//

	void RequestScene(const std::string& key);

	void SetSceneFactory(std::unique_ptr<const BaseSceneFactory>&& factory) { factory_ = std::move(factory); }

	void ActivateNextScene();

	//* scene option *//

	void InitScene();

	void UpdateScene();

	void DrawScene();

	void TermScene();

private:

	//=========================================================================================
	// private variables
	//=========================================================================================

	std::unique_ptr<IScene> scene_;
	std::unique_ptr<IScene> nextScene_ = nullptr;

	std::unique_ptr<const BaseSceneFactory> factory_;

	//=========================================================================================
	// private methods
	//=========================================================================================

};
