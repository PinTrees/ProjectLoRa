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
	// ���� ���� ũ��
	float force = _force.Length();

	if (0.f != force)
	{
		// ����
		_force.Normalize();

		float accel = force / _mass;

		_accel = _force * accel;
	}

	// ============================================
	// ���� �ֵ� ����  �߰� ���ӵ��� ����� �ؾ��Ѵ�.
	// ============================================
	_accel += _accelAlpha; // �߰� ���ӵ��� ���Ѵ�.

	 // �ӵ� (���� + �ӷ�) �ѹ� ���� �ӵ��� �ʱ�ȭ �� �ʿ䰡 ����.
	_velocity += _accel * fDT;

	// =================
	// ������ ����
	// =================
	// �����¿� ���� �ݴ���������� ���ӵ�
	if (_velocity != Vec2::zero)
	{
		Vec2 vel = _velocity;
		vel.Normalize();
		Vec2 friction = (vel * -1.f) * _frictCoeff * fDT;

		if (_velocity.Length() <= friction.Length())
		{
			// ���� ���ӵ��� ���� �ӵ����� �� ū ���
			_velocity = Vec2(0.f, 0.f);
		}
		else
		{
			_velocity += friction;
		}
	}

	// �ִ�ӵ� ���� (�ӵ� ���� �˻�)
	if (abs(_maxVelocity.x) < abs(_velocity.x))
	{
		_velocity.x = (_velocity.x / abs(_velocity.x)) * abs(_maxVelocity.x);
	}

	if (abs(_maxVelocity.y) < abs(_velocity.y))
	{
		_velocity.y = (_velocity.y / abs(_velocity.y)) * abs(_maxVelocity.y);
	}

	Move();

	// �� �ʱ�ȭ
	_force = Vec2(0.f, 0.f);

	// �߰� ���ӵ� ������ �ʱ�ȭ
	_accelAlpha = Vec2(0.f, 0.f);

	// ���ӵ� �ʱ�ȭ
	_accel = Vec2(0.f, 0.f);
}

void CRigidBody::Move()
{
	// �̵� �ӷ�
	float speed = _velocity.Length();

	if (0.f != speed)
	{
		// �̵� ����
		Vec2 dir = _velocity;
		dir.Normalize();

		Vec2 pos = p_owner->GetPos();
		pos += dir * speed * fDT;

		p_owner->SetPos(pos);
	}
}