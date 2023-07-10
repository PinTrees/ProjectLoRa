#pragma once

class CObject;

class CRigidBody
{
private:
	CObject* mpOwner;

	Vec2		mvForce;		//	크기, 방향
	Vec2		mvAccel;		//	가속도
	Vec2		mvVelocity;		//	속도 ( 크기 : 속력, 방향)

	float		mfMass;			//	질량
	float		mfFricCoeff;	//	마찰 계수
	float		mfMaxSpeed;		//	최대속력

	// F = M*A
	// V += A * DT


public:
	void FinalUpdate();

public:
	void AddForce(Vec2 _vF) { mvForce += _vF; }

	void SetMass(float _fMass) { mfMass = _fMass; }
	float GetMass() { return mfMass; }


	void SetVelocity(Vec2 _v) { mvVelocity = _v; }
	void AddVelocity(Vec2 _v) { mvVelocity += _v; }
	void SetMaxVelocity(float _s) { mfMaxSpeed = _s; }
private:
	void Move();



public:

	CRigidBody();
	~CRigidBody();

	friend class CObject;
};

