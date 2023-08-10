#include "pch.h"
#include "Bullet.h"

#include "CCore.h"

// Core Class Header
#include "CTexture.h"
#include "CScene.h"

// Core Manager Header
#include "CSceneMgr.h"
#include "CTimeMgr.h"
#include "CResMgr.h"

// Componets Header
#include "CAnimation.h"
#include "CAnimator.h"
#include "CCollider.h"

#include "Random.h"

// GameObject Header
#include "Monster.h"
#include "Particle.h"




Bullet::Bullet(const wstring& _type)
	: m_vDir(Vect2(1.f, 1.f))
	, mDelay(2.f)
	, mCurDelay(0.f)
	, mInfo({})
{
	m_vDir.Normalize();
	CreateCollider();
	GetCollider()->SetScale(Vect2(15, 15));
	GetCollider()->SetOffsetPos(Vect2(0.f, 0.f));

	CTexture* pTex = CResMgr::GetI()->LoadTexture(L"Effect" + _type, L"texture\\bullet\\" + _type + L".bmp");
	CreateAnimator();

	if (_type == L"1")
	{
		GetAnimator()->CreateAnimation(L"IDLE", pTex, Vect2(0.f, 0.f), Vect2(48.f, 32.f), Vect2(48.f, 0.f), 0.03f, 4);
		SetScale(Vect2(48.f, 32.f) * 1.2f);
		SetAngleOffset(180);
	}
	else if (_type == L"2")
	{
		GetAnimator()->CreateAnimation(L"IDLE", pTex, Vect2(0.f, 0.f), Vect2(95.f, 32.f), Vect2(95.f, 0.f), 0.5f, 4);
		SetScale(Vect2(95.f, 32.f) * 1.2f);
	}
	else if (_type == L"3")
	{
		GetAnimator()->CreateAnimation(L"IDLE", pTex, Vect2(0.f, 0.f), Vect2(63.f, 32.f), Vect2(63.f, 0.f), 0.03f, 5);
		SetScale(Vect2(63.f, 32.f) * 1.5f);
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

	Vect2 vPos = GetPos();
	CScene* pCurScene = CSceneMgr::GetI()->GetCurScene();

	Vect2 vRes = CCore::GetI()->GetResolution();
	Vect2 vRenderPos = CCamera::GetI()->GetRenderPos(GetLocalPos());

	if (mInfo.bounceCount > 0)
	{
		if (vRes.y < vRenderPos.y
			|| 0 > vRenderPos.y)
		{
			m_vDir = m_vDir * Vect2(1.f, -1.f);
			SetAngle(m_vDir.ToAngle());
			--mInfo.bounceCount;
		}
		else if (vRes.x < vRenderPos.x
			|| 0 > vRenderPos.x)
		{
			m_vDir = m_vDir * Vect2(-1.f, 1.f);
			SetAngle(m_vDir.ToAngle());
			--mInfo.bounceCount;
		}
	}

	vPos += m_vDir * DT * 350.f;

	SetPos(vPos);
	GetAnimator()->Update();
}

void Bullet::Render(HDC _dc)
{
	Vect2 vPos = GetPos();
	Vect2 vScale = GetScale();

	CompnentRender(_dc);
}


void Bullet::OnCollisionEnter(CCollider* _pOther)
{
	CObject* pOtherObj = _pOther->GetObj();

	if (pOtherObj->GetName() == L"Monster")
	{
		((Monster*)pOtherObj)->AddDamage(mInfo.damage);

		--mInfo.penetrationCount;
		if (mInfo.penetrationCount <= 0)
		{
			DeleteObject(this);
		}

		int randPos = 25;
		Particle* pEff = new Particle(L"202");
		pEff->SetName(L"Particle");
		pEff->SetPos(GetPos() + Vect2(rand() % randPos - randPos, rand() % randPos - randPos) + m_vDir * 25.f);
		CreateObject(pEff, GROUP_TYPE::EFFECT);

		if (mInfo.splitCount > 0)
		{
			for (int i = 0; i < mInfo.splitCount; ++i)
			{
				int angle = CRandom::GetI()->Next(0, 360);

				tBullet bInfo = {};
				bInfo.damage = mInfo.damage * 0.5f;
				bInfo.penetrationCount = 0;
				bInfo.bounceCount = 0;
				bInfo.splitCount = 0;

				Bullet* pDiv = new Bullet(L"3");
				pDiv->SetPos(GetPos());
				pDiv->SetScale(GetScale() * 0.65f);
				pDiv->SetAngle((float)angle);
				pDiv->SetDir(Vect2::FromAngle(angle).Normalize());
				pDiv->SetInfo(bInfo);
				CreateObject(pDiv, GROUP_TYPE::PROJ_PLAYER);
			}
		}
	}

	if (pOtherObj->GetName() == L"ENV")
	{
		DeleteObject(this);

		int randPos = 50;

		Particle* pEff = new Particle(L"1");
		pEff->SetName(L"Particle");
		pEff->SetPos(GetPos() + Vect2(rand() % randPos - randPos, rand() % randPos - randPos) + m_vDir * 25.f);
		CreateObject(pEff, GROUP_TYPE::EFFECT);
	}
}