
#include "ActorBase.h"

#include "../../../Utility/MatrixUtility.h"


ActorBase::ActorBase(void)
{
}

ActorBase::~ActorBase(void)
{
}

void ActorBase::Init(void)
{

	// ���\�[�X���[�h
	InitLoad();

	// Transform������
	InitTransform();

	// �傫���A��]�A���W�̃��f���ݒ�
	InitTransformPost();

	// �A�j���[�V�����̏�����
	InitAnimation();

	// ��������̌ʏ���
	InitPost();

}

void ActorBase::Update(void)
{

	// ���f����Y����]
	//angles_.y += 0.01f;
	// �v���C���[�̒x����]����
	DelayRotate();

	// �s��̍���(�q, �e�Ǝw�肷��Ɛe�ˎq�̏��ɓK�p�����)
	MATRIX mat = MatrixUtility::Multiplication(localAngles_, angles_);

	// ��]�s������f���ɔ��f
	MV1SetRotationMatrix(modelId_, mat);

	// �v���C���[�̈ړ�����
	Move();
	MV1SetPosition(modelId_, pos_);

	// �A�j���[�V�����̍X�V
	animationController_->Update();

}

void ActorBase::Draw(void)
{
	MV1DrawModel(modelId_);
}

void ActorBase::Release(void)
{
	MV1DeleteModel(modelId_);
	delete animationController_;
}

const VECTOR& ActorBase::GetPos(void) const
{
	return pos_;
}

void ActorBase::InitTransformPost(void)
{

	// �傫�������f���ɔ��f
	MV1SetScale(modelId_, scales_);

	// �p�x��������ɕϊ�����
	moveDir_ = { sinf(angles_.y), 0.0f, cosf(angles_.y) };
	//preInputDir_ = moveDir_;

	// �s��̍���(�q, �e�Ǝw�肷��Ɛe�ˎq�̏��ɓK�p�����)
	MATRIX mat = MatrixUtility::Multiplication(localAngles_, angles_);

	// ��]�s������f���ɔ��f
	MV1SetRotationMatrix(modelId_, mat);

	// ���W�����f���ɔ��f
	MV1SetPosition(modelId_, pos_);

}

void ActorBase::Move(void)
{
}

void ActorBase::DelayRotate(void)
{

	// �ړ���������p�x�ɕϊ�����
	float goal = atan2f(moveDir_.x, moveDir_.z);

	// ��ɍŒZ�o�H�ŕ��
	angles_.y = AsoUtility::LerpAngle(angles_.y, goal, 0.2f);

}
