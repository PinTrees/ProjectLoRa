#include "pch.h"
#include "CUIMgr.h"

#include "CSceneMgr.h"
#include "CScene.h"
#include "CUI.h"

#include "CKeyMgr.h"


CUIMgr::CUIMgr()
	: mpFocusedUI(nullptr)
{

}
CUIMgr::~CUIMgr()
{

}

void CUIMgr::Update()
{

	// 1. FocusedUI 확인

	mpFocusedUI = GetFocusedUI();

	if (!mpFocusedUI)
		return;

	// 2. FocuedUI 내에서 ,  부모 UI 포함 자식 UI 들 중 실제 타겟팅 된 UI 를 가져온다.
	CUI* pTargetUI = GetTargetedUI(mpFocusedUI);

	bool bLbtnAway = KEY_AWAY(KEY::LBTN);
	bool bLbtnTap = KEY_TAP(KEY::LBTN);

	if (nullptr != pTargetUI)
	{
		pTargetUI->MouseOn();

		if (bLbtnTap)
		{
			pTargetUI->MouseLbtnDown();
			pTargetUI->mbLbtnDown = true;
		}
		else if (bLbtnAway)
		{
			pTargetUI->MouseLbtnUp();

			if (pTargetUI->mbLbtnDown)
			{
				pTargetUI->MouseLbtnClicked();
			}
			// 왼쪽 버튼 뗴면 눌렀던 체크를 다시 해제한다.
			pTargetUI->mbLbtnDown = false;
		}
	}
}

void CUIMgr::SetFocusedUI(CUI* _pUI)
{
	// 이미 포커싱 중인 경우  or  포커싱 해제요청인경우 nullptr인경우
	if (mpFocusedUI == _pUI || nullptr == _pUI)
	{
		mpFocusedUI = _pUI;
		return;
	}

	mpFocusedUI = _pUI;

	CScene* pCurScene = CSceneMgr::GetI()->GetCurScene();
	vector<CObject*>& vecUI = pCurScene->GetUIGroup();

	vector<CObject*>::iterator iter = vecUI.begin();

	for (; iter != vecUI.end(); ++iter)
	{
		if (mpFocusedUI == *iter)
		{
			break;
		}
	}


	// 벡터 내에서 맨 뒤로 순번 교체
	vecUI.erase(iter);
	vecUI.push_back(mpFocusedUI);
}

CUI* CUIMgr::GetFocusedUI()
{

	CScene* pCurScene = CSceneMgr::GetI()->GetCurScene();
	vector<CObject*>& vecUI = pCurScene->GetUIGroup();

	bool bLbtnTap = KEY_TAP(KEY::LBTN);

	// 기존 포커싱 UI 를 받아두고 변경되었는지 확인한다.
	CUI* pFocusedUI = mpFocusedUI;

	if (!bLbtnTap)
	{
		return pFocusedUI;
	}


	
	// 왼쪽버튼 TAP 이 발생했다는 전제하에 실행
	vector<CObject*>::iterator targetiter = vecUI.end();
	vector<CObject*>::iterator iter = vecUI.begin();


	for (; iter != vecUI.end(); ++iter)
	{
		if (((CUI*)*iter)->IsMouseOn())
		{
			targetiter = iter;
		}
	}

	// 이번에 focus 된 UI가없으면 리턴
	if (vecUI.end() == targetiter)
	{
		return nullptr;
	}

	pFocusedUI = (CUI*)*targetiter;
	
	// 벡터 내에서 맨 뒤로 순번 교체
	vecUI.erase(targetiter);
	vecUI.push_back(pFocusedUI);

	return pFocusedUI;
}

CUI* CUIMgr::GetTargetedUI(CUI* _pParentUI)
{
	bool bLbtnAway = KEY_AWAY(KEY::LBTN);


	// 1. 부모 UI 포함, 모든 자식들을 검사 한다.
	CUI* pTargetUI = nullptr;

	static list<CUI*>queue;
	static vector<CUI*> vecNoneTarget;

	queue.clear();
	vecNoneTarget.clear();

	queue.push_back(_pParentUI);

	while (!queue.empty())
	{
		// 큐에서 데이터 하나 꺼내기
		CUI* pUI = queue.front();
		queue.pop_front();

		// 큐에서 꺼내온 UI 가 TargetUI 인지 확인
		// 타겟 UI 들 중, 더 우선순위가 높은 기준은 더 낮은 계층의 자식
		if (pUI->IsMouseOn())
		{
			if (nullptr != pTargetUI)
			{
				vecNoneTarget.push_back(pTargetUI);
			}

			pTargetUI = pUI;
		}
		else
		{
			vecNoneTarget.push_back(pUI);
		}


		const vector<CUI*>& vecChild = pUI->GetChildUI();
		for (size_t i = 0; i < vecChild.size(); ++i)
		{
			queue.push_back(vecChild[i]);
		}
	}

	if (bLbtnAway)
	{
		for (size_t i = 0; i < vecNoneTarget.size(); ++i)
		{
			//왼쪽 버튼 떼면 눌렸던 체크를 다시 해제한다.
			vecNoneTarget[i]->mbLbtnDown = false;
		}
	}

	return pTargetUI;
}
