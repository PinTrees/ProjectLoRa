#include "pch.h"
#include "CBtnUI.h"



CBtnUI::CBtnUI() 
	:CUI(false)
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
}
