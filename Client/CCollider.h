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
	int			miCol;			
public:
	void SetOffsetPos(Vec2 _vPos) { mvOffsetPos = _vPos; }
	void SetScale(Vec2 _vScale) { mvScale= _vScale; }

	Vec2 GetFinalPos() { return mvFinalPos; }
	Vec2 GetOffsetPos() { return mvOffsetPos; }
	Vec2 GetScale() { return mvScale; }
	
	UINT GetID() { return miID; }

public:
	void FinalUpdate();
	void Render(HDC _dc);

public:
	// �浹 ���� �Լ�
	void OnCollision(CCollider* _pOther); // �浹 ���� ��� ȣ��Ǵ� �Լ�
	void OnCollisionEnter(CCollider* _pOther); // �浹 ���Խ�
	void OnCollisionExit(CCollider* _pOther); // �浹 ������




	//���Կ����� operator ����
	CCollider& operator	 =(CCollider& _origin) = delete;
public:
	CCollider();
	CCollider(const CCollider& _origin);
	~CCollider();

	friend class CObject;
};

