#include "pch.h"
#include "CRigidBody.h"

#include "CTimeMgr.h"
#include "CObject.h"

CRigidBody::CRigidBody()
	:mpOwner(nullptr)
	, mfMass(1.f)
	, mfFricCoeff(100.f)
	, mfMaxSpeed(200.f)
{

}

CRigidBody::~CRigidBody()
{

}


void CRigidBody::FinalUpdate()
{
	// 힘의크기
	float fForce = mvForce.Length();

	if (0.f != fForce)
	{
		// 힘의 방향
		mvForce.Normalize();

		//가속도의 크기
		float mfAccel = fForce / mfMass;

		//가속도
		mvAccel = mvForce * mfAccel;// mvForce / mfMass;

		// 속도
		mvVelocity += mvAccel * fDT;
	}

	// 마찰력 적용
	if (!mvVelocity.IsZero())
	{
		Vec2 vFricDir = -mvVelocity;
		vFricDir.Normalize();
		Vec2 vFriction = vFricDir * mfFricCoeff * fDT;
		if (mvVelocity.Length() <= vFriction.Length())
		{
			// 마찰가속도가 본래 속도보다 더 큰 경우
			mvVelocity = Vec2(0.f, 0.f);
		}
		else
		{
			mvVelocity += vFriction;
		}
	}
	
	// 속도 제한 검사
	if (mfMaxSpeed < mvVelocity.Length())
	{
		mvVelocity.Normalize();
		mvVelocity *= mfMaxSpeed;
	}

	// 속도에 따른 이동
	Move();

	// 힘 초기화
	mvForce = Vec2(0.f, 0.f);
}

void CRigidBody::Move()
{
	// 이동 속력
	float fSpeed = mvVelocity.Length();

	if (0.f != fSpeed)
	{
		// 이동방향
		Vec2 vDir = mvVelocity;
		vDir.Normalize();
		Vec2 vPos = mpOwner->GetPos();
		vPos += mvVelocity * fDT;
		mpOwner->SetPos(vPos);
	}


}