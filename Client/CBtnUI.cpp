#include "pch.h"
#include "CBtnUI.h"


CBtnUI::CBtnUI()
	: CUI(false)
	, mSceneFunc(nullptr)
	, mScene(nullptr)
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
}



void CBtnUI::SetClickedCallBack(CScene* scene, SCENE_FUNC func)
{
	mSceneFunc = func;
	mScene = scene;
}
