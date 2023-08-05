#include "pch.h"
#include "CObject.h"

#include "CCollider.h"
#include "CAnimator.h"
#include "RigidBody.h"

#include "SelectGDI.h"




CObject::CObject()
	: mvPos(Vect2::zero)
	, mvScale{}
	, mpCollider(nullptr)
	, mpAnimator(nullptr)
	, mbAlive(true)
	, mAngle(0.f)
	, mAngleOffset(0.f)
	, mFlip(false)
	, mVisible(true)
	, mpRigidBody(nullptr)
	, mAlpha(255)
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
	, mpRigidBody(nullptr)
	, mAlpha(_origin.mAlpha)
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

	if (_origin.mpRigidBody)
	{
		mpRigidBody = new CRigidBody(*_origin.mpRigidBody);
		mpRigidBody->mpOwner = this;
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

	if (nullptr != mpRigidBody)
	{
		delete mpRigidBody;
	}
}



void CObject::FinalUpdate()
{
	if (mpCollider)
		mpCollider->FinalUpdate();
	/*if (mpAnimator)
		mpAnimator->Fi*/
	if (mpRigidBody)
		mpRigidBody->FinalUpdate();
}


void CObject::Render(HDC _dc)
{
	Vect2 vRenderPos = CCamera::GetI()->GetRenderPos(mvPos);

	Rectangle(_dc,	(int)(vRenderPos.x - mvScale.x * 0.5f),
					(int)(vRenderPos.y - mvScale.y * 0.5f),
					(int)(vRenderPos.x + mvScale.x * 0.5f),
					(int)(vRenderPos.y + mvScale.y * 0.5f));

	CompnentRender(_dc);
}


void CObject::CompnentRender(HDC _dc)
{
	if (!mVisible)
		return;

	if (nullptr != mpAnimator)
		mpAnimator->Render(_dc);
	
	if (DEBUG)
	{
		if (nullptr != mpCollider)
			mpCollider->Render(_dc);
	}

	SelectGDI b(_dc, BRUSH_TYPE::RED);
	SelectGDI p(_dc, PEN_TYPE::RED);
	  
	Vect2 vRenderPos = CCamera::GetI()->GetRenderPos(GetLocalPos());
	float pivotSize = 3.f;

	if (DEBUG)
	{
		Ellipse(_dc
			, (int)(vRenderPos.x - pivotSize * 0.5f)
			, (int)(vRenderPos.y - pivotSize * 0.5f)
			, (int)(vRenderPos.x + pivotSize * 0.5f)
			, (int)(vRenderPos.y + pivotSize * 0.5f));
	}
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
	mpRigidBody->mpOwner = this;
}

