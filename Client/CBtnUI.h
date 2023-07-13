#pragma once
#include "CUI.h"
<<<<<<< Updated upstream
=======
#include "TextUI.h"
>>>>>>> Stashed changes

#include "CScene.h"
#include "CObject.h"

typedef void(*BTN_FUNC) (DWORD_PTR, DWORD_PTR);
typedef void(CScene::*SCENE_FUNC) (void);
typedef void(CObject::*OBJECT_FUNC) (void);
<<<<<<< Updated upstream
=======
typedef void(CObject::* OBJECT_FUNC_P) (DWORD_PTR);

class TextUI;

>>>>>>> Stashed changes

class CBtnUI :
	public CUI
{
private:
<<<<<<< Updated upstream
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
=======
	BTN_FUNC        mpFunc;				// 전역함수
	DWORD_PTR		mparam1;			// 매개변수 임시 저장
	DWORD_PTR		mparam2;			// 매개변수 임시 저장

	SCENE_FUNC		mSceneFunc;			// 씬 멤버 함수
	CScene*			mScene;				// 호출자

	OBJECT_FUNC		mObjectFunc;		// 매개변수가 없는 오브젝트 멤버함수
	OBJECT_FUNC_P	mObjectFuncP;		// 매개변수가 존재하는 오브젝트 멤버함수
	CObject*		mObject;			// 호출자

	TextUI*			mText;

	CTexture*		mpVeilTex;			// 버튼 이펙트에 사용할 텍스쳐 (버튼이 눌린 것처럼 연출함)
	CTexture*		mpChangeTex;		// 클릭 시 변경될 텍스쳐


public:
	TextUI* GetText() { return mText; }
	void	SetText(const wstring& _text) { mText->SetText(_text); }
	 
	void		SetChangeTex(CTexture* _tex) { mpChangeTex = _tex; } // 변경할 텍스쳐 세팅
	CTexture*	GetChangeTex() { return mpChangeTex; }
>>>>>>> Stashed changes

	void SetClickedCallBack(BTN_FUNC _pFunc, DWORD_PTR _param1, DWORD_PTR _param2)
	{
		mpFunc = _pFunc;
		mparam1 = _param1;
		mparam2 = _param2;
	}

	void SetClickedCallBack(CScene* scene, SCENE_FUNC func);
<<<<<<< Updated upstream

	void ApplyAlphaBlend(HDC _dc, int _alpha); // 알파블렌드 적용함수

	CLONE(CBtnUI);

=======
	void SetClickedCallBack(CObject* object, OBJECT_FUNC func);
	void SetClickedCallBack(CObject* object, OBJECT_FUNC_P func, DWORD_PTR param);


public:
	void ApplyAlphaBlend(HDC _dc, int _alpha);


public:
	virtual void Render(HDC dc) override;

	virtual void MouseOn() override;
	virtual void MouseLbtnDown() override;
	virtual void MouseLbtnUp() override;
	virtual void MouseLbtnClick() override;

	CLONE(CBtnUI);


>>>>>>> Stashed changes
public:
	CBtnUI();
	~CBtnUI();
};

