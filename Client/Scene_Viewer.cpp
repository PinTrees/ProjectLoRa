#include "pch.h"
#include "Scene_Viewer.h"

//Core Mgr
#include "CCore.h"
#include "CCamera.h"
#include "CPathMgr.h"

// resource
#include "CResMgr.h"
#include "CSprite.h"
#include "CTexture.h"
#include "resource.h"
// ui
#include "CUI.h"
#include "CBtnUI.h"
#include "CWrap.h"
#include "CColumn.h"
#include "CRow.h"
#include "CPanelUI.h"
#include "TextUI.h"

//SceneMgr
#include "CSceneMgr.h"


// animator
#include "CAnimator.h"
#include "CAnimation.h"
//ViewerSceneMgr
#include "Player.h"
#include "AnimationView.h"

//ViewerSceneMgr //소숫점 없애려고 쓰는 헤더
#include <iomanip>

// player
#include "AI.h"
#include "PIdleState.h"
#include "PRunState.h"
#include "PDashState.h"
#include "PAtkState.h"

Scene_Viewer::Scene_Viewer()
	:mpTex(nullptr)
	, mpAnimViewer(nullptr)
	, mpAnimation(nullptr)
	, mAnimInfo{}
	, mpCurFrmInfo(nullptr)
{

}

Scene_Viewer::~Scene_Viewer()
{

}


void Scene_Viewer::Enter()
{
	Vect2 vResolution = CCore::GetI()->GetResolution();// 화면 크기
	CCore::GetI()->SetActiveMenu(true);


	CreateViewerUI(); //뷰어씬 UI 생성함수



	CCamera::GetI()->SetLookAt(vResolution / 2.f);
}

void Scene_Viewer::Render(HDC _dc)
{
	for (UINT i = 0; i < (UINT)GROUP_TYPE::END; ++i)
	{
		vector<CObject*>::iterator iter = mArrObj[i].begin();

		for (; iter != mArrObj[i].end();)
		{
			// Render Object
			if (!(*iter)->IsDead())
			{
				if ((*iter)->IsVisible())
				{
					(*iter)->Render(_dc);
				}
				++iter;
			}
			// Delete Object
			else
			{
				(*iter)->OnDestroy();
				iter = mArrObj[i].erase(iter);
			}
		}
	}
}

void Scene_Viewer::Update()
{
	CScene::Update();
	UpdateInfo();



}


void Scene_Viewer::Exit()
{
	CCore::GetI()->SetActiveMenu(false);
	DeleteAll();
}

void Scene_Viewer::AnimPlaySwitch()
{
	if (mpAnimViewer == nullptr)
		return;
	mpAnimViewer->GetAnimator()->PlaySwitch();
}

void Scene_Viewer::AnimStopSwitch()
{
	if (mpAnimViewer == nullptr)
		return;
	mpAnimViewer->GetAnimator()->StopSwitch();
}

void Scene_Viewer::AnimNextFrm()
{
	if (mpAnimViewer == nullptr)
		return;
	mpAnimViewer->GetAnimator()->NextFrm();
}

void Scene_Viewer::AnimPrevFrm()
{
	if (mpAnimViewer == nullptr)
		return;

	if (nullptr == mpAnimViewer->GetAnimator())
		return;

	mpAnimViewer->GetAnimator()->PrevFrm();
}





void Scene_Viewer::LoadAnimData()
{
	wchar_t szName[256] = {};

	OPENFILENAME ofn = {};

	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.hwndOwner = CCore::GetI()->GetMainHwnd();
	ofn.lpstrFile = szName;
	ofn.nMaxFile = sizeof(szName);
	ofn.lpstrFilter = L"BMP Files\0*.bmp\0";
	ofn.nFilterIndex = 0;
	ofn.lpstrFileTitle = nullptr;
	ofn.nMaxFileTitle = 0;

	wstring strTitleFolder = CPathMgr::GetI()->GetContentPath();
	strTitleFolder += L"viewer";

	ofn.lpstrInitialDir = strTitleFolder.c_str();
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

	// Modal Dialog
	if (GetOpenFileName(&ofn))
	{
		DeleteGroup(GROUP_TYPE::DEFAULT);
		Vect2 resolution = CCore::GetI()->GetResolution();


		wstring path = CPathMgr::GetI()->GetRelativePath(szName);
		CTexture* pTex = CResMgr::GetI()->LoadTexture(szName, path);
		mpTex = pTex;

		int w = mpTex->Width();
		int h = mpTex->Heigth();
		mAnimInfo.scale = Vect2(100.f, 100.f);
		// 애니메이션을 보여줄 오브젝트 생성
		mpAnimViewer = new AnimationView();
		mpAnimViewer->SetScale(mAnimInfo.scale);
		mpAnimViewer->SetPos(Vect2(resolution.x * 0.5f, resolution.y * 0.3f));


		//pAnimViewer->GetAnimator()->Play(L"test", false);
		CreateObject(mpAnimViewer, GROUP_TYPE::DEFAULT);
		//if (nullptr == mpAnimViewer->GetAnimator()->GetCurAnimation())
		//	mpAnimViewer->GetAnimator()->CreateAnimation();


		UpdateInfo();
	}


}

