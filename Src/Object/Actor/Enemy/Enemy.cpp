
#include "Enemy.h"

Enemy::Enemy(void)
{
}

Enemy::~Enemy(void)
{
}

void Enemy::InitLoad(void)
{

	// モデルの読み込み
	modelId_ = MV1LoadModel((Application::PATH_MODEL + "Player/Player.mv1").c_str());

}

void Enemy::InitTransform(void)
{

	// 大きさ
	scales_ = { 1.f, 1.f, 1.f };

	// 角度
	angles_ = { 0.f, AsoUtility::Deg2RadF(45.f), 0.f };
	localAngles_ = { 0.f, AsoUtility::Deg2RadF(180.f), 0.f };

	// 座標
	pos_ = { 200.f, 0.f, 150.f };
}

void Enemy::InitAnimation(void)
{

	// モデルアニメーションの初期化
	animationController_ = new AnimationController(modelId_);

	// アニメーションの追加
	animationController_->Add(static_cast<int>(ANIM_TYPE::IDLE), 30.f, Application::PATH_MODEL + "Player/Idle.mv1");
	animationController_->Add(static_cast<int>(ANIM_TYPE::WALK), 30.f, Application::PATH_MODEL + "Player/Walk.mv1");

	// 初期アニメーションの再生
	animationController_->Play(static_cast<int>(ANIM_TYPE::IDLE));

}

void Enemy::InitPost(void)
{
}
