#include "pch.h"
#include "CScene.h"
#include "CObject.h"
#include "Background.h"

#include "CCore.h"
#include "SelectGDI.h"

#include "CTimeMgr.h"

// Include Components
#include "RigidBody.h"


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


void CScene::AddObject(CObject* _pObj, GROUP_TYPE _eType)
{
	mArrObj[(UINT)_eType].push_back(_pObj);
}


void CScene::AddForce(tForce& force)
{
	mArrForce.push_back(force);
}


void CScene::Update()
{
	for (int i = mArrForce.size() - 1; i >= 0; --i)
	{
		mArrForce[i].curRadius += mArrForce[i].radius * mArrForce[i].speed * DT;

		if (mArrForce[i].curRadius > mArrForce[i].radius)
		{
			mArrForce.erase(mArrForce.begin() + i);
		}
	}


	for (UINT i = 0; i < (UINT)GROUP_TYPE::END; ++i)
	{
		for (size_t j = 0; j < mArrObj[i].size();++j)
		{
			if (!mArrObj[i][j]->IsDead())
			{
				// 오브젝트에 폭발력 전달
				for (int f = mArrForce.size() - 1; f >= 0; --f)
				{
					Vec2 vDiff = mArrForce[f].pos - mArrObj[i][j]->GetLocalPos();
					float len = vDiff.Length();

					if (len < mArrForce[f].radius)
					{
						float ratio = 1.f - (len / mArrForce[f].radius);
						float force = mArrForce[f].force * ratio;

						if (mArrObj[i][j]->GetRigidBody())
						{
							mArrObj[i][j]->GetRigidBody()->AddForce(vDiff.Normalize() * force * -1.f);
						}
					}
				}

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
	//Vec2 vCamPos = CCamera::GetI()->GetLookAt();
	//Vec2 vRes = CCore::GetI()->GetResolution();
	//Vec2 vLeftTop = vCamPos - vRes * 0.5f;

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
				//Vec2 vPos = (*iter)->GetLocalPos();
				//Vec2 vSize = (*iter)->GetScale();

				//// 화면을 벗어난 오브젝트인지 확인
				//if (vPos.y < vLeftTop.y - vSize.y
				//	|| vPos.y > vLeftTop.y + vRes.y
				//	|| vPos.x < vLeftTop.x - vSize.x
				//	|| vPos.x > vLeftTop.x + vRes.x)
				//{
				//	++iter;
				//	continue;
				//}

				(*iter)->Render(_dc);
				++iter;
			}
			else
			{
				(*iter)->OnDestroy();
				iter = mArrObj[i].erase(iter);
			}
		}
	}

	// [Debug] Render Force Object
	SelectGDI b(_dc, BRUSH_TYPE::HOLLOW);
	SelectGDI p(_dc, PEN_TYPE::BLUE);

	for (int i = mArrForce.size() - 1; i >= 0; --i)
	{
		Vec2 vRenderPos = CCamera::GetI()->GetRenderPos(mArrForce[i].pos);

		Ellipse(_dc
			, vRenderPos.x - mArrForce[i].curRadius
			, vRenderPos.y - mArrForce[i].curRadius
			, vRenderPos.x + mArrForce[i].curRadius
			, vRenderPos.y + mArrForce[i].curRadius );
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
