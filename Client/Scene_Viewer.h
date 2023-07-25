#pragma once
#include "CScene.h"

class AnimationView;
class CAnimation;
class CTexture;
class CBtnUI;
class TextUI;

enum class eBtnFunc
{
	// 함수포인터 값으로 enum값 0을넣으면 오류가있음 nullptr로 취급되는듯함
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
	// 애니메이션 정보
	wstring name; //파일이름
	UINT FrameCount;// 프레임 전체 개수
	UINT FrameLT; // 시작포인트
	UINT xPixel;
	UINT yPixel;//프레임당 y크기 밑 슬라이스 크기
	Vect2 scale;
	float Duration; // 애니메이션시간
	int curFrame; // 현재 보고있는 프레임
};

class Scene_Viewer :
	public CScene
{
private:
	AnimationView* mpAnimViewer; // 뷰어오브젝트
	CAnimation* mpAnimation; // 애니메이션
	CTexture* mpTex;	//가져온 텍스쳐
	TextUI* mpCurFrmInfo; // 현재 보고있는 애니메이션 이름

	TextUI* mpCurFrmNumber; // 현재 보고있는 프레임 넘버
	TextUI* mpXPixelSize; // 현재 보고있는 프레임 넘버
	TextUI* mpYPixelSize; // 현재 보고있는 프레임 넘버
	TextUI* mpLT; // 현재 보고있는 프레임 넘버
	TextUI* mpDuration; // 현재 보고있는 프레임 넘버
	TextUI* mpMaxFrm; // 현재 보고있는 프레임 넘버


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
	void ChangeAnim();// 오브젝트 생성과 삭제를 동시에 진행
private:
	void CreateViewerUI();
	void UpdateInfo(); // 현재 애니메이션 정보 업데이트 밑 출력
	void ChangeInfo(eBtnFunc _e);



	wstring to_wstring_with_precision(float value, int precision);
public:
	Scene_Viewer();
	~Scene_Viewer();

};

