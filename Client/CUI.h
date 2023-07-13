#pragma once
#include "CObject.h"

class CTexture;
<<<<<<< Updated upstream
class CFont;
=======
>>>>>>> Stashed changes

class CUI : public CObject
{
	virtual CUI* Clone() = 0;

private:
	vector<CUI*>	mVecChildUI; // 깊은 복사 진행 해야함.
	CUI*			mpParentUI;

	CTexture*		mpTexture;
<<<<<<< Updated upstream
	CFont*			mFont;
	Vec2			mvContentOffset; // 텍스쳐 혹은 텍스트의 위치를 보정하는 변수

	Vec2			mvFinalPos;
=======
	Vect2			mvContentOffset; // 텍스쳐 혹은 텍스트의 위치를 보정하는 변수

	Vect2			mvFinalPos;
>>>>>>> Stashed changes

	COLORREF		mColor;		// 텍스쳐의 색상 비율값입니다.

	bool			mCameraAffected;
<<<<<<< Updated upstream

protected:
	bool			mOnMouseCheck;
=======
	bool			mOnMouseCheck;	
>>>>>>> Stashed changes
	bool			mLbtnDown;


public:
	virtual void Update() override;
	virtual void FinalUpdate() override;
	virtual void Render(HDC _dc) override;

<<<<<<< Updated upstream
=======
	virtual void OnDestroy() override;

>>>>>>> Stashed changes
	void UpdateChild();
	void FinalUpdateChild();
	void RenderChild(HDC dc);

<<<<<<< Updated upstream
=======

>>>>>>> Stashed changes
public:
	void OnMouseCheck();
	bool IsMouseOn() { return mOnMouseCheck; };
	bool IsLbtnDown() { return mLbtnDown; }

public:
	virtual void MouseOn();
	virtual void MouseLbtnDown();
	virtual void MouseLbtnUp();
	virtual void MouseLbtnClick();

<<<<<<< Updated upstream
=======
private:
	virtual void SetDead() override;

>>>>>>> Stashed changes
public:
	void AddChild(CUI* ui)
	{
		mVecChildUI.push_back(ui);
		ui->mpParentUI = this;
	}

public:
	CUI*	GetParentUI() { return mpParentUI; }
<<<<<<< Updated upstream
	Vec2	GetFinalPos() { return mvFinalPos; }
=======
	Vect2	GetFinalPos() { return mvFinalPos; }
>>>>>>> Stashed changes
	const vector<CUI*> GetChild() { return mVecChildUI; }

	bool GetLbtnDown() { return mLbtnDown; }
	bool GetIsMouseOn() { return mOnMouseCheck; }

	CUI*		GetFindChild(CUI* parentUI, const wstring& childUI);
<<<<<<< Updated upstream
	void		SetContentOffset(Vec2 _offset) { mvContentOffset = _offset; }
=======
	void		SetContentOffset(Vect2 _offset) { mvContentOffset = _offset; }
>>>>>>> Stashed changes

	CTexture*	GetTextrue() { return mpTexture; }
	void		SetTextrue(CTexture* _texture) { mpTexture = _texture; }

	void		SetColor(COLORREF color) { mColor = color; }
	COLORREF	GetColor() { return mColor; }

	void	SetCameraAffected(bool active) { mCameraAffected = active; };
	bool	GetCameraAffected() { return mCameraAffected; };
<<<<<<< Updated upstream

	CFont* GetFont() { return mFont; }
	void	SetFont(CFont* _text) { mFont = _text; }


public:
	CUI(bool cameraAffected);
	CUI(const CUI& origin);
	virtual ~CUI() override;
=======
public:
	CUI(bool cameraAffected);
	CUI(const CUI& origin);
	virtual ~CUI();
>>>>>>> Stashed changes

	friend class CUIMgr;
};

