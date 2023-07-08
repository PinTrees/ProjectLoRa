#include "pch.h"
#include "RigidBody.h"

#include "CTimeMgr.h"
#include "CObject.h"

CRigidBody::CRigidBody()
	:
	p_owner(nullptr),
	_mass(1.f),
	_frictCoeff(250.f),
	_maxVelocity(Vec2(400.f, 1200.f))
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
	// 순수 힘의 크기
	float force = _force.Length();

	if (0.f != force)
	{
		// 방향
		_force.Normalize();

		float accel = force / _mass;

		_accel = _force * accel;
	}

	// ============================================
	// 힘이 있든 없든  추가 가속도를 계산을 해야한다.
	// ============================================
	_accel += _accelAlpha; // 추가 가속도를 더한다.

	 // 속도 (방향 + 속력) 한번 붙은 속도는 초기화 할 필요가 없다.
	_velocity += _accel * fDT;

	// =================
	// 마찰력 적용
	// =================
	// 마찰력에 의한 반대방향으로의 가속도
	if (_velocity != Vec2::zero)
	{
		Vec2 vel = _velocity;
		vel.Normalize();
		Vec2 friction = (vel * -1.f) * _frictCoeff * fDT;

		if (_velocity.Length() <= friction.Length())
		{
			// 마찰 가속도가 본래 속도보다 더 큰 경우
			_velocity = Vec2(0.f, 0.f);
		}
		else
		{
			_velocity += friction;
		}
	}

	// 최대속도 제한 (속도 제한 검사)
	if (abs(_maxVelocity.x) < abs(_velocity.x))
	{
		_velocity.x = (_velocity.x / abs(_velocity.x)) * abs(_maxVelocity.x);
	}

	if (abs(_maxVelocity.y) < abs(_velocity.y))
	{
		_velocity.y = (_velocity.y / abs(_velocity.y)) * abs(_maxVelocity.y);
	}

	Move();

	// 힘 초기화
	_force = Vec2(0.f, 0.f);

	// 추가 가속도 누적량 초기화
	_accelAlpha = Vec2(0.f, 0.f);

	// 가속도 초기화
	_accel = Vec2(0.f, 0.f);
}

void CRigidBody::Move()
{
	// 이동 속력
	float speed = _velocity.Length();

	if (0.f != speed)
	{
		// 이동 방향
		Vec2 dir = _velocity;
		dir.Normalize();

		Vec2 pos = p_owner->GetPos();
		pos += dir * speed * fDT;

		p_owner->SetPos(pos);
	}
}