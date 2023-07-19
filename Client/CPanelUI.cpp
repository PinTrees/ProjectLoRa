#include "pch.h"
#include "CPanelUI.h"
#include "CKeyMgr.h"

#include "CTexture.h"




CPanelUI::CPanelUI()
	: CUI(false)
	, mpTex(nullptr)
	, mFixedPos(true)
{
}

CPanelUI::~CPanelUI()
{
}


void CPanelUI::Update()
{
	CUI::Update();
}

void CPanelUI::Render(HDC dc)
{
	CUI::Render(dc);

	Vect2 vPos = IsCameraAffected() ? CCamera::GetI()->GetRenderPos(GetFinalPos()) : GetFinalPos();
	Vect2 vScale = GetScale();

	if (mpTex)
	{
		TransparentBlt(dc
			, (int)(vPos.x - vScale.x * 0.5f)
			, (int)(vPos.y - vScale.y * 0.5f)
			, (int)vScale.x
			, (int)vScale.y
			, mpTex->GetDC()
			, 0, 0
			, (int)mpTex->Width()
			, (int)mpTex->Heigth()
			, RGB(255, 0, 255));
	}

	CUI::RenderChild(dc);
}

void CPanelUI::MouseOn()
{
	if (mFixedPos)
		return;

	if (IsLbtnDown())
	{
	 	Vect2 vDiff = (MOUSE_POS - mvDragStartPos);

		Vect2 vCurPos = GetPos();
		vCurPos += vDiff;
		SetPos(vCurPos);
		mvDragStartPos = MOUSE_POS;
	}
}


void CPanelUI::MouseLbtnDown()
{
	mvDragStartPos = MOUSE_POS;
}


void CPanelUI::MouseLbtnUp()
{

}
