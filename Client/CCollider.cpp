#include "pch.h"
#include "CCollider.h"

#include "CObject.h"
#include "CCore.h"

#include "SelectGDI.h"

UINT CCollider::giNextID = 0;

CCollider::CCollider()
	:mpOwner(nullptr)
	, miID(giNextID++)
{
}

CCollider::CCollider(const CCollider& _origin)
	:mpOwner(nullptr)
	, mvOffsetPos(_origin.mvOffsetPos)
	, mvScale(_origin.mvScale)
	, miID(giNextID++)
{
}

CCollider::~CCollider()
{
}


void CCollider::FinalUpdate()
{

	// object의 위치를 따라간다.

	Vec2 vObejctPos = mpOwner->GetPos();
	mvFinalPos = vObejctPos + mvOffsetPos;
}

void CCollider::Render(HDC _dc)
{

	SelectGDI p(_dc, PEN_TYPE::GREEN);
	SelectGDI b(_dc, BRUSH_TYPE::HOLLOW);

	Rectangle(_dc
		, mvFinalPos.x - mvScale.x / 2.f
		, mvFinalPos.y - mvScale.y / 2.f
		, mvFinalPos.x + mvScale.x / 2.f
		, mvFinalPos.y + mvScale.y / 2.f);

}

