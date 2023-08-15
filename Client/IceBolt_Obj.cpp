#include "pch.h"
#include "IceBolt_Obj.h"
#include "IceBolt_Effect.h"

#include "CResMgr.h"
#include "CTimeMgr.h"
#include "CSceneMgr.h"

#include "CScene.h"
#include "CAnimator.h"
#include "CCollider.h"

#include "Monster.h"




IceBolt_Obj::IceBolt_Obj()
	: mCurDelay()
	, mRange(100.f)
{
	SetMaxDelay(3.f);		// ��ų ���ӽð� ����
	SetName(L"IceBolt");
	SetDamage(3.f);
	CreateCollider();
	GetCollider()->SetScale(Vect2(80.f, 80.f));
	GetCollider()->SetOffsetPos(Vect2(0.f, 0.f));

	CTexture* pTex = CResMgr::GetI()->LoadTexture(L"IceBolt", L"texture\\bullet\\3.bmp");
	CreateAnimator();

	GetAnimator()->CreateAnimation(L"IceBolt", pTex, Vect2(0.f, 0.f), Vect2(63.f, 32.f), Vect2(63.f, 0.f), 0.07f, 5);
	SetScale(Vect2(63.f, 32.f) * 3.f);

	GetAnimator()->Play(L"IceBolt", true);
}

IceBolt_Obj::~IceBolt_Obj()
{
}

void IceBolt_Obj::Update()
{
	if (mCurDelay >= GetMaxDelay())		// ���������� ���ӽð��� ������ ���������� ��
	{
		mCurDelay = 0.f;	
		DeleteObject(this);
		return;
	}

	SetPos(GetPos() + mvDir * 300.f * DT);
	GetAnimator()->Update();
}

void IceBolt_Obj::Render(HDC _dc)
{
	SkillObj::Render(_dc);
}

void IceBolt_Obj::OnCollisionEnter(CCollider* _pOther)
{
	CObject* pObj = _pOther->GetObj();

	if (pObj->GetName() == L"Monster")
	{
		CScene* cscene = CSceneMgr::GetI()->GetCurScene();

		const vector<CObject*>& vecMon = cscene->GetGroupObject(GROUP_TYPE::MONSTER);
		Vect2 monsterPos;

		for (size_t i = 0; i < vecMon.size(); ++i)
		{
			if (vecMon[i]->IsDead()) continue;

			monsterPos = vecMon[i]->GetPos();
			if (mRange > (monsterPos - pObj->GetPos()).Length())			// ���� �����ȿ� �ִ� ���͵��� ���� ���·� ����
			{
				((Monster*)vecMon[i])->SetFreeze(3.5f);

				IceBolt_Effect* pIce = new IceBolt_Effect;					// ����ȿ�� ����
				pIce->SetPos(vecMon[i]->GetLocalPos() - Vect2(0.f, pIce->GetScale().y * 0.5f));
				pIce->SetTargetMonster(vecMon[i]);							// ����ִ� ���͸� ���ͷ� �޾Ƴ���
				CreateObject(pIce, GROUP_TYPE::PROJ_PLAYER);
			}
		}

		DeleteObject(this);
	}
}
