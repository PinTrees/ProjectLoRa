#include "pch.h"
#include "CHP.h"
#include "SelectGDI.h"
#include "CCamera.h"
#include "CObject.h"


CHP::CHP()
	: mpOwner(nullptr)
	, mvOffset(Vec2(-50.f, -70.f))
	, mvSize(Vec2(45.f, 10.f))
	, mFullHP(0.f)
	, mCurHP(0.f)
{
}

CHP::~CHP()
{
}

void CHP::Update()
{
}

void CHP::Render(HDC _dc)
{
	SelectGDI b(_dc, BRUSH_TYPE::BLACK);

	Vec2 vRenderPos = CCamera::GetI()->GetRenderPos(mvFinalPos);

	Rectangle(_dc
		, (int)(vRenderPos.x)
		, (int)(vRenderPos.y)
		, (int)(vRenderPos.x + mvSize.x)
		, (int)(vRenderPos.y + mvSize.y));

	SelectGDI b1(_dc, BRUSH_TYPE::RED);

	Rectangle(_dc
		, (int)(vRenderPos.x)
		, (int)(vRenderPos.y)
		, (int)(vRenderPos.x + mCurHP)
		, (int)(vRenderPos.y + mvSize.y));
}

void CHP::FinalUpdate()
{
	// object�� ��ġ�� ���󰣴�.
	Vec2 vObejctPos = mpOwner->GetPos();
	mvFinalPos = vObejctPos + mvOffset;

	// �ִ� ü���� ���� ü�¹ٿ��� ������ ���Ѵ�.
	mFullHP = mpOwner->GetFullHP();
	float fRatio = mvSize.x / mFullHP;

	// ���� ü�¿� ������ ���Ѵ�.
	mCurHP = mpOwner->GetHP() * fRatio;
}