#pragma once


struct tForce
{
	float radius;			// 충격 반경
	float curRadius = 0;	// 현재 반경
	float speed;			// 폭발 속도
	float force;			// 폭발력
	Vect2  pos;				// 폭발 지점
};


class CObject;
class Background;
class CCollider;

class CScene
{
protected:
	vector<CObject*> mArrObj[(UINT)GROUP_TYPE::END];
	vector<vector<vector<unordered_map<UINT, CCollider*>>>> mCollisionHashMap;


private:
	wstring			 mStrName;		//Scene 이름
	vector<tForce>	 mArrForce;		// 씬 오브젝트 물리 폭발 관리

	bool		mbBSP;
	UINT		mGridWidth;
	UINT		mGridHeight;
	UINT		mBspWidth;
	UINT		mBspHeight;
	Vect2		mWorldScale;


protected:
	void render_background(HDC dc);


public:
	void SetName(const wstring& _strName) { mStrName = _strName; }
	const wstring& GetName() { return mStrName; }

	// 공간 분할 충돌 확인
	void InitBSP(Vect2 scale, UINT width, UINT height);
	CCollider* FindBSPObj(UINT w, UINT h, UINT idx, CCollider* col);
	void AddBSPObj(UINT w, UINT h, UINT idx, CCollider* col);
	void RemoveBSPObj(UINT w, UINT h, UINT idx, CCollider* col);

	bool IsBSP() { return mbBSP; }
	UINT GetBspWidth() { return mBspWidth; }
	UINT GetBspHeight() { return mBspHeight; }

	const unordered_map<UINT, CCollider*>& GetCollisionGropObject(UINT x, UINT y, UINT idx) { return mCollisionHashMap[x][y][idx]; }


	// Life Cycle Point Function -------------------------------------
	virtual void Update();			// 매 프레임 마다 호출
	virtual void UpdateUI();
	virtual void FinalUpdate();		// 매 마지막 프레임 마다 호츨
	virtual void Render(HDC _dc);	// 매 렌더링 프레임 마다 호출
	
	virtual void Enter() = 0;		// 씬 진입시 호출
	virtual void Exit() = 0;		// 씬 탈출시 호출


public:
	void AddObject(CObject* _pObj, GROUP_TYPE _eType);
	void AddForce(tForce& force);

	//void DeleteObject(CObject* _pObj, GROUP_TYPE _eType);
	//void DeleteForce(tForce force);

	const vector<CObject*>& GetGroupObject(GROUP_TYPE _eTYpe) { return mArrObj[(UINT)_eTYpe]; }
	vector<CObject*>& GetUIGroups() { return mArrObj[(UINT)GROUP_TYPE::UI]; }

	void DeleteGroup(GROUP_TYPE _eTarget);
	void DeleteAll();


public:
	CScene();
	virtual ~CScene();
};

