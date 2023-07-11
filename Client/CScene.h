#pragma once


struct tForce
{
	float radius;			// 충격 반경
	float curRadius = 0;	// 현재 반경
	float speed;			// 폭발 속도
	float force;			// 폭발력
	Vec2  pos;				// 폭발 지점
};


class CObject;
class Background;

class CScene
{
private:
	vector<CObject*> mArrObj[(UINT)GROUP_TYPE::END];
	wstring			 m_strName; //Scene 이름

	// 씬 오브젝트 물리 폭발 관리
	vector<tForce> mArrForce;


protected:
	void _render_parallax(HDC dc);


public:
	void SetName(const wstring& _strName) { m_strName = _strName; }
	const wstring& GetName() { return m_strName; }

	virtual void Update();
	virtual void FinalUpdate();
	virtual void Render(HDC _dc);

	virtual void Enter() = 0; // 해당 씬 진입시 호출
	virtual void Exit() = 0;  // 해당씬 탈출시 호출


public:
	void AddObject(CObject* _pObj, GROUP_TYPE _eType);
	void AddForce(tForce& force);

	//void DeleteObject(CObject* _pObj, GROUP_TYPE _eType);
	//void DeleteForce(tForce force);

	const vector<CObject*>& GetGroupObject(GROUP_TYPE _eTYpe) { return mArrObj[(UINT)_eTYpe]; }
	vector<CObject*>& GetUIGroups(const GROUP_TYPE& type) { return mArrObj[static_cast<UINT>(GROUP_TYPE::UI)]; }

	void DeleteGroup(GROUP_TYPE _eTarget);
	void DeleteAll();
public:
	CScene();
	virtual ~CScene();
};

