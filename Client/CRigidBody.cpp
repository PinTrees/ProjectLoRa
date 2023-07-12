#include "pch.h"
#include "CRigidBody.h"

#include "CTimeMgr.h"
#include "CObject.h"

CRigidBody::CRigidBody()
	: mMass(1.f)
	, mFrictCoeff(200.f)
	, mvMaxVelocity(Vect2(400.f, 1200.f))
	, mKinematic(false)
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
	mvAccel += mvAccelAlpha; // 추가 가속도를 더한다.

	// Calculate Velocity From Final Accel With DT
	mvVelocity += mvAccel * DT;

	// Have Velocity
	if (mvVelocity != Vect2::zero)
	{
		// Velocity Flip Direction
		Vect2 vel = mvVelocity;
		vel.Normalize();

		Vect2 friction = (vel * -1.f) * mFrictCoeff * DT;

		// Friction Over Velocity
		if (mvVelocity.Length() <= friction.Length())
		{
			mvVelocity = Vect2(0.f, 0.f);
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
	mvForce = Vect2(0.f, 0.f);			// 힘 초기화
	mvAccelAlpha = Vect2(0.f, 0.f);		// 추가 가속도 누적량 초기화
	mvAccel = Vect2(0.f, 0.f);			// 가속도 초기화
}

void CRigidBody::Move()
{
	// Speed
	float speed = mvVelocity.Length();

	if (0.f == speed)
		return;

	// Force Direction
	Vect2 dir = mvVelocity;
	dir.Normalize();

	Vect2 pos = GetO()->GetPos();
	pos += dir * speed * DT;

	GetO()->SetPos(pos);
}


void CRigidBody::AddForce(Vect2 force)
{
	if (mKinematic)
		return;

	mvForce += force; 
}

