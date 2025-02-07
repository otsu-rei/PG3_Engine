#include "Field.h"

//-----------------------------------------------------------------------------------------
// include
//-----------------------------------------------------------------------------------------
//* engine
#include <Engine/Asset/SxavengerAsset.h>

//* c++
#include <fstream>

////////////////////////////////////////////////////////////////////////////////////////////
// Field class methods
////////////////////////////////////////////////////////////////////////////////////////////

void Field::Init() {

	AttributeComponent::SetName("field");

	texture_ = SxavengerAsset::TryImport<AssetTexture>("asset/textures/tile_white.png");
	size_    = { 32.0f, 32.0f };

	for (uint32_t row = 0; row < kBlockCount_; ++row) {
		for (uint32_t col = 0; col < kBlockCount_; ++col) {
			blocks_[row][col].index   = { col, row };
			blocks_[row][col].isExist = false;

			blocks_[row][col].block = std::make_unique<LSprite>();
			blocks_[row][col].block->Init();
			blocks_[row][col].block->SetTexture(texture_);
			blocks_[row][col].block->SetPosition({ col * size_.x, row * size_.y });
			blocks_[row][col].block->SetSize(size_);
		}
	}

	thread_ = std::thread([this]() {
		while (true) {
			{
				std::unique_lock<std::mutex> lock(mutex_);
				condition_.wait(lock, [this]() { return isTerm_ || isLoad_; });
			}

			if (isTerm_) {
				break;
			}

			LoadFile();
		}
	});

	Load();
}

void Field::Load() {
	isLoad_ = true;
	condition_.notify_one();
}

void Field::Term() {
	isTerm_ = true;
	condition_.notify_all();

	thread_.join();
}

void Field::Render(const RenderContext& context) {
	std::unique_lock<std::mutex> lock(state_); //!< 描画のためlock

	for (uint32_t row = 0; row < kBlockCount_; ++row) {
		for (uint32_t col = 0; col < kBlockCount_; ++col) {
			if (!blocks_[row][col].block->CheckVisibility()) {
				continue;
			}

			blocks_[row][col].block->Render(context);
		}
	}
}

void Field::AttributeImGui() {
	if (ImGui::Button("load")) {
		Load();
	}
}

void Field::LoadFile() {
	std::unique_lock<std::mutex> lock(state_); //!< file読み取りのためlock

	std::filesystem::path filepath = "asset/field.csv";

	std::ifstream file(filepath);

	if (!file.is_open()) {
		return;
	}

	{
		std::string line;
		uint32_t    row = 0;

		while (std::getline(file, line) && row < kBlockCount_) {
			std::stringstream ss(line);
			std::string       cell;

			uint32_t col = 0;

			std::bitset<kBlockCount_> bits;

			while (std::getline(ss, cell, ',') && col < kBlockCount_) {
				blocks_[row][col].isExist = (std::stoi(cell) == 1);

				bits[col] = blocks_[row][col].isExist;
				col++;
			}

			row++;
		}
	}


	for (uint32_t row = 0; row < kBlockCount_; ++row) {
		for (uint32_t col = 0; col < kBlockCount_; ++col) {
			blocks_[row][col].block->SetActive(blocks_[row][col].isExist);
		}
	}

	isLoad_ = false;
}
