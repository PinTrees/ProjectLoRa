#include "pch.h"
#include "CCamera.h"


#include "CObject.h"
#include "CCore.h"	

#include "CTimeMgr.h"
#include "CKeyMgr.h"

#include "CResMgr.h"
#include "CTexture.h"

CCamera::CCamera()
	:mpTargetObj(nullptr)
	, mfTime(1.f)
	, mfSpeed(0.f)
	, mfAccTime(0.5f)
	, mpVeilTex(nullptr)
{
}

CCamera::~CCamera()
{
}


void CCamera::Update()
{
	if (mpTargetObj)
	{
		if (mpTargetObj->IsDead())
		{
			mpTargetObj = nullptr;
		}
		else
		{
			mvLookAt = mpTargetObj->GetPos();
		}
	}


	if (KEY_HOLD(KEY::UP))
		mvLookAt.y -= fDT * 500.f;
	if (KEY_HOLD(KEY::DOWN))
		mvLookAt.y += fDT * 500.f;
	if (KEY_HOLD(KEY::LEFT))
		mvLookAt.x -= fDT * 500.f;
	if (KEY_HOLD(KEY::RIGHT))
		mvLookAt.x += fDT * 500.f;


	// ȭ�� �߾���ǥ�� ī�޶� LookAt ��ǥ���� ���̰� ���
	calDiff();
}

void CCamera::calDiff()
{
	// ���� LookAt �� ���� look �� ���̰��� �����ؼ� ������ LookAt�� ���Ѵ�.

	mfAccTime += fDT;

	if (mfTime <= mfAccTime)
	{
		mvCurLookAt = mvLookAt;
	}
	else
	{
		Vec2 vLookDir = mvLookAt - mvPrevLookAt;

		if (!vLookDir.IsZero())
		{
			mvCurLookAt = mvPrevLookAt + vLookDir.Normalize() * mfSpeed * fDT;
		}

	}


	//Lerp(mvPrevLookAt, mvLookAt,)



	Vec2 vResolution = CCore::GetI()->GetResolution();
	Vec2 vCenter = vResolution / 2;

	mvDiff = mvCurLookAt - vCenter;
	mvPrevLookAt = mvCurLookAt;
}

void CCamera::Init()
{
	Vec2 vResolution = CCore::GetI()->GetResolution();

	mpVeilTex = CResMgr::GetI()->CreateTexture(L"CameraVeil", (UINT)vResolution.x, (UINT)vResolution.y);
}

void CCamera::Render(HDC _dc)
{

	if (mListCamEffect.empty())
		return;

	// �ð� �������� üũ
	tCamEffect& effect = mListCamEffect.front();
	effect.fCurTime += fDT;

	float fRatio = 0.f; // ����Ʈ ���� ����
	fRatio = effect.fCurTime / effect.fDuration;

	if (fRatio < 0.f)
		fRatio = 0.f;
	if (fRatio > 1.f)
		fRatio = 1.f;




	int iAlpha = 0;

	if (CAM_EFFECT::FADE_OUT == effect.eEffect)
	{
		iAlpha = (int)(255.f * fRatio);


	}
	else if (CAM_EFFECT::FADE_IN == effect.eEffect)
	{
		iAlpha = (int)(255.f * (1.f - fRatio));
	}



	BLENDFUNCTION bf = {};


	bf.BlendOp = AC_SRC_OVER;
	bf.BlendFlags = 0;
	bf.AlphaFormat = 0;
	bf.SourceConstantAlpha = iAlpha;

	AlphaBlend(_dc, 0, 0
		, mpVeilTex->Width()
		, mpVeilTex->Heigth()
		, mpVeilTex->GetDC(), 0, 0
		, mpVeilTex->Width()
		, mpVeilTex->Heigth(), bf);




	// ���� �ð��� ����Ʈ �ִ� �����ð��� �Ѿ ���
	if (effect.fDuration < effect.fCurTime)
	{
		// ȿ�� ����
		mListCamEffect.pop_front();
	}


}
