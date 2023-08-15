#pragma once

class CObject;

class CCollider
{
private:
	static UINT giNextID;

	CObject*	mpOwner;		// collider  를 소유하고 있는 오브젝트
	Vect2		mvOffsetPos;	// 오브젝트로 부터 상대적인 위치
	Vect2		mvFinalPos;		// finalupdate 에서 매프레임마다 계산
	Vect2		mvScale;		// 충돌체의 크기정보

	UINT		mBspX;
	UINT		mBspY;

	UINT		miID;			// 충돌체 고유한 ID 값
	int			miCol;			

	bool		mIsTrigger;		// 해당 충돌체의 겹침 여부 
	bool		mIsActive;


public:
	void SetBSP(UINT x, UINT y) { mBspX = x; mBspY = y; };
	UINT GetBSPX() { return mBspX; };
	UINT GetBSPY() { return mBspY; };

	void SetActive(bool _active) { mIsActive = _active; }
	bool GetActive() { return mIsActive; }

	void SetOffsetPos(Vect2 _vPos) { mvOffsetPos = _vPos; }
	void SetScale(Vect2 _vScale) { mvScale= _vScale; }

	void SetTrigger(bool _trigger) { mIsTrigger = _trigger; }
	bool GetTrigger() { return mIsTrigger; }

	Vect2 GetFinalPos() { return mvFinalPos; }
	Vect2 GetOffsetPos() { return mvOffsetPos; }
	Vect2 GetScale() { return mvScale; }
	
	CObject* GetObj() { return mpOwner; }

	UINT GetID() { return miID; }


public:
	void FinalUpdate();
	void Render(HDC _dc);


public:
	// 충돌 시점 함수
	void OnCollisionEnter(CCollider* _pOther); // 충돌 진입시
	void OnCollisionStay(CCollider* _pOther); // 충돌 중인 경우 호출되는 함수
	void OnCollisionExit(CCollider* _pOther); // 충돌 해제시

	//대입연산자 operator 삭제
	CCollider& operator	 =(CCollider& _origin) = delete;


public:
	CCollider();
	CCollider(const CCollider& _origin);
	~CCollider();

	friend class CObject;
};

