#include "pch.h"
#include "CObject.h"

#include "CCollider.h"
#include "CAnimator.h"
#include "RigidBody.h"
#include "Gravity.h"

#include "SelectGDI.h"




CObject::CObject()
	: mvPos{}
	, mvScale{}
	, mpCollider(nullptr)
	, mpAnimator(nullptr)
	, mbAlive(true)
	, mAngle(0.f)
	, mAngleOffset(0.f)
	, mFlip(false)
	, mVisible(true)
	, mpGravity(nullptr)
	, mpRigidBody(nullptr)
{

}

CObject::CObject(const CObject& _origin)
	: mStrName(_origin.mStrName)
	, mvPos(_origin.mvPos)
	, mvScale(_origin.mvScale)
	, mpAnimator(nullptr)
	, mpCollider(nullptr)
	, mbAlive(true)
	, mAngle(0.f)
	, mAngleOffset(0.f)
	, mFlip(false)
	, mVisible(true)
	, mpGravity(nullptr)
	, mpRigidBody(nullptr)
{
	if (_origin.mpCollider)
	{
		mpCollider = new CCollider(*_origin.mpCollider);
		mpCollider->mpOwner = this;
	}

	if (_origin.mpAnimator)
	{
		mpAnimator = new CAnimator(*_origin.mpAnimator);
		mpAnimator->mpOwner = this;
	}
}

CObject::~CObject()
{
	if (nullptr != mpCollider)
	{
		delete mpCollider;
	}

	if (nullptr != mpAnimator)
	{
		delete mpAnimator;
	}
}



void CObject::FinalUpdate()
{
	if (mpCollider)
		mpCollider->FinalUpdate();
}


void CObject::Render(HDC _dc)
{
	Vec2 vRenderPos = CCamera::GetI()->GetRenderPos(mvPos);

	Rectangle(_dc,	(int)(vRenderPos.x - mvScale.x / 2.f),
					(int)(vRenderPos.y - mvScale.y / 2.f),
					(int)(vRenderPos.x + mvScale.x / 2.f),
					(int)(vRenderPos.y + mvScale.y / 2.f));

	CompnentRender(_dc);
}


void CObject::CompnentRender(HDC _dc)
{
	if (!mVisible)
		return;

	if (nullptr != mpCollider)
	{
		mpCollider->Render(_dc);
	}

	if (nullptr != mpAnimator)
	{
		mpAnimator->Render(_dc);
	}

	SelectGDI p(_dc, PEN_TYPE::RED);
	SelectGDI b(_dc, BRUSH_TYPE::RED);

	Vec2 vRenderPos = CCamera::GetI()->GetRenderPos(mvPos + mvPivot);
	float pivotSize = 6.f;

	Ellipse(_dc
		, (int)(vRenderPos.x - pivotSize * 0.5f)
		, (int)(vRenderPos.y - pivotSize * 0.5f)
		, (int)(vRenderPos.x + pivotSize * 0.5f)
		, (int)(vRenderPos.y + pivotSize * 0.5f));
}

void CObject::CreateCollider()
{
	mpCollider = new CCollider;
	mpCollider->mpOwner = this;
}

void CObject::CreateAnimator()
{
	mpAnimator = new CAnimator;
	mpAnimator->mpOwner = this;
}

void CObject::CreateRigidBody()
{
	mpRigidBody = new CRigidBody();
	mpRigidBody->p_owner = this;
}

void CObject::CreateGravity()
{
	mpGravity = new CGravity();
	mpGravity->p_owner = this;
}

//void CObject::DeleteCollider()
//{
//	if (mpCollider != nullptr)
//	{
//		delete mpCollider;
//	}
//
//	mpCollider = nullptr;
//}


