#pragma once

class CObject;

class CCollider
{
private:
	static UINT giNextID;

	CObject*	mpOwner;		// collider  �� �����ϰ� �ִ� ������Ʈ
	Vec2		mvOffsetPos;	// ������Ʈ�� ���� ������� ��ġ
	Vec2		mvFinalPos;		// finalupdate ���� �������Ӹ��� ���
	Vec2		mvScale;		// �浹ü�� ũ������

	UINT		miID;			// �浹ü ������ ID ��
public:
	void SetOffsetPos(Vec2 _vPos) { mvOffsetPos = _vPos; }
	void SetScale(Vec2 _vScale) { mvScale= _vScale; }

	Vec2 GetOffsetPos() { return mvOffsetPos; }
	Vec2 GetScale() { return mvScale; }
	
	UINT GetID() { return miID; }

public:
	void FinalUpdate();
	void Render(HDC _dc);

	//���Կ����� operator ����
	CCollider& operator	 =(CCollider& _origin) = delete;
public:
	CCollider();
	CCollider(const CCollider& _origin);
	~CCollider();

	friend class CObject;
};

