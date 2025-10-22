
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

	// モデルの読み込み
	modelId_ = MV1LoadModel((Application::PATH_MODEL + "Player/Player.mv1").c_str());

	// モデルの角度
	angles_ = { 0.f, 0.f, 0.f };
	localAngles_ = { 0.f, AsoUtility::Deg2RadF(180.f), 0.f };

	// モデルの回転行列
	MATRIX mat = MGetIdent();
	mat = MMult(mat, MGetRotX(angles_.x));
	mat = MMult(mat, MGetRotY(angles_.y));
	mat = MMult(mat, MGetRotZ(angles_.z));

	// モデルのローカル回転行列
	MATRIX localMat = MGetIdent();
	localMat = MMult(localMat, MGetRotX(localAngles_.x));
	localMat = MMult(localMat, MGetRotY(localAngles_.y));
	localMat = MMult(localMat, MGetRotZ(localAngles_.z));

	// 行列の合成(子, 親と指定すると親⇒子の順に適用される)
	mat = MMult(localMat, mat);

	// 回転行列をモデルに反映
	MV1SetRotationMatrix(modelId_, mat);

	// モデルの位置設定
	pos_ = AsoUtility::VECTOR_ZERO;
	MV1SetPosition(modelId_, pos_);

	// モデルアニメーションの初期化
	animationController_ = new AnimationController(modelId_);

	// アニメーションの追加
	animationController_->Add(static_cast<int>(ANIM_TYPE::IDLE), 30.f, Application::PATH_MODEL + "Player/Idle.mv1");
	animationController_->Add(static_cast<int>(ANIM_TYPE::WALK), 30.f, Application::PATH_MODEL + "Player/Walk.mv1");

	// 初期アニメーションの再生
	animationController_->Play(static_cast<int>(ANIM_TYPE::IDLE));
}

void Player::Update(void)
{

	// アニメーションの更新
	animationController_->Update();

}

void Player::Draw(void)
{

	// プレイヤーの描画
	MV1DrawModel(modelId_);

}

void Player::Release(void)
{

	// モデルの解放
	MV1DeleteModel(modelId_);
	delete animationController_;

}
