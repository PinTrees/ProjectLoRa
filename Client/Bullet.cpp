#include "pch.h"
#include "Bullet.h"

#include "CScene.h"
#include "CSceneMgr.h"

#include "CTimeMgr.h"
#include "CCollider.h"

#include "CAnimation.h"
#include "CAnimator.h"
#include "CTexture.h"
#include "CResMgr.h"


Bullet::Bullet(const wstring& _type)
	: m_tTheta(PI / 4.f)
	, m_vDir(Vec2(1.f, 1.f))
	, mDelay(1.5f)
	, mCurDelay(0.f)
{
	m_vDir.Normalize();
	CreateCollider();
	GetCollider()->SetScale(Vec2(15, 15));

	CTexture* pTex = CResMgr::GetI()->LoadTexture(L"Effect" + _type, L"texture\\bullet\\" + _type + L".bmp");
	CreateAnimator();

	if (_type == L"1")
	{
		GetAnimator()->CreateAnimation(L"IDLE", pTex, Vec2(0.f, 0.f), Vec2(48.f, 32.f), Vec2(48.f, 0.f), 0.1f, 4);
		SetScale(Vec2(48.f, 32.f) * 2.f);
	}


	GetAnimator()->Play(L"IDLE", true);
}




Bullet::~Bullet()
{

}

void Bullet::Update()
{
	mCurDelay += fDT;
	if (mCurDelay > mDelay)
	{
		DeleteObject(this);
		return;
	}

	Vec2 vPos = GetPos();
	CScene* pCurScene = CSceneMgr::GetI()->GetCurScene();

	//vPos.x += 800.f * cosf(m_tTheta) * fDT;
	//vPos.y -= 800.f * sinf(m_tTheta) * fDT;

	vPos.x += 500.f * m_vDir.x * fDT;
	vPos.y += 500.f * m_vDir.y * fDT;

	if (vPos.y < 110)
		pCurScene->DeleteObject(this, GROUP_TYPE::PROJ_PLAYER);

	SetPos(vPos);
	GetAnimator()->Update();
}

void Bullet::Render(HDC _dc)
{
	Vec2 vPos = GetPos();
	Vec2 vScale = GetScale();

	CompnentRender(_dc);
}

void Bullet::OnCollisionEnter(CCollider* _pOther)
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