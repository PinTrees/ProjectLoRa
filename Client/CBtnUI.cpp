#include "pch.h"
#include "CBtnUI.h"
#include "CResMgr.h"
#include "CTexture.h"
#include "CCore.h"


CBtnUI::CBtnUI()
	: CUI(false)
	, mpFunc(nullptr)
	, mparam1(0)
	, mparam2(0)
	, mSceneFunc(nullptr)
	, mScene(nullptr)
	, mpVeilTex(nullptr)
	, mpChangeTex(nullptr)
{
	
}

CBtnUI::~CBtnUI()
{

}

void CBtnUI::Render(HDC _dc)
{
	CUI::Render(_dc);

	if (mOnMouseCheck)
	{
		ApplyAlphaBlend(_dc, 64);
	}

	if (mLbtnDown)
	{
		ApplyAlphaBlend(_dc, 128);
	}
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

	if (nullptr != mpChangeTex)
	{
		mpChangeTex->SetSize(GetTextrue()->GetSize());
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

void CBtnUI::ApplyAlphaBlend(HDC _dc, int _alpha)
{
	Vec2 vSize = GetScale();
	Vec2 vPos = GetFinalPos();
	mpVeilTex = CResMgr::GetI()->CreateTexture(L"VeilTex", (UINT)vSize.x, (UINT)vSize.y, RGB(0, 0, 0));

	BLENDFUNCTION bf = {};

	bf.BlendOp = AC_SRC_OVER;
	bf.BlendFlags = 0;
	bf.AlphaFormat = 0;
	bf.SourceConstantAlpha = _alpha;

	AlphaBlend(_dc
		, (int)vPos.x
		, (int)vPos.y
		, (int)mpVeilTex->Width(), (int)mpVeilTex->Heigth()
		, mpVeilTex->GetDC()
		, 0, 0
		, (int)mpVeilTex->Width(), (int)mpVeilTex->Heigth(), bf);
}
