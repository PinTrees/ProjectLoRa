#include "pch.h"
#include "CSlider.h"

#include "CResMgr.h"
#include "CTexture.h"
#include "CImageUI.h"

#include "CSliderBar.h"


CSlider::CSlider()
	: CUI(false)
	, mCurValue(0)
	, mLowValue(0)
	, mMaxValue(100)
{
	mpRoad = new CImageUI;
	mpRoad->SetName(L"SliderRoad");
	mpRoad->SetScale(Vect2(4.f, 4.f));
	mpRoad->SetColor(RGB(137, 90, 69));
	AddChild(mpRoad);

	mpSliderBar = new CSliderBar;
	mpSliderBar->mpOwner = this;
	AddChild(mpSliderBar);
}

CSlider::~CSlider()
{
}


void CSlider::SetValue(int val)
{
	mCurValue = val;

	Vect2 vScale = GetScale();
	Vect2 vScrollBarPos = mpSliderBar->GetPos();
	Vect2 vScrollBarSize = mpSliderBar->GetScale();
	mpSliderBar->SetPos(Vect2((vScale.x * -0.5f) + (vScrollBarSize.x * 0.5f), 0.f));

	if (mSliderFunc && mFuncOwner)
	{
		(mFuncOwner->*mSliderFunc)(mCurValue);
	}
}

void CSlider::SetHorSliderValue()
{
	Vect2 vScale = GetScale();

	Vect2 vScrollBarPos = mpSliderBar->GetPos();
	Vect2 vScrollBarSize = mpSliderBar->GetScale();

	// 스크롤바의 좌표와 스크롤뷰의 크기를 사용하여 mRatio 값을 계산하고,
	// 스크롤바의 크기만큼 비율에서 제거합니다.
	mRatio = (vScrollBarPos.x + (vScale.x - vScrollBarSize.x) * 0.5f) / (vScale.x - vScrollBarSize.x);
	mCurValue = (mMaxValue - mLowValue) * mRatio + mLowValue;

	mCurValue = mCurValue > mMaxValue ? mMaxValue : mCurValue < mLowValue ? mLowValue : mCurValue;

	// 등록 함수 호출
	if (mSliderFunc && mFuncOwner)
	{
		(mFuncOwner->*mSliderFunc)(mCurValue);
	}
}


void CSlider::Update()
{
	CUI::Update();

	mpRoad->SetScale(Vect2(GetScale().x, 4.f));

	Vect2 vScale = GetScale();
	Vect2 vScrollBarPos = mpSliderBar->GetPos();
	Vect2 vScrollBarSize = mpSliderBar->GetScale();

	// 스크롤바 이동 영역 제한
	if (mRatio < 0.f)
	{
		mRatio = 0.f;
		mpSliderBar->SetPos(Vect2((vScale.x * -0.5f) + (vScrollBarSize.x * 0.5f), vScrollBarPos.y));
	}
	else if (mRatio > 1.f)
	{
		mRatio = 1.f;
		mpSliderBar->SetPos(Vect2((vScale.x * 0.5f) - (vScrollBarSize.x * 0.5f), vScrollBarPos.y));
	}
}


void CSlider::Render(HDC dc)
{
	CUI::Render(dc);
	CUI::RenderChild(dc);
}

