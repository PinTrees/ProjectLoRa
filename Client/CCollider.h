#pragma once

class CObject;

class CCollider
{
private:
	static UINT giNextID;

	CObject*	mpOwner;		// collider  를 소유하고 있는 오브젝트
	Vec2		mvOffsetPos;	// 오브젝트로 부터 상대적인 위치
	Vec2		mvFinalPos;		// finalupdate 에서 매프레임마다 계산
	Vec2		mvScale;		// 충돌체의 크기정보

	UINT		miID;			// 충돌체 고유한 ID 값
public:
	void SetOffsetPos(Vec2 _vPos) { mvOffsetPos = _vPos; }
	void SetScale(Vec2 _vScale) { mvScale= _vScale; }

	Vec2 GetOffsetPos() { return mvOffsetPos; }
	Vec2 GetScale() { return mvScale; }
	
	UINT GetID() { return miID; }

public:
	void FinalUpdate();
	void Render(HDC _dc);

	//대입연산자 operator 삭제
	CCollider& operator	 =(CCollider& _origin) = delete;
public:
	CCollider();
	CCollider(const CCollider& _origin);
	~CCollider();

	friend class CObject;
};