void Scene_Viewer::SaveAnimation()
{


	mpAnimViewer->GetAnimator()->GetCurAnimation()->Save(L"viewer\\" + mAnimInfo.name + L".anim");

}


void Scene_Viewer::CreateViewerUI()
{
	Vect2 vResolution = CCore::GetI()->GetResolution();

	CSprite* pPanelSprite = CResMgr::GetI()->LoadSprite(L"UI_panel_1", L"texture\\ui\\panel_1.png");
	pPanelSprite->SetRenderMode(SPRITE_RENDER_TYPE::POINT);

	//우측 ui판넬
	CPanelUI* pRightPanelUI = new CPanelUI;
	pRightPanelUI->SetScale(Vect2(300.f, vResolution.y));
	pRightPanelUI->SetPos(Vect2(vResolution.x - (pRightPanelUI->GetScale().x / 2), vResolution.y / 2.f));
	pRightPanelUI->SetTexture(pPanelSprite);
	pRightPanelUI->SetFixedPos(true);

	//우측 CWrap 바
	CColumn* pRightColumn = new CColumn;
	pRightColumn->SetScale(pRightPanelUI->GetScale());
	pRightColumn->SetPos(Vect2::zero);
	pRightPanelUI->AddChild(pRightColumn);


	CRow* pRow1 = new CRow();
	CRow* pRow2 = new CRow();
	CRow* pRow3 = new CRow();
	CRow* pRow4 = new CRow();
	CRow* pRow5 = new CRow();

	pRow1->SetScale(Vect2(300.f, 50.f));
	pRow2->SetScale(Vect2(300.f, 50.f));
	pRow3->SetScale(Vect2(300.f, 50.f));
	pRow4->SetScale(Vect2(300.f, 50.f));
	pRow5->SetScale(Vect2(300.f, 50.f));


	pRightColumn->AddChild(pRow1);
	pRightColumn->AddChild(pRow2);
	pRightColumn->AddChild(pRow3);
	pRightColumn->AddChild(pRow4);
	pRightColumn->AddChild(pRow5);

	//하단 ui판넬
	CPanelUI* pBottomPanelUI = new CPanelUI;
	pBottomPanelUI->SetScale(Vect2(vResolution.x - pRightPanelUI->GetScale().x, 160.f));
	pBottomPanelUI->SetPos(Vect2((vResolution.x / 2) - (pRightPanelUI->GetScale().x / 2.f), vResolution.y - (pBottomPanelUI->GetScale().y / 2.f)));
	pBottomPanelUI->SetTexture(pPanelSprite);
	pBottomPanelUI->SetFixedPos(true);

	//우측 CWrap 바
	CWrap* pBottomWrap = new CWrap;
	pBottomWrap->SetScale(pBottomPanelUI->GetScale());
	pBottomWrap->SetPos(Vect2::zero);
	pBottomPanelUI->AddChild(pBottomWrap);


	// 버튼	pToolBtn->SetClickedCallBack(&ChangeSceneTool, 0, 0);
	CBtnUI* pFileOpenBtn = new CBtnUI;
	pFileOpenBtn->SetContentOffset(Vect2(-40.f, -10.f));
	pFileOpenBtn->SetScale(Vect2(150.f, 50.f));
	pFileOpenBtn->GetText()->SetFontSize(1.f);
	pFileOpenBtn->SetText(L"파일열기");
	pFileOpenBtn->GetText()->SetFontSize(20.f);
	pFileOpenBtn->SetClickedCallBack(this, (SCENE_FUNC)&Scene_Viewer::LoadAnimData);
	pFileOpenBtn->SetTexture(CResMgr::GetI()->LoadTexture(L"UI_Btn_1", L"texture\\ui\\button_1.bmp"));
	pBottomWrap->AddChild(pFileOpenBtn);

	CBtnUI* pSaveBtn = new CBtnUI;
	pSaveBtn->SetContentOffset(Vect2(-40.f, -10.f));
	pSaveBtn->SetScale(Vect2(150.f, 50.f));
	pSaveBtn->SetText(L"저장");
	pSaveBtn->SetClickedCallBack(this, (SCENE_FUNC)&Scene_Viewer::SaveAnimation);
	pSaveBtn->GetText()->SetFontSize(20.f);
	pSaveBtn->SetTexture(CResMgr::GetI()->LoadTexture(L"UI_Btn_1", L"texture\\ui\\button_1.bmp"));
	pBottomWrap->AddChild(pSaveBtn);


	CBtnUI* pPrevBtn = new CBtnUI;
	pPrevBtn->SetContentOffset(Vect2(0.f, 0.f));
	pPrevBtn->SetScale(Vect2(150.f, 50.f));
	pPrevBtn->SetText(L"이전프레임");
	pPrevBtn->SetClickedCallBack(this, (SCENE_FUNC)&Scene_Viewer::AnimPrevFrm);
	pPrevBtn->GetText()->SetFontSize(20.f);
	pPrevBtn->SetTexture(CResMgr::GetI()->LoadTexture(L"UI_Btn_1", L"texture\\ui\\button_1.bmp"));
	pBottomWrap->AddChild(pPrevBtn);

	CBtnUI* pNextBtn = new CBtnUI;
	pNextBtn->SetContentOffset(Vect2(-40.f, -10.f));
	pNextBtn->SetScale(Vect2(150.f, 50.f));
	pNextBtn->SetText(L"다음프레임");
	pNextBtn->SetClickedCallBack(this, (SCENE_FUNC)&Scene_Viewer::AnimNextFrm);
	pNextBtn->GetText()->SetFontSize(20.f);
	pNextBtn->SetTexture(CResMgr::GetI()->LoadTexture(L"UI_Btn_1", L"texture\\ui\\button_1.bmp"));
	pBottomWrap->AddChild(pNextBtn);

	CBtnUI* pPlayBtn = new CBtnUI;
	pPlayBtn->SetContentOffset(Vect2(-40.f, -10.f));
	pPlayBtn->SetScale(Vect2(150.f, 50.f));
	pPlayBtn->SetText(L"정지");
	pPlayBtn->SetClickedCallBack(this, (SCENE_FUNC)&Scene_Viewer::AnimStopSwitch);
	pPlayBtn->GetText()->SetFontSize(20.f);
	pPlayBtn->SetTexture(CResMgr::GetI()->LoadTexture(L"UI_Btn_1", L"texture\\ui\\button_1.bmp"));
	pBottomWrap->AddChild(pPlayBtn);

	CBtnUI* pStopbtn = new CBtnUI;
	pStopbtn->SetContentOffset(Vect2(-40.f, -10.f));
	pStopbtn->SetScale(Vect2(150.f, 50.f));
	pStopbtn->SetText(L"시작");
	pStopbtn->SetClickedCallBack(this, (SCENE_FUNC)&Scene_Viewer::AnimPlaySwitch);
	pStopbtn->GetText()->SetFontSize(20.f);
	pStopbtn->SetTexture(CResMgr::GetI()->LoadTexture(L"UI_Btn_1", L"texture\\ui\\button_1.bmp"));
	pBottomWrap->AddChild(pStopbtn);


	//CBtnUI* pChangeBtn = new CBtnUI;
	//pChangeBtn->SetContentOffset(Vect2(-40.f, -10.f));
	//pChangeBtn->SetScale(Vect2(150.f, 50.f));
	//pChangeBtn->SetText(L"확인");
	//pChangeBtn->SetClickedCallBack(this, (SCENE_FUNC)&Scene_Viewer::ChangeAnim);
	//pChangeBtn->GetText()->SetFontSize(20.f);
	//pChangeBtn->SetTexture(CResMgr::GetI()->LoadTexture(L"UI_Btn_1", L"texture\\ui\\button_1.bmp"));
	//pBottomWrap->AddChild(pChangeBtn);




	CBtnUI* pSubXBtn = new CBtnUI;
	pSubXBtn->SetContentOffset(Vect2(-40.f, -10.f));
	pSubXBtn->SetScale(Vect2(150.f, 50.f));
	pSubXBtn->SetText(L"X_Pixel--");
	pSubXBtn->SetClickedCallBack(this, (SCENE_FUNC_P)&Scene_Viewer::ChangeInfo, (int)eBtnFunc::SUB_XPIXEL);
	pSubXBtn->GetText()->SetFontSize(20.f);
	pSubXBtn->SetTexture(CResMgr::GetI()->LoadTexture(L"UI_Btn_1", L"texture\\ui\\button_1.bmp"));
	pRow1->AddChild(pSubXBtn);

	CBtnUI* pAddXBtn = new CBtnUI;
	pAddXBtn->SetContentOffset(Vect2(-40.f, -10.f));
	pAddXBtn->SetScale(Vect2(150.f, 50.f));
	pAddXBtn->SetText(L"X_Pixel++");
	pAddXBtn->SetClickedCallBack(this, (SCENE_FUNC_P)&Scene_Viewer::ChangeInfo, (int)eBtnFunc::ADD_XPIXEL);
	pAddXBtn->GetText()->SetFontSize(20.f);
	pAddXBtn->SetTexture(CResMgr::GetI()->LoadTexture(L"UI_Btn_1", L"texture\\ui\\button_1.bmp"));
	pRow1->AddChild(pAddXBtn);



	CBtnUI* pSubYBtn = new CBtnUI;
	pSubYBtn->SetContentOffset(Vect2(-40.f, -10.f));
	pSubYBtn->SetScale(Vect2(150.f, 50.f));
	pSubYBtn->SetText(L"Y_Pixel--");
	pSubYBtn->SetClickedCallBack(this, (SCENE_FUNC_P)&Scene_Viewer::ChangeInfo, (int)eBtnFunc::SUB_YPIXEL);
	pSubYBtn->GetText()->SetFontSize(20.f);
	pSubYBtn->SetTexture(CResMgr::GetI()->LoadTexture(L"UI_Btn_1", L"texture\\ui\\button_1.bmp"));
	pRow2->AddChild(pSubYBtn);

	CBtnUI* pAddYBtn = new CBtnUI;
	pAddYBtn->SetContentOffset(Vect2(-40.f, -10.f));
	pAddYBtn->SetScale(Vect2(150.f, 50.f));
	pAddYBtn->SetText(L"Y_Pixel++");
	pAddYBtn->SetClickedCallBack(this, (SCENE_FUNC_P)&Scene_Viewer::ChangeInfo, (int)eBtnFunc::ADD_YPIXEL);
	pAddYBtn->GetText()->SetFontSize(20.f);
	pAddYBtn->SetTexture(CResMgr::GetI()->LoadTexture(L"UI_Btn_1", L"texture\\ui\\button_1.bmp"));
	pRow2->AddChild(pAddYBtn);




	CBtnUI* pSubLT = new CBtnUI;
	pSubLT->SetContentOffset(Vect2(-40.f, -10.f));
	pSubLT->SetScale(Vect2(150.f, 50.f));
	pSubLT->SetText(L"LT--");
	pSubLT->SetClickedCallBack(this, (SCENE_FUNC_P)&Scene_Viewer::ChangeInfo, (int)eBtnFunc::SUB_LT);
	pSubLT->GetText()->SetFontSize(20.f);
	pSubLT->SetTexture(CResMgr::GetI()->LoadTexture(L"UI_Btn_1", L"texture\\ui\\button_1.bmp"));
	pRow3->AddChild(pSubLT);

	CBtnUI* pAddLT = new CBtnUI;
	pAddLT->SetContentOffset(Vect2(-40.f, -10.f));
	pAddLT->SetScale(Vect2(150.f, 50.f));
	pAddLT->SetText(L"LT++");
	pAddLT->SetClickedCallBack(this, (SCENE_FUNC_P)&Scene_Viewer::ChangeInfo, (int)eBtnFunc::ADD_LT);
	pAddLT->GetText()->SetFontSize(20.f);
	pAddLT->SetTexture(CResMgr::GetI()->LoadTexture(L"UI_Btn_1", L"texture\\ui\\button_1.bmp"));
	pRow3->AddChild(pAddLT);

	CBtnUI* pSubDur = new CBtnUI;
	pSubDur->SetContentOffset(Vect2(-40.f, -10.f));
	pSubDur->SetScale(Vect2(150.f, 50.f));
	pSubDur->SetText(L"Duration--");
	pSubDur->SetClickedCallBack(this, (SCENE_FUNC_P)&Scene_Viewer::ChangeInfo, (int)eBtnFunc::SUB_DUR);
	pSubDur->GetText()->SetFontSize(20.f);
	pSubDur->SetTexture(CResMgr::GetI()->LoadTexture(L"UI_Btn_1", L"texture\\ui\\button_1.bmp"));
	pRow4->AddChild(pSubDur);

	CBtnUI* pAddDur = new CBtnUI;
	pAddDur->SetContentOffset(Vect2(-40.f, -10.f));
	pAddDur->SetScale(Vect2(150.f, 50.f));
	pAddDur->SetText(L"Duration++");
	pAddDur->SetClickedCallBack(this, (SCENE_FUNC_P)&Scene_Viewer::ChangeInfo, (int)eBtnFunc::ADD_DUR);
	pAddDur->GetText()->SetFontSize(20.f);
	pAddDur->SetTexture(CResMgr::GetI()->LoadTexture(L"UI_Btn_1", L"texture\\ui\\button_1.bmp"));
	pRow4->AddChild(pAddDur);


	CBtnUI* pSubMaxFrm = new CBtnUI;
	pSubMaxFrm->SetContentOffset(Vect2(-40.f, -10.f));
	pSubMaxFrm->SetScale(Vect2(150.f, 50.f));
	pSubMaxFrm->SetText(L"프레임수--");
	pSubMaxFrm->SetClickedCallBack(this, (SCENE_FUNC_P)&Scene_Viewer::ChangeInfo, (int)eBtnFunc::SUB_MAX_FRM_COUNT);
	pSubMaxFrm->GetText()->SetFontSize(20.f);
	pSubMaxFrm->SetTexture(CResMgr::GetI()->LoadTexture(L"UI_Btn_1", L"texture\\ui\\button_1.bmp"));
	pRow5->AddChild(pSubMaxFrm);

	CBtnUI* pAddMaxFrm = new CBtnUI;
	pAddMaxFrm->SetContentOffset(Vect2(-40.f, -10.f));
	pAddMaxFrm->SetScale(Vect2(150.f, 50.f));
	pAddMaxFrm->SetText(L"프레임수++");
	pAddMaxFrm->SetClickedCallBack(this, (SCENE_FUNC_P)&Scene_Viewer::ChangeInfo, (int)eBtnFunc::ADD_MAX_FRM_COUNT);
	pAddMaxFrm->GetText()->SetFontSize(20.f);
	pAddMaxFrm->SetTexture(CResMgr::GetI()->LoadTexture(L"UI_Btn_1", L"texture\\ui\\button_1.bmp"));
	pRow5->AddChild(pAddMaxFrm);




	// 텍스트 UI 애니메이션정보

	mpCurFrmInfo = new TextUI;
	mpCurFrmInfo->SetScale(Vect2(470.f, 50.f));
	mpCurFrmInfo->SetPos(Vect2(vResolution.x / 2, 50.f));
	mpCurFrmInfo->SetColor(RGB(255, 0, 255));
	mpCurFrmInfo->SetText(L"애니메이션을 생성해주세요");
	AddObject(mpCurFrmInfo, GROUP_TYPE::UI);

	mpCurFrmNumber = new TextUI;
	mpCurFrmNumber->SetScale(Vect2(400.f, 50.f));
	mpCurFrmNumber->SetColor(RGB(255, 255, 0));
	mpCurFrmNumber->SetText(L"프레임 : 0 / 0");
	mpCurFrmNumber->SetFontSize(20.f);
	pRightColumn->AddChild(mpCurFrmNumber);


	mpXPixelSize = new TextUI;
	mpXPixelSize->SetScale(Vect2(400.f, 50.f));
	mpXPixelSize->SetColor(RGB(255, 255, 0));
	mpXPixelSize->SetText(L"X픽셀 사이즈");
	mpXPixelSize->SetFontSize(20.f);
	pRightColumn->AddChild(mpXPixelSize);

	mpYPixelSize = new TextUI;
	mpYPixelSize->SetScale(Vect2(400.f, 50.f));
	mpYPixelSize->SetColor(RGB(255, 255, 0));
	mpYPixelSize->SetText(L"Y픽셀 사이즈");
	mpYPixelSize->SetFontSize(20.f);
	pRightColumn->AddChild(mpYPixelSize);

	mpLT = new TextUI;
	mpLT->SetScale(Vect2(400.f, 50.f));
	mpLT->SetColor(RGB(255, 255, 0));
	mpLT->SetText(L"시작LT포인트");
	mpLT->SetFontSize(20.f);
	pRightColumn->AddChild(mpLT);

	mpDuration = new TextUI;
	mpDuration->SetScale(Vect2(400.f, 50.f));
	mpDuration->SetColor(RGB(255, 255, 0));
	mpDuration->SetText(L"애니메이션 속도");
	mpDuration->SetFontSize(20.f);
	pRightColumn->AddChild(mpDuration);

	mpMaxFrm = new TextUI;
	mpMaxFrm->SetScale(Vect2(400.f, 50.f));
	mpMaxFrm->SetColor(RGB(255, 255, 0));
	mpMaxFrm->SetText(L"최대프레임수");
	mpMaxFrm->SetFontSize(20.f);
	pRightColumn->AddChild(mpMaxFrm);


	AddObject(pRightPanelUI, GROUP_TYPE::UI); //옵션 판넬 ui
	AddObject(pBottomPanelUI, GROUP_TYPE::UI); //옵션 판넬 ui

}

