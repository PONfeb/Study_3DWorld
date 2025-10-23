
#pragma once

#include "../../Actor/Base/ActorBase.h"

class Enemy : public ActorBase
{

public:

	// アニメーション種別
	enum class ANIM_TYPE
	{
		IDLE,
		WALK,
		MAX,
	};

	// コンストラクタ
	Enemy(void);
	// デストラクタ
	~Enemy(void) override;

protected:

	// リリースロード
	void InitLoad(void) override;

	// 大きさ、回転、座標の初期化
	void InitTransform(void) override;

	// アニメーションの初期化
	void InitAnimation(void) override;

	// 初期化後の個別処理
	void InitPost(void) override;

};
