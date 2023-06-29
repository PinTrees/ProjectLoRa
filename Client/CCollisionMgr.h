#pragma once

class CCollider;

union COLLIDER_ID
{

	struct 
	{
		UINT Left_id;
		UINT RIght_id;
	};
	ULONGLONG ID;
};

class CCollisionMgr
{
	SINGLE(CCollisionMgr)
private:
	map<ULONGLONG, bool> mMapColInfo;						// �浹ü ���� ���� ������ �浹 ����  
	UINT				mArrCheck[(UINT)GROUP_TYPE::END];	// �׷찣�� �浹 üũ ��Ʈ����

public:
	void Update();
	void CheckGroup(GROUP_TYPE _eLeft, GROUP_TYPE _eRight);
	void Reset() { memset(mArrCheck, 0, sizeof(UINT) * (UINT)GROUP_TYPE::END); }

private:
	void collisionGroupUpdate(GROUP_TYPE _eLeft, GROUP_TYPE _eRight);
	bool isCollision(CCollider* _pLeftCol, CCollider* _pRightCol);
};

