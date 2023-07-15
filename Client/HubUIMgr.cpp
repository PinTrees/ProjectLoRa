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
	: mBulletRowUI(nullptr)
	, mReroadUI(nullptr)
{
}


HubUIMgr::~HubUIMgr()
{
	DeleteObject(mBulletRowUI);
}


void HubUIMgr::Init()
{
	Vect2 vRes = CCore::GetI()->GetResolution();


	CRow* pRowUI = new CRow;
	pRowUI->SetPos(vRes - Vect2(200.f, 50.f));
	pRowUI->SetScale(Vect2(350.f, 50.f));
	pRowUI->SetSpacing(-8.f);

	mBulletRowUI = pRowUI;

	CTexture* pTex = CResMgr::GetI()->LoadTexture(L"UI_B1", L"texture\\ui\\bullet_1.bmp");

	for (int i = 0; i < 10; ++i)
	{
		CImageUI* bImg = new CImageUI;
		bImg->SetScale(Vect2(40.f, 60.f));

		bImg->CreateAnimator();
		bImg->GetAnimator()->CreateAnimation(L"IDLE", pTex, Vect2(0.f, 0.f), Vect2(32.f, 48.f), Vect2(32.f, 0.f), 0.1f, 4);
		bImg->GetAnimator()->Play(L"IDLE", true);
		mBulletRowUI->AddChild(bImg);
	}

	CreateObject(mBulletRowUI, GROUP_TYPE::UI);

	//mReroadUI = 
}


void HubUIMgr::SetBulletUI(UINT count)
{
	vector<CUI*> vecBulletUI = mBulletRowUI->GetChild();
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
