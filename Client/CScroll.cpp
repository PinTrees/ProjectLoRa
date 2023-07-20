#include "pch.h"
#include "CScroll.h"
#include "CResMgr.h"
#include "CTexture.h"
#include "CColumn.h"
#include "CKeyMgr.h"
#include "CPanelUI.h"
#include "CCore.h"

CScroll::CScroll(CUI* _pUI, Vect2 _size) // ScrollView 안에 넣을 UI와 ScrollView의 사이즈
	: CUI(false)
	, mpScrollBar(nullptr)
	, mRatio()
{
	SetScale(_size);
	mpTargetUI = _pUI;
	mpTargetUI->SetPos(mpTargetUI->GetScale() / 2.f);
	this->AddChild(_pUI);

	mpTex = CResMgr::GetI()->CreateTexture(L"ScrollBuffer", 5000, 5000); // 버퍼 생성
	Rectangle(mpTex->GetDC(), 0, 0, 5000, 5000); // 버퍼 하얗게 칠하기

	mpScrollBar = new CPanelUI;		// 스크롤 바 생성 및 설정
	mpScrollBar->SetFixedPos_y(false);

	mRatio = GetScale().y / mpTargetUI->GetScale().y;
	mpScrollBar->SetScale(Vect2(10.f, GetScale().y * mRatio));

	mvInitScrollPos = Vect2(GetScale().x / 2.f - 10.f, 0.f - (GetScale().y / 2.f - mpScrollBar->GetScale().y / 2.f));

	mpScrollBar->SetPos(mvInitScrollPos);
	this->AddChild(mpScrollBar);
}

CScroll::~CScroll()
{
}

void CScroll::Update()
{
	CUI::Update();

	if (mpScrollBar->GetPos().y<= mvInitScrollPos.y)
		mpScrollBar->SetPos(Vect2(mpScrollBar->GetPos().x, mvInitScrollPos.y));

	else if(mpScrollBar->GetPos().y + mpScrollBar->GetScale().y / 2.f >= GetScale().y / 2.f)
		mpScrollBar->SetPos(Vect2(mpScrollBar->GetPos().x, GetScale().y / 2.f - mpScrollBar->GetScale().y / 2.f));
}

void CScroll::Render(HDC _dc)
{
	mpTargetUI->Render(mpTex->GetDC());

	BitBlt(_dc
		, (int)(GetPos().x - GetScale().x / 2.f)
		, (int)(GetPos().y - GetScale().y / 2.f)
		, (int)(GetScale().x)
		, (int)(GetScale().y)
		, mpTex->GetDC()
		, (int)(GetPos().x)
		, (int)(GetPos().y) + (int)(mpScrollBar->GetPos().y - mvInitScrollPos.y) / mRatio
		, SRCCOPY);

	mpScrollBar->Render(_dc);
}
