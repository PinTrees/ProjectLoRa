#pragma once

#include "global.h"

#include "CMonFactory.h"


class CObject;

class CScene
{
private:
	vector<CObject*> mArrObj[(UINT)GROUP_TYPE::END];
	wstring				m_strName; //Scene 이름

	UINT			miTileX;
	UINT			miTileY;

	CObject* mpPlayer; // 그냥 기억해버리기 말이안돼지만 일단 이게 관리측면에서 편함
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

	virtual void Enter() = 0; //해당 씬 진입시 호출
	virtual void Exit() = 0;  // 해당씬 탈출시 호출

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

