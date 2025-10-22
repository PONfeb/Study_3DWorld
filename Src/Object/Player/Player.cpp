
#include "Player.h"

#include "../../Application.h"
#include "../../Utility/AsoUtility.h"

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

	// ���f���̉�]�s��
	MATRIX mat = MGetIdent();
	mat = MMult(mat, MGetRotX(angles_.x));
	mat = MMult(mat, MGetRotY(angles_.y));
	mat = MMult(mat, MGetRotZ(angles_.z));

	// ���f���̃��[�J����]�s��
	MATRIX localMat = MGetIdent();
	localMat = MMult(localMat, MGetRotX(localAngles_.x));
	localMat = MMult(localMat, MGetRotY(localAngles_.y));
	localMat = MMult(localMat, MGetRotZ(localAngles_.z));

	// �s��̍���(�q, �e�Ǝw�肷��Ɛe�ˎq�̏��ɓK�p�����)
	mat = MMult(localMat, mat);

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
}

void Player::Update(void)
{

	// �A�j���[�V�����̍X�V
	animationController_->Update();

}

void Player::Draw(void)
{

	// �v���C���[�̕`��
	MV1DrawModel(modelId_);

}

void Player::Release(void)
{

	// ���f���̉��
	MV1DeleteModel(modelId_);
	delete animationController_;

}
