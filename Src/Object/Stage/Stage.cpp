
#include "Stage.h"

#include " ../../../../Application.h"

Stage::Stage(void)
{

	modelId_ = -1;
	pos_ = { 0.f, 0.f, 0.f };

}

Stage::~Stage(void)
{
}

void Stage::Init(void)
{

	// ステージのモデル読み込み
	modelId_ = MV1LoadModel((Application::PATH_MODEL + "Stage.mv1").c_str());

	// モデルの位置
	pos_ = { 0.f, 80.f, 0.f };

	// モデルの位置を設定
	MV1SetPosition(modelId_, pos_);

}

void Stage::Update(void)
{
}

void Stage::Draw(void)
{

	// ステージモデル描画
	MV1DrawModel(modelId_);

}

void Stage::Release(void)
{

	MV1DeleteModel(modelId_);

}
