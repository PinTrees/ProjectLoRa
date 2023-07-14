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


class CTexture;

class CUI : public CObject
{
	virtual CUI* Clone() = 0;

private:
	vector<CUI*>	mVecChildUI; // 깊은 복사 진행 해야함.
	CUI*			mpParentUI;

	CTexture*		mpTexture;
	Vect2			mvContentOffset; // 텍스쳐 혹은 텍스트의 위치를 보정하는 변수

	Vect2			mvFinalPos;

	COLORREF		mColor;		// 텍스쳐의 색상 비율값입니다.

	bool			mCameraAffected;
	bool			mOnMouseCheck;	
	bool			mLbtnDown;


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
	bool IsMouseOn() { return mOnMouseCheck; };
	bool IsLbtnDown() { return mLbtnDown; }

public:
	virtual void MouseOn();
	virtual void MouseLbtnDown();
	virtual void MouseLbtnUp();
	virtual void MouseLbtnClick();

private:
	virtual void SetDead() override;

public:
	void AddChild(CUI* ui)
	{
		mVecChildUI.push_back(ui);
		ui->mpParentUI = this;
	}

public:
	CUI*	GetParentUI() { return mpParentUI; }
	Vect2	GetFinalPos() { return mvFinalPos; }
	const vector<CUI*> GetChild() { return mVecChildUI; }

	bool GetLbtnDown() { return mLbtnDown; }
	bool GetIsMouseOn() { return mOnMouseCheck; }

	CUI*		GetFindChild(CUI* parentUI, const wstring& childUI);
	void		SetContentOffset(Vect2 _offset) { mvContentOffset = _offset; }

	CTexture*	GetTextrue() { return mpTexture; }
	void		SetTextrue(CTexture* _texture) { mpTexture = _texture; }

	void		SetColor(COLORREF color) { mColor = color; }
	COLORREF	GetColor() { return mColor; }

	void	SetCameraAffected(bool active) { mCameraAffected = active; };
	bool	IsCameraAffected() { return mCameraAffected; };


public:
	CUI(bool cameraAffected);
	CUI(const CUI& origin);
	virtual ~CUI();

	friend class CUIMgr;
};

