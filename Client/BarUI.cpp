#include "pch.h"
#include "BarUI.h"
#include "SelectGDI.h"
#include "CCamera.h"
#include "CObject.h"


BarUI::BarUI()
	: CUI(false)
{
	SetScale(Vect2(45.f, 6.f));
}


BarUI::~BarUI()
{
}


void BarUI::Update()
{
}


void BarUI::Render(HDC _dc)
{
	SelectGDI b(_dc, BRUSH_TYPE::BLACK);

	Vect2 vRenderPos = GetLocalPos();
	Vect2 vSize = GetScale();

	if (!GetCameraAffected())
	{
		vRenderPos = CCamera::GetI()->GetRenderPos(vRenderPos);
	}

	Rectangle(_dc
		, (int)(vRenderPos.x - vSize.x * 0.5f)
		, (int)(vRenderPos.y - vSize.y * 0.5f)
		, (int)(vRenderPos.x + vSize.x * 0.5f)
		, (int)(vRenderPos.y + vSize.y * 0.5f));

	SelectGDI b1(_dc, NULL, GetColor());

	float amountX = vSize.x * mAmount;

	Rectangle(_dc
		, (int)(vRenderPos.x - vSize.x * 0.5f)
		, (int)(vRenderPos.y - vSize.y * 0.5f)
		, (int)(vRenderPos.x - vSize.x * 0.5f + amountX)
		, (int)(vRenderPos.y + vSize.y * 0.5f));
}


void BarUI::FinalUpdate()
{
}