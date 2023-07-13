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
			//�׷캰 CObject ����
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


<<<<<<< Updated upstream
void CScene::Update()
{
=======


void CScene::Update()
{
	// Physical Force Update
>>>>>>> Stashed changes
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
<<<<<<< Updated upstream
				// ������Ʈ�� ���߷� ����
				for (int f = mArrForce.size() - 1; f >= 0; --f)
				{
					Vec2 vDiff = mArrForce[f].pos - mArrObj[i][j]->GetLocalPos();
=======
				// Object Physical Force Calculation
				for (int f = mArrForce.size() - 1; f >= 0; --f)
				{
					Vect2 vDiff = mArrForce[f].pos - mArrObj[i][j]->GetLocalPos();
>>>>>>> Stashed changes
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
	if (!CTimeMgr::GetI()->IsPlay())
	{
		vector<CObject*> arrUI = GetGroupObject(GROUP_TYPE::UI);
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


<<<<<<< Updated upstream
void CScene::_render_parallax(HDC dc)
{
	vector<CObject*> parallaxs = GetGroupObject(GROUP_TYPE::PARALLAX);

	Vec2 vCamPos = CCamera::GetI()->GetLookAt();
	Vec2 vRes = CCore::GetI()->GetResolution();

	Vec2 vLeftTop = vCamPos - vRes * 0.5f;
=======
void CScene::render_parallax(HDC dc)
{
	vector<CObject*> parallaxs = GetGroupObject(GROUP_TYPE::PARALLAX);

	Vect2 vCamPos = CCamera::GetI()->GetLookAt();
	Vect2 vRes = CCore::GetI()->GetResolution();

	Vect2 vLeftTop = vCamPos - vRes * 0.5f;
>>>>>>> Stashed changes

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

				//// ȭ���� ��� ������Ʈ���� Ȯ��
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
<<<<<<< Updated upstream
		DeleteGroup((GROUP_TYPE)i);
=======
		// Render Background
		if ((UINT)GROUP_TYPE::PARALLAX == i)
		{
			render_parallax(_dc);
			continue;
		}

		vector<CObject*>::iterator iter = mArrObj[i].begin();

		for (;iter != mArrObj[i].end();)
		{
			// Render Object
			if (!(*iter)->IsDead())
			{
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
	}


	// [Debug] Render Force Object
	if (DEBUG)
	{
		SelectGDI b(_dc, BRUSH_TYPE::HOLLOW);
		SelectGDI p(_dc, PEN_TYPE::BLUE);

		for (int i = mArrForce.size() - 1; i >= 0; --i)
		{
			Vect2 vRenderPos = CCamera::GetI()->GetRenderPos(mArrForce[i].pos);

			Ellipse(_dc
				, vRenderPos.x - mArrForce[i].curRadius
				, vRenderPos.y - mArrForce[i].curRadius
				, vRenderPos.x + mArrForce[i].curRadius
				, vRenderPos.y + mArrForce[i].curRadius);
		}
>>>>>>> Stashed changes
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
