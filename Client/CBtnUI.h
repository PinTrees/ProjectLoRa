#pragma once
#include "CUI.h"

#include "CScene.h"
#include "CObject.h"

typedef void(*BTN_FUNC) (DWORD_PTR, DWORD_PTR);
typedef void(CScene::*SCENE_FUNC) (void);
typedef void(CObject::*OBJECT_FUNC) (void);

class CBtnUI :
	public CUI
{
private:
	BTN_FUNC        mpFunc;
	DWORD_PTR		mparam1;
	DWORD_PTR		mparam2;

	SCENE_FUNC		mSceneFunc;
	CScene*			mScene;

	CTexture*		mpVeilTex; // 버튼 이펙트에 사용할 텍스쳐 (버튼이 눌린 것처럼 연출함)
	CTexture*		mpChangeTex; // 클릭 시 변경될 텍스쳐

public:
	virtual void Render(HDC _dc);

	virtual void MouseOn();
	virtual void MouseLbtnDown();
	virtual void MouseLbtnUp();
	virtual void MouseLbtnClick() override;

	void SetChangeTex(CTexture* _tex) { mpChangeTex = _tex; } // 변경할 텍스쳐 세팅
	CTexture* GetChangeTex() { return mpChangeTex; }

	void SetClickedCallBack(BTN_FUNC _pFunc, DWORD_PTR _param1, DWORD_PTR _param2)
	{
		mpFunc = _pFunc;
		mparam1 = _param1;
		mparam2 = _param2;
	}

	void SetClickedCallBack(CScene* scene, SCENE_FUNC func);

	void ApplyAlphaBlend(HDC _dc, int _alpha); // 알파블렌드 적용함수

	CLONE(CBtnUI);

public:
	CBtnUI();
	~CBtnUI();
};

