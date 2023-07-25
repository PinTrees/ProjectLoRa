#pragma once
#include "CScene.h"

class AnimationView;
class CAnimation;
class CTexture;
class CBtnUI;
class TextUI;

enum class eBtnFunc
{
	// �Լ������� ������ enum�� 0�������� ���������� nullptr�� ��޵Ǵµ���
	FIRST,
	ADD_XPIXEL,
	SUB_XPIXEL,
	ADD_YPIXEL,
	SUB_YPIXEL,
	ADD_MAX_FRM_COUNT,
	SUB_MAX_FRM_COUNT,
	ADD_LT,
	SUB_LT,
	ADD_DUR,
	SUB_DUR,
	ADD_X_SCALE,
	SUB_X_SCALE,
	ADD_Y_SCALE,
	SUB_Y_SCALE,
	END,
};

struct tAniminfo
{
	// �ִϸ��̼� ����
	wstring name; //�����̸�
	UINT FrameCount;// ������ ��ü ����
	UINT FrameLT; // ��������Ʈ
	UINT xPixel;
	UINT yPixel;//�����Ӵ� yũ�� �� �����̽� ũ��
	Vect2 scale;
	float Duration; // �ִϸ��̼ǽð�
	int curFrame; // ���� �����ִ� ������
};

class Scene_Viewer :
	public CScene
{
private:
	AnimationView* mpAnimViewer; // ��������Ʈ
	CAnimation* mpAnimation; // �ִϸ��̼�
	CTexture* mpTex;	//������ �ؽ���
	TextUI* mpCurFrmInfo; // ���� �����ִ� �ִϸ��̼� �̸�

	TextUI* mpCurFrmNumber; // ���� �����ִ� ������ �ѹ�
	TextUI* mpXPixelSize; // ���� �����ִ� ������ �ѹ�
	TextUI* mpYPixelSize; // ���� �����ִ� ������ �ѹ�
	TextUI* mpLT; // ���� �����ִ� ������ �ѹ�
	TextUI* mpDuration; // ���� �����ִ� ������ �ѹ�
	TextUI* mpMaxFrm; // ���� �����ִ� ������ �ѹ�


	tAniminfo mAnimInfo;


public:
	AnimationView* GetAnimObj() { return mpAnimViewer; }
	CAnimation* GetAnimation() { return mpAnimation; }
	void SetAnimation(CAnimation* _pAnim) { mpAnimation = _pAnim; }
	CTexture* GetTex() { return mpTex; }

	tAniminfo& GetAnimInfo() { return mAnimInfo; }

public:
	virtual void Update();
	virtual void Enter();
	virtual void Render(HDC _dc);
	virtual void Exit();

	void AnimPlaySwitch();
	void AnimStopSwitch();
	void AnimNextFrm();
	void AnimPrevFrm();

	void LoadAnimData();
	void SaveAnimation();
	void ChangeAnim();// ������Ʈ ������ ������ ���ÿ� ����
private:
	void CreateViewerUI();
	void UpdateInfo(); // ���� �ִϸ��̼� ���� ������Ʈ �� ���
	void ChangeInfo(eBtnFunc _e);



	wstring to_wstring_with_precision(float value, int precision);
public:
	Scene_Viewer();
	~Scene_Viewer();

};

