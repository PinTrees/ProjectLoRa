#include "pch.h"
#include "EnergyBall_Obj.h"

#include "CTimeMgr.h"
#include "CResMgr.h"

#include "CCollider.h"
#include "CAnimator.h"




EnergyBall_Obj::EnergyBall_Obj()
	: mCurDelay()
	, mSpeed(200.f)
{
	SetMaxDelay(3.f);		// ��ų ���ӽð� ����
	SetDamageDelay(0.3f);	// ~�ʸ��� �������� ����
	SetName(L"EnergyBall");
	CreateCollider();
	GetCollider()->SetScale(Vect2(128.f, 128.f));
	GetCollider()->SetOffsetPos(Vect2(0.f, 0.f));

	CTexture* pTex = CResMgr::GetI()->LoadTexture(L"EnergyBall", L"texture\\effect\\10.bmp");
	CreateAnimator();

	GetAnimator()->CreateAnimation(L"EnergyBall", pTex, Vect2(0.f, 0.f), Vect2(80.f, 80.f), Vect2(80.f, 0.f), 0.05f, 15);
	SetScale(Vect2(180.f, 180.f));

	GetAnimator()->Play(L"EnergyBall", true);
	SetAlpha(255);
}

EnergyBall_Obj::~EnergyBall_Obj()
{
}

void EnergyBall_Obj::Update()
{
	mCurDelay += DT;

	if (mCurDelay >= GetMaxDelay())		// ���������� ���ӽð��� ������ ���������� ��
	{
		DeleteObject(this);
		mCurDelay = 0.f;
		return;
	}

	Vect2 vPos = GetPos();

	vPos += mvDir * mSpeed * DT;	// ���� �� �������� ��� �����̰� �Ѵ�.

	SetPos(vPos);
	GetAnimator()->Update();
}

void EnergyBall_Obj::Render(HDC _dc)
{
	SkillObj::Render(_dc);
}
