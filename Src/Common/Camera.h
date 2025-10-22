
#pragma once

#include <DxLib.h>

class Camera
{

public:

	// �J�����̏������W
	static constexpr VECTOR DEFAULT_POS = { 0.f, 200.f, -500.f };

	// �J�����̏����p�x
	static constexpr VECTOR DEFAULT_ANGLES = { 30.f * DX_PI_F / 180.f, 0.f, 0.f };

	// �J�����̃N���b�v�͈�
	static constexpr float VIEW_NEAR = 1.f;
	static constexpr float VIEW_FAR  = 30000.f;

	// �J�������[�h
	enum class MODE
	{
		NONE,
		FIXED_POINT,
		FREE,
	};

	// �R���X�g���N�^
	Camera(void);

	// �f�X�g���N�^
	~Camera(void);

	// ������
	void Init(void);

	// �X�V
	void Update(void);

	// �`��O�̃J�����ݒ�
	void SetBeforeDraw(void);
	void SetBeforeDrawFixedPoint(void);
	void SetBeforeDrawFree(void);

	// �f�o�b�O�p�`��
	void DrawDebug(void);

	// ���
	void Release(void);

	// ���W�̎擾
	const VECTOR& GetPos(void) const;

	// �p�x�̎擾
	const VECTOR& GetAngles(void) const;

	// �J�������[�h�̕ύX
	void ChangeMode(MODE mode);

private:

	// �J�������[�h
	MODE mode_;

	// �J�����̈ʒu
	VECTOR pos_;

	// �J�����̊p�x
	VECTOR angles_;

	void MoveXYZDirection(void);
};
