#pragma once
#include "CUI.h"
#include "TextUI.h"

#include "CScene.h"
#include "CObject.h"

typedef void(*BTN_FUNC) (DWORD_PTR, DWORD_PTR);
typedef void(CScene::*SCENE_FUNC) (void);
typedef void(CObject::*OBJECT_FUNC) (void);
typedef void(CObject::* OBJECT_FUNC_P) (DWORD_PTR);

class TextUI;


class CBtnUI :
	public CUI
{
private:
	BTN_FUNC        mpFunc;				// �����Լ�
	DWORD_PTR		mparam1;			// �Ű����� �ӽ� ����
	DWORD_PTR		mparam2;			// �Ű����� �ӽ� ����

	SCENE_FUNC		mSceneFunc;			// �� ��� �Լ�
	CScene*			mScene;				// ȣ����

	OBJECT_FUNC		mObjectFunc;		// �Ű������� ���� ������Ʈ ����Լ�
	OBJECT_FUNC_P	mObjectFuncP;		// �Ű������� �����ϴ� ������Ʈ ����Լ�
	CObject*		mObject;			// ȣ����

	TextUI*			mText;

	CTexture*		mpVeilTex;			// ��ư ����Ʈ�� ����� �ؽ��� (��ư�� ���� ��ó�� ������)
	CTexture*		mpChangeTex;		// Ŭ�� �� ����� �ؽ���


public:
	TextUI* GetText() { return mText; }
	void	SetText(const wstring& _text) { mText->SetText(_text); }
	 
	void		SetChangeTex(CTexture* _tex) { mpChangeTex = _tex; } // ������ �ؽ��� ����
	CTexture*	GetChangeTex() { return mpChangeTex; }

	void SetClickedCallBack(BTN_FUNC _pFunc, DWORD_PTR _param1, DWORD_PTR _param2)
	{
		mpFunc = _pFunc;
		mparam1 = _param1;
		mparam2 = _param2;
	}

	void SetClickedCallBack(CScene* scene, SCENE_FUNC func);
	void SetClickedCallBack(CObject* object, OBJECT_FUNC func);
	void SetClickedCallBack(CObject* object, OBJECT_FUNC_P func, DWORD_PTR param);


public:
	void ApplyAlphaBlend(HDC _dc);


public:
	virtual void Render(HDC dc) override;

	virtual void MouseOn() override;
	virtual void MouseLbtnDown() override;
	virtual void MouseLbtnUp() override;
	virtual void MouseLbtnClick() override;

	CLONE(CBtnUI);


public:
	CBtnUI(const CUI& origin);
	CBtnUI();
	~CBtnUI();
};

