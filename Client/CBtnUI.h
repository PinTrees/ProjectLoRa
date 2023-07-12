#pragma once
#include "CUI.h"
#include "TextUI.h"

#include "CScene.h"
#include "CObject.h"

typedef void(*BTN_FUNC) (DWORD_PTR, DWORD_PTR);
typedef void(CScene::*SCENE_FUNC) (void);
typedef void(CObject::*OBJECT_FUNC) (void);

class TextUI;


class CBtnUI :
	public CUI
{
private:
	BTN_FUNC        mpFunc;
	DWORD_PTR		mparam1;
	DWORD_PTR		mparam2;

	SCENE_FUNC		mSceneFunc;
	CScene*			mScene;

	OBJECT_FUNC		mObjectFunc;
	CObject*		mObject;

	TextUI*			mText;


public:
	TextUI* GetText() { return mText; }
	void	SetText(const wstring& _text) { mText->SetText(_text); }
	 

public:
	virtual void MouseOn() override;
	virtual void MouseLbtnDown() override;
	virtual void MouseLbtnUp() override;
	virtual void MouseLbtnClick() override;

	void SetClickedCallBack(BTN_FUNC _pFunc, DWORD_PTR _param1, DWORD_PTR _param2)
	{
		mpFunc = _pFunc;
		mparam1 = _param1;
		mparam2 = _param2;
	}

	void SetClickedCallBack(CScene* scene, SCENE_FUNC func);
	void SetClickedCallBack(CObject* object, OBJECT_FUNC func);

	CLONE(CBtnUI);


public:
	CBtnUI();
	virtual ~CBtnUI();
};

