#include "CBtnUI.h"


CBtnUI::CBtnUI()
	:CUI(false)
	,mpFunc(nullptr)
	,mparam1(0)
	,mparam2(0)
	, mpSceneFunc(nullptr)
	, mpSceneInst(nullptr)
{

}

CBtnUI::~CBtnUI()
{

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

void CBtnUI::MouseLbtnClicked()
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

void CBtnUI::SetClickedCallBack(CScene* _pScene, SCENE_MEMFUNC _pSceneFunc)
{
	mpSceneInst = _pScene;
	mpSceneFunc = _pSceneFunc;
}