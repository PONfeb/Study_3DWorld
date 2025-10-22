
#include "Camera.h"

#include "../Utility/AsoUtility.h"
#include "../Common/Instance.h"

Camera::Camera(void)
{
	// DxLib�̏����ݒ�ł́A
	// �J�����̈ʒu�� x = 320.0f, y = 240.0f, z = (��ʂ̃T�C�Y�ɂ���ĕω�)�A
	// �����_�̈ʒu�� x = 320.0f, y = 240.0f, z = 1.0f
	// �J�����̏������ x = 0.0f, y = 1.0f, z = 0.0f
	// �E��ʒu����Z���̃v���X����������悤�ȃJ����
}

Camera::~Camera(void)
{
}

void Camera::Init(void)
{

	// �J�����̏������W
	pos_ = DEFAULT_POS;

	// �J�����̏������W
	angles_ = DEFAULT_ANGLES;

}

void Camera::Update(void)
{
}

void Camera::SetBeforeDraw(void)
{

	// �N���b�v������ݒ肷��(SetDrawScreen�Ń��Z�b�g�����)
	SetCameraNearFar(VIEW_NEAR, VIEW_FAR);
	switch (mode_)
	{
	case Camera::MODE::FIXED_POINT:
		SetBeforeDrawFixedPoint();
		break;
	case Camera::MODE::FREE:
		SetBeforeDrawFree();
		break;
	}

	// �J�����̐ݒ�(�ʒu�Ɗp�x�ɂ�鐧��)
	SetCameraPositionAndAngle(pos_, angles_.x, angles_.y, angles_.z);

}


void Camera::SetBeforeDrawFixedPoint(void)
{
	// �����Ȃ�
}

void Camera::SetBeforeDrawFree(void)
{

	//// ���L�[�ŃJ�����̊p�x��ς���
	//float rotPow = 1.f * DX_PI_F / 180.f;
	//if (Ins::input().IsNew(KEY_INPUT_DOWN))  { angles_.x += rotPow; }
	//if (Ins::input().IsNew(KEY_INPUT_UP))    { angles_.x -= rotPow; }
	//if (Ins::input().IsNew(KEY_INPUT_RIGHT)) { angles_.y += rotPow; }
	//if (Ins::input().IsNew(KEY_INPUT_LEFT))  { angles_.y -= rotPow; }

	//// WASD�ŃJ�������ړ�������
	//float movePow = 3.f;
	//if (Ins::input().IsNew(KEY_INPUT_W)) { pos_.z += movePow; }
	//if (Ins::input().IsNew(KEY_INPUT_A)) { pos_.x -= movePow; }
	//if (Ins::input().IsNew(KEY_INPUT_S)) { pos_.z -= movePow; }
	//if (Ins::input().IsNew(KEY_INPUT_D)) { pos_.x += movePow; }
	//if (Ins::input().IsNew(KEY_INPUT_Q)) { pos_.y += movePow; }
	//if (Ins::input().IsNew(KEY_INPUT_E)) { pos_.y -= movePow; }

	MoveXYZDirection();

}

void Camera::DrawDebug(void)
{

	DrawFormatString(0, 10, 0xffffff, "�J�������W: (%.1f, %.1f, %.1f)", pos_.x, pos_.y, pos_.z);  

	DrawFormatString(0, 30, 0xffffff, "�J�����p�x: (%.1f, %.1f, %.1f)", AsoUtility::Rad2DegF(angles_.x), AsoUtility::Rad2DegF(angles_.y), AsoUtility::Rad2DegF(angles_.z));  

}


void Camera::Release(void)
{
}

const VECTOR& Camera::GetPos(void) const
{
	return pos_;
}

const VECTOR& Camera::GetAngles(void) const
{
	return angles_;
}

void Camera::ChangeMode(MODE mode)
{

	// �J�������[�h�̕ύX
	mode_ = mode;

	// �ύX���̏���������
	switch (mode_)
	{
	case Camera::MODE::FIXED_POINT:
		break;
	case Camera::MODE::FREE:
		break;
	}

}

void Camera::MoveXYZDirection(void)
{

	auto& ins = InputManager::GetInstance();

	// ���L�[�ŃJ�����̊p�x��ς���
	float rotPow = 1.0f * DX_PI_F / 180.0f;
	if (ins.IsNew(KEY_INPUT_DOWN)) { angles_.x += rotPow; }
	if (ins.IsNew(KEY_INPUT_UP)) { angles_.x -= rotPow; }
	if (ins.IsNew(KEY_INPUT_RIGHT)) { angles_.y += rotPow; }
	if (ins.IsNew(KEY_INPUT_LEFT)) { angles_.y -= rotPow; }

	// WASD�ŃJ�������ړ�������
	const float movePow = 3.0f;

	VECTOR dir = AsoUtility::VECTOR_ZERO;

	if (ins.IsNew(KEY_INPUT_W)) { dir = { 0.0f, 0.0f, 1.0f }; }
	if (ins.IsNew(KEY_INPUT_A)) { dir = { -1.0f, 0.0f, 0.0f }; }
	if (ins.IsNew(KEY_INPUT_S)) { dir = { 0.0f, 0.0f, -1.0f }; }
	if (ins.IsNew(KEY_INPUT_D)) { dir = { 1.0f, 0.0f, 0.0f }; }

	if (!AsoUtility::EqualsVZero(dir))
	{
		// XYZ�̉�]�s��
		// XZ���ʈړ��ɂ���ꍇ�́AXZ�̉�]���l�����Ȃ��悤�ɂ���
		MATRIX mat = MGetIdent();
		mat = MMult(mat, MGetRotX(angles_.x));
		mat = MMult(mat, MGetRotY(angles_.y));
		//mat = MMult(mat, MGetRotZ(angles_.z));
		
		// ��]�s����g�p���āA�x�N�g������]������
		VECTOR moveDir = VTransform(dir, mat);

		// �����~�X�s�[�h�ňړ��ʂ�����āA���W�ɑ����Ĉړ�
		pos_ = VAdd(pos_, VScale(moveDir, movePow));
	}

}
