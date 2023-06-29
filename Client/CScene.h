#pragma once

class CObject;

class CScene
{
private:
	vector<CObject*> m_arrObj[(UINT)GROUP_TYPE::END];
	wstring				m_strName; //Scene �̸�

public:
	void SetName(const wstring& _strName) { m_strName = _strName; }
	const wstring& GetName() { return m_strName; }

	void Update();
	void Render(HDC _dc);

	virtual void Enter() = 0; //�ش� �� ���Խ� ȣ��
	virtual void Exit() = 0;  // �ش�� Ż��� ȣ��

public:
	void AddObject(CObject* _pObj, GROUP_TYPE _eType);
	void DeleteObject(CObject* _pObj, GROUP_TYPE _eType);

public:
	CScene();
	virtual ~CScene();
};

