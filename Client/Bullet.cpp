#include "pch.h"
#include "Bullet.h"

#include "CScene.h"
#include "CSceneMgr.h"
#include "CCore.h"

#include "CTimeMgr.h"
#include "CCollider.h"

#include "CAnimation.h"
#include "CAnimator.h"
#include "CTexture.h"
#include "CResMgr.h"

#include "Particle.h"
#include "Random.h"

Bullet::Bullet(const wstring& _type)
	: m_tTheta(PI / 4.f)
	, m_vDir(Vec2(1.f, 1.f))
	, mDelay(2.f)
	, mCurDelay(0.f)
	, mPenetrationCount(3)
	, mDivideCount(3)
	, mBounceCount(3)
{
	m_vDir.Normalize();
	CreateCollider();
	GetCollider()->SetScale(Vec2(15, 15));
	GetCollider()->SetOffsetPos(Vec2(0.f, 0.f));

	CTexture* pTex = CResMgr::GetI()->LoadTexture(L"Effect" + _type, L"texture\\bullet\\" + _type + L".bmp");
	CreateAnimator();

	if (_type == L"1")
	{
		GetAnimator()->CreateAnimation(L"IDLE", pTex, Vec2(0.f, 0.f), Vec2(48.f, 32.f), Vec2(48.f, 0.f), 0.5f, 4);
		SetScale(Vec2(48.f, 32.f) * 1.5f);
		SetAngleOffset(180);
	}
	else if (_type == L"2")
	{
		GetAnimator()->CreateAnimation(L"IDLE", pTex, Vec2(0.f, 0.f), Vec2(95.f, 32.f), Vec2(95.f, 0.f), 0.5f, 4);
		SetScale(Vec2(95.f, 32.f) * 1.2f);
	}
	else if (_type == L"3")
	{
		GetAnimator()->CreateAnimation(L"IDLE", pTex, Vec2(0.f, 0.f), Vec2(63.f, 32.f), Vec2(63.f, 0.f), 0.03f, 5);
		SetScale(Vec2(63.f, 32.f) * 1.5f);
	}


	GetAnimator()->Play(L"IDLE", true);
}






Bullet::~Bullet()
{

}

void Bullet::Update()
{
	mCurDelay += DT;
	if (mCurDelay > mDelay)
	{
		DeleteObject(this);
		return;
	}

	Vec2 vPos = GetPos();
	CScene* pCurScene = CSceneMgr::GetI()->GetCurScene();

	Vec2 vRes = CCore::GetI()->GetResolution();
	Vec2 vRenderPos = CCamera::GetI()->GetRenderPos(GetLocalPos());

	if (mBounceCount > 0)
	{
		if (vRes.y < vRenderPos.y
			|| 0 > vRenderPos.y)
		{
			m_vDir = m_vDir * Vec2(1.f, -1.f);
			SetAngle(m_vDir.ToAngle());
			--mBounceCount;
		}
		else if (vRes.x < vRenderPos.x
			|| 0 > vRenderPos.x)
		{
			m_vDir = m_vDir * Vec2(-1.f, 1.f);
			SetAngle(m_vDir.ToAngle());
			--mBounceCount;
		}
	}

	vPos.x += 500.f * m_vDir.x * DT;
	vPos.y += 500.f * m_vDir.y * DT;

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
		--mPenetrationCount;
		if (mPenetrationCount <= 0)
		{
			DeleteObject(this);
		}

		int randPos = 50;
		Particle* pEff = new Particle(L"4");
		pEff->SetPos(GetPos() + Vec2(rand() % randPos - randPos, rand() % randPos - randPos) + m_vDir * 25.f);
		pEff->SetName(L"Particle");
		CreateObject(pEff, GROUP_TYPE::EFFECT);

		if (mDivideCount > 0)
		{
			for (int i = 0; i < mDivideCount; ++i)
			{
				int angle = CRandom::GetI()->Next(0, 360);
				Bullet* pDiv = new Bullet(L"3");
				pDiv->SetPenetrationCount(0);
				pDiv->SetDivideCount(0);
				pDiv->SetBounceCount(0);
				pDiv->SetPos(GetPos());
				pDiv->SetScale(GetScale() * 0.65f);
				pDiv->SetAngle(angle);
				pDiv->SetDir(Vec2::FromAngle(angle).Normalize());
				CreateObject(pDiv, GROUP_TYPE::PROJ_PLAYER);
			}
		}
	}

	if (pOtherObj->GetName() == L"ENV")
	{
		DeleteObject(this);

		int randPos = 50;

		Particle* pEff = new Particle(L"1");
		pEff->SetPos(GetPos() + Vec2(rand() % randPos - randPos, rand() % randPos - randPos) + m_vDir * 25.f);
		pEff->SetName(L"Particle");
		CreateObject(pEff, GROUP_TYPE::EFFECT);
	}
}