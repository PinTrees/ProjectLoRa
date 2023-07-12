#pragma once
#include "CEventMgr.h"

class CObject;
class CScene;
template <typename T>
class AI;

struct tForce;

void CreateObject(CObject* _pObj, GROUP_TYPE _eGroup);
void DeleteObject(CObject* _pObj);
void ChangeScene(SCENE_TYPE _eNext);
void CreateForce(tForce& force);

template <typename T>
void ChangeAIState(AI<T>* pAI, MONSTER_STATE nextState)
{
	tEvent evn = {};
	evn.eEven = EVENT_TYPE::CHANGE_AI_STATE;
	evn.lParam = (DWORD_PTR)pAI;
	evn.wParam = (DWORD_PTR)nextState;

	pAI->ChangeState(nextState);

	//추후 변경
	//CEventMgr::GetI()->AddEvent(evn);
}



template<typename T>
void Safe_Delete_Vec(vector<T>& _vec)
{
	for (size_t i = 0; i < _vec.size(); ++i)
	{
		if (nullptr != _vec[i])
			delete _vec[i];
	}
	_vec.clear();
}


template<typename T1,typename T2>
void Safe_Delete_Map(map<T1, T2>& _map)
{
	typename map<T1, T2>::iterator	iter = _map.begin();

	for (; iter != _map.end(); ++iter)
	{
		if (nullptr != iter->second)
			delete iter->second;
	}
	_map.clear();
}




Vect2 curvesCircle(Vect2 c1, float _radius, float _amount);

void FlipImage(HDC hdc, int x, int y, int width, int height, HDC srcDC, int srcX, int srcY, int srcWidth, int srcHeight);


void LoadTile(CScene* pScene, const wstring& _fullPath);
void CreateTile(CScene* pScene, UINT xCount, UINT yCount);