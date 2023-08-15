#include "pch.h"
#include "CCollisionMgr.h"

#include "CSceneMgr.h"
#include "CScene.h"
#include "CObject.h"
#include "CCollider.h"

SINGLE_HEADER(CCollisionMgr);


CCollisionMgr::CCollisionMgr()
	:mArrCheck{}
{
}


CCollisionMgr::~CCollisionMgr()
{
	mMapColInfo.clear();
}



void CCollisionMgr::Update()
{
	CScene* pCurScene = CSceneMgr::GetI()->GetCurScene();

	for (UINT iRow = 0; iRow < (UINT)GROUP_TYPE::END; ++iRow)
	{
		for (UINT iCol = iRow; iCol < (UINT)GROUP_TYPE::END; ++iCol)
		{
			if (mArrCheck[iRow] & (1 << iCol))
			{
				if (pCurScene->IsBSP())
				{
					UINT width = pCurScene->GetBspWidth();
					UINT height = pCurScene->GetBspHeight();

					for (int w = 0; w < width; ++w)
					{
						for (int h = 0; h < height; ++h)
						{
							collisionBspGroupUpdate(w, h, (GROUP_TYPE)iRow, (GROUP_TYPE)iCol);
						}
					}
				}
				else
				{
					collisionGroupUpdate((GROUP_TYPE)iRow, (GROUP_TYPE)iCol);
				}
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

			//�浹 ������ �� ��ϵ� ������ ��� ���� ��� (�浹���� �ʾҴٷ�)
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


void CCollisionMgr::collisionBspGroupUpdate(UINT x, UINT y, GROUP_TYPE _eLeft, GROUP_TYPE _eRight)
{
	CScene* pCurScene = CSceneMgr::GetI()->GetCurScene();
	const unordered_map<UINT, CCollider*>& vecLeft = pCurScene->GetCollisionGropObject(x, y, (UINT)_eLeft);
	const unordered_map<UINT, CCollider*>& vecRight = pCurScene->GetCollisionGropObject(x, y, (UINT)_eRight);
	map<ULONGLONG, bool>::iterator iter;

	for (const auto& lPair : vecLeft) 
	{
		UINT leftKey = lPair.first;
		CCollider* leftValue = lPair.second;

		for (const auto& rPair : vecRight)
		{
			UINT rightKey = rPair.first;
			CCollider* rightValue = rPair.second;

			if (nullptr == rightValue || leftKey == rightKey)
				continue;

			// �� �浹ü ���� ���̵� ����
			COLLIDER_ID ID;
			ID.Left_id = leftKey;
			ID.RIght_id = rightKey;

			iter = mMapColInfo.find(ID.ID);

			//�浹 ������ �� ��ϵ� ������ ��� ���� ��� (�浹���� �ʾҴٷ�)
			if (mMapColInfo.end() == iter)
			{
				mMapColInfo.insert(make_pair(ID.ID, false));
				iter = mMapColInfo.find(ID.ID);
			}

			if (isCollision(leftValue, rightValue))
			{
				// ���� �浹 ���̴�.
				if (iter->second)
				{
					// �������� �浹���̿���.
					if (leftValue->GetObj()->IsDead() || rightValue->GetObj()->IsDead())
					{
						// �ٵ� ���� �ϳ��� ���� �����̶�� �浹 ���������ش�.
						leftValue->OnCollisionExit(rightValue);
						rightValue->OnCollisionExit(leftValue);
						iter->second = false;
					}
					else
					{
						leftValue->OnCollisionStay(rightValue);
						rightValue->OnCollisionStay(leftValue);
					}
				}
				else
				{
					// �������� �浹���� �ʾҴ�.
					if (!leftValue->GetObj()->IsDead() && !rightValue->GetObj()->IsDead())
					{
						// �̹��� �浹�� ���۵Ǿ���.
						leftValue->OnCollisionEnter(rightValue);
						rightValue->OnCollisionEnter(leftValue);
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
					leftValue->OnCollisionExit(rightValue);
					rightValue->OnCollisionExit(leftValue);
					iter->second = false;
				}
			}
		}
	}
}


bool CCollisionMgr::isCollision(CCollider* _pLeftCol, CCollider* _pRightCol)
{
	Vect2 vLeftPos = _pLeftCol->GetFinalPos();
	Vect2 vLeftScale = _pLeftCol->GetScale();

	Vect2 vRightPos = _pRightCol->GetFinalPos();
	Vect2 vRightScale = _pRightCol->GetScale();

	return (abs(vRightPos.x - vLeftPos.x) < (vLeftScale.x + vRightScale.x) * 0.5f)
		&& (abs(vRightPos.y - vLeftPos.y) < (vLeftScale.y + vRightScale.y) * 0.5f);
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


