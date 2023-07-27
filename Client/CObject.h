#pragma once
#include "CCamera.h"

class CCollider;
class CAnimator;
class CRigidBody;




class CObject
{
private:
	// Tag
	wstring		mStrName;

	// Vector pos, size, offset
	Vect2		mvPos;
	Vect2		mvScale;
	Vect2		mvPivot;	

	Vect2		mvTargetPos;
	// Rotation
	float		mAngle;
	float		mAngleOffset;

	// Alpha
	UINT		mAlpha;

	// Components
	CCollider* mpCollider;
	CAnimator* mpAnimator;
	CRigidBody* mpRigidBody;

	bool		mbAlive;
	bool		mVisible;
	bool		mFlip;
	
	
public:
	void SetPos(Vect2 _vPos)		{ mvPos = _vPos; }
	void SetScale(Vect2 _vScale) { mvScale = _vScale; }
	void SetTarget(Vect2 _TargetPos) { mvTargetPos = _TargetPos; }
	void SetPivot(Vect2 _vPivot) { mvPivot = _vPivot; }
	void SetAngle(float _angle) { mAngle = _angle; }
	void SetAngleOffset(float _angle) { mAngleOffset = _angle; }

	Vect2 GetPos() { return mvPos; }
	Vect2 GetScale() { return mvScale; }
	Vect2 GetPivot() { return mvPivot; }
	Vect2 GetLocalPos() { return mvPos + mvPivot; }
	float GetAngle() { return mAngle + mAngleOffset; }
	float GetAngleOrg() { return mAngle; }

	void SetFlip(bool _f) { mFlip = _f; }
	bool GetFlip() { return mFlip; }

	void SetAlpha(int alpha) { mAlpha = alpha; }
	int GetAlpha() { return (int)mAlpha; }

	void SetVisible(bool _visible) { mVisible = _visible; }
	bool IsVisible() { return mVisible; }

	void SetName(const wstring& _strName) { mStrName = _strName; }
	const wstring& GetName() { return mStrName; }

	CCollider* GetCollider() { return mpCollider; }
	CAnimator* GetAnimator() { return mpAnimator; }
	CRigidBody* GetRigidBody() { return mpRigidBody; }

	bool	IsDead() { return !mbAlive; }

	// Component Create Function
	void CreateCollider();
	void CreateAnimator();
	void CreateRigidBody();

	// Collision Point Function
	virtual void OnCollisionStay(CCollider* _pOther) {}		// In Collision
	virtual void OnCollisionEnter(CCollider* _pOther) {}	// Start Collision
	virtual void OnCollisionExit(CCollider* _pOther) {}		// Exit Collision

	// Life Cycle Point Function
	virtual void OnStart() {}		// Initailization
	virtual void OnDestroy() {}		// Decommissioning


private:
	virtual void SetDead() { mbAlive = false; }


public:
	virtual void Update() = 0;		// Object Game Logic
	virtual void FinalUpdate();		// End Of Frame
	virtual void Render(HDC _dc);	// Scene Rendering
	void CompnentRender(HDC _dc);	// Object Component Rendering

	virtual CObject* Clone() = 0;


public:
	CObject();
	CObject(const CObject& _origin);
	virtual ~CObject();

	friend class CEventMgr;
	friend class CUI;
};

