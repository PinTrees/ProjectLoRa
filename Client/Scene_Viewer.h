#pragma once
#include "CScene.h"

class AnimationView;
class CAnimation;
class CTexture;
class CBtnUI;
class TextUI;

enum class eBtnFunc
{
	ADD_XPIXEL,
	SUB_XPIXEL,
	ADD_YPIXEL,
	SUB_YPIXEL,
	ADD_FRM,
	SUB_FRM,
	ADD_DUR,
	SUB_DUR,

};

struct tAniminfo
{
	// �ִϸ��̼� ����
	wstring name; //�����̸�
	UINT FrameCount;// ������ ��ü ����
	UINT FrameLT; // ��������Ʈ
	UINT xPixel;
	UINT yPixel;//�����Ӵ� yũ�� �� �����̽� ũ��
	float durTime; // �ִϸ��̼ǽð�
	int curFrame; // ���� �����ִ� ������
};

class Scene_Viewer :
	public CScene
{
private:
	AnimationView* mpAnimViewer; // ��������Ʈ
	CAnimation* mpAnimation; // �ִϸ��̼�
	CTexture* mpTex;	//������ �ؽ���
	TextUI* mpCurFrmInfo; // ���� �����ִ� �ִϸ��̼� �� ����������

	TextUI* mpCurFrmNumber; // ���� �����ִ� ������ �ѹ�


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

	void LoadFile();
	void LoadAnimData();

	void ChangeAnim();// ������Ʈ ������ ������ ���ÿ� ����
private:
	void CreateViewerUI();
	void UpdateInfo(); // ���� �ִϸ��̼� ���� ������Ʈ �� ���

	void addXPixel() { ++mAnimInfo.xPixel; ChangeAnim(); }
	void subXPixel() {
		if (mAnimInfo.xPixel <= 0)
			return;
		--mAnimInfo.xPixel; ChangeAnim(); }
	void addYPixel() { ++mAnimInfo.yPixel; ChangeAnim(); }
	void subYPixel() { 
		if (mAnimInfo.yPixel <= 0)
			return;
		--mAnimInfo.yPixel; ChangeAnim(); }
	void addLT() { ++mAnimInfo.FrameLT; ChangeAnim(); }
	void subLT() 
	{
		if (mAnimInfo.FrameLT <= 0)
			return;

		--mAnimInfo.FrameLT; ChangeAnim(); }
	void addFrameCount() { ++mAnimInfo.FrameCount; ChangeAnim(); }
	void subFrameCount() { 
		if (mAnimInfo.FrameCount <= 0)
			return;
		--mAnimInfo.FrameCount; ChangeAnim(); }
	void addDurTime() { 

		mAnimInfo.durTime += 0.1f; ChangeAnim(); }
	void subDurTime() { 
		if (mAnimInfo.durTime <= 0.f)
			return; 
		mAnimInfo.durTime -= 0.1f; ChangeAnim(); }
	wstring to_wstring_with_precision(float value, int precision);
public:
	Scene_Viewer();
	~Scene_Viewer();

};

