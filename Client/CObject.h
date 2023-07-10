#pragma once
#include "CCamera.h"

class CCollider;
class CAnimator;
class CRigidBody;
class CGravity;

class CObject
{
private:
	wstring		mStrName;

	Vec2		mvPos;
	Vec2		mvScale;
	Vec2		mvPivot;	// 오브젝트의 피봇 위치 입니다.

	CCollider* mpCollider;
	CAnimator* mpAnimator;
	CRigidBody* mpRigidBody;
	CGravity*   mpGravity;

	bool		mbAlive;

	/// 변경된 코드
	float		mAngle;
	float		mAngleOffset;

	UINT		mAlpha;
	bool		mFlip;
	bool		mVisible;

public:
	void SetPos(Vec2 _vPos)		{ mvPos = _vPos; }
	void SetScale(Vec2 _vScale) { mvScale = _vScale; }
	void SetPivot(Vec2 _vPivot) { mvPivot = _vPivot; }
	void SetAngle(float _angle) { mAngle = _angle; }
	void SetAngleOffset(float _angle) { mAngleOffset = _angle; }

	Vec2 GetPos() { return mvPos; }
	Vec2 GetScale() { return mvScale; }
	Vec2 GetPivot() { return mvPivot; }
	Vec2 GetLocalPos() { return mvPos + mvPivot; }
	float GetAngle() { return mAngle + mAngleOffset; }

	void SetFlip(bool _f) { mFlip = _f; }
	bool GetFlip() { return mFlip; }

	void SetAlpha(int alpha) { mAlpha = alpha; }
	int GetAlpha() { return (int)mAlpha; }

	void SetVisible(bool _visible) { mVisible = _visible; }
	bool GetVisible() { return mVisible; }

	void SetName(const wstring& _strName) { mStrName = _strName; }
	const wstring& GetName() { return mStrName; }

	CCollider* GetCollider() { return mpCollider; }
	CAnimator* GetAnimator() { return mpAnimator; }
	CRigidBody* GetRigidBody() { return mpRigidBody; }

	bool	IsDead() { return !mbAlive; }

	void CreateCollider();
	void CreateAnimator();
	void CreateRigidBody();
	void CreateGravity();

	//void DeleteCollider();

	// 충돌 시점 함수
	virtual void OnCollisionStay(CCollider* _pOther) {}		// 충돌 중인 경우 호출되는 함수
	virtual void OnCollisionEnter(CCollider* _pOther) {}// 충돌 진입시
	virtual void OnCollisionExit(CCollider* _pOther) {} // 충돌 해제시

	// 시점 함수
	virtual void OnDestroy() {}	// 삭제 시점


private:
	void	SetDead() { mbAlive = false; }


public:
	virtual void Update() = 0;
	virtual void FinalUpdate();
	virtual void Render(HDC _dc);

	void CompnentRender(HDC _dc);

	virtual CObject* Clone() = 0;
public:
	CObject();
	CObject(const CObject& _origin);
	virtual ~CObject();

	friend class CEventMgr;
};

