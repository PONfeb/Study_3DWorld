
#include "Player.h"

#include "../../../Application.h"

#include "../../../Common/Instance.h"
#include "../../../Common/Camera.h"

#include "../../../Utility/AsoUtility.h"
#include "../../../Utility/MatrixUtility.h"

#include "../../../Common/AnimationController.h"

Player::Player(void)
{
}

Player::~Player(void)
{
}

void Player::Update(void)
{

	ActorBase::Update();

	// �T�C�R����Z����]
	diceAngles_.z += 0.01f;
	SyncDice();

}

void Player::Draw(void)
{

	ActorBase::Draw();

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

	ActorBase::Release();

	MV1DeleteModel(diceModelId_);

}

void Player::InitLoad(void)
{	
	
	// ���f���̓ǂݍ���
	modelId_ = MV1LoadModel((Application::PATH_MODEL + "Player/Player.mv1").c_str());

}

void Player::InitTransform(void)
{

	// �傫��
	scales_ = { 1.f, 1.f, 1.f };

	// ���f���̊p�x
	angles_ = { 0.f, 0.f, 0.f };
	localAngles_ = { 0.f, AsoUtility::Deg2RadF(180.f), 0.f };

	// ���f���̈ʒu�ݒ�
	pos_ = AsoUtility::VECTOR_ZERO;

}

void Player::InitAnimation(void)
{

	// ���f���A�j���[�V�����̏�����
	animationController_ = new AnimationController(modelId_);

	// �A�j���[�V�����̒ǉ�
	animationController_->Add(static_cast<int>(ANIM_TYPE::IDLE), 30.f, Application::PATH_MODEL + "Player/Idle.mv1");
	animationController_->Add(static_cast<int>(ANIM_TYPE::WALK), 30.f, Application::PATH_MODEL + "Player/Walk.mv1");

	// �����A�j���[�V�����̍Đ�
	animationController_->Play(static_cast<int>(ANIM_TYPE::IDLE));

}

void Player::InitPost(void)
{

	InitDice();

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

void Player::Move(void)
{

	// �J�����̊p�x���擾����
	VECTOR cameraAngles = Ins::scene().GetCamera()->GetAngles();

	VECTOR dir = AsoUtility::VECTOR_ZERO;

	// �Q�[���p�b�h���ڑ�����Ă��鐔�ŏ����𕪂���
	if (GetJoypadNum() == 0)
	{
		// �L�[�{�[�h����
		if (Ins::input().IsNew(KEY_INPUT_W)) { dir = AsoUtility::DIR_F; }
		if (Ins::input().IsNew(KEY_INPUT_A)) { dir = AsoUtility::DIR_L; }
		if (Ins::input().IsNew(KEY_INPUT_S)) { dir = AsoUtility::DIR_B; }
		if (Ins::input().IsNew(KEY_INPUT_D)) { dir = AsoUtility::DIR_R; }
	}
	else
	{
		// �Q�[���p�b�h����
		// �ڑ�����Ă���Q�[���p�b�h1�̏����擾
		InputManager::JOYPAD_IN_STATE padState = Ins::input().GetJPadInputState(InputManager::JOYPAD_NO::PAD1);

		// �A�i���O�L�[�̓��͒l����������擾
		dir = Ins::input().GetDirectionXZAKey(padState.AKeyLX, padState.AKeyLY);
	}

	// WASD�ŃJ�������ړ�������
	const float movePow = 3.0f;
	
	if (!AsoUtility::EqualsVZero(dir))
	{
		// XYZ�̉�]�s��
		// XZ���ʈړ��ɂ���ꍇ�́AXZ�̉�]���l�����Ȃ��悤�ɂ���
		MATRIX mat = MGetIdent();
		//mat = MMult(mat, MGetRotX(cameraAngles.x));
		mat = MMult(mat, MGetRotY(cameraAngles.y));
		//mat = MMult(mat, MGetRotZ(cameraAngles.z));

		// ��]�s����g�p���āA�x�N�g������]������
		moveDir_ = VTransform(dir, mat);

		// �ړ���������p�x�ɕύX����
		//angles_.y = atan2f(moveDir.x, moveDir.z);

		// �����~�X�s�[�h�ňړ��ʂ�����āA���W�ɑ����Ĉړ�
		pos_ = VAdd(pos_, VScale(moveDir_, movePow));

		// �����A�j���[�V����
		animationController_->Play(static_cast<int>(ANIM_TYPE::WALK));
	}
	else
	{
		// �����A�j���[�V����
		animationController_->Play(static_cast<int>(ANIM_TYPE::IDLE));
	}
	
}
