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

	bool		mIsTrigger;		// �ش� �浹ü�� ��ħ ���� 


public:
	void SetOffsetPos(Vec2 _vPos) { mvOffsetPos = _vPos; }
	void SetScale(Vec2 _vScale) { mvScale= _vScale; }

	void SetTrigger(bool _trigger) { mIsTrigger = _trigger; }
	bool GetTrigger() { return mIsTrigger; }

	Vec2 GetFinalPos() { return mvFinalPos; }
	Vec2 GetOffsetPos() { return mvOffsetPos; }
	Vec2 GetScale() { return mvScale; }
	
	CObject* GetObj() { return mpOwner; }

	UINT GetID() { return miID; }


public:
	void FinalUpdate();
	void Render(HDC _dc);


public:
	// �浹 ���� �Լ�
	void OnCollisionEnter(CCollider* _pOther); // �浹 ���Խ�
	void OnCollisionStay(CCollider* _pOther); // �浹 ���� ��� ȣ��Ǵ� �Լ�
	void OnCollisionExit(CCollider* _pOther); // �浹 ������

	//���Կ����� operator ����
	CCollider& operator	 =(CCollider& _origin) = delete;


public:
	CCollider();
	CCollider(const CCollider& _origin);
	~CCollider();

	friend class CObject;
};

