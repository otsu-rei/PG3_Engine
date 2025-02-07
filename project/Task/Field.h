#pragma once

//-----------------------------------------------------------------------------------------
// include
//-----------------------------------------------------------------------------------------
//* engine
#include <Engine/!Render/Canvas/Layer/Layers/LSprite.h>
#include <Engine/!Render/Canvas/FCanvas.h>
#include <Engine/!Render/Canvas/Layer/LLayer.h>
#include <Engine/Editor/EditorComponent/AttributeComponent.h>

//* lib
#include <Lib/Geometry/Vector2.h>

//* c++
#include <array>
#include <bitset>
#include <thread>

////////////////////////////////////////////////////////////////////////////////////////////
// Field class
////////////////////////////////////////////////////////////////////////////////////////////
class Field
	: public AttributeComponent, public LLayer {
public:

	//=========================================================================================
	// public methods
	//=========================================================================================

	Field()  = default;
	~Field() { Term(); }

	void Init();

	void Load();

	void Term();

	void Render(const RenderContext& context) override;

	void AttributeImGui() override;

private:

	////////////////////////////////////////////////////////////////////////////////////////////
	// Block structure
	////////////////////////////////////////////////////////////////////////////////////////////
	struct Block {
		Vector2ui                index;
		bool                     isExist;
		std::unique_ptr<LSprite> block;
	};

private:

	//=========================================================================================
	// private variables
	//=========================================================================================

	static const uint32_t kBlockCount_ = 12;

	//* thread *//

	std::thread thread_;

	bool isTerm_ = false;
	bool isLoad_ = false;

	std::mutex              mutex_;
	std::condition_variable condition_;

	//* blocks *//

	std::array<std::array<Block, kBlockCount_>, kBlockCount_> blocks_;

	AssetObserver<AssetTexture> texture_;
	Vector2f                    size_;

	std::mutex state_;

	//=========================================================================================
	// private methods
	//=========================================================================================

	void LoadFile();

};
