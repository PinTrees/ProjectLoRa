#include "pch.h"
#include "Boss.h"
#include "CCollider.h"
#include "Environment.h"
#include "Monster.h"

Boss::Boss(const wstring& uid)
	: Monster(uid)
{

}

Boss::~Boss()
{
}

void Boss::OnCollisionEnter(CCollider* _pOther)
{
	CObject* pOtherObj = _pOther->GetObj();
	if (pOtherObj->GetName() == L"ENV")
	{
		((Environment*)pOtherObj)->DistoryEnvi();

	}
	
}


