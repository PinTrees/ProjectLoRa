#pragma once
#include "CObject.h"


// UI 정렬
enum class ALIGNMENT
{
	BOTTOM_CENTER,
	BOTTOM_LEFT,
	BOTTOM_RIGHT,

	CENTER,
	CENTER_LEFT,
	CENTER_RIGHT,

	TOP_CENTER,
	TOP_LEFT,
	TOP_RIGHT
};


enum class AXIS_ALIGNMENT
{
	START,
	END,
	SPACE,
};

class CTexture;




class CUI : public CObject
{
	virtual CUI* Clone() = 0;

private:
	vector<CUI*>	mVecChildUI; // 깊은 복사 진행 해야함.
	CUI*			mpParentUI;

	Vect2			mvOffset;	// 
	Vect2			mvFinalPos;

	COLORREF		mColor;		// 텍스쳐의 색상 비율값입니다.

	bool			mCameraAffected;
	bool			mOnMouseCheck;	
	bool			mLbtnDown;

	bool			mFixedChildMouseCheck;	// 자식 UI의 마우스 좌표 범위를 해당 UI 크기로 제한합니다.
	bool			mOriginalMouseCheck;	// mFixedChildMouseCheck 옵션을 무시합니다.
		
	bool			mbRaycastTarget;		// 마우스 범위 체크 여부

	// 삭제될 자식 UI
	vector<CUI*>	mDeleteChildUI;


public:
	virtual void Update() override;
	virtual void FinalUpdate() override;
	virtual void Render(HDC _dc) override;

	virtual void OnDestroy() override;

	void UpdateChild();
	void FinalUpdateChild();
	void RenderChild(HDC dc);


public:
	void OnMouseCheck();
	bool IsMouseOnUI() { return mOnMouseCheck; };
	bool IsLbtnDown() { return mLbtnDown; }

public:
	virtual void MouseOn();
	virtual void MouseLbtnDown();
	virtual void MouseLbtnUp();
	virtual void MouseLbtnClick();

private:
	virtual void SetDead() override;

public:
	virtual void AddChild(CUI* ui);
	virtual void SetTopChild(CUI* ui);
	void DeleteChild(CUI* ui);


public:
	CUI*	GetParentUI() { return mpParentUI; }
	Vect2	GetFinalPos() { return mvFinalPos; }
	const vector<CUI*> GetChild() { return mVecChildUI; }

	bool GetLbtnDown() { return mLbtnDown; }
	bool GetIsMouseOn() { return mOnMouseCheck; }

	CUI*		GetFindChild(CUI* parentUI, const wstring& childUI);
	void		SetOffset(Vect2 _offset) { mvOffset = _offset; }

	void		SetColor(COLORREF color) { mColor = color; }
	COLORREF	GetColor() { return mColor; }

	void	SetCameraAffected(bool active) { mCameraAffected = active; };
	bool	IsCameraAffected() { return mCameraAffected; };

	// 마우스 좌표 범위 설정
	void	SetFixedChildMouseCheck(bool active) { mFixedChildMouseCheck = active; }
	bool	IsFixedChildMouseCheck();
	CUI*	GetFixedChildMouseCheckParent();
	void	SetOriginalMouseCheck(bool active) { mOriginalMouseCheck = active; }

	void	SetRaycastTarget(bool active) { mbRaycastTarget = active; }


public:
	CUI(bool cameraAffected);
	CUI(const CUI& origin);
	virtual ~CUI();

	friend class CUIMgr;


public:
	static bool IsAligmentLeft(ALIGNMENT aligment);
	static bool IsAligmentRight(ALIGNMENT aligment);
	static bool IsAligmentBottom(ALIGNMENT aligment);
	static bool IsAligmentTop(ALIGNMENT aligment);
	static bool IsAligmentCenter(ALIGNMENT aligment);
	static bool IsAligmentCenter_Ver(ALIGNMENT aligment);
	static bool IsAligmentCenter_Hor(ALIGNMENT aligment);
};



