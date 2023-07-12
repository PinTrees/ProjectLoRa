#include "pch.h"
#include "CCollider.h"

#include "CObject.h"
#include "CCore.h"
#include "CCamera.h"

#include "SelectGDI.h"
#include "CTimeMgr.h"

// Include Components
#include "CRigidBody.h"

UINT CCollider::giNextID = 0;

CCollider::CCollider()
	
	: miID(giNextID++)
	, miCol(0)
	, mIsTrigger(true)
{
}

CCollider::CCollider(const CCollider& _origin)
	
	: mvOffsetPos(_origin.mvOffsetPos)
	, mvScale(_origin.mvScale)
	, miID(giNextID++)
	, miCol(0)
	, mIsTrigger(_origin.mIsTrigger)
{
}

CCollider::~CCollider()
{
}


void CCollider::FinalUpdate()
{
	// object의 위치를 따라간다.
	Vect2 vObejctPos = GetO()->GetPos();
	mvFinalPos = vObejctPos + mvOffsetPos;

	assert(0 <= miCol);
}

void CCollider::Render(HDC _dc)
{
	if (!DEBUG)
		return;

	SelectGDI p(_dc, miCol > 0 ? PEN_TYPE::RED : PEN_TYPE::GREEN);
	SelectGDI b(_dc, BRUSH_TYPE::HOLLOW);

	Vect2 vRenderPos = CCamera::GetI()->GetRenderPos(mvFinalPos);

	Rectangle(_dc
		, (int)(vRenderPos.x - mvScale.x * 0.5f)
		, (int)(vRenderPos.y - mvScale.y * 0.5f)
		, (int)(vRenderPos.x + mvScale.x * 0.5f)
		, (int)(vRenderPos.y + mvScale.y * 0.5f));
}




void CCollider::OnCollisionStay(CCollider* _pOther)
{
	GetO()->OnCollisionStay(_pOther);

	if (!mIsTrigger && !_pOther->GetTrigger() 
		&& GetO()->GetRigidBody())
	{
		if (GetO()->GetRigidBody()->IsKinematic())
			return;

		Vect2 vDis = (GetO()->GetLocalPos() - _pOther->GetObj()->GetLocalPos()).Normalize();
		GetO()->SetPos(GetO()->GetPos() + vDis * 100.f * DT);
		//mpOwner->GetRigidBody()->AddForce(vDis * 100.f);
	}
}

void CCollider::OnCollisionEnter(CCollider* _pOther)
{
	++miCol;
	GetO()->OnCollisionEnter(_pOther);
}

void CCollider::OnCollisionExit(CCollider* _pOther)
{
	--miCol;
	GetO()->OnCollisionExit(_pOther);

}

