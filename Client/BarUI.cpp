#include "pch.h"
#include "BarUI.h"
#include "SelectGDI.h"
#include "CCamera.h"
#include "CObject.h"

#include "CCore.h"


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
	Vect2 vRenderPos = !IsCameraAffected() ? CCamera::GetI()->GetRenderPos(GetLocalPos() + GetFinalPos()) : GetLocalPos() + GetFinalPos();

	if (!IsCameraAffected())
	{
		Vect2 vRes = CCore::GetI()->GetResolution();
		Vect2 vCamPos = CCamera::GetI()->GetLookAt();
		Vect2 vGap = vRes * 0.1f;
		
		if (vRenderPos.x < -vGap.x || vRenderPos.x > vRes.x + vGap.x
			|| vRenderPos.y < -vGap.y || vRenderPos.y > vRes.y + vGap.y)
		{
			return;
		}
	}

	Vect2 vSize = GetScale();
	float amountX = vSize.x * mFillAmount;

	SelectGDI b(_dc, BRUSH_TYPE::BLACK);

	Rectangle(_dc
		, (int)(vRenderPos.x - vSize.x * 0.5f)
		, (int)(vRenderPos.y - vSize.y * 0.5f)
		, (int)(vRenderPos.x + vSize.x * 0.5f)
		, (int)(vRenderPos.y + vSize.y * 0.5f));

	SelectGDI b1(_dc, NULL, GetColor());

	Rectangle(_dc
		, (int)(vRenderPos.x - vSize.x * 0.5f)
		, (int)(vRenderPos.y - vSize.y * 0.5f)
		, (int)(vRenderPos.x - vSize.x * 0.5f + amountX)
		, (int)(vRenderPos.y + vSize.y * 0.5f));
}


void BarUI::FinalUpdate()
{
}