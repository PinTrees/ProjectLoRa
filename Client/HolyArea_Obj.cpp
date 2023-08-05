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
	SetMaxDelay(0.f);		// 스킬 지속시간이 필요 없기 때문에 0으로 세팅
	SetDamageDelay(0.2f);	// ~초마다 데미지를 입힘
	SetName(L"HolyArea");
	CreateCollider();
	GetCollider()->SetScale(Vect2(80.f, 80.f));
	GetCollider()->SetOffsetPos(Vect2(0.f, 0.f));

	CTexture* pTex = CResMgr::GetI()->LoadTexture(L"HolyArea", L"texture\\effect\\5.bmp");
	CreateAnimator();

	GetAnimator()->CreateAnimation(L"HolyArea", pTex, Vect2(144.f, 0.f), Vect2(48.f, 48.f), Vect2(48.f, 0.f), 0.5f, 1);
	SetScale(Vect2(100.f, 100.f));

	GetAnimator()->Play(L"HolyArea", true);
}

HolyArea_Obj::~HolyArea_Obj()
{
}

void HolyArea_Obj::Update()
{
	if (mPrevLv < GetOwner()->GetSkillLevel())			// 레벨업을 하면 스킬을 새로 사용하기 위해 현재 오브젝트를 삭제
	{
		DeleteObject(this);
		return;
	}

	if (mTheta <= 0.f)
	{
		mTheta = 360.f;		// Theta 값이 너무 커지지 않도록 조정한다.
	}

	Vect2 vPos = PlayerMgr::GetI()->GetPlayer()->GetPos();

	SetPos(Vect2(vPos.x - 19.f, vPos.y));
	SetAngle(mTheta);					// 오브젝트를 회전시킨다.
	GetAnimator()->Update();
	SetAlpha(mAlpha);

	mAlpha += mPlusAlpha * DT;			// 명암에 추가값을 더한다.

	if (mAlpha < 0 || mAlpha > 255)			// 명암값이 0 ~ 255 범위를 넘어선 경우
	{
		mPlusAlpha *= -1;				// 명암의 추가값이 반대로 이뤄지도록 한다.
	}
	mTheta -= 120.f * DT;
}

void HolyArea_Obj::Render(HDC _dc)
{
	SkillObj::Render(_dc);
}
