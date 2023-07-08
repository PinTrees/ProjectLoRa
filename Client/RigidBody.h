#pragma once

class CObject;

class CRigidBody
{
private: 
	CObject* mpOwner;

	Vec2	mvForce;		// ũ��, ����
	Vec2	mvAccel;		// ���ӵ� 
	Vec2	mvAccelAlpha;	// �߰� ���ӵ�
	Vec2	mvVelocity;		// �ӵ� (ũ�� : �ӷ�, ����)
	Vec2	mvMaxVelocity;	// �ִ� �ӵ� (ũ�� : �ӷ�, ����)

	float	mMass;			// ���� 
	float	mFrictCoeff;	// ���� ���

	bool	mKinematic;	// ������ ���� ����


public:
	void Update();
	void FinalUpdate();


private:
	void Move();


public:
	void	AddForce(Vec2 force);
	void	AddVeloctiy(Vec2 velocity) { mvVelocity += velocity; }


public:
	void	SetMess(float mass) { mMass = mass; }
	void	SetVelocity(Vec2 velocity) { mvVelocity = velocity; }
	void	SetMaxVelocity(Vec2 maxVelocity) { mvMaxVelocity = maxVelocity; }
	void	SetAccelAlpha(Vec2 accelAlpha) { mvAccelAlpha = accelAlpha; }

	float	GetMass() { return mMass; }
	Vec2	GetVelocity() { return mvVelocity; }
	Vec2	GetMaxVelocity() { return mvMaxVelocity; }
	float	GetSpeed() { return mvVelocity.Length(); }

	void	SetKinematic(bool active) { mKinematic = active; }
	bool	IsKinematic() { return mKinematic; }


public:
	CRigidBody();
	~CRigidBody();

	friend class CObject;
};

