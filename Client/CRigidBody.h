#pragma once
#include "CCompnent.h"

class CObject;

class CRigidBody 
	:public CCompnent
{
private: 

	Vect2	mvForce;		// ũ��, ����
	Vect2	mvAccel;		// ���ӵ� 
	Vect2	mvAccelAlpha;	// �߰� ���ӵ�
	Vect2	mvVelocity;		// �ӵ� (ũ�� : �ӷ�, ����)
	Vect2	mvMaxVelocity;	// �ִ� �ӵ� (ũ�� : �ӷ�, ����)

	float	mMass;			// ���� 
	float	mFrictCoeff;	// ���� ���

	bool	mKinematic;	// ������ ���� ����


public:
	virtual void Update() override;
	virtual void FinalUpdate() override;


private:
	void Move();


public:
	void	AddForce(Vect2 force);
	void	AddVeloctiy(Vect2 velocity) { mvVelocity += velocity; }


public:
	void	SetMess(float mass) { mMass = mass; }
	void	SetVelocity(Vect2 velocity) { mvVelocity = velocity; }
	void	SetMaxVelocity(Vect2 maxVelocity) { mvMaxVelocity = maxVelocity; }
	void	SetAccelAlpha(Vect2 accelAlpha) { mvAccelAlpha = accelAlpha; }

	float	GetMass() { return mMass; }
	Vect2	GetVelocity() { return mvVelocity; }
	Vect2	GetMaxVelocity() { return mvMaxVelocity; }
	float	GetSpeed() { return mvVelocity.Length(); }

	void	SetKinematic(bool active) { mKinematic = active; }
	bool	IsKinematic() { return mKinematic; }


public:
	CRigidBody();
	virtual ~CRigidBody();

	friend class CObject;
};

