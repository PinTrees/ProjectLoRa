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

	mArrForce.clear();
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
	// Physical Force Update
	for (int i = (int)mArrForce.size() - 1; i >= 0; --i)
	{
		mArrForce[i].curRadius += mArrForce[i].radius * mArrForce[i].speed * DT;

		if (mArrForce[i].curRadius > mArrForce[i].radius)
		{
			mArrForce.erase(mArrForce.begin() + i);
		}
	}


	for (UINT i = 0; i < (UINT)GROUP_TYPE::END; ++i)
	{
		if ((GROUP_TYPE)i == GROUP_TYPE::UI)
			continue;

		for (size_t j = 0; j < mArrObj[i].size();++j)
		{
			if (!mArrObj[i][j]->IsDead())
			{
				// Object Physical Force Calculation
				for (int f = mArrForce.size() - 1; f >= 0; --f)
				{
					Vect2 vDiff = mArrForce[f].pos - mArrObj[i][j]->GetLocalPos();
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


void CScene::UpdateUI()
{
	const vector<CObject*>& arrUI = GetGroupObject(GROUP_TYPE::UI);
	for (int i = 0; i < arrUI.size(); ++i)
	{
		if (!arrUI[i]->IsDead())
		{
			arrUI[i]->Update();
		}
	}
}


void CScene::FinalUpdate()
{
	if (!CTimeMgr::GetI()->IsPlay())
	{
		const vector<CObject*>& arrUI = GetGroupObject(GROUP_TYPE::UI);
		for (int i = 0; i < arrUI.size(); ++i)
		{
			arrUI[i]->FinalUpdate();
		}

		return;
	}

	for (UINT i = 0; i < (UINT)GROUP_TYPE::END; ++i)
	{
		for (size_t j = 0; j < mArrObj[i].size(); ++j)
		{
			mArrObj[i][j]->FinalUpdate();
		}
	}
}



#define CUR_TILE_SIZE 500


void CScene::render_background(HDC dc)
{
	const vector<CObject*>& parallaxs = GetGroupObject(GROUP_TYPE::BACKGROUND);

	Vect2 vCamPos = CCamera::GetI()->GetLookAt();
	Vect2 vRes = CCore::GetI()->GetResolution();

	Vect2 vLeftTop = vCamPos - vRes * 0.5f;

	for (int i = 0; i < parallaxs.size(); i++)
	{
		Background* parallax = (Background*)parallaxs[i];
		parallax->Render(dc, vLeftTop, vRes);
	}
}



void CScene::Render(HDC _dc)
{
	Vect2 vRes = CCore::GetI()->GetResolution();
	Vect2 vCenterPos = CCamera::GetI()->GetLookAt();
	vRes = vRes * 1.1f;

	float left	 = vCenterPos.x - vRes.x * 0.5f;
	float right  = vCenterPos.x + vRes.x * 0.5f;
	float top	 = vCenterPos.y - vRes.y * 0.5f;
	float bottom = vCenterPos.y + vRes.y * 0.5f;

	for (UINT i = 0; i < (UINT)GROUP_TYPE::END; ++i)
	{
		// Render Background
		if ((UINT)GROUP_TYPE::BACKGROUND == i)
		{
			render_background(_dc);
			continue;
		}

		// Render UI
		else if ((UINT)GROUP_TYPE::UI == i)
		{
			for (auto iter = mArrObj[i].begin(); iter != mArrObj[i].end();)
			{
				if (!(*iter)->IsDead())
				{
					if ((*iter)->IsVisible()) 
						(*iter)->Render(_dc);
					++iter;
				}
				// Delete Object
				else
				{
					(*iter)->OnDestroy();
					iter = mArrObj[i].erase(iter);
				}
			}
			continue;
		}

		for (auto iter = mArrObj[i].begin(); iter != mArrObj[i].end();)
		{
			// Render Object
			if (!(*iter)->IsDead())
			{
				if ((*iter)->IsVisible())
				{
					Vect2 vRenderPos = (*iter)->GetPos();
					if (vRenderPos.x < left || vRenderPos.x > right || vRenderPos.y < top || vRenderPos.y > bottom) {}
					else (*iter)->Render(_dc);
				}
				++iter;
			}
			// Delete Object
			else
			{
				(*iter)->OnDestroy();
				iter = mArrObj[i].erase(iter);
			}
		}
	}

	//// [Debug] Render Force Object
	//if (DEBUG)
	//{
	//	SelectGDI b(_dc, BRUSH_TYPE::HOLLOW);
	//	SelectGDI p(_dc, PEN_TYPE::BLUE);

	//	for (int i = mArrForce.size() - 1; i >= 0; --i)
	//	{
	//		Vect2 vRenderPos = CCamera::GetI()->GetRenderPos(mArrForce[i].pos);

	//		Ellipse(_dc
	//			, vRenderPos.x - mArrForce[i].curRadius
	//			, vRenderPos.y - mArrForce[i].curRadius
	//			, vRenderPos.x + mArrForce[i].curRadius
	//			, vRenderPos.y + mArrForce[i].curRadius);
	//	}
	//}
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
