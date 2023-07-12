#pragma once

class CObject;
class CScene;
class AI;

struct tForce;

void CreateObject(CObject* _pObj, GROUP_TYPE _eGroup);
void DeleteObject(CObject* _pObj);
void ChangeScene(SCENE_TYPE _eNext);
void ChangeAIState(AI* pAI, MONSTER_STATE nextState);
void CreateForce(tForce& force);


Vect2 curvesCircle(Vect2 c1, float _radius, float _amount);
void FlipImage(HDC hdc, int x, int y, int width, int height, HDC srcDC, int srcX, int srcY, int srcWidth, int srcHeight);
void LoadTile(CScene* pScene, const wstring& _fullPath);
void CreateTile(CScene* pScene, UINT xCount, UINT yCount);

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
void SaveWString(const wstring& _str, FILE* _pFIle);
void LoadWString(wstring& _str,FILE* _pFIle);

void FScanf(char* _pOutBuff, FILE* _pFile);

