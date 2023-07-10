#pragma once

class CObject;

class CRigidBody
{
private:
	CObject* mpOwner;

	Vec2		mvForce;		//	ũ��, ����
	Vec2		mvAccel;		//	���ӵ�
	Vec2		mvVelocity;		//	�ӵ� ( ũ�� : �ӷ�, ����)

	float		mfMass;			//	����
	float		mfFricCoeff;	//	���� ���
	float		mfMaxSpeed;		//	�ִ�ӷ�

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

