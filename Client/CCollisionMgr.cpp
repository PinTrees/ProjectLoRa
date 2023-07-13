#include "pch.h"
#include "CCollisionMgr.h"

#include "CSceneMgr.h"
#include "CScene.h"
#include "CObject.h"
#include "CCollider.h"

union Test
{
	int a;
	float f;
};

CCollisionMgr::CCollisionMgr()
	:mArrCheck{}
{

}


CCollisionMgr::~CCollisionMgr()
{

}




void CCollisionMgr::Update()
{
	for (UINT iRow = 0; iRow < (UINT)GROUP_TYPE::END; ++iRow)
	{
		for (UINT iCol = iRow; iCol < (UINT)GROUP_TYPE::END; ++iCol)
		{
			if (mArrCheck[iRow] & (1 << iCol))
			{
				collisionGroupUpdate((GROUP_TYPE)iRow, (GROUP_TYPE)iCol);
			}
		}

	}

}

void CCollisionMgr::collisionGroupUpdate(GROUP_TYPE _eLeft, GROUP_TYPE _eRight)
{
	CScene* pCurScene = CSceneMgr::GetI()->GetCurScene();
	const vector<CObject*>& vecLeft = pCurScene->GetGroupObject(_eLeft);
	const vector<CObject*>& vecRight = pCurScene->GetGroupObject(_eRight);
	map<ULONGLONG, bool>::iterator iter;

	for (size_t i = 0; i < vecLeft.size(); ++i)
	{
		// �浹ü�� �������� ���� ���
		if (nullptr == vecLeft[i]->GetCollider())
		{
			continue;
		}
		for (size_t j = 0; j < vecRight.size(); ++j)
		{
			// �浹ü�� ���ų� , �ڱ� �ڽŰ��� �浹�� ���
			if (nullptr == vecRight[j]->GetCollider()
				|| vecLeft[i] == vecRight[j])
			{
				continue;
			}

			CCollider* pLeftCol = vecLeft[i]->GetCollider();
			CCollider* pRightCol = vecRight[j]->GetCollider();

			// �� �浹ü ���� ���̵� ����
			COLLIDER_ID ID;
			ID.Left_id = pLeftCol->GetID();
			ID.RIght_id = pRightCol->GetID();

			iter = mMapColInfo.find(ID.ID);

			//�浹 ������ �� ��ϵ� ������ ��� ���� ��� ( �浹���� �ʾҴٷ�)
			if (mMapColInfo.end() == iter)
			{
				mMapColInfo.insert(make_pair(ID.ID, false));
				iter = mMapColInfo.find(ID.ID);
			}

			if (isCollision(pLeftCol, pRightCol))
			{
				// ���� �浹 ���̴�.
				if (iter->second)
				{
					// �������� �浹���̿���.
					if (vecLeft[i]->IsDead() || vecRight[j]->IsDead())
					{
						// �ٵ� ���� �ϳ��� ���� �����̶�� �浹 ���������ش�.
						pLeftCol->OnCollisionExit(pRightCol);
						pRightCol->OnCollisionExit(pLeftCol);
						iter->second = false;
					}
					else
					{
						pLeftCol->OnCollisionStay(pRightCol);
						pRightCol->OnCollisionStay(pLeftCol);
					}
				}
				else
				{
					// �������� �浹���� �ʾҴ�.
					if (!vecLeft[i]->IsDead() && !vecRight[j]->IsDead())
					{
						// �̹��� �浹�� ���۵Ǿ���.
						pLeftCol->OnCollisionEnter(pRightCol);
						pRightCol->OnCollisionEnter(pLeftCol);
						iter->second = true;
					}
				}
			}
			else
			{
				// ���� �浹���� �ʰ��ִ�.
				if (iter->second)
				{
					// �������� �浹���̿���.
					pLeftCol->OnCollisionExit(pRightCol);
					pRightCol->OnCollisionExit(pLeftCol);
					iter->second = false;
				}
			}
		}
	}
}

bool CCollisionMgr::isCollision(CCollider* _pLeftCol, CCollider* _pRightCol)
{
<<<<<<< Updated upstream
	Vec2 vLeftPos = _pLeftCol->GetFinalPos();
	Vec2 vLeftScale = _pLeftCol->GetScale();

	Vec2 vRightPos = _pRightCol->GetFinalPos();
	Vec2 vRightScale = _pRightCol->GetScale();
=======
	Vect2 vLeftPos = _pLeftCol->GetFinalPos();
	Vect2 vLeftScale = _pLeftCol->GetScale();

	Vect2 vRightPos = _pRightCol->GetFinalPos();
	Vect2 vRightScale = _pRightCol->GetScale();
>>>>>>> Stashed changes

	if (abs(vRightPos.x - vLeftPos.x) < (vLeftScale.x + vRightScale.x) / 2.f
		&& abs(vRightPos.y - vLeftPos.y) < (vLeftScale.y + vRightScale.y) / 2.f)
	{
		return true;
	}

	return false;
}

void CCollisionMgr::CheckGroup(GROUP_TYPE _eLeft, GROUP_TYPE _eRight)
{
	// �� ���� ���� �׷� Ÿ���� ������,
	// ū ���� ��(��Ʈ) �� ���

	UINT iRow = (UINT)_eLeft;
	UINT iCol = (UINT)_eRight;

	if (iCol < iRow)
	{
		iRow = (UINT)_eRight;
		iCol = (UINT)_eLeft;
	}

	if (mArrCheck[iRow] & (1 << iCol))
	{
		mArrCheck[iRow] &= ~(1 << iCol);
	}
	else
	{
		mArrCheck[iRow] |= (1 << iCol);
	}
}


