
#include "TitleScene.h"

#include <cmath>

#include "../Common/Instance.h"

#include "../Common/Camera.h"
#include "../Object/Grid.h"

#include "../Object/Stage/Stage.h"
#include "../Object/Actor/Player/Player.h"

TitleScene::TitleScene(void) : SceneBase()
{

	grid_ = nullptr;

}

TitleScene::~TitleScene(void)
{
}

void TitleScene::Init(void)
{

	player_ = new Player();

	// カメラモード変更
	Camera* camera = SceneManager::GetInstance().GetCamera();
	camera->SetFollow(player_);
	camera->ChangeMode(Camera::MODE::FOLLOW);

	// グリッド初期化
	grid_ = new Grid();
	grid_->Init();

	stage_ = new Stage();
	stage_->Init();



}

void TitleScene::Update(void)
{

	// グリッド更新
	grid_->Update();

	// ステージ
	stage_->Update();

	// プレイヤー
	player_->Update();
}

void TitleScene::Draw(void)
{

	// グリッド描画
	grid_->Draw();

	// ステージ
	stage_->Draw();

	// プレイヤー
	player_->Draw();

}

void TitleScene::Release(void)
{

	// グリッド解放
	grid_->Release();
	delete grid_;

	// ステージ解放
	stage_->Release();
	delete stage_;

	// プレイヤー開放
	player_->Release();
	delete player_;

}
