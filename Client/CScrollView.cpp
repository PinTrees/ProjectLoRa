#include "pch.h"
#include "CScrollView.h"
#include "CResMgr.h"
#include "CTexture.h"
#include "CColumn.h"
#include "CKeyMgr.h"

#include "CPanelUI.h"
#include "CScrollBar.h"

#include "CCore.h"

CScrollView::CScrollView() // ScrollView �ȿ� ���� UI�� ScrollView�� ������
	: CUI(false)
	, mpScrollBar(nullptr)
	, mContentUI(nullptr)
	, mRatio()
	, mvContentSize(Vect2::zero)
{
	mpTex = CResMgr::GetI()->CreateTexture(L"ScrollBuffer", 5000, 5000, RGB(255, 255, 255)); // ���� ����

	mpScrollBar = new CScrollBar;	// ��ũ�� �� ���� �� ����
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

	// ��ũ�ѹ��� ��ǥ�� ��ũ�Ѻ��� ũ�⸦ ����Ͽ� mRatio ���� ����ϰ�,
	// ��ũ�ѹ��� ũ�⸸ŭ �������� �����մϴ�.
	mRatio = (vScrollBarPos.y - vPos.y + (vScale.y - vScrollBarSize.y) * 0.5f) / (vScale.y - vScrollBarSize.y);
}



void CScrollView::Update()
{
	CUI::Update();

	Vect2 vPos = GetPos();
	Vect2 vScale = GetScale();

	float ratioY = mRatio * (mvContentSize.y - vScale.y + 48.f);

	// �ڽ� Ŭ���� ���� ���� ��ġ���� �̵�
	vector<CUI*> vecChild = GetChild();
	for (int i = 0; i < vecChild.size(); i++)
	{
		if (vecChild[i]->GetName() == L"ScrollBar")
			continue;

		// �ڽ� ��ġ���� ��ũ�� ������ŭ �̵�
		vecChild[i]->SetOffset(Vect2(0.f, (mvContentSize.y - vScale.y) * 0.5f - ratioY));
	}

	Vect2 vScrollBarPos = mpScrollBar->GetPos();
	Vect2 vScrollBarSize = mpScrollBar->GetScale();

	// ��ũ�ѹ� �̵� ���� ����
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
	// ���� DC �ʱ�ȭ
	mpTex->Clear(RGB(255, 0, 255));
	CUI::RenderChild(mpTex->GetDC());

	Vect2 vPos = IsCameraAffected() ? CCamera::GetI()->GetRenderPos(GetFinalPos()) : GetFinalPos();
	Vect2 vScale = GetScale();

	// ���� ��ũ�� ���� ����
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

	// ��ũ�� ���� ����DC�� ���
	TransparentBlt(_dc
		, (int)((vPos.x - vScale.x * 0.5f) + renderGapX)
		, (int)((vPos.y - vScale.y * 0.5f) + renderGapY)
		, (int)(vScale.x - renderGapX)
		, (int)(vScale.y - renderGapY)
		, mpTex->GetDC()

		, (int)startX
		, (int)stratY
		, (int)(vScale.x - renderGapX)
		, (int)(vScale.y - renderGapY)
		, RGB(255, 0, 255));

	mpScrollBar->Render(_dc);
	CUI::Render(_dc);
}



void CScrollView::SetContentUI(CUI* ui)
{
	mContentUI = ui;
	AddChild(ui);
}

void CScrollView::AddChild(CUI* ui)
{
	CUI::AddChild(ui);

	// �ű� �ڽ��� �߰��� �� ���� ������ ������ ����
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