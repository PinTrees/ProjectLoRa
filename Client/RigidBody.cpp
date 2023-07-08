#include "pch.h"
#include "RigidBody.h"

#include "CTimeMgr.h"
#include "CObject.h"

CRigidBody::CRigidBody()
	: mpOwner(nullptr)
	, mMass(1.f)
	, mFrictCoeff(200.f)
	, mvMaxVelocity(Vec2(400.f, 1200.f))
{
}


CRigidBody::~CRigidBody()
{
}


void CRigidBody::Update()
{

}


void CRigidBody::FinalUpdate()
{
	// Force Vector Size
	float force = mvForce.Length();

	// Have Force
	if (0.f != force)
	{
		// Force Direction Normalize 
		mvForce.Normalize();
		
		// Get Accel 
		float accel = force / mMass;
		mvAccel = mvForce * accel;
	}

	// OffserAccel Calculate
	mvAccel += mvAccelAlpha; // �߰� ���ӵ��� ���Ѵ�.

	// Calculate Velocity From Final Accel With DT
	mvVelocity += mvAccel * fDT;

	// Have Velocity
	if (mvVelocity != Vec2::zero)
	{
		// Velocity Flip Direction
		Vec2 vel = mvVelocity;
		vel.Normalize();

		Vec2 friction = (vel * -1.f) * mFrictCoeff * fDT;

		// Friction Over Velocity
		if (mvVelocity.Length() <= friction.Length())
		{
			mvVelocity = Vec2(0.f, 0.f);
		}
		else
		{
			// Calculate Velocity With Friction
			mvVelocity += friction;
		}
	}

	// Limit Velocity
	if (abs(mvMaxVelocity.x) < abs(mvVelocity.x))
	{
		mvVelocity.x = (mvVelocity.x / abs(mvVelocity.x)) * abs(mvMaxVelocity.x);
	}
	if (abs(mvMaxVelocity.y) < abs(mvVelocity.y))
	{
		mvVelocity.y = (mvVelocity.y / abs(mvVelocity.y)) * abs(mvMaxVelocity.y);
	}

	Move();

	// Clear Force Vector
	mvForce = Vec2(0.f, 0.f);			// �� �ʱ�ȭ
	mvAccelAlpha = Vec2(0.f, 0.f);		// �߰� ���ӵ� ������ �ʱ�ȭ
	mvAccel = Vec2(0.f, 0.f);			// ���ӵ� �ʱ�ȭ
}

void CRigidBody::Move()
{
	// Speed
	float speed = mvVelocity.Length();

	if (0.f == speed)
		return;

	// Force Direction
	Vec2 dir = mvVelocity;
	dir.Normalize();

	Vec2 pos = mpOwner->GetPos();
	pos += dir * speed * fDT;

	mpOwner->SetPos(pos);
}