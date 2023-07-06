#include "CImgBtnUI.h"

#include "CResMgr.h"
#include "CTexture.h"


CImgBtnUI::CImgBtnUI()
	:CUI(false)
	, mpBtnTex(nullptr)
	, mpFunc(nullptr)
	, mparam1(0)
	, mparam2(0)
	, mpSceneFunc(nullptr)
	, mpSceneInst(nullptr)
{

	// texture 로딩하기

	CTexture* mpBtnTex = CResMgr::GetI()->LoadTexture(L"BtnOK", L"texture\\BtnOK.bmp");

}

CImgBtnUI::~CImgBtnUI()
{

}

void CImgBtnUI::MouseOn()
{
}

void CImgBtnUI::MouseLbtnDown()
{
}

void CImgBtnUI::MouseLbtnUp()
{
}

void CImgBtnUI::MouseLbtnClicked()
{
	if (nullptr != mpFunc)
	{
		mpFunc(mparam1, mparam2);
	}

	if (mpSceneInst && mpSceneFunc)
	{
		(mpSceneInst->*mpSceneFunc)();
	}
}

void CImgBtnUI::Render(HDC _dc)
{
	CUI::Render(_dc);
	if (nullptr == mpBtnTex) //텍스쳐가 없으면 안그림
		return;

	UINT iWidth = mpBtnTex->Width();
	UINT iHeight = mpBtnTex->Heigth();


	Vec2	vRenderPos = CCamera::GetI()->GetRenderPos(GetPos());
	Vec2 vScale = GetScale();

	BitBlt(_dc
		, vRenderPos.x
		, vRenderPos.y
		, vScale.x
		, vScale.y
		, mpBtnTex->GetDC()
		, iWidth
		, iHeight
		, SRCCOPY);
}

void CImgBtnUI::SetClickedCallBack(CScene* _pScene, SCENE_MEMFUNC _pSceneFunc)
{
	mpSceneInst = _pScene;
	mpSceneFunc = _pSceneFunc;
}