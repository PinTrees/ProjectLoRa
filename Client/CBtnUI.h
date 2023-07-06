#pragma once
#include "CUI.h"

#include "CScene.h"
#include "CObject.h"

class CScene;

typedef void(*BTN_FUNC) (DWORD_PTR, DWORD_PTR);

typedef void(CScene::*SCENE_MEMFUNC) (void);
typedef void(CObject::*OBJECT_MEMFUNC) (void);

class CBtnUI :
	public CUI
{
private:
	BTN_FUNC        mpFunc;
	DWORD_PTR		mparam1;
	DWORD_PTR		mparam2;

	SCENE_MEMFUNC	mpSceneFunc;
	CScene*			mpSceneInst;

public:
	virtual void MouseOn();
	virtual void MouseLbtnDown();
	virtual void MouseLbtnUp();
	virtual void MouseLbtnClicked();

	void SetClickedCallBack(BTN_FUNC _pFunc, DWORD_PTR _param1, DWORD_PTR _param2)
	{
		mpFunc = _pFunc;
		mparam1 = _param1;
		mparam2 = _param2;
	}

	void SetClickedCallBack(CScene* _pScene, SCENE_MEMFUNC _pSceneFunc);

	CLONE(CBtnUI);

public:
	CBtnUI();
	~CBtnUI();
};

