#include "pch.h"
#include "HubUIMgr.h"

#include "CCore.h"

#include "CAnimator.h"
#include "CResMgr.h"
#include "CTexture.h"

#include "CUI.h"
#include "CPanelUI.h"
#include "CRow.h"
#include "CImageUI.h"

SINGLE_HEADER(HubUIMgr);


HubUIMgr::HubUIMgr()
	: mBulletUI(nullptr)
	, mReroadUI(nullptr)
{
}


HubUIMgr::~HubUIMgr()
{
	DeleteObject(mBulletUI);
}


void HubUIMgr::Init()
{
	Vect2 vRes = CCore::GetI()->GetResolution();

	mBulletUI = new CRow;
	mBulletUI->SetPos(vRes - Vect2(200.f, 50.f));
	mBulletUI->SetScale(Vect2(350.f, 50.f));

	CTexture* pTex = CResMgr::GetI()->LoadTexture(L"UI_B1", L"texture\\ui\\bullet_1.bmp");

	for (int i = 0; i < 10; ++i)
	{
		CImageUI* bImg = new CImageUI;
		bImg->SetScale(Vect2(40.f, 60.f));

		bImg->CreateAnimator();
		bImg->GetAnimator()->CreateAnimation(L"IDLE", pTex, Vect2(0.f, 0.f), Vect2(32.f, 48.f), Vect2(32.f, 0.f), 0.1f, 4);
		bImg->GetAnimator()->Play(L"IDLE", true);
		mBulletUI->AddChild(bImg);
	}

	CreateObject(mBulletUI, GROUP_TYPE::UI);

	//mReroadUI = 
}


void HubUIMgr::SetBulletUI(UINT count)
{
	vector<CUI*> vecBulletUI = mBulletUI->GetChild();
	for (int i = 0; i < vecBulletUI.size(); ++i)
	{
		if (i >= count)
		{
			vecBulletUI[i]->SetVisible(false);
		}
		else
		{
			vecBulletUI[i]->SetVisible(true);
		}
	}
}
