#include "pch.h"
#include "CCollider.h"

#include "CObject.h"
#include "CCore.h"
#include "CCamera.h"

#include "SelectGDI.h"
#include "CTimeMgr.h"

// Include Components
#include "RigidBody.h"

UINT CCollider::giNextID = 0;

CCollider::CCollider()
	:mpOwner(nullptr)
	, miID(giNextID++)
	, miCol(0)
	, mIsTrigger(true)
{
}

CCollider::CCollider(const CCollider& _origin)
	:mpOwner(nullptr)
	, mvOffsetPos(_origin.mvOffsetPos)
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
	// object�� ��ġ�� ���󰣴�.
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




void CCollider::OnCollisionStay(CCollider* _pOther)
{
	mpOwner->OnCollisionStay(_pOther);

	if (!mIsTrigger && !_pOther->GetTrigger() 
		&& mpOwner->GetRigidBody())
	{
		if (mpOwner->GetRigidBody()->IsKinematic())
			return;

		Vec2 vDis = (mpOwner->GetLocalPos() - _pOther->GetObj()->GetLocalPos()).Normalize();
		mpOwner->SetPos(mpOwner->GetPos() + vDis * 100.f * DT);
		//mpOwner->GetRigidBody()->AddForce(vDis * 100.f);
	}
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

