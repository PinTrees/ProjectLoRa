#pragma once

class CObject;

class CRigidBody
{
private: 
	CObject* mpOwner;

<<<<<<< Updated upstream
	Vec2	mvForce;		// 크기, 방향
	Vec2	mvAccel;		// 가속도 
	Vec2	mvAccelAlpha;	// 추가 가속도
	Vec2	mvVelocity;		// 속도 (크기 : 속력, 방향)
	Vec2	mvMaxVelocity;	// 최대 속도 (크기 : 속력, 방향)
=======
	Vect2	mvForce;		// 크기, 방향
	Vect2	mvAccel;		// 가속도 
	Vect2	mvAccelAlpha;	// 추가 가속도
	Vect2	mvVelocity;		// 속도 (크기 : 속력, 방향)
	Vect2	mvMaxVelocity;	// 최대 속도 (크기 : 속력, 방향)
>>>>>>> Stashed changes

	float	mMass;			// 질량 
	float	mFrictCoeff;	// 마찰 계수

	bool	mKinematic;	// 포지션 고정 여부


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

