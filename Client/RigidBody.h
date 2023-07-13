#pragma once

class CObject;

class CRigidBody
{
private: 
	CObject* mpOwner;

<<<<<<< Updated upstream
	Vec2	mvForce;		// ũ��, ����
	Vec2	mvAccel;		// ���ӵ� 
	Vec2	mvAccelAlpha;	// �߰� ���ӵ�
	Vec2	mvVelocity;		// �ӵ� (ũ�� : �ӷ�, ����)
	Vec2	mvMaxVelocity;	// �ִ� �ӵ� (ũ�� : �ӷ�, ����)
=======
	Vect2	mvForce;		// ũ��, ����
	Vect2	mvAccel;		// ���ӵ� 
	Vect2	mvAccelAlpha;	// �߰� ���ӵ�
	Vect2	mvVelocity;		// �ӵ� (ũ�� : �ӷ�, ����)
	Vect2	mvMaxVelocity;	// �ִ� �ӵ� (ũ�� : �ӷ�, ����)
>>>>>>> Stashed changes

	float	mMass;			// ���� 
	float	mFrictCoeff;	// ���� ���

	bool	mKinematic;	// ������ ���� ����


public:
	void Update();
	void FinalUpdate();


private:
	void Move();


public:
<<<<<<< Updated upstream
	void	AddForce(Vec2 force);
	void	AddVeloctiy(Vec2 velocity) { mvVelocity += velocity; }
=======
	void	AddForce(Vect2 force);
	void	AddVeloctiy(Vect2 velocity) { mvVelocity += velocity; }
>>>>>>> Stashed changes


public:
	void	SetMess(float mass) { mMass = mass; }
<<<<<<< Updated upstream
	void	SetVelocity(Vec2 velocity) { mvVelocity = velocity; }
	void	SetMaxVelocity(Vec2 maxVelocity) { mvMaxVelocity = maxVelocity; }
	void	SetAccelAlpha(Vec2 accelAlpha) { mvAccelAlpha = accelAlpha; }

	float	GetMass() { return mMass; }
	Vec2	GetVelocity() { return mvVelocity; }
	Vec2	GetMaxVelocity() { return mvMaxVelocity; }
=======
	void	SetVelocity(Vect2 velocity) { mvVelocity = velocity; }
	void	SetMaxVelocity(Vect2 maxVelocity) { mvMaxVelocity = maxVelocity; }
	void	SetAccelAlpha(Vect2 accelAlpha) { mvAccelAlpha = accelAlpha; }

	float	GetMass() { return mMass; }
	Vect2	GetVelocity() { return mvVelocity; }
	Vect2	GetMaxVelocity() { return mvMaxVelocity; }
>>>>>>> Stashed changes
	float	GetSpeed() { return mvVelocity.Length(); }

	void	SetKinematic(bool active) { mKinematic = active; }
	bool	IsKinematic() { return mKinematic; }


public:
	CRigidBody();
	~CRigidBody();

	friend class CObject;
};

