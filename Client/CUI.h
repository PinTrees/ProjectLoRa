#pragma once
#include "CObject.h"

class CUI :
	public CObject
{
private:
	vector<CUI*>        mVecChildUI;
	CUI*				mpParentUI;
	Vec2				mvFinalPos;

	bool				mbCamAffected;	// UI가 카메라 영향을 받는지 유무
	bool				mbMouseOn;		// UI 위에 마우스가 있는지
	bool				mbLbtnDown;		// UI 에 왼쪽버튼이 눌린적이 있는지

public:
	Vec2 GetFinalPos() { return mvFinalPos; }
	CUI* GetParent() { return mpParentUI; }
	bool IsMouseOn() { return mbMouseOn; }
	bool IsLbtnDown() { return mbLbtnDown; }

	void AddChild(CUI* _pUI) { mVecChildUI.push_back(_pUI); _pUI->mpParentUI = this; }
	const vector<CUI*>& GetChildUI(){ return mVecChildUI; }

public:
	virtual void Update();
	virtual void FinalUpdate();
	virtual void Render(HDC _dc);
private:
	void update_child();
	void finalupdate_child();
	void render_child(HDC _dc);

	void MouseOnCheck();
public:
	virtual void MouseOn();

	virtual void MouseLbtnDown();
	virtual void MouseLbtnUp();
	virtual void MouseLbtnClicked();

	virtual CUI* Clone() = 0;

public:

	CUI(bool _bCamAff);
	CUI(const CUI& _origin);
	virtual ~CUI();

	friend class CUIMgr;
};

