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

	CTexture*		mpVeilTex; // ��ư ����Ʈ�� ����� �ؽ��� (��ư�� ���� ��ó�� ������)
	CTexture*		mpChangeTex; // Ŭ�� �� ����� �ؽ���

public:
	virtual void Render(HDC _dc);

	virtual void MouseOn();
	virtual void MouseLbtnDown();
	virtual void MouseLbtnUp();
	virtual void MouseLbtnClick() override;

	void SetChangeTex(CTexture* _tex) { mpChangeTex = _tex; } // ������ �ؽ��� ����
	CTexture* GetChangeTex() { return mpChangeTex; }

	void SetClickedCallBack(BTN_FUNC _pFunc, DWORD_PTR _param1, DWORD_PTR _param2)
	{
		mpFunc = _pFunc;
		mparam1 = _param1;
		mparam2 = _param2;
	}

	void SetClickedCallBack(CScene* scene, SCENE_FUNC func);

	void ApplyAlphaBlend(HDC _dc, int _alpha); // ���ĺ��� �����Լ�

	CLONE(CBtnUI);

public:
	CBtnUI();
	~CBtnUI();
};

