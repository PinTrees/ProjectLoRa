#pragma once

#include "global.h"

#include "CMonFactory.h"


class CObject;

class CScene
{
private:
	vector<CObject*> mArrObj[(UINT)GROUP_TYPE::END];
	wstring				m_strName; //Scene �̸�

	UINT			miTileX;
	UINT			miTileY;

	CObject* mpPlayer; // �׳� ����ع����� ���̾ȵ����� �ϴ� �̰� �������鿡�� ����
public:
	void SetName(const wstring& _strName) { m_strName = _strName; }
	const wstring& GetName() { return m_strName; }

	UINT GetTileX() { return miTileX; }
	UINT GetTileY() { return miTileY; }

	CObject* GetPlayer() { return mpPlayer; }

	virtual void Update();
	virtual void FinalUpdate();
	virtual void Render(HDC _dc);
	void Render_Tile(HDC _dc);

	virtual void Enter() = 0; //�ش� �� ���Խ� ȣ��
	virtual void Exit() = 0;  // �ش�� Ż��� ȣ��

public:

	void AddObject(CObject* _pObj, GROUP_TYPE _eType);
	void RegisterPlayer(CObject* _pPlayer) { mpPlayer = _pPlayer; }

	const vector<CObject*>& GetGroupObject(GROUP_TYPE _eTYpe) { return mArrObj[(UINT)_eTYpe]; }
	void DeleteGroup(GROUP_TYPE _eTarget);
	void DeleteAll();
	void CreateTile(UINT _iXCount, UINT _iYCount);
	void LoadTile(const wstring& _strRelativePath);


	vector<CObject*>& GetUIGroup() { return mArrObj[(UINT)GROUP_TYPE::UI]; }

public:
	CScene();
	virtual ~CScene();
};

