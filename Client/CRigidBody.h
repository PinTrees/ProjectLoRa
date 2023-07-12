#pragma once
#include "CCompnent.h"

class CObject;

class CRigidBody 
	:public CCompnent
{
private: 

	Vect2	mvForce;		// 크기, 방향
	Vect2	mvAccel;		// 가속도 
	Vect2	mvAccelAlpha;	// 추가 가속도
	Vect2	mvVelocity;		// 속도 (크기 : 속력, 방향)
	Vect2	mvMaxVelocity;	// 최대 속도 (크기 : 속력, 방향)

	float	mMass;			// 질량 
	float	mFrictCoeff;	// 마찰 계수

	bool	mKinematic;	// 포지션 고정 여부


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

