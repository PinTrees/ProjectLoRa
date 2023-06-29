#pragma once

class CObject;

class CScene
{
private:
	vector<CObject*> mArrObj[(UINT)GROUP_TYPE::END];
	wstring				m_strName; //Scene 이름

public:
	void SetName(const wstring& _strName) { m_strName = _strName; }
	const wstring& GetName() { return m_strName; }

	void Update();
	void FinalUpdate();
	void Render(HDC _dc);

	virtual void Enter() = 0; //해당 씬 진입시 호출
	virtual void Exit() = 0;  // 해당씬 탈출시 호출

public:
	void AddObject(CObject* _pObj, GROUP_TYPE _eType);
	void DeleteObject(CObject* _pObj, GROUP_TYPE _eType);

	const vector<CObject*>& GetGroupObject(GROUP_TYPE _eTYpe) { return mArrObj[(UINT)_eTYpe]; }

public:
	CScene();
	virtual ~CScene();
};

