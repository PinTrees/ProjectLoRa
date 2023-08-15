#include "pch.h"
#include "CCollider.h"

#include "CObject.h"
#include "CCore.h"
#include "CCamera.h"

#include "SelectGDI.h"
#include "CTimeMgr.h"

// Include Components
#include "RigidBody.h"
#include "CSceneMgr.h"
#include "CScene.h"


UINT CCollider::giNextID = 0;

CCollider::CCollider()
	:mpOwner(nullptr)
	, miID(giNextID++)
	, miCol(0)
	, mIsTrigger(true)
	, mIsActive(true)
{
}

CCollider::CCollider(const CCollider& _origin)
	:mpOwner(nullptr)
	, mvOffsetPos(_origin.mvOffsetPos)
	, mvScale(_origin.mvScale)
	, miID(giNextID++)
	, miCol(0)
	, mIsTrigger(_origin.mIsTrigger)
	, mIsActive(_origin.mIsActive)
{
}

CCollider::~CCollider()
{
}


void CCollider::FinalUpdate()
{
	// object의 위치를 따라간다.
	Vect2 vObejctPos = mpOwner->GetPos();
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
	if (mIsActive && _pOther->GetActive())
	{
		mpOwner->OnCollisionStay(_pOther);
	}

	if (!mIsTrigger && !_pOther->GetTrigger() 
		&& mpOwner->GetRigidBody())
	{
		if (mpOwner->GetRigidBody()->IsKinematic())
			return;

		Vect2 vDis = (mpOwner->GetLocalPos() - _pOther->GetObj()->GetLocalPos()).Normalize();
		mpOwner->GetRigidBody()->AddForce(vDis * 100.f);
	}
}

void CCollider::OnCollisionEnter(CCollider* _pOther)
{
	++miCol;
	if (mIsActive && _pOther->GetActive())
	{
		mpOwner->OnCollisionEnter(_pOther);
	}
}

void CCollider::OnCollisionExit(CCollider* _pOther)
{
	--miCol;
	if (mIsActive && _pOther->GetActive())
	{
		mpOwner->OnCollisionExit(_pOther);
	}
}

