#pragma once

class CObject;

class CScene
{
private:
	vector<CObject*> mArrObj[(UINT)GROUP_TYPE::END];
	wstring			 m_strName; //Scene �̸�

public:
	void SetName(const wstring& _strName) { m_strName = _strName; }
	const wstring& GetName() { return m_strName; }

	virtual void Update();
	virtual void FinalUpdate();
	virtual void Render(HDC _dc);

	virtual void Enter() = 0; //�ش� �� ���Խ� ȣ��
	virtual void Exit() = 0;  // �ش�� Ż��� ȣ��

public:
	void AddObject(CObject* _pObj, GROUP_TYPE _eType);
	void DeleteObject(CObject* _pObj, GROUP_TYPE _eType);

	const vector<CObject*>& GetGroupObject(GROUP_TYPE _eTYpe) { return mArrObj[(UINT)_eTYpe]; }
	vector<CObject*>& GetUIGroups(const GROUP_TYPE& type) { return mArrObj[static_cast<UINT>(GROUP_TYPE::UI)]; }


	void DeleteGroup(GROUP_TYPE _eTarget);
	void DeleteAll();
public:
	CScene();
	virtual ~CScene();
};

