
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

	// サイコロのZ軸回転
	diceAngles_.z += 0.01f;
	SyncDice();

}

void Player::Draw(void)
{

	ActorBase::Draw();

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

	ActorBase::Release();

	MV1DeleteModel(diceModelId_);

}

void Player::InitLoad(void)
{	
	
	// モデルの読み込み
	modelId_ = MV1LoadModel((Application::PATH_MODEL + "Player/Player.mv1").c_str());

}

void Player::InitTransform(void)
{

	// 大きさ
	scales_ = { 1.f, 1.f, 1.f };

	// モデルの角度
	angles_ = { 0.f, 0.f, 0.f };
	localAngles_ = { 0.f, AsoUtility::Deg2RadF(180.f), 0.f };

	// モデルの位置設定
	pos_ = AsoUtility::VECTOR_ZERO;

}

void Player::InitAnimation(void)
{

	// モデルアニメーションの初期化
	animationController_ = new AnimationController(modelId_);

	// アニメーションの追加
	animationController_->Add(static_cast<int>(ANIM_TYPE::IDLE), 30.f, Application::PATH_MODEL + "Player/Idle.mv1");
	animationController_->Add(static_cast<int>(ANIM_TYPE::WALK), 30.f, Application::PATH_MODEL + "Player/Walk.mv1");

	// 初期アニメーションの再生
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

void Player::Move(void)
{

	// カメラの角度を取得する
	VECTOR cameraAngles = Ins::scene().GetCamera()->GetAngles();

	VECTOR dir = AsoUtility::VECTOR_ZERO;

	// ゲームパッドが接続されている数で処理を分ける
	if (GetJoypadNum() == 0)
	{
		// キーボード操作
		if (Ins::input().IsNew(KEY_INPUT_W)) { dir = AsoUtility::DIR_F; }
		if (Ins::input().IsNew(KEY_INPUT_A)) { dir = AsoUtility::DIR_L; }
		if (Ins::input().IsNew(KEY_INPUT_S)) { dir = AsoUtility::DIR_B; }
		if (Ins::input().IsNew(KEY_INPUT_D)) { dir = AsoUtility::DIR_R; }
	}
	else
	{
		// ゲームパッド操作
		// 接続されているゲームパッド1の情報を取得
		InputManager::JOYPAD_IN_STATE padState = Ins::input().GetJPadInputState(InputManager::JOYPAD_NO::PAD1);

		// アナログキーの入力値から方向を取得
		dir = Ins::input().GetDirectionXZAKey(padState.AKeyLX, padState.AKeyLY);
	}

	// WASDでカメラを移動させる
	const float movePow = 3.0f;
	
	if (!AsoUtility::EqualsVZero(dir))
	{
		// XYZの回転行列
		// XZ平面移動にする場合は、XZの回転を考慮しないようにする
		MATRIX mat = MGetIdent();
		//mat = MMult(mat, MGetRotX(cameraAngles.x));
		mat = MMult(mat, MGetRotY(cameraAngles.y));
		//mat = MMult(mat, MGetRotZ(cameraAngles.z));

		// 回転行列を使用して、ベクトルを回転させる
		moveDir_ = VTransform(dir, mat);

		// 移動方向から角度に変更する
		//angles_.y = atan2f(moveDir.x, moveDir.z);

		// 方向×スピードで移動量を作って、座標に足して移動
		pos_ = VAdd(pos_, VScale(moveDir_, movePow));

		// 歩くアニメーション
		animationController_->Play(static_cast<int>(ANIM_TYPE::WALK));
	}
	else
	{
		// 歩くアニメーション
		animationController_->Play(static_cast<int>(ANIM_TYPE::IDLE));
	}
	
}
