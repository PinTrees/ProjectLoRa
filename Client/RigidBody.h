#pragma once

class CObject;

class CRigidBody
{
private: 
	CObject* mpOwner;

	Vec2	mvForce;		// 크기, 방향
	Vec2	mvAccel;		// 가속도 
	Vec2	mvAccelAlpha;	// 추가 가속도
	Vec2	mvVelocity;		// 속도 (크기 : 속력, 방향)
	Vec2	mvMaxVelocity;	// 최대 속도 (크기 : 속력, 방향)


	float	mMass;			// 질량 
	float	mFrictCoeff;	// 마찰 계수

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
		mvForce += force;
	}


public:
	void SetMess(float mass) { mMass = mass; }
	void SetVelocity(Vec2 velocity) { mvVelocity = velocity; }
	void AddVeloctiy(Vec2 velocity) { mvVelocity += velocity; }
	void SetMaxVelocity(Vec2 maxVelocity) { mvMaxVelocity = maxVelocity; }
	void SetAccelAlpha(Vec2 accelAlpha) { mvAccelAlpha = accelAlpha; }


public:
	float	GetMass() { return mMass; }
	Vec2	GetVelocity() { return mvVelocity; }
	Vec2	GetMaxVelocity() { return mvMaxVelocity; }
	float	GetSpeed() { return mvVelocity.Length(); }

	friend class CObject;
};

