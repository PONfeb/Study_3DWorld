
#pragma once

#include "../../Actor/Base/ActorBase.h"

class Enemy : public ActorBase
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
	Enemy(void);
	// �f�X�g���N�^
	~Enemy(void) override;

protected:

	// �����[�X���[�h
	void InitLoad(void) override;

	// �傫���A��]�A���W�̏�����
	void InitTransform(void) override;

	// �A�j���[�V�����̏�����
	void InitAnimation(void) override;

	// ��������̌ʏ���
	void InitPost(void) override;

};
