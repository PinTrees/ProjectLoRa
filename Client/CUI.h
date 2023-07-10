#pragma once
#include "CObject.h"

class CTexture;

class CUI : public CObject
{
	virtual CUI* Clone() = 0;

private:
	vector<CUI*>	mVecChildUI; // ���� ���� ���� �ؾ���.
	CUI*			mpParentUI;

	CTexture*		mpTexture;
	wstring			mText;
	Vect2			mvContentOffset; // �ؽ��� Ȥ�� �ؽ�Ʈ�� ��ġ�� �����ϴ� ����

	Vect2			mvFinalPos;

	COLORREF		mColor;		// �ؽ����� ���� �������Դϴ�.

	bool			mCameraAffected;
	bool			mOnMouseCheck;
	bool			mLbtnDown;


public:
	virtual void Update() override;
	virtual void FinalUpdate() override;
	virtual void Render(HDC _dc) override;

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
	bool	GetCameraAffected() { return mCameraAffected; };

	wstring GetText() { return mText; }
	void	SetText(const wstring& _text) { mText = _text; }


public:
	CUI(bool cameraAffected);
	CUI(const CUI& origin);
	virtual ~CUI() override;

	friend class CUIMgr;
};

