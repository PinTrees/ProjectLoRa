#include "pch.h"
#include "CObject.h"

#include "CCollider.h"
#include "CAnimator.h"



CObject::CObject()
	: mvPos{}
	, mvScale{}
	, mpCollider(nullptr)
	, mpAnimator(nullptr)
	, mbAlive(true)
{

}

CObject::CObject(const CObject& _origin)
	:mStrName(_origin.mStrName)
	,mvPos(_origin.mvPos)
	,mvScale(_origin.mvScale)
	,mpAnimator(nullptr)
	,mpCollider(nullptr)
	,mbAlive(true)
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
	if (nullptr != mpCollider)
	{
		mpCollider->Render(_dc);
	}

	if (nullptr != mpAnimator)
	{
		mpAnimator->Render(_dc);
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


