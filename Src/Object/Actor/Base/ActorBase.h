#pragma once

#include <string>
#include <DxLib.h>

#include "../../../Application.h"

#include "../../../Utility/AsoUtility.h"

#include "../../../Common/AnimationController.h"

class AnimationController;

class ActorBase
{

public:

	// �A�j���[�V�����̍Đ����x
	static constexpr float SPEED_ANIM = 20.0f;

	// �R���X�g���N�^
	ActorBase(void);
	// �f�X�g���N�^
	virtual ~ActorBase(void);

	void Init(void);
	virtual void Update(void);
	virtual void Draw(void);
	virtual void Release(void);

	// ���W���擾
	const VECTOR& GetPos(void) const;

protected:

	// �A�j���[�V��������
	AnimationController* animationController_;

	// �A�j���[�V�������
	int animType_;

	// ���f�����
	int modelId_;

	VECTOR pos_;
	VECTOR angles_;
	VECTOR scales_;
	VECTOR localAngles_;

	// �ړ�����
	VECTOR moveDir_;

	// ���\�[�X���[�h
	virtual void InitLoad(void) = 0;

	// �傫���A��]�A���W�̏�����
	virtual void InitTransform(void) = 0;

	// �傫���A��]�A���W�̃��f���ݒ�
	void InitTransformPost(void);

	// �A�j���[�V�����̏�����
	virtual void InitAnimation(void) = 0;

	// ��������̌ʏ���
	virtual void InitPost(void) = 0;

	// �ړ�����
	virtual void Move(void);

	// �x����]����
	void DelayRotate(void);

};