void Scene_Viewer::ChangeAnim()
{
	if (mpAnimViewer == nullptr)
		return;


	if (mAnimInfo.xPixel == 0 || mAnimInfo.yPixel == 0)
		return;

	mpAnimViewer->GetAnimator()->DeleteAnimation();//애니메이션 삭제후 변경된 정보로 다시 생성

	mpAnimViewer->GetAnimator()->CreateAnimation(
		mAnimInfo.name
		, mpTex
		, Vect2(0.f, mAnimInfo.FrameLT)				// 시작포인트지점
		, Vect2(mAnimInfo.xPixel, mAnimInfo.yPixel) // 한프레임 크기
		, Vect2(mAnimInfo.xPixel, 0.f)				// x축으로 스텝
		, mAnimInfo.Duration							// 한프레임당 시간
		, mAnimInfo.FrameCount);					// 프레임 개수 
	mpAnimViewer->SetScale(mAnimInfo.scale);
	mpAnimation = mpAnimViewer->GetAnimator()->GetCurAnimation();
	mpAnimViewer->GetAnimator()->Play(mAnimInfo.name, true);
	UpdateInfo();
	AnimStopSwitch();
}

void Scene_Viewer::UpdateInfo()
{
	if (mpAnimViewer == nullptr)
		return;
	if (nullptr == mpAnimation)
		return;
	if (nullptr == mpAnimViewer->GetAnimator()->GetCurAnimation())
		return;

	mpCurFrmInfo->SetText(L"애니메이션 이름 : " + mAnimInfo.name);

	mAnimInfo.curFrame = mpAnimViewer->GetAnimator()->GetCurAnimation()->GetCurFrame() + 1;
	mpCurFrmNumber->SetText(L"프레임 : "
		+ std::to_wstring(mAnimInfo.curFrame)
		+ L" / " + std::to_wstring(mAnimInfo.FrameCount));

	mpXPixelSize->SetText(L"\n x픽셀 크기 : " + std::to_wstring(mAnimInfo.xPixel));
	mpYPixelSize->SetText(L"\n y픽셀 크기 : " + std::to_wstring(mAnimInfo.yPixel));
	mpLT->SetText(L"시작y축 픽셀 지점 : " + std::to_wstring(mAnimInfo.FrameLT));
	mpDuration->SetText(L"애니메이션 속도 : " + to_wstring_with_precision(mAnimInfo.Duration, 1) + L"초");
}

