#include "pch.h"
#include "CMonster.h"

#include "AI.h"	

#include "CTimeMgr.h"
#include "CCollider.h"


CMonster::CMonster()
	:mpAI(nullptr)
	, mtInfo{}
{
	CreateCollider();
	GetCollider()->SetScale(Vec2(40.f, 40.f));
}

CMonster::~CMonster()
{
	if (nullptr != mpAI)
		delete mpAI;
}




void CMonster::Update()
{
	if (nullptr != mpAI)
	mpAI->Update();



}

void CMonster::SetAI(AI* _ai)
{
	mpAI = _ai;
	mpAI->mpOwner = this;
}

void CMonster::OnCollisionEnter(CCollider* _pOther)
{
	CObject* pOtherObj = _pOther->GetObj();

	if (pOtherObj->GetName() == L"Missile_Player")
	{
		
	}
	//
}

