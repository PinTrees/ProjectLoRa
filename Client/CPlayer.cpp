#include "pch.h"
#include "CPlayer.h"

#include "CScene.h"
#include "CSceneMgr.h"


#include "CKeyMgr.h"
#include "CTimeMgr.h"


#include "CMissile.h"

#include "CResMgr.h"
#include "CTexture.h"
#include "CCollider.h"
#include "CAnimator.h"
#include "CAnimation.h"

CPlayer::CPlayer()
{
	// Texture 로딩하기 [더미코드]
	//mPTex = CResMgr::GetI()->LoadTexture(L"PlayerTex", L"texture\\Player.bmp");

	CreateCollider();
	GetCollider()->SetOffsetPos(Vec2(0.f, 12.f));
	GetCollider()->SetScale(Vec2(20.f, 40.f));


	// Texture 로딩하기
	CTexture* pTex = CResMgr::GetI()->LoadTexture(L"PlayerTex", L"texture\\link.bmp");

	CreateAnimator();
	GetAnimator()->CreateAnimation(L"WALK_DOWN", pTex, Vec2(0.f, 260.f), Vec2(60.f, 65.f), Vec2(60.f, 0.f), 0.07f, 10);
	GetAnimator()->Play(L"WALK_DOWN",true);

	CAnimation* pAnim = GetAnimator()->FindAnimation(L"WALK_DOWN");
	for (UINT i = 0; i < pAnim->GetMaxFrame(); i++)
	{
		pAnim->GetFrame(i).vOffset = Vec2(0.f, -20.f);

	}
}

CPlayer::~CPlayer()
{

}

void CPlayer::Update()
{
	Vec2 vPos = GetPos();

	if (KEY_HOLD(KEY::W))
	{
		vPos.y -= 200.f * fDT;
	}
	if (KEY_HOLD(KEY::S))
	{
		vPos.y += 200.f * fDT;

	}
	if (KEY_HOLD(KEY::A))
	{
		vPos.x -= 200.f * fDT;

	}
	if (KEY_HOLD(KEY::D))
	{
		vPos.x += 200.f * fDT;

	}

	if (KEY_TAP(KEY::SPACE))
	{
		createMissile();
	}

	SetPos(vPos);
	GetAnimator()->Update();

}

void CPlayer::Render(HDC _dc)
{


	//컴포넌트 ( 충돌체 , ect...	) 가 있는경우 랜더
	//CompnentRender(_dc);
	CTexture* pTex = CResMgr::GetI()->LoadTexture(L"plane", L"texture\\PlayerA.bmp");
	Vec2 vPos = GetPos();
	vPos = CCamera::GetI()->GetRenderPos(vPos);

	float width = (float)pTex->Width();
	float height = (float)pTex->Heigth();

	BLENDFUNCTION bf = {};
	bf.BlendOp = AC_SRC_OVER;
	bf.BlendFlags = 0;
	bf.AlphaFormat = AC_SRC_ALPHA;
	bf.SourceConstantAlpha = 127;

	AlphaBlend(_dc
		, vPos.x - width / 2.f
		, vPos.y - height / 2.f
		, width, height
		, pTex->GetDC()
		, 0, 0, width, height
		, bf);

}

void CPlayer::createMissile()
{
	Vec2 vMissilePos = GetPos();
	vMissilePos.y -= GetScale().y / 2.f;

	// Missile Object
	CMissile* pMissile = new CMissile;
	pMissile->SetPos(vMissilePos);
	pMissile->SetScale(Vec2(25.f, 25.f));
	pMissile->SetDir(Vec2(0.f, -1.f));
	pMissile->SetName(L"Missile_Player");

	//*** setPos setScale 는 인자로 받아서 설정하게 수정필요
	CreateObject(pMissile, GROUP_TYPE::PROJ_PLAYER);
}