void Scene_Viewer::ChangeInfo(eBtnFunc _e)
{
	switch (_e)
	{
	case eBtnFunc::ADD_XPIXEL:
		++mAnimInfo.xPixel;
		break;
	case eBtnFunc::SUB_XPIXEL:
		if (mAnimInfo.xPixel <= 0)
			break;
		--mAnimInfo.xPixel;
		break;
	case eBtnFunc::ADD_YPIXEL:
		++mAnimInfo.yPixel;
		break;
	case eBtnFunc::SUB_YPIXEL:
		if (mAnimInfo.yPixel <= 0)
			break;
		--mAnimInfo.yPixel;
		break;
	case eBtnFunc::ADD_LT:
		++mAnimInfo.FrameLT;
		break;
	case eBtnFunc::SUB_LT:
		if (mAnimInfo.FrameLT <= 0)
			break;
		--mAnimInfo.FrameLT;
		break;
	case eBtnFunc::ADD_MAX_FRM_COUNT:
		++mAnimInfo.FrameCount;
		break;
	case eBtnFunc::SUB_MAX_FRM_COUNT:
		if (mAnimInfo.FrameCount <= 1)
			break;
		--mAnimInfo.FrameCount;
		break;
	case eBtnFunc::ADD_DUR:
		mAnimInfo.Duration += 0.1f;
		break;
	case eBtnFunc::SUB_DUR:
		if (mAnimInfo.Duration <= 0.11f)
			break;
		mAnimInfo.Duration -= 0.1f;
		break;
	case eBtnFunc::ADD_X_SCALE:
		++mAnimInfo.scale.x;
		break;
	case eBtnFunc::SUB_X_SCALE:
		if (mAnimInfo.scale.x <= 1.f)
			break;
		--mAnimInfo.scale.x;
		break;
	case eBtnFunc::ADD_Y_SCALE:
		++mAnimInfo.scale.y;
		break;
	case eBtnFunc::SUB_Y_SCALE:
		if (mAnimInfo.scale.y <= 1.f)
			break;
		--mAnimInfo.scale.y;
		break;
	default:
		break;
	}

	ChangeAnim();

}

