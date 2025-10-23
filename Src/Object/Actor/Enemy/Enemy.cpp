
#include "Enemy.h"

Enemy::Enemy(void)
{
}

Enemy::~Enemy(void)
{
}

void Enemy::InitLoad(void)
{

	// ���f���̓ǂݍ���
	modelId_ = MV1LoadModel((Application::PATH_MODEL + "Player/Player.mv1").c_str());

}

void Enemy::InitTransform(void)
{

	// �傫��
	scales_ = { 1.f, 1.f, 1.f };

	// �p�x
	angles_ = { 0.f, AsoUtility::Deg2RadF(45.f), 0.f };
	localAngles_ = { 0.f, AsoUtility::Deg2RadF(180.f), 0.f };

	// ���W
	pos_ = { 200.f, 0.f, 150.f };
}

void Enemy::InitAnimation(void)
{

	// ���f���A�j���[�V�����̏�����
	animationController_ = new AnimationController(modelId_);

	// �A�j���[�V�����̒ǉ�
	animationController_->Add(static_cast<int>(ANIM_TYPE::IDLE), 30.f, Application::PATH_MODEL + "Player/Idle.mv1");
	animationController_->Add(static_cast<int>(ANIM_TYPE::WALK), 30.f, Application::PATH_MODEL + "Player/Walk.mv1");

	// �����A�j���[�V�����̍Đ�
	animationController_->Play(static_cast<int>(ANIM_TYPE::IDLE));

}

void Enemy::InitPost(void)
{
}
