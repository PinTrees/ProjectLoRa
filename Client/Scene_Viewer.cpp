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
{

}

Scene_Viewer::~Scene_Viewer()
{

}

void Scene_Viewer::Enter()
{
	Vect2 vResolution = CCore::GetI()->GetResolution();// 화면 크기
	CCore::GetI()->SetActiveMenu(true);



	CSprite* pPanelSprite = CResMgr::GetI()->LoadSprite(L"UI_panel_1", L"texture\\ui\\panel_1.png");
	pPanelSprite->SetRenderMode(SPRITE_RENDER_TYPE::POINT);

	//ui판넬
	CPanelUI* pPanelUI = new CPanelUI;
	pPanelUI->SetScale(Vect2(vResolution.x, 200.f));
	pPanelUI->SetPos(Vect2(vResolution.x / 2.f, (vResolution.y - (pPanelUI->GetScale().y / 2.f))));
	pPanelUI->SetTexture(pPanelSprite);
	((CPanelUI*)pPanelUI)->SetFixedPos(false);

	//하단 바
	CRow* RowBar = new CRow;
	RowBar->SetScale(Vect2(vResolution.x, 200.f));
	RowBar->SetPos(Vect2::zero);
	RowBar->SetSpacing(100.f);
	pPanelUI->AddChild(RowBar);

	// 버튼	pToolBtn->SetClickedCallBack(&ChangeSceneTool, 0, 0);
	CBtnUI* pFileOpenBtn = new CBtnUI;
	pFileOpenBtn->SetContentOffset(Vect2(-40.f, -10.f));
	pFileOpenBtn->SetScale(Vect2(150.f, 50.f));
	pFileOpenBtn->SetText(L"파일열기");
	pFileOpenBtn->GetText()->SetFontSize(20.f);
	pFileOpenBtn->SetClickedCallBack(this, (SCENE_FUNC)&Scene_Viewer::LoadAnimData);
	pFileOpenBtn->SetTexture(CResMgr::GetI()->LoadTexture(L"UI_Btn_1", L"texture\\ui\\button_1.bmp"));
	RowBar->AddChild(pFileOpenBtn);
	CBtnUI* pPrevBtn = new CBtnUI;
	pPrevBtn->SetContentOffset(Vect2(0.f,0.f));
	pPrevBtn->SetScale(Vect2(150.f, 50.f));
	pPrevBtn->SetText(L"이전프레임");
	pPrevBtn->SetClickedCallBack(this, (SCENE_FUNC)&Scene_Viewer::AnimPrevFrm);
	pPrevBtn->GetText()->SetFontSize(20.f);
	pPrevBtn->SetTexture(CResMgr::GetI()->LoadTexture(L"UI_Btn_1", L"texture\\ui\\button_1.bmp"));
	RowBar->AddChild(pPrevBtn);

	CBtnUI* pNextBtn = new CBtnUI;
	pNextBtn->SetContentOffset(Vect2(-40.f, -10.f));
	pNextBtn->SetScale(Vect2(150.f, 50.f));
	pNextBtn->SetText(L"다음프레임");
	pNextBtn->SetClickedCallBack(this, (SCENE_FUNC)&Scene_Viewer::AnimNextFrm);
	pNextBtn->GetText()->SetFontSize(20.f);
	pNextBtn->SetTexture(CResMgr::GetI()->LoadTexture(L"UI_Btn_1", L"texture\\ui\\button_1.bmp"));
	RowBar->AddChild(pNextBtn);


	mpPlayBtn = new CBtnUI;
	mpPlayBtn->SetContentOffset(Vect2(-40.f, -10.f));
	mpPlayBtn->SetScale(Vect2(150.f, 50.f));
	mpPlayBtn->SetText(L"정지");
	mpPlayBtn->SetClickedCallBack(this, (SCENE_FUNC)&Scene_Viewer::AnimPlaySwitch);
	mpPlayBtn->GetText()->SetFontSize(20.f);
	mpPlayBtn->SetTexture(CResMgr::GetI()->LoadTexture(L"UI_Btn_1", L"texture\\ui\\button_1.bmp"));
	RowBar->AddChild(mpPlayBtn);

	// text ui 전체 프레임 수와 현재 보고있는 프레임수 ex) 1/4 전체 4프레임 1프레임화면

	//TextUI* pText = new TextUI;
	//pText->SetText(L"1");
	//RowBar->AddChild(pText);



	AddObject(pPanelUI, GROUP_TYPE::UI); //옵션 판넬 ui


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

	


}


void Scene_Viewer::Exit()
{
	CCore::GetI()->SetActiveMenu(false);
	DeleteAll();
}

void Scene_Viewer::AnimPlaySwitch()
{
	mpAnimViewer->GetAnimator()->PlaySwitch();

	if(mpPlayBtn->GetText()->GetText() == L"정지")
		mpPlayBtn->SetText(L"시작");
	else
	{
		mpPlayBtn->SetText(L"정지");
	}
}

void Scene_Viewer::AnimNextFrm()
{
	mpAnimViewer->GetAnimator()->NextFrm();
}

void Scene_Viewer::AnimPrevFrm()
{
	mpAnimViewer->GetAnimator()->PrevFrm();
}



void Scene_Viewer::LoadFile()
{

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
		CTexture* pTex = CResMgr::GetI()->LoadTexture(L"default", path);
		mpTex = pTex;
		
		int w = mpTex->Width();
		int h = mpTex->Heigth();

		// 애니메이션을 보여줄 오브젝트 생성
		mpAnimViewer = new AnimationView();
		mpAnimViewer->SetScale(Vect2(100.f, 100.f));
		mpAnimViewer->SetPos(resolution * 0.5f);
		//pAnimViewer->GetAnimator()->Play(L"test", false);
		CreateObject(mpAnimViewer, GROUP_TYPE::DEFAULT);

	}


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
		if (LOWORD(wParam) == IDOK )
		{
			
			wchar_t szName[256] = {};

			//x축 픽셀크기와 y축 픽셀크기 가져옴
			GetDlgItemTextW(hDlg,IDC_ANIM_NAME, szName,256);
			wstring name(szName);
			UINT FrameCount = 0;
			UINT FrameLT = GetDlgItemInt(hDlg, IDC_FRAME_COUNT2, nullptr, false);
			UINT xPixel = GetDlgItemInt(hDlg, IDC_X_PIXEL, nullptr, false);
			UINT yPixel = GetDlgItemInt(hDlg, IDC_Y_PIXEL, nullptr, false);
			float durTime = ((float)GetDlgItemInt(hDlg, IDC_FRAME_TIME, nullptr, false))*0.1f;
			Scene_Viewer* curScene = (Scene_Viewer*)CSceneMgr::GetI()->GetCurScene();
			curScene->GetAnimObj()->GetAnimator()->DeleteAnimation();
			CTexture* iTex = curScene->GetTex();
			UINT x = iTex->Width();
			UINT y = iTex->Heigth();
			FrameCount = x / xPixel;
			curScene->GetAnimObj()->SetScale(Vect2(xPixel, yPixel));
			curScene->GetAnimObj()->GetAnimator()->CreateAnimation(
				name,
				iTex,
				Vect2(0.f, FrameLT* yPixel),
				Vect2(xPixel, yPixel),
				Vect2(xPixel, 0.f),
				durTime, FrameCount);

			curScene->GetAnimObj()->GetAnimator()->Play(name,true);
			//curScene->GetAnimObj()->GetAnimator()->Stop();

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