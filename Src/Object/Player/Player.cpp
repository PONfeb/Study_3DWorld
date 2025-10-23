
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

	// モデルの読み込み
	modelId_ = MV1LoadModel((Application::PATH_MODEL + "Player/Player.mv1").c_str());

	// モデルの角度
	angles_ = { 0.f, 0.f, 0.f };
	localAngles_ = { 0.f, AsoUtility::Deg2RadF(180.f), 0.f };

	MATRIX mat = MatrixUtility::Multiplication(localAngles_, angles_);

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

	InitDice();

}

void Player::Update(void)
{

	// モデルのY軸回転
	angles_.y += AsoUtility::Deg2RadF(0.1f);

	MATRIX mat = MatrixUtility::Multiplication(localAngles_, angles_);

	// 回転行列をモデルに反映
	MV1SetRotationMatrix(modelId_, mat);

	// アニメーションの更新
	animationController_->Update();

	// サイコロのZ軸回転
	diceAngles_.z += 0.01f;
	SyncDice();

}

void Player::Draw(void)
{

	// プレイヤーの描画
	MV1DrawModel(modelId_);

	// サイコロの描画
	MV1DrawModel(diceModelId_);

	DrawFormatString(
		0, 50, 0xffffff, 
		"キャラ角度　: (%.1f, %.1f, %.1f)",
		AsoUtility::Rad2DegF(angles_.x),
		AsoUtility::Rad2DegF(angles_.y),
		AsoUtility::Rad2DegF(angles_.z)
	);

}

void Player::Release(void)
{

	// モデルの解放
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

	// プレイヤーからの相対座標
	diceLocalPos_ = { 200.f, 100.f, 0.f };

	SyncDice();

}

void Player::SyncDice(void)
{

	// 行列の合成
	MATRIX selfMat = MatrixUtility::Multiplication(diceLocalAngles_, diceAngles_);

	// 親の回転行列
	MATRIX parentMat = MatrixUtility::GetMatrixRotateXYZ(angles_);

	// 行列の合成
	MATRIX mat = MatrixUtility::Multiplication(selfMat, parentMat);

	// 行列を使用してモデルの角度を設定
	MV1SetRotationMatrix(diceModelId_, mat);

	// サイコロのローカル座標を親の回転行列で回転
	VECTOR localRotPos = VTransform(diceLocalPos_, parentMat);

	// サイコロのワールド座標
	dicePos_ = VAdd(localRotPos, pos_);

	// サイコロの位置を設定
	MV1SetPosition(diceModelId_, dicePos_);

}
