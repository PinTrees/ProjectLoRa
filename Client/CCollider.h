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
	int			miCol;			
public:
	void SetOffsetPos(Vec2 _vPos) { mvOffsetPos = _vPos; }
	void SetScale(Vec2 _vScale) { mvScale= _vScale; }

	Vec2 GetFinalPos() { return mvFinalPos; }
	Vec2 GetOffsetPos() { return mvOffsetPos; }
	Vec2 GetScale() { return mvScale; }
	
	UINT GetID() { return miID; }

public:
	void FinalUpdate();
	void Render(HDC _dc);

public:
	// 충돌 시점 함수
	void OnCollision(CCollider* _pOther); // 충돌 중인 경우 호출되는 함수
	void OnCollisionEnter(CCollider* _pOther); // 충돌 진입시
	void OnCollisionExit(CCollider* _pOther); // 충돌 해제시




	//대입연산자 operator 삭제
	CCollider& operator	 =(CCollider& _origin) = delete;
public:
	CCollider();
	CCollider(const CCollider& _origin);
	~CCollider();

	friend class CObject;
};

