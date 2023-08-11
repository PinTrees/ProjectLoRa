#include "pch.h"
#include "CSlider.h"
#include "CSliderBar.h"

#include "CResMgr.h"

#include "CTexture.h"

CSlider::CSlider()
	: CUI(false)
	, mpRoadTex(nullptr)
	, mpSliderBar(nullptr)
	, mMaxValue()
	, mLowValue()
	, mCurValue()
{
	SetFixedChildMouseCheck(true);

	//mpRoadTex = CResMgr::GetI()->LoadTexture(L"", L"");

	mpSliderBar = new CSliderBar;	// 스크롤 바 생성 및 설정
	mpSliderBar->SetName(L"mpSliderBar");
	mpSliderBar->SetScale(Vect2(16.f, 16.f));
	mpSliderBar->SetOwner(this);
	mpSliderBar->SetTexture(CResMgr::GetI()->LoadTexture(L"mpSliderBar", L"texture\\ui\\scrollview\\scrollbar.bmp"));
	AddChild(mpSliderBar);
}

CSlider::~CSlider()
{
}


void CSlider::Update()
{

}

void CSlider::Render(HDC dc)
{
	mpSliderBar->Render(dc);

	CUI::Render(dc);
}

