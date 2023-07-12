#pragma once
#include "CCompnent.h"

class CObject;

class CCollider : public CCompnent
{
private:
	static UINT giNextID;
	Vect2		mvOffsetPos;	// ������Ʈ�� ���� ������� ��ġ
	Vect2		mvFinalPos;		// finalupdate ���� �������Ӹ��� ���
	Vect2		mvScale;		// �浹ü�� ũ������

	UINT		miID;			// �浹ü ������ ID ��
	int			miCol;			

	bool		mIsTrigger;		// �ش� �浹ü�� ��ħ ���� 


public:
	void SetOffsetPos(Vect2 _vPos) { mvOffsetPos = _vPos; }
	void SetScale(Vect2 _vScale) { mvScale= _vScale; }

	void SetTrigger(bool _trigger) { mIsTrigger = _trigger; }
	bool GetTrigger() { return mIsTrigger; }

	Vect2 GetFinalPos() { return mvFinalPos; }
	Vect2 GetOffsetPos() { return mvOffsetPos; }
	Vect2 GetScale() { return mvScale; }
	
	CObject* GetObj() { return GetO(); }

	UINT GetID() { return miID; }


public:
	virtual void FinalUpdate() override;
	virtual void Render(HDC _dc) override;


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
	virtual ~CCollider() override;

};

