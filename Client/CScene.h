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

class CScene
{
protected:
	vector<CObject*> mArrObj[(UINT)GROUP_TYPE::END];

private:
	wstring			 mStrName;		//Scene 이름

	// 씬 오브젝트 물리 폭발 관리
	vector<tForce>	 mArrForce;


protected:
	void render_parallax(HDC dc);


public:
	void SetName(const wstring& _strName) { mStrName = _strName; }
	const wstring& GetName() { return mStrName; }

	// Life Cycle Point Function
	virtual void Update();			// 매 프레임 마다 호출
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

