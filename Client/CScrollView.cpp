#include "pch.h"
#include "CScrollView.h"
#include "CResMgr.h"
#include "CTexture.h"
#include "CColumn.h"
#include "CKeyMgr.h"

#include "CPanelUI.h"
#include "CScrollBar.h"

#include "CCore.h"

CScrollView::CScrollView() // ScrollView 안에 넣을 UI와 ScrollView의 사이즈
	: CUI(false)
	, mpScrollBar(nullptr)
	, mRatio()
	, mvContentSize(Vect2::zero)
{
	mpTex = CResMgr::GetI()->CreateTexture(L"ScrollBuffer", 5000, 5000, RGB(255, 255, 255)); // 버퍼 생성

	mpScrollBar = new CScrollBar;	// 스크롤 바 생성 및 설정
	mpScrollBar->SetName(L"ScrollBar");
	mpScrollBar->SetScale(Vect2(20.f, 75.f));
	mpScrollBar->mScrollView = this;

	mRatio = 0.f;
	this->AddChild(mpScrollBar);
}

CScrollView::~CScrollView()
{
}




void CScrollView::SetVerticalScroll()
{
	Vect2 vPos = GetPos();
	Vect2 vScale = GetScale();

	Vect2 vScrollBarPos = mpScrollBar->GetPos();
	Vect2 vScrollBarSize = mpScrollBar->GetScale();

	// 스크롤바의 좌표와 스크롤뷰의 크기를 사용하여 mRatio 값을 계산하고,
	// 스크롤바의 크기만큼 비율에서 제거합니다.
	mRatio = (vScrollBarPos.y - vPos.y + (vScale.y - vScrollBarSize.y) * 0.5f) / (vScale.y - vScrollBarSize.y);
}


void CScrollView::Update()
{
	CUI::Update();

	vector<CUI*> vecChild = GetChild();
	for (int i = 0; i < vecChild.size(); i++)
	{
		if (vecChild[i]->GetName() == L"ScrollBar")
			continue;
		//vecChild[i]->SetPos();
	}

	Vect2 vPos = GetPos();
	Vect2 vScale = GetScale();

	Vect2 vScrollBarPos = mpScrollBar->GetPos();
	Vect2 vScrollBarSize = mpScrollBar->GetScale();

	if (mRatio < 0.f)
	{
		mRatio = 0.f;
		mpScrollBar->SetPos(Vect2(vScrollBarPos.x
			, vPos.y - (vScale.y * 0.5f)
			+ (vScrollBarSize.y * 0.5f)));
	}
	else if(mRatio > 1.f)
	{
		mRatio = 1.f;
		mpScrollBar->SetPos(Vect2(vScrollBarPos.x
			, vPos.y + (vScale.y * 0.5f)
			- (vScrollBarSize.y * 0.5f)));
	}
}


void CScrollView::Render(HDC _dc)
{
	mpTex->Clear(RGB(255, 0, 255));
	CUI::RenderChild(mpTex->GetDC());

	Vect2 vPos = IsCameraAffected() ? CCamera::GetI()->GetRenderPos(GetFinalPos()) : GetFinalPos();
	Vect2 vScale = GetScale();

	// 수직 비율 계산
	float startY = mRatio * (mvContentSize.y - vScale.y * 0.5f);

	TransparentBlt(_dc
		, (int)(vPos.x - vScale.x * 0.5f)
		, (int)(vPos.y - vScale.y * 0.5f)
		, (int)vScale.x
		, (int)vScale.y
		, mpTex->GetDC()

		, (int)(vPos.x - vScale.x * 0.5f)
		, (int)(vPos.y + startY - mvContentSize.y * 0.5f)
		//, (int)(vPos.y + vScale.y * 0.5f)
		, (int)vScale.x
		, (int)vScale.y
		, RGB(255, 0, 255));

	mpScrollBar->Render(_dc);
	CUI::Render(_dc);
}



void CScrollView::AddChild(CUI* ui)
{
	CUI::AddChild(ui);
	
	mRatio = 0.f;
	Vect2 vPos = GetPos();
	Vect2 vScale = GetScale();
	Vect2 vScrollBarSize = mpScrollBar->GetScale();

	mvContentSize = Vect2::zero;
	vector<CUI*> vecChild = GetChild();

	for (int i = 0; i < vecChild.size(); i++)
	{
		if (vecChild[i]->GetName() == L"ScrollBar")
			continue;

		mvContentSize += vecChild[i]->GetScale();
	}

	SetTopChild(mpScrollBar);

	float startY = mRatio * (vScale.y);
	mpScrollBar->SetPos(Vect2(vPos.x + vScale.x * 0.5f
		, vPos.y + startY 
		- (vScale.y * 0.5f) 
		+ (vScrollBarSize.y * 0.5f)));
}
