#include "pch.h"
#include "CMonster.h"

#include "CTimeMgr.h"
#include "CCollider.h"
CMonster::CMonster()
	:m_vCenterPos(Vec2(0.f, 0.f))
	, m_fSpeed(100.f)
	, m_fMaxDistance(50.f)
	,m_iDir(1)
	, mHp(5)
{
	CreateCollider();
	GetCollider()->SetScale(Vec2(40.f, 40.f));
}

CMonster::~CMonster()
{
}




void CMonster::Update()
{
	//***삭제
	return;
	
	Vec2 vCurPos = GetPos(); // 현재 위치는 부모에있는 함수로 받아올수있다.

	SetPos(curvesCircle(m_vCenterPos, 200.f, (fDT * m_fSpeed * m_iDir) * 0.1f));



	// 진행 방향으로 시간당 m_fSpeed 만큼 이동
	vCurPos.x += fDT * m_fSpeed * m_iDir;

	float fDist = abs(m_vCenterPos.x - vCurPos.x) - m_fMaxDistance;


	if ( 0.f< fDist)
	{
		m_iDir *= -1;

		vCurPos.x += fDist * m_iDir;
	}

	SetPos(vCurPos);

}

void CMonster::OnCollisionEnter(CCollider* _pOther)
{
	CObject* pOtherObj = _pOther->GetObj();

	if (pOtherObj->GetName() == L"Missile_Player")
	{
		mHp -= 1;
		if (mHp <= 0)
		{
			DeleteObject(this);
		}
	}
	//
}

