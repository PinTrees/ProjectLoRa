#pragma once

class CObject;

class CRigidBody
{
private: 
	CObject* p_owner;

	Vec2	_force;			// 크기, 방향
	Vec2	_accel;			// 가속도 
	Vec2	_accelAlpha;	// 추가 가속도
	Vec2	_velocity;		// 속도 (크기 : 속력, 방향)
	Vec2	_maxVelocity;	// 최대 속도 (크기 : 속력, 방향)

	float	_mass;			// 질량
	float	_frictCoeff;	// 마찰 계수

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

	// 움직일 때 즉시 속력을 위한 함수
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

