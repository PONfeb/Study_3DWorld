
#include "Player.h"

#include "../../Application.h"
#include "../../Utility/AsoUtility.h"
#include "../../Utility/MatrixUtility.h"

#include "../../Common/AnimationController.h"

Player::Player(void)
{
}

Player::~Player(void)
{
}

void Player::Init(void)
{

	// ���f���̓ǂݍ���
	modelId_ = MV1LoadModel((Application::PATH_MODEL + "Player/Player.mv1").c_str());

	// ���f���̊p�x
	angles_ = { 0.f, 0.f, 0.f };
	localAngles_ = { 0.f, AsoUtility::Deg2RadF(180.f), 0.f };

	MATRIX mat = MatrixUtility::Multiplication(localAngles_, angles_);

	// ��]�s������f���ɔ��f
	MV1SetRotationMatrix(modelId_, mat);

	// ���f���̈ʒu�ݒ�
	pos_ = AsoUtility::VECTOR_ZERO;
	MV1SetPosition(modelId_, pos_);

	// ���f���A�j���[�V�����̏�����
	animationController_ = new AnimationController(modelId_);

	// �A�j���[�V�����̒ǉ�
	animationController_->Add(static_cast<int>(ANIM_TYPE::IDLE), 30.f, Application::PATH_MODEL + "Player/Idle.mv1");
	animationController_->Add(static_cast<int>(ANIM_TYPE::WALK), 30.f, Application::PATH_MODEL + "Player/Walk.mv1");

	// �����A�j���[�V�����̍Đ�
	animationController_->Play(static_cast<int>(ANIM_TYPE::IDLE));

	InitDice();

}

void Player::Update(void)
{

	// ���f����Y����]
	angles_.y += AsoUtility::Deg2RadF(0.1f);

	MATRIX mat = MatrixUtility::Multiplication(localAngles_, angles_);

	// ��]�s������f���ɔ��f
	MV1SetRotationMatrix(modelId_, mat);

	// �A�j���[�V�����̍X�V
	animationController_->Update();

	// �T�C�R����Z����]
	diceAngles_.z += 0.01f;
	SyncDice();

}

void Player::Draw(void)
{

	// �v���C���[�̕`��
	MV1DrawModel(modelId_);

	// �T�C�R���̕`��
	MV1DrawModel(diceModelId_);

	DrawFormatString(
		0, 50, 0xffffff, 
		"�L�����p�x�@: (%.1f, %.1f, %.1f)",
		AsoUtility::Rad2DegF(angles_.x),
		AsoUtility::Rad2DegF(angles_.y),
		AsoUtility::Rad2DegF(angles_.z)
	);

}

void Player::Release(void)
{

	// ���f���̉��
	MV1DeleteModel(modelId_);
	delete animationController_;

	MV1DeleteModel(diceModelId_);

}

void Player::InitDice(void)
{

	diceModelId_ = MV1LoadModel((Application::PATH_MODEL + "Dice.mv1").c_str());

	diceScales_ = { 0.1f, 0.1f, 0.1f };
	MV1SetScale(diceModelId_, diceScales_);

	diceAngles_ = { AsoUtility::VECTOR_ZERO };
	diceLocalAngles_ = { AsoUtility::VECTOR_ZERO };

	// �v���C���[����̑��΍��W
	diceLocalPos_ = { 200.f, 100.f, 0.f };

	SyncDice();

}

void Player::SyncDice(void)
{

	// �s��̍���
	MATRIX selfMat = MatrixUtility::Multiplication(diceLocalAngles_, diceAngles_);

	// �e�̉�]�s��
	MATRIX parentMat = MatrixUtility::GetMatrixRotateXYZ(angles_);

	// �s��̍���
	MATRIX mat = MatrixUtility::Multiplication(selfMat, parentMat);

	// �s����g�p���ă��f���̊p�x��ݒ�
	MV1SetRotationMatrix(diceModelId_, mat);

	// �T�C�R���̃��[�J�����W��e�̉�]�s��ŉ�]
	VECTOR localRotPos = VTransform(diceLocalPos_, parentMat);

	// �T�C�R���̃��[���h���W
	dicePos_ = VAdd(localRotPos, pos_);

	// �T�C�R���̈ʒu��ݒ�
	MV1SetPosition(diceModelId_, dicePos_);

}
