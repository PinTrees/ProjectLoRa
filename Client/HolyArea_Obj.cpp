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
	, mFadeDelay(0.2f)
	, mCurDelay(0.f)
{
	SetName(L"HolyArea");

	SetMaxDelay(0.f);		// 스킬 지속시간이 필요 없기 때문에 0으로 세팅
	SetDamageDelay(0.2f);	// ~초마다 데미지를 입힘
	SetScale(Vect2(100.f, 100.f) * 0.5f);
	SetDamage(5.f);

	CreateAnimator();
	CreateCollider();

	GetCollider()->SetScale(Vect2(80.f, 80.f));
	GetCollider()->SetOffsetPos(Vect2::zero);

	CTexture* pTex = CResMgr::GetI()->LoadTexture(L"HolyArea", L"texture\\effect\\10.bmp");

	GetAnimator()->CreateAnimation(L"HolyArea", pTex, Vect2(80.f, 0.f) * 13, Vect2(80.f, 80.f), Vect2(80.f, 0.f), 0.5f, 1);
	GetAnimator()->Play(L"HolyArea", true);
}

HolyArea_Obj::~HolyArea_Obj()
{
}

void HolyArea_Obj::Update()
{
	mCurDelay += DT * mFadeDir;

	if (mCurDelay >= mFadeDelay) mFadeDir = -1.f;
	else if (mCurDelay <= 0.f) mFadeDir = 1.f;

	if (mPrevLv < GetOwner()->GetSkillLevel())			// 레벨업을 하면 스킬을 새로 사용하기 위해 현재 오브젝트를 삭제
	{
		DeleteObject(this);
		return;
	}

	if (mTheta <= 0.f)
	{
		mTheta = 360.f;		// Theta 값이 너무 커지지 않도록 조정한다.
	}

	Vect2 vPos = PlayerMgr::GetI()->GetPlayer()->GetLocalPos();

	SetPos(Vect2(vPos.x, vPos.y));
	SetAngle(mTheta);					// 오브젝트를 회전시킨다.
	GetAnimator()->Update();

	float ratio = mCurDelay / mFadeDelay;
	SetAlpha(100 * ratio + 120);

	mTheta -= 120.f * DT;
}

void HolyArea_Obj::Render(HDC _dc)
{
	SkillObj::Render(_dc);
}
