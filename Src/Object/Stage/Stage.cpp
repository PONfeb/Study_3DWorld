
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

	// �X�e�[�W�̃��f���ǂݍ���
	modelId_ = MV1LoadModel((Application::PATH_MODEL + "Stage.mv1").c_str());

	// ���f���̈ʒu
	pos_ = { 0.f, 80.f, 0.f };

	// ���f���̈ʒu��ݒ�
	MV1SetPosition(modelId_, pos_);

}

void Stage::Update(void)
{
}

void Stage::Draw(void)
{

	// �X�e�[�W���f���`��
	MV1DrawModel(modelId_);

}

void Stage::Release(void)
{

	MV1DeleteModel(modelId_);

}
