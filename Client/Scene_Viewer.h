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
	// 애니메이션 정보
	wstring name; //파일이름
	UINT FrameCount;// 프레임 전체 개수
	UINT FrameLT; // 시작포인트
	UINT xPixel;
	UINT yPixel;//프레임당 y크기 밑 슬라이스 크기
	float durTime; // 애니메이션시간
	int curFrame; // 현재 보고있는 프레임
};

class Scene_Viewer :
	public CScene
{
private:
	AnimationView* mpAnimViewer; // 뷰어오브젝트
	CAnimation* mpAnimation; // 애니메이션
	CTexture* mpTex;	//가져온 텍스쳐
	TextUI* mpCurFrmInfo; // 현재 보고있는 애니메이션 밑 프레임정보

	TextUI* mpCurFrmNumber; // 현재 보고있는 프레임 넘버


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

	void ChangeAnim();// 오브젝트 생성과 삭제를 동시에 진행
private:
	void CreateViewerUI();
	void UpdateInfo(); // 현재 애니메이션 정보 업데이트 밑 출력

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

