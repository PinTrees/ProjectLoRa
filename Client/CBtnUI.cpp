#include "pch.h"
#include "CBtnUI.h"
<<<<<<< Updated upstream
=======

>>>>>>> Stashed changes
#include "CResMgr.h"
#include "CTexture.h"
#include "CCore.h"


<<<<<<< Updated upstream
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
	
=======


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
>>>>>>> Stashed changes
}

CBtnUI::~CBtnUI()
{
<<<<<<< Updated upstream

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
=======
}




void CBtnUI::Render(HDC dc)
{
	CUI::Render(dc);

	if (IsMouseOn())
	{
		ApplyAlphaBlend(dc, 64);
	}

	if (IsLbtnDown())
	{
		ApplyAlphaBlend(dc, 128);
>>>>>>> Stashed changes
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

<<<<<<< Updated upstream
	if (nullptr != mpChangeTex)
	{
		mpChangeTex->SetSize(GetTextrue()->GetSize());
=======
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
>>>>>>> Stashed changes
		CTexture* temp = mpChangeTex;
		mpChangeTex = GetTextrue();
		SetTextrue(temp);
	}
}


<<<<<<< Updated upstream

=======
>>>>>>> Stashed changes
void CBtnUI::SetClickedCallBack(CScene* scene, SCENE_FUNC func)
{
	mSceneFunc = func;
	mScene = scene;
}

<<<<<<< Updated upstream
void CBtnUI::ApplyAlphaBlend(HDC _dc, int _alpha)
{
	Vec2 vSize = GetScale();
	Vec2 vPos = GetFinalPos();
=======
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


void CBtnUI::ApplyAlphaBlend(HDC _dc, int _alpha)
{
	Vect2 vSize = GetScale();
	Vect2 vPos = GetFinalPos();
>>>>>>> Stashed changes
	mpVeilTex = CResMgr::GetI()->CreateTexture(L"VeilTex", (UINT)vSize.x, (UINT)vSize.y, RGB(0, 0, 0));

	BLENDFUNCTION bf = {};

	bf.BlendOp = AC_SRC_OVER;
	bf.BlendFlags = 0;
	bf.AlphaFormat = 0;
	bf.SourceConstantAlpha = _alpha;

	AlphaBlend(_dc
<<<<<<< Updated upstream
		, (int)vPos.x
		, (int)vPos.y
		, (int)mpVeilTex->Width(), (int)mpVeilTex->Heigth()
		, mpVeilTex->GetDC()
		, 0, 0
		, (int)mpVeilTex->Width(), (int)mpVeilTex->Heigth(), bf);
=======
		, (int)vPos.x - vSize.x * 0.5f
		, (int)vPos.y - vSize.y * 0.5f
		, (int)vSize.x
		, (int)vSize.y
		, mpVeilTex->GetDC()
		, 0, 0
		, (int)mpVeilTex->Width()
		, (int)mpVeilTex->Heigth(), bf);
>>>>>>> Stashed changes
}
