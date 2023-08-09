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
	, mHoberAlpha(0.f)
	, mObjectFunc(nullptr)
	, mObjectFuncP(nullptr)
	, mObject(nullptr)
	, mpFunc(nullptr)
	, mparam1(0)
	, mparam2(0)
{
	mText = new TextUI;
	mText->SetFontSize(24);
	AddChild(mText);
}

CBtnUI::~CBtnUI()
{
}




void CBtnUI::Render(HDC dc)
{
	Vect2 vPos = IsCameraAffected() ? CCamera::GetI()->GetRenderPos(GetFinalPos()) : GetFinalPos();
	Vect2 vScale = GetScale();

	if(mpTexture)
	{
		BLENDFUNCTION bf = {};

		bf.BlendOp = AC_SRC_OVER;
		bf.BlendFlags = 0;
		bf.AlphaFormat = AC_SRC_ALPHA;
		bf.SourceConstantAlpha = static_cast<BYTE>(GetAlpha());

		AlphaBlend(dc
			, (int)(vPos.x - vScale.x * 0.5f)
			, (int)(vPos.y - vScale.y * 0.5f)
			, (int)vScale.x
			, (int)vScale.y
			, mpTexture->GetDC()
			, 0, 0
			, (int)mpTexture->Width()
			, (int)mpTexture->Heigth()
			, bf);
	}

	CUI::Render(dc);
	CUI::RenderChild(dc);

	if (IsLbtnDown())
	{
		RenderHover(dc, 128.f);
	}
	else if (IsMouseOnUI())
	{
		RenderHover(dc, 32.f);
	}
}

void CBtnUI::MouseOn()
{
	CUI::MouseOn();
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
		mpChangeTex = GetTexture();
		SetTexture(temp);
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


void CBtnUI::RenderHover(HDC _dc, float alpha)
{
	Vect2 vSize = GetScale();
	Vect2 vPos = GetFinalPos();
	mpVeilTex = CResMgr::GetI()->CreateTexture(L"VeilTex", (UINT)vSize.x, (UINT)vSize.y, RGB(0, 0, 0));

	BLENDFUNCTION bf = {};

	bf.BlendOp = AC_SRC_OVER;
	bf.BlendFlags = 0;
	bf.AlphaFormat = 0;
	bf.SourceConstantAlpha = static_cast<BYTE>(alpha);

	AlphaBlend(_dc
		, (int)(vPos.x - vSize.x * 0.5f)
		, (int)(vPos.y - vSize.y * 0.5f)
		, (int)vSize.x
		, (int)vSize.y
		, mpVeilTex->GetDC()
		, 0, 0
		, (int)mpVeilTex->Width()
		, (int)mpVeilTex->Heigth(), bf);
}
