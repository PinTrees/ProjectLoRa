#include "pch.h"
#include "CBtnUI.h"

#include "CResMgr.h"
#include "CTexture.h"
#include "CCore.h"




CBtnUI::CBtnUI()
	: CUI(false)
	, mSceneFunc(nullptr)
	, mScene(nullptr)
	, mText(nullptr)
	, mpVeilTex(nullptr)
	, mpChangeTex(nullptr)
{
	mText = new TextUI;
	this->AddChild(mText);
}

CBtnUI::~CBtnUI()
{
}




void CBtnUI::Render(HDC dc)
{
	CUI::Render(dc);

	if (IsLbtnDown())
	{
		SetAlpha(128);
	}
	else if (IsMouseOn())
	{
		SetAlpha(32);
	}
	else
	{
		SetAlpha(0);
	}

	ApplyAlphaBlend(dc);
}

void CBtnUI::MouseOn()
{
}

void CBtnUI::MouseLbtnDown()
{
}

void CBtnUI::MouseLbtnUp()
{
}

void CBtnUI::MouseLbtnClick()
{
	if (nullptr != mpFunc)
	{
		mpFunc(mparam1, mparam2);
	}

	if (mSceneFunc && mScene)
	{
		(mScene->*mSceneFunc)();
	}

	if (mObjectFunc && mObject)
	{
		(mObject->*mObjectFunc)();
	}

	if (mObjectFuncP && mObject)
	{
		(mObject->*mObjectFuncP)(mparam1);
	}


	if (nullptr != mpChangeTex)
	{
		//mpChangeTex->SetSize(GetTextrue()->GetSize());
		CTexture* temp = mpChangeTex;
		mpChangeTex = GetTextrue();
		SetTextrue(temp);
	}
}


void CBtnUI::SetClickedCallBack(CScene* scene, SCENE_FUNC func)
{
	mSceneFunc = func;
	mScene = scene;
}

void CBtnUI::SetClickedCallBack(CObject* object, OBJECT_FUNC func)
{
	mObjectFunc = func;
	mObject = object;
}

void CBtnUI::SetClickedCallBack(CObject* object, OBJECT_FUNC_P func, DWORD_PTR param)
{
	mObject = object;
	mObjectFuncP = func;
	mparam1 = param;
}


void CBtnUI::ApplyAlphaBlend(HDC _dc)
{
	Vect2 vSize = GetScale();
	Vect2 vPos = GetFinalPos();
	mpVeilTex = CResMgr::GetI()->CreateTexture(L"VeilTex", (UINT)vSize.x, (UINT)vSize.y, RGB(0, 0, 0));

	BLENDFUNCTION bf = {};

	bf.BlendOp = AC_SRC_OVER;
	bf.BlendFlags = 0;
	bf.AlphaFormat = 0;
	bf.SourceConstantAlpha = GetAlpha();

	AlphaBlend(_dc
		, (int)vPos.x - vSize.x * 0.5f
		, (int)vPos.y - vSize.y * 0.5f
		, (int)vSize.x
		, (int)vSize.y
		, mpVeilTex->GetDC()
		, 0, 0
		, (int)mpVeilTex->Width()
		, (int)mpVeilTex->Heigth(), bf);
}
