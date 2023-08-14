#pragma once


struct tForce
{
	float radius;			// ��� �ݰ�
	float curRadius = 0;	// ���� �ݰ�
	float speed;			// ���� �ӵ�
	float force;			// ���߷�
	Vect2  pos;				// ���� ����
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
	wstring			 mStrName;		//Scene �̸�
	vector<tForce>	 mArrForce;		// �� ������Ʈ ���� ���� ����

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

	// ���� ���� �浹 Ȯ��
	void InitBSP(Vect2 scale, UINT width, UINT height);
	CCollider* FindBSPObj(UINT w, UINT h, UINT idx, CCollider* col);
	void AddBSPObj(UINT w, UINT h, UINT idx, CCollider* col);
	void RemoveBSPObj(UINT w, UINT h, UINT idx, CCollider* col);

	bool IsBSP() { return mbBSP; }
	UINT GetBspWidth() { return mBspWidth; }
	UINT GetBspHeight() { return mBspHeight; }

	const unordered_map<UINT, CCollider*>& GetCollisionGropObject(UINT x, UINT y, UINT idx) { return mCollisionHashMap[x][y][idx]; }


	// Life Cycle Point Function -------------------------------------
	virtual void Update();			// �� ������ ���� ȣ��
	virtual void UpdateUI();
	virtual void FinalUpdate();		// �� ������ ������ ���� ȣ��
	virtual void Render(HDC _dc);	// �� ������ ������ ���� ȣ��
	
	virtual void Enter() = 0;		// �� ���Խ� ȣ��
	virtual void Exit() = 0;		// �� Ż��� ȣ��


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

