#pragma once

#include "../../Actor/Base/ActorBase.h"

class AnimationController;

class Player : ActorBase
{

public:

	// �A�j���[�V�������
	enum class ANIM_TYPE
	{
		IDLE,
		WALK,
		MAX,
	};

	// �R���X�g���N�^
	Player(void);
	// �f�X�g���N�^
	~Player(void) override;
	
	void Update(void)  override;
	void Draw(void)	   override;
	void Release(void) override;
	
protected:

	// �����[�X���[�h
	void InitLoad(void) override;

	// �傫���A��]�A���W�̏�����
	void InitTransform(void) override;

	// �A�j���[�V�����̏�����
	void InitAnimation(void) override;

	// ��������̌ʏ���
	void InitPost(void) override;

	// �ړ�����
	void Move(void) override;

private:
	
	// �T�C�R�����f�����
	int diceModelId_;
	
	VECTOR dicePos_;
	VECTOR diceAngles_;
	VECTOR diceScales_;
	
	VECTOR diceLocalPos_;
	VECTOR diceLocalAngles_;
	
	// �ړ�����
	VECTOR moveDir_;
	
	void InitDice(void);
	void SyncDice(void);
	
};