#pragma once

class CObject;

class CRigidBody
{
private: 
	CObject* p_owner;

	Vec2	_force;			// ũ��, ����
	Vec2	_accel;			// ���ӵ� 
	Vec2	_accelAlpha;	// �߰� ���ӵ�
	Vec2	_velocity;		// �ӵ� (ũ�� : �ӷ�, ����)
	Vec2	_maxVelocity;	// �ִ� �ӵ� (ũ�� : �ӷ�, ����)

	float	_mass;			// ����
	float	_frictCoeff;	// ���� ���

public:
	CRigidBody();
	~CRigidBody();

public:
	void Update();
	void FinalUpdate();

private:
	void Move();

public:
	void AddForce(Vec2 force)
	{
		_force += force;
	}

	// ������ �� ��� �ӷ��� ���� �Լ�
	void AddVelocity(Vec2 velocity) { _velocity += velocity; }

public:
	void SetMess(float mass) { _mass = mass; }
	void SetVelocity(Vec2 velocity) { _velocity = velocity; }
	void SetMaxVelocity(Vec2 maxVelocity) { _maxVelocity = maxVelocity; }
	void SetAccelAlpha(Vec2 accelAlpha) { _accelAlpha = accelAlpha; }

public:
	float	GetMass() { return _mass; }
	Vec2	GetVelocity() { return _velocity; }
	Vec2	GetMaxVelocity() { return _maxVelocity; }
	float	GetSpeed() { return _velocity.Length(); }

	friend class CObject;
};

