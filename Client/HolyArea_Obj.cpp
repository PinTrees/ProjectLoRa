#include "pch.h"
#include "HolyArea_Obj.h"

#include "CResMgr.h"
#include "CTimeMgr.h"
#include "PlayerMgr.h"

#include "Player.h"
#include "CCollider.h"
#include "CAnimator.h"
#include "Skill.h"




HolyArea_Obj::HolyArea_Obj()
	: mPrevLv()
	, mTheta(360.f)
	, mAlpha()
	, mPlusAlpha(70.f)
{
	SetMaxDelay(0.f);		// ��ų ���ӽð��� �ʿ� ���� ������ 0���� ����
	SetDamageDelay(0.2f);	// ~�ʸ��� �������� ����
	SetName(L"HolyArea");
	CreateCollider();
	GetCollider()->SetScale(Vect2(80.f, 80.f));
	GetCollider()->SetOffsetPos(Vect2(0.f, 0.f));

	CTexture* pTex = CResMgr::GetI()->LoadTexture(L"HolyArea", L"texture\\effect\\10.bmp");
	CreateAnimator();

	GetAnimator()->CreateAnimation(L"HolyArea", pTex, Vect2(80.f, 0.f) * 13, Vect2(80.f, 80.f), Vect2(80.f, 0.f), 0.5f, 1);
	SetScale(Vect2(100.f, 100.f) * 0.5f);

	GetAnimator()->Play(L"HolyArea", true);
}

HolyArea_Obj::~HolyArea_Obj()
{
}

void HolyArea_Obj::Update()
{
	if (mPrevLv < GetOwner()->GetSkillLevel())			// �������� �ϸ� ��ų�� ���� ����ϱ� ���� ���� ������Ʈ�� ����
	{
		DeleteObject(this);
		return;
	}

	if (mTheta <= 0.f)
	{
		mTheta = 360.f;		// Theta ���� �ʹ� Ŀ���� �ʵ��� �����Ѵ�.
	}

	Vect2 vPos = PlayerMgr::GetI()->GetPlayer()->GetLocalPos();

	SetPos(Vect2(vPos.x, vPos.y));
	SetAngle(mTheta);					// ������Ʈ�� ȸ����Ų��.
	GetAnimator()->Update();
	SetAlpha(150);

	mTheta -= 120.f * DT;
}

void HolyArea_Obj::Render(HDC _dc)
{
	SkillObj::Render(_dc);
}
