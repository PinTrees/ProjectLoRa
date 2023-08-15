#include "pch.h"
#include "HelpDialogUI.h"

#include "CCore.h"
#include "CTimeMgr.h"

#include "TextUI.h"
#include "CBtnUI.h"
#include "GUIMgr.h"
#include "CColumn.h"
#include "CImageUI.h"

#include "CTexture.h"
#include "CResMgr.h"
#include "CScrollView.h"
#include "CPanelUI.h"
#include "CRow.h"

#include "UIMgr.h"
#include "DatabaseMgr.h"
#include "Skill.h"




HelpDialogUI::HelpDialogUI()
	: CImageUI()
{
	SetScale(CCore::GetI()->GetResolution());
	SetColor(RGB(0, 0, 0));
	SetAlpha(180);

	Vect2 vRes = CCore::GetI()->GetResolution();

	CPanelUI* pPanelUI = new CPanelUI;
	pPanelUI->SetFixedPos(false);
	pPanelUI->SetScale(Vect2(500.f, 550.f));
	pPanelUI->SetPos(Vect2::zero);
	pPanelUI->SetTexture(CResMgr::GetI()->LoadSprite(L"UI_panel_1", L"texture\\ui\\panel_1.bmp"));
	this->AddChild(pPanelUI);

	CScrollView* pScrollView = new CScrollView;
	pScrollView->SetPos(Vect2(0.f, 25.f));
	pScrollView->SetScale(Vect2(pPanelUI->GetScale().x * 0.85f, 350.f));
	pPanelUI->AddChild(pScrollView);

	CColumn* pColumn = new CColumn;
	pColumn->SetPos(Vect2(0.f, 128.f));
	pColumn->SetScale(Vect2(pScrollView->GetScale().x, 650.f));
	pScrollView->AddChild(pColumn);

	for (int i = 0; i < (int)SKILL_TYPE::END; ++i)
	{
		Skill* skill = DatabaseMgr::GetI()->GetSkill((SKILL_TYPE)i);
		if (nullptr == skill)
			return;

		CRow* pRow = new CRow;
		pRow->SetSpacing(18.f);
		pRow->SetScale(Vect2(pColumn->GetPos().x, 80.f));

		CImageUI* pIcon = new CImageUI; 
		pIcon->SetScale(Vect2(50.f, 50.f));
		pIcon->SetTexture(CResMgr::GetI()->LoadTexture(L"Icon_Skill_" + skill->GetIconStr(), L"texture\\icon\\" + skill->GetIconStr()));
		pRow->AddChild(pIcon); 

		TextUI* pInfoText = new TextUI;
		pInfoText->SetScale(Vect2(350.f, 50.f));
		pInfoText->SetText(L"스킬 정보 설명 텍스트 입력란");
		pInfoText->SetColor(RGB(255, 255, 255));
		pInfoText->SetFontSize(22.f);
		pRow->AddChild(pInfoText);

		pColumn->AddChild(pRow);
	}
	
	CBtnUI* pCloseBtn = new CBtnUI;
	pCloseBtn->SetPos(Vect2(0.f, 230.f));
	pCloseBtn->SetScale(Vect2(150.f, 42.f));
	pCloseBtn->SetText(L"닫기");
	pCloseBtn->SetTexture(CResMgr::GetI()->LoadTexture(L"UI_Btn_3", L"texture\\ui\\button\\3.bmp"));
	pCloseBtn->SetClickedCallBack(this, (OBJECT_FUNC)&HelpDialogUI::Close);
	pPanelUI->AddChild(pCloseBtn);
}

HelpDialogUI::~HelpDialogUI()
{
}


void HelpDialogUI::Close()
{
	SetVisible(false);
}


void HelpDialogUI::Build()
{
}

void HelpDialogUI::Update()
{
	CUI::Update();

	if (!IsVisible())
		return;
}

