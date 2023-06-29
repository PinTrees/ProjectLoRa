#include "pch.h"
#include "CObject.h"
#include "CKeyMgr.h"
#include "CTimeMgr.h"


#include "CCollider.h"


CObject::CObject()
	: m_vPos{}
	, m_vScale{}
	, mpCollider(nullptr)
{
}

CObject::~CObject()
{
	if (nullptr != mpCollider)
	{
		delete mpCollider;
	}
}



void CObject::FinalUpdate()
{
	if (mpCollider)
		mpCollider->FinalUpdate();
}

void CObject::Render(HDC _dc)
{
	Rectangle(_dc,	(int)(m_vPos.x - m_vScale.x / 2.f),
					(int)(m_vPos.y - m_vScale.y / 2.f),
					(int)(m_vPos.x + m_vScale.x / 2.f),
					(int)(m_vPos.y + m_vScale.y / 2.f));

	CompnentRender(_dc);

}

void CObject::CompnentRender(HDC _dc)
{
	if (nullptr != mpCollider)
	{
		mpCollider->Render(_dc);
	}
}

void CObject::CreateCollider()
{
	mpCollider = new CCollider;
	mpCollider->mpOwner = this;

}