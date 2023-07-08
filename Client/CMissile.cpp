#include "pch.h"
#include "CMissile.h"

#include "CScene.h"
#include "CSceneMgr.h"

#include "CTimeMgr.h"
#include "CCollider.h"

#include "CAnimation.h"
#include "CAnimator.h"
#include "CTexture.h"
#include "CResMgr.h"

CMissile::CMissile()
	:m_tTheta(PI / 4.f)
	, m_vDir(Vec2(1.f, 1.f))
	, mType(L"1")
	, mDelay(5.f)
	, mCurDelay(0.f)
{
	m_vDir.Normalize();
	CreateCollider();
	GetCollider()->SetScale(Vec2(15,15));

	CTexture* pTex = CResMgr::GetI()->LoadTexture(L"Effect_1", L"texture\\effect\\" + mType + L".bmp");

	CreateAnimator();
	GetAnimator()->CreateAnimation(L"MAIN", pTex, Vec2(0.f, 0.f), Vec2(70.f, 52.f), Vec2(70.f, 0.f), 0.07f, 8);
	GetAnimator()->Play(L"MAIN", true);
}



CMissile::CMissile(const wstring& _type)
	: m_tTheta(PI / 4.f)
	, m_vDir(Vec2(1.f, 1.f))
	, mDelay(1.5f)
	, mCurDelay(0.f)
{
	m_vDir.Normalize();
	CreateCollider();
	GetCollider()->SetScale(Vec2(15, 15));

	CTexture* pTex = CResMgr::GetI()->LoadTexture(L"Effect" + _type, L"texture\\effect\\" + _type + L".bmp");
	CreateAnimator();

	if (_type == L"1")
		GetAnimator()->CreateAnimation(L"MAIN", pTex, Vec2(70.f, 0.f), Vec2(70.f, 52.f), Vec2(70.f, 0.f), 0.1f, 8 - 1);
	if (_type == L"2")
		GetAnimator()->CreateAnimation(L"MAIN", pTex, Vec2(40.f, 0.f), Vec2(40.f, 52.f), Vec2(40.f, 0.f), 0.07f, 6 - 1);
	if (_type == L"3")
		GetAnimator()->CreateAnimation(L"MAIN", pTex, Vec2(60.f, 0.f), Vec2(60.f, 80.f), Vec2(60.f, 0.f), 0.07f, 10 - 1);
	if (_type == L"4")
		GetAnimator()->CreateAnimation(L"MAIN", pTex, Vec2(48.f, 0.f), Vec2(48.f, 48.f), Vec2(48.f, 0.f), 0.07f, 11 - 1);
	if (_type == L"5")
		GetAnimator()->CreateAnimation(L"MAIN", pTex, Vec2(48.f, 0.f), Vec2(48.f, 48.f), Vec2(48.f, 0.f), 0.07f, 9 - 1);
	if (_type == L"6")
		GetAnimator()->CreateAnimation(L"MAIN", pTex, Vec2(36.f, 0.f), Vec2(36.f, 36.f), Vec2(36.f, 0.f), 0.07f, 5 - 1);
	if (_type == L"7")
		GetAnimator()->CreateAnimation(L"MAIN", pTex, Vec2(36.f, 0.f), Vec2(36.f, 36.f), Vec2(36.f, 0.f), 0.07f, 6 - 1);
	if (_type == L"8")
		GetAnimator()->CreateAnimation(L"MAIN", pTex, Vec2(32.f, 0.f), Vec2(32.f, 32.f), Vec2(32.f, 0.f), 0.07f, 9 - 1);

	GetAnimator()->Play(L"MAIN", true);
}




CMissile::~CMissile()
{

}

void CMissile::Update()
{
	mCurDelay += DT;
	if (mCurDelay > mDelay)
	{
		DeleteObject(this);
		return;
	}

	Vec2 vPos = GetPos();
	CScene* pCurScene = CSceneMgr::GetI()->GetCurScene();

	//vPos.x += 800.f * cosf(m_tTheta) * DT;
	//vPos.y -= 800.f * sinf(m_tTheta) * DT;

	vPos.x += 500.f * m_vDir.x * DT;
	vPos.y += 500.f * m_vDir.y * DT;

	if (vPos.y < 110)
		pCurScene->DeleteObject(this, GROUP_TYPE::PROJ_PLAYER);

	SetPos(vPos);
	GetAnimator()->Update();
}

void CMissile::Render(HDC _dc)
{
	Vec2 vPos = GetPos();
	Vec2 vScale = GetScale();

	CompnentRender(_dc);
}

void CMissile::OnCollisionEnter(CCollider* _pOther)
{
	CObject* pOtherObj = _pOther->GetObj();

	if (pOtherObj->GetName() == L"Monster")
	{
		DeleteObject(this);
	}

	if (pOtherObj->GetName() == L"ENV")
	{
		DeleteObject(this);
	}
}