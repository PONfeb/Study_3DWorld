
#include "TitleScene.h"

#include <cmath>

#include "../Common/Instance.h"

#include "../Common/Camera.h"
#include "../Object/Grid.h"

#include "../Object/Stage/Stage.h"
#include "../Object/Player/Player.h"

TitleScene::TitleScene(void) : SceneBase()
{

	grid_ = nullptr;

}

TitleScene::~TitleScene(void)
{
}

void TitleScene::Init(void)
{

	// �J�������[�h�ύX
	Camera* camera = SceneManager::GetInstance().GetCamera();
	camera->ChangeMode(Camera::MODE::FREE);

	// �O���b�h������
	grid_ = new Grid();
	grid_->Init();

	stage_ = new Stage();
	stage_->Init();

	player_ = new Player();
	player_->Init();

}

void TitleScene::Update(void)
{

	// �O���b�h�X�V
	grid_->Update();

	// �X�e�[�W
	stage_->Update();

	// �v���C���[
	player_->Update();
}

void TitleScene::Draw(void)
{

	// �O���b�h�`��
	grid_->Draw();

	// �X�e�[�W
	stage_->Draw();

	// �v���C���[
	player_->Draw();

}

void TitleScene::Release(void)
{

	// �O���b�h���
	grid_->Release();
	delete grid_;

	// �X�e�[�W���
	stage_->Release();
	delete stage_;

	// �v���C���[�J��
	player_->Release();
	delete player_;

}