// float형의 소숫점을 precision번째 자리까지 출력
wstring Scene_Viewer::to_wstring_with_precision(float value, int precision)
{
	std::wstringstream stream;
	stream << std::fixed << std::setprecision(precision) << value;
	return stream.str();
}

/// <summary>
///  Animation Window Proc
/// </summary>
/// 
INT_PTR CALLBACK AnimationProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK)
		{

			//현재 씬 가져오기
			Scene_Viewer* curScene = (Scene_Viewer*)CSceneMgr::GetI()->GetCurScene();
			//현재씬에있는 애니메이션 구조체 가져오기
			tAniminfo& animInfo = curScene->GetAnimInfo();
			// 현재씬의 모든 애니메이션 지우기
			if (nullptr == curScene->GetAnimObj())
				return (INT_PTR)TRUE;

			curScene->GetAnimObj()->GetAnimator()->DeleteAnimation();
			//다이얼로그에 있는 Name 가져오기
			wchar_t szName[256] = {};
			GetDlgItemTextW(hDlg, IDC_ANIM_NAME, szName, 256);
			wstring iName(szName);
			animInfo.name = iName;
			// 시작점 포인트 가져오기 LeftTop
			animInfo.FrameLT = GetDlgItemInt(hDlg, IDC_FRAME_COUNT2, nullptr, false);
			// 한프레임의 x와 y 픽셀값 가져오기
			animInfo.xPixel = GetDlgItemInt(hDlg, IDC_X_PIXEL, nullptr, false);
			animInfo.yPixel = GetDlgItemInt(hDlg, IDC_Y_PIXEL, nullptr, false);
			// 한프레임당 넘어갈 시간값 가져오기
			animInfo.Duration = ((float)GetDlgItemInt(hDlg, IDC_FRAME_TIME, nullptr, false)) * 0.1f;
			CTexture* iTex = curScene->GetTex();

			if (nullptr == iTex)
				return (INT_PTR)TRUE;

			//텍스쳐의 총 크기 가져오기
			UINT x = iTex->Width();
			UINT y = iTex->Heigth();
			// 프레임 카운트 설정
			animInfo.FrameCount = 5;
			// 오브젝트 크기 픽셀에 맞게 조정
			curScene->GetAnimObj()->SetScale(Vect2(animInfo.xPixel, animInfo.yPixel));
			//해당 오브젝트의 애니메이션 생성
			curScene->GetAnimObj()->GetAnimator()->CreateAnimation(
				animInfo.name,
				iTex,
				Vect2(0.f, animInfo.FrameLT),
				Vect2(animInfo.xPixel, animInfo.yPixel),
				Vect2(animInfo.xPixel, 0.f),
				animInfo.Duration, animInfo.FrameCount);

			curScene->SetAnimation(curScene->GetAnimObj()->GetAnimator()->GetCurAnimation());

			curScene->GetAnimObj()->GetAnimator()->Play(animInfo.name, true);
			//curScene->GetAnimObj()->GetAnimator()->Stop();
			curScene->ChangeAnim();
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		else if (LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}