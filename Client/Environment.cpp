#include "pch.h"
#include "Environment.h"

#include "CResMgr.h"
#include "CTimeMgr.h"

#include "CObject.h"
#include "CAnimation.h"
#include "CAnimator.h"

#include "CCollider.h"

#include "CScene.h"
#include "CSceneMgr.h"

#include "CKeyMgr.h"
#include "CTimeMgr.h"
#include "CTexture.h"

// 해당 오브젝트가 제거되면 해당인덱스에있는 노드추가
//#include "TileMgr.h"

Environment::Environment(const wstring& _type)
	: mType(_type)
	, mpShadowTex(nullptr)
	, mpTex(nullptr)
	, mvShadowOffset(Vect2::zero)
	, mvShadowScale(Vect2::zero)
{
	CreateCollider();
	SetName(L"ENV");

	// Texture 로딩하기
	mpTex = CResMgr::GetI()->LoadTexture(L"ENV_" + mType, L"texture\\map\\" + mType + L".bmp");

	if (mType == L"3")
	{
		mpShadowTex = CResMgr::GetI()->LoadTexture(L"Shadow_4", L"texture\\shadow\\4.bmp");
		SetScale(Vect2(48.f, 48.f));
		GetCollider()->SetScale(GetScale() * 0.9f);
		mvShadowOffset = Vect2(0.f, 15.f);
		mvShadowScale = Vect2(120.f, 74.f);
	}
	else if (mType == L"4")
	{
		mpShadowTex = CResMgr::GetI()->LoadTexture(L"Shadow_4", L"texture\\shadow\\4.bmp");
		SetScale(Vect2(19.f, 17.f) * 2.f);
		GetCollider()->SetScale(GetScale() * 0.9f);
		mvShadowOffset = Vect2(0.f, 12.f);
		mvShadowScale = Vect2(100.f, 55.f);
	}

	if (mType == L"101")
	{
		CreateAnimator();
		GetAnimator()->CreateAnimation(L"IDLE", mpTex, Vect2(0.f, 0.f), Vect2(80.f, 80.f), Vect2(80.f, 0.f), 0.1f, 1);
		GetAnimator()->FindAnimation(L"IDLE")->SetAllFrameOffet(Vect2(0.f, 0.f));
		GetAnimator()->Play(L"IDLE", true);
	}

	else if (mType == L"back_1")
	{
		CreateAnimator();
		GetAnimator()->CreateAnimation(L"IDLE", mpTex, Vect2(0.f, 0.f), Vect2(80.f, 80.f), Vect2(80.f, 0.f), 5.f, 1);
		GetAnimator()->FindAnimation(L"IDLE")->SetAllFrameOffet(Vect2(0.f, 0.f));
		GetAnimator()->Play(L"IDLE", true);
	}
}

Environment::~Environment()
{
}



void Environment::DistoryEnvi()
{
	//TileMgr::GetI()->SetWallNode(xIdx, yIdx, false);
	DeleteObject(this);
}

void Environment::Update()
{
}

void Environment::Render(HDC _dc)
{
	Vect2 vPos = CCamera::GetI()->GetRenderPos(GetPos());
	Vect2 vScale = GetScale();

	if (mpShadowTex)
	{
		TransparentBlt(_dc
			, (int)(vPos.x + mvShadowOffset.x - mvShadowScale.x * 0.5f)
			, (int)(vPos.y + mvShadowOffset.y - mvShadowScale.y * 0.5f)
			, (int)(mvShadowScale.x)
			, (int)(mvShadowScale.y)
			, mpShadowTex->GetDC()
			, 0, 0
			, (int)mpShadowTex->Width()
			, (int)mpShadowTex->Heigth()
			, RGB(255, 0, 255));
	}

	TransparentBlt(_dc
		, (int)(vPos.x - vScale.x * 0.5f)
		, (int)(vPos.y - vScale.y * 0.5f)
		, (int)(vScale.x)
		, (int)(vScale.y)
		, mpTex->GetDC()
		, 0, 0
		, (int)mpTex->Width()
		, (int)mpTex->Heigth()
		, RGB(255, 0, 255));

	CompnentRender(_dc);
}

void Environment::OnCollisionStay(CCollider* _pOther)
{
	CObject* pObj = _pOther->GetObj();
	if (pObj->GetName() == L"Player")
	{
		Vect2 vObjPos = _pOther->GetFinalPos();
		Vect2 vObjSize = _pOther->GetScale();

		Vect2 vPos = GetCollider()->GetFinalPos();
		Vect2 vSize = GetCollider()->GetScale();

		if (vObjPos.x < vPos.x - vSize.x / 2.f
			&& vObjPos.y + vObjSize.y / 2.f > vPos.y - vSize.y / 2.f
			&& vObjPos.y - vObjSize.y / 2.f < vPos.y + vSize.y / 2.f)				// 플레이어가 장애물보다 왼쪽에 있을 때
		{
			float fLen = abs(vObjPos.x - vPos.x);
			float fUp = (vObjSize.x / 2.f + vSize.x / 2.f) - fLen;

			vObjPos = pObj->GetPos();
			vObjPos.x -= fUp;

			pObj->SetPos(vObjPos);
		}
		else if (vObjPos.x > vPos.x + vSize.x / 2.f
			&& vObjPos.y + vObjSize.y / 2.f > vPos.y - vSize.y / 2.f
			&& vObjPos.y - vObjSize.y / 2.f < vPos.y + vSize.y / 2.f)				// 플레이어가 장애물보다 오른쪽에 있을 때
		{
			float fLen = abs(vObjPos.x - vPos.x);
			float fUp = (vObjSize.x / 2.f + vSize.x / 2.f) - fLen;

			vObjPos = pObj->GetPos();
			vObjPos.x += fUp;

			pObj->SetPos(vObjPos);
		}
		else if (vObjPos.y < vPos.y - vSize.y / 2.f
			&& vObjPos.x - vSize.x / 2.f < vPos.x + vSize.x / 2.f
			&& vObjPos.x + vSize.x / 2.f > vPos.x - vSize.x / 2.f)					// 플레이어가 장애물보다 위에 있을 때
		{
			float fLen = abs(vObjPos.y - vPos.y);
			float fUp = (vObjSize.y / 2.f + vSize.y / 2.f) - fLen;

			vObjPos = pObj->GetPos();
			vObjPos.y -= fUp;

			pObj->SetPos(vObjPos);
		}
		else if (vObjPos.y > vPos.y + vSize.y / 2.f
			&& vObjPos.x - vSize.x / 2.f < vPos.x + vSize.x / 2.f
			&& vObjPos.x + vSize.x / 2.f > vPos.x - vSize.x / 2.f)					// 플레이어가 장애물보다 아래에 있을 때
		{
			float fLen = abs(vObjPos.y - vPos.y);
			float fUp = (vObjSize.y / 2.f + vSize.y / 2.f) - fLen;

			vObjPos = pObj->GetPos();
			vObjPos.y += fUp;

			pObj->SetPos(vObjPos);
		}
	}
}
