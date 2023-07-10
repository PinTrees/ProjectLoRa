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
	// ����ũ��
	float fForce = mvForce.Length();

	if (0.f != fForce)
	{
		// ���� ����
		mvForce.Normalize();

		//���ӵ��� ũ��
		float mfAccel = fForce / mfMass;

		//���ӵ�
		mvAccel = mvForce * mfAccel;// mvForce / mfMass;

		// �ӵ�
		mvVelocity += mvAccel * fDT;
	}

	// ������ ����
	if (!mvVelocity.IsZero())
	{
		Vec2 vFricDir = -mvVelocity;
		vFricDir.Normalize();
		Vec2 vFriction = vFricDir * mfFricCoeff * fDT;
		if (mvVelocity.Length() <= vFriction.Length())
		{
			// �������ӵ��� ���� �ӵ����� �� ū ���
			mvVelocity = Vec2(0.f, 0.f);
		}
		else
		{
			mvVelocity += vFriction;
		}
	}
	
	// �ӵ� ���� �˻�
	if (mfMaxSpeed < mvVelocity.Length())
	{
		mvVelocity.Normalize();
		mvVelocity *= mfMaxSpeed;
	}

	// �ӵ��� ���� �̵�
	Move();

	// �� �ʱ�ȭ
	mvForce = Vec2(0.f, 0.f);
}

void CRigidBody::Move()
{
	// �̵� �ӷ�
	float fSpeed = mvVelocity.Length();

	if (0.f != fSpeed)
	{
		// �̵�����
		Vec2 vDir = mvVelocity;
		vDir.Normalize();
		Vec2 vPos = mpOwner->GetPos();
		vPos += mvVelocity * fDT;
		mpOwner->SetPos(vPos);
	}


}