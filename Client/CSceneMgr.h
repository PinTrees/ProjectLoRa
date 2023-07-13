#pragma once

class CScene;

class CSceneMgr
{
	SINGLE(CSceneMgr)
private:
	CScene* m_arrScene[(UINT)SCENE_TYPE::END];		// ��� �� ���
	CScene* m_pCurScene;							// ���� ��


public:
	void Init();
	void Update();
	void FinalUpdate();
	void Render(HDC _dc);

public:
	CScene* GetCurScene() { return m_pCurScene; }
	CScene* GetScene(SCENE_TYPE _eScene) { return m_arrScene[(UINT)_eScene]; }


private:
	void ChangeScene(SCENE_TYPE _eNext);
	friend class CEventMgr;
};
