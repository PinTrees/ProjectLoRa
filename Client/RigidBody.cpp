#include "pch.h"
#include "RigidBody.h"

#include "CTimeMgr.h"
#include "CObject.h"

CRigidBody::CRigidBody()
	: mpOwner(nullptr)
	, mMass(1.f)
	, mFrictCoeff(200.f)
<<<<<<< Updated upstream
	, mvMaxVelocity(Vec2(400.f, 1200.f))
=======
	, mvMaxVelocity(Vect2(400.f, 1200.f))
>>>>>>> Stashed changes
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
<<<<<<< Updated upstream
	if (mvVelocity != Vec2::zero)
	{
		// Velocity Flip Direction
		Vec2 vel = mvVelocity;
		vel.Normalize();

		Vec2 friction = (vel * -1.f) * mFrictCoeff * DT;
=======
	if (mvVelocity != Vect2::zero)
	{
		// Velocity Flip Direction
		Vect2 vel = mvVelocity;
		vel.Normalize();

		Vect2 friction = (vel * -1.f) * mFrictCoeff * DT;
>>>>>>> Stashed changes

		// Friction Over Velocity
		if (mvVelocity.Length() <= friction.Length())
		{
<<<<<<< Updated upstream
			mvVelocity = Vec2(0.f, 0.f);
=======
			mvVelocity = Vect2(0.f, 0.f);
>>>>>>> Stashed changes
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
<<<<<<< Updated upstream
	mvForce = Vec2(0.f, 0.f);			// 힘 초기화
	mvAccelAlpha = Vec2(0.f, 0.f);		// 추가 가속도 누적량 초기화
	mvAccel = Vec2(0.f, 0.f);			// 가속도 초기화
=======
	mvForce = Vect2(0.f, 0.f);			// 힘 초기화
	mvAccelAlpha = Vect2(0.f, 0.f);		// 추가 가속도 누적량 초기화
	mvAccel = Vect2(0.f, 0.f);			// 가속도 초기화
>>>>>>> Stashed changes
}

void CRigidBody::Move()
{
	// Speed
	float speed = mvVelocity.Length();

	if (0.f == speed)
		return;

	// Force Direction
<<<<<<< Updated upstream
	Vec2 dir = mvVelocity;
	dir.Normalize();

	Vec2 pos = mpOwner->GetPos();
=======
	Vect2 dir = mvVelocity;
	dir.Normalize();

	Vect2 pos = mpOwner->GetPos();
>>>>>>> Stashed changes
	pos += dir * speed * DT;

	mpOwner->SetPos(pos);
}


<<<<<<< Updated upstream
void CRigidBody::AddForce(Vec2 force)
=======
void CRigidBody::AddForce(Vect2 force)
>>>>>>> Stashed changes
{
	if (mKinematic)
		return;

	mvForce += force; 
}

