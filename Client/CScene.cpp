#include "pch.h"
#include "CScene.h"
#include "CObject.h"
#include "Background.h"

#include "CCore.h"


void CScene::AddObject(CObject* _pObj, GROUP_TYPE _eType)
{
	mArrObj[(UINT)_eType].push_back(_pObj);
}

void CScene::DeleteObject(CObject* _pObj, GROUP_TYPE _eType)
{
	//for (int i = 0; i < m_arrObj[(UINT)_eType].size(); ++i)
	//{
	//	if (_pObj == m_arrObj[(UINT)_eType][i])   
	//	{
	//		m_arrObj[(UINT)_eType].erase(m_arrObj[(UINT)_eType].begin() + i);
	//		
	//		break;
	//	}
	//}
}


CScene::CScene()
{
}

CScene::~CScene()
{
	for (UINT i = 0; i < (UINT)GROUP_TYPE::END; i++)
	{
		for (size_t j = 0; j < mArrObj[i].size(); j++)
		{
			//그룹별 CObject 삭제
			delete mArrObj[i][j];
		}
	}
}
void CScene::Update()
{
	for (UINT i = 0; i < (UINT)GROUP_TYPE::END; ++i)
	{
		for (size_t j = 0; j < mArrObj[i].size();++j)
		{
			if (!mArrObj[i][j]->IsDead())
			{
				mArrObj[i][j]->Update();
			}
		}
	}
}

void CScene::FinalUpdate()
{
	for (UINT i = 0; i < (UINT)GROUP_TYPE::END; ++i)
	{
		for (size_t j = 0; j < mArrObj[i].size(); ++j)
		{
			mArrObj[i][j]->FinalUpdate();
		}
	}
}



#define CUR_TILE_SIZE 500


void CScene::_render_parallax(HDC dc)
{
	vector<CObject*> parallaxs = GetGroupObject(GROUP_TYPE::PARALLAX);

	Vec2 vCamPos = CCamera::GetI()->GetLookAt();
	Vec2 vRes = CCore::GetI()->GetResolution();

	Vec2 vLeftTop = vCamPos - vRes * 0.5f;

	for (int i = 0; i < parallaxs.size(); i++)
	{
		Background* parallax = (Background*)parallaxs[i];
		parallax->Render(dc, vLeftTop, vRes);
	}
}



void CScene::Render(HDC _dc)
{
	Vec2 vCamPos = CCamera::GetI()->GetLookAt();
	Vec2 vRes = CCore::GetI()->GetResolution();
	Vec2 vLeftTop = vCamPos - vRes * 0.5f;

	for (UINT i = 0; i < (UINT)GROUP_TYPE::END; ++i)
	{
		if ((UINT)GROUP_TYPE::PARALLAX == i)
		{
			_render_parallax(_dc);
			continue;
		}

		vector<CObject*>::iterator iter = mArrObj[i].begin();

		for (;iter != mArrObj[i].end();)
		{
			if (!(*iter)->IsDead())
			{
				Vec2 vPos = (*iter)->GetLocalPos();
				Vec2 vSize = (*iter)->GetScale();

				// 화면을 벗어난 오브젝트인지 확인
				if (vPos.y < vLeftTop.y - vSize.y
					|| vPos.y > vLeftTop.y + vRes.y
					|| vPos.x < vLeftTop.x - vSize.x
					|| vPos.x > vLeftTop.x + vRes.x)
				{
					++iter;
					continue;
				}

				(*iter)->Render(_dc);
				++iter;
			}
			else
			{
				iter = mArrObj[i].erase(iter);
			}
		}
	}
}


void CScene::DeleteGroup(GROUP_TYPE _eTarget)
{
	Safe_Delete_Vec<CObject*>(mArrObj[(UINT)_eTarget]);
}

void CScene::DeleteAll()
{
	for (UINT i = 0; i < (UINT)GROUP_TYPE::END; ++i)
	{
		DeleteGroup((GROUP_TYPE)i);
	}
}
