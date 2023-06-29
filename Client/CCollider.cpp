#include "pch.h"
#include "CCollider.h"

#include "CObject.h"
#include "CCore.h"
#include "CCamera.h"

#include "SelectGDI.h"

UINT CCollider::giNextID = 0;

CCollider::CCollider()
	:mpOwner(nullptr)
	, miID(giNextID++)
	,miCol(0)
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

	assert(0 <= miCol);
}

void CCollider::Render(HDC _dc)
{
	PEN_TYPE ePen = PEN_TYPE::GREEN;

	if (miCol)
		ePen = PEN_TYPE::RED;

	SelectGDI p(_dc, ePen);
	SelectGDI b(_dc, BRUSH_TYPE::HOLLOW);

	Vec2 vRenderPos = CCamera::GetI()->GetRenderPos(mvFinalPos);

	Rectangle(_dc
		, (int)(vRenderPos.x - mvScale.x / 2.f)
		, (int)(vRenderPos.y - mvScale.y / 2.f)
		, (int)(vRenderPos.x + mvScale.x / 2.f)
		, (int)(vRenderPos.y + mvScale.y / 2.f));

}




void CCollider::OnCollision(CCollider* _pOther)
{
	mpOwner->OnCollision(_pOther);
}

void CCollider::OnCollisionEnter(CCollider* _pOther)
{

	++miCol;
	mpOwner->OnCollisionEnter(_pOther);

}

void CCollider::OnCollisionExit(CCollider* _pOther)
{
	--miCol;
	mpOwner->OnCollisionExit(_pOther);

}

