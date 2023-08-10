#include "pch.h"
#include "CScrollView.h"
#include "CResMgr.h"
#include "CTexture.h"
#include "CColumn.h"

#include "CKeyMgr.h"
#include "CTimeMgr.h"

#include "CPanelUI.h"
#include "CScrollBar.h"
#include "CImageUI.h"

#include "CCore.h"



CScrollView::CScrollView() // ScrollView 안에 넣을 UI와 ScrollView의 사이즈
	: CUI(false)
	, mpScrollBar(nullptr)
	, mRatio(0.f)
	, mvContentSize(Vect2::zero)
{
	SetFixedChildMouseCheck(true);

	mpBufferTexture = CResMgr::GetI()->CreateTexture(L"ScrollBuffer", 5000, 5000, RGB(255, 255, 255)); // 버퍼 생성

	mpScrollBar = new CScrollBar;	// 스크롤 바 생성 및 설정
	mpScrollBar->SetName(L"ScrollBar");
	mpScrollBar->SetScale(Vect2(16.f, 75.f));
	mpScrollBar->mScrollView = this;
	mpScrollBar->SetTexture(CResMgr::GetI()->LoadTexture(L"FW_ScrollBar", L"texture\\ui\\scrollview\\scrollbar.bmp"));
	AddChild(mpScrollBar);
	
	mpScrollRoad = new CImageUI;
	mpScrollRoad->SetName(L"ScrollRoad");
	mpScrollRoad->SetScale(Vect2(4.f, 10.f));
	mpScrollRoad->SetColor(RGB(137, 90, 69));
	AddChild(mpScrollRoad);
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

	Vect2 vPos = GetPos();
	Vect2 vScale = GetScale();

	float ratioY = mRatio * (mvContentSize.y - vScale.y + 48.f);

	// 자식 클릭을 위해 실제 위치값을 이동
	vector<CUI*> vecChild = GetChild();
	for (int i = 0; i < vecChild.size(); i++)
	{
		if (vecChild[i]->GetName() == L"ScrollBar" || vecChild[i]->GetName() == L"ScrollRoad")
			continue;

		// 자식 위치값을 스크롤 비율만큼 이동
		vecChild[i]->SetOffset(Vect2(0.f, (mvContentSize.y - vScale.y) * 0.5f - ratioY));
	}

	Vect2 vScrollBarPos = mpScrollBar->GetPos();
	Vect2 vScrollBarSize = mpScrollBar->GetScale();

	if (IsMouseOnUI())
	{
		float axis = CKeyMgr::GetI()->GetWheelAxis();
		mRatio += axis * DT * -0.02f;

		float startY = mRatio * (vScale.y - vScrollBarSize.y);
		mpScrollBar->SetPos(Vect2(vScrollBarPos.x
			, startY - (vScale.y * 0.5f)
			+ (vScrollBarSize.y * 0.5f)));
	}

	// 스크롤바 이동 영역 제한
	if (mRatio < 0.f)
	{
		mRatio = 0.f;
		mpScrollBar->SetPos(Vect2(vScrollBarPos.x
			, (vScale.y * 0.5f) + (vScrollBarSize.y * 0.5f)));
	}
	else if(mRatio > 1.f)
	{
		mRatio = 1.f;
		mpScrollBar->SetPos(Vect2(vScrollBarPos.x
			, (vScale.y * 0.5f) - (vScrollBarSize.y * 0.5f)));
	}


	Vect2 vScrollRoadSize = mpScrollRoad->GetScale();
	mpScrollRoad->SetPos(Vect2(vScale.x * 0.5f + vScrollBarSize.x * 0.5f, 0.f));
	mpScrollRoad->SetScale(Vect2(vScrollRoadSize.x, vScale.y));
}


void CScrollView::Render(HDC _dc)
{
	// 버퍼 DC 초기화
	mpBufferTexture->Clear(RGB(255, 254, 255));
	CUI::RenderChild(mpBufferTexture->GetDC());

	Vect2 vPos = IsCameraAffected() ? CCamera::GetI()->GetRenderPos(GetFinalPos()) : GetFinalPos();
	Vect2 vScale = GetScale();

	// 현재 스크롤 영역 산출
	float stratY = (vPos.y - vScale.y * 0.5f);
	float startX = (vPos.x - vScale.x * 0.5f);

	float renderGapY = 0.f;
	float renderGapX = 0.f;

	if (stratY < 0)
	{
		renderGapY = stratY * -1;
		stratY = 0.f;
	}

	if (startX < 0)
	{
		renderGapX = startX * -1;
		startX = 0.f;
	}

	// 스크롤 영역 메인DC에 출력
	TransparentBlt(_dc
		, (int)((vPos.x - vScale.x * 0.5f) + renderGapX)
		, (int)((vPos.y - vScale.y * 0.5f) + renderGapY)
		, (int)(vScale.x - renderGapX)
		, (int)(vScale.y - renderGapY)
		, mpBufferTexture->GetDC()
		, (int)startX
		, (int)stratY
		, (int)(vScale.x - renderGapX)
		, (int)(vScale.y - renderGapY)
		, RGB(255, 254, 255));

	mpScrollRoad->Render(_dc);
	mpScrollBar->Render(_dc);

	CUI::Render(_dc);
}


void CScrollView::AddChild(CUI* ui)
{
	CUI::AddChild(ui);

	// 신규 자식이 추가될 때 마다 컨텐츠 사이즈 재계산
	mRatio = 0.f;
	Vect2 vPos = GetPos();
	Vect2 vScale = GetScale();
	Vect2 vScrollBarSize = mpScrollBar->GetScale();

	mvContentSize = Vect2::zero;
	vector<CUI*> vecChild = GetChild();

	for (int i = 0; i < vecChild.size(); i++)
	{
		if (vecChild[i]->GetName() == L"ScrollBar" || vecChild[i]->GetName() == L"ScrollRoad")
			continue;

		mvContentSize += vecChild[i]->GetScale();
	}

	SetTopChild(mpScrollBar);

	float startY = mRatio * (vScale.y);
	mpScrollBar->SetPos(Vect2(vPos.x + vScale.x * 0.5f + vScrollBarSize.x * 0.5f
		, vPos.y + startY 
		- (vScale.y * 0.5f) 
		+ (vScrollBarSize.y * 0.5f)));
}

