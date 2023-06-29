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

	for (size_t i = 0; i < vecLeft.size(); ++i)
	{
		// 충돌체를 보유하지 않은 경우
		if (nullptr == vecLeft[i]->GetCollider())
		{
			continue;
		}
		for (size_t j = 0; j < vecRight.size(); ++j)
		{
			// 충돌체가 없거나 , 자기 자신과의 충돌인 경우
			if (nullptr == vecRight[j]->GetCollider()
				|| vecLeft[i] == vecRight[j])
			{
				continue;
			}

			// 두 충돌체
			COLLIDER_ID ID;
			ID.Left_id = vecLeft[i]->GetCollider()->GetID();
			ID.RIght_id = vecLeft[j]->GetCollider()->GetID();


			ID.ID; 

			if (isCollision(vecLeft[i]->GetCollider(), vecRight[j]->GetCollider()))
			{
				
			}
			else
			{

			}
		}
	}
}

bool CCollisionMgr::isCollision(CCollider* _pLeftCol, CCollider* _pRightCol)
{

	return false;
}

void CCollisionMgr::CheckGroup(GROUP_TYPE _eLeft, GROUP_TYPE _eRight)
{
	// 더 작은 값의 그룹 타입을 행으로,
	// 큰 값을 열(비트) 로 사용

	UINT iRow = (UINT)_eLeft;
	UINT iCol = (UINT)_eRight;

	if (iCol < iRow)
	{
		UINT iRow = (UINT)_eRight;
		UINT iCol = (UINT)_eLeft;
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


