#pragma once
#include "global.h"
#include "CCamera.h"

class CCollider;
class CAnimator;

class CObject
{
private:
	wstring		mStrName;

	Vec2		mvPos;
	Vec2		mvScale;

	CCollider*	mpCollider;
	CAnimator*	mpAnimator;

	bool		mbAlive;

public:
	void SetPos(Vec2 _vPos) { mvPos = _vPos; }
	void SetScale(Vec2 _vScale) { mvScale = _vScale; }

	Vec2 GetPos() { return mvPos; }
	Vec2 GetScale() { return mvScale; }

	void SetName(const wstring& _strName) { mStrName = _strName; }
	const wstring& GetName() { return mStrName; }

	CCollider* GetCollider() { return mpCollider; }
	CAnimator* GetAnimator() { return mpAnimator; }

	bool	IsDead() { return !mbAlive; }

	void CreateCollider();
	void CreateAnimator();

	// �浹 ���� �Լ�
	virtual void OnCollision(CCollider* _pOther) {}		// �浹 ���� ��� ȣ��Ǵ� �Լ�
	virtual void OnCollisionEnter(CCollider* _pOther) {}// �浹 ���Խ�
	virtual void OnCollisionExit(CCollider* _pOther) {} // �浹 ������

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

