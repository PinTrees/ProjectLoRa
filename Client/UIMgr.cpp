#include "pch.h"
#include "UIMgr.h"

#include "CSceneMgr.h"
#include "CKeyMgr.h"
#include "CScene.h"
#include "CUI.h"

CUIMgr::CUIMgr()
	:
	_focusedUI(nullptr)
{

}

CUIMgr::~CUIMgr()
{

}

void CUIMgr::Update()
{
	_focusedUI = GetFocusUI();

	if (nullptr == _focusedUI)
	{
		return;
	}

	CUI* targetUI = GetTargetUI(_focusedUI);

	bool tapLbtn = KEY_TAP(KEY::LBTN);
	bool awayLbtn = KEY_AWAY(KEY::LBTN);

	if (nullptr != targetUI)
	{
		if (targetUI->IsDead())
			return;

		// UI위에있다고 알려준다.
		targetUI->MouseOn();

		if (tapLbtn)
		{
			targetUI->MouseLbtnDown();
			targetUI->mLbtnDown = true;
		}
		else if (awayLbtn)
		{
			targetUI->MouseLbtnUp();

			// 마우스 올라가있는 상태에서 때진것이라면은 클릭이다.
			if (targetUI->mLbtnDown)
			{
				targetUI->MouseLbtnClick();
			}

			// 왼쪽버튼 때면, 눌렀던 체크를 다시 해제한다.
			targetUI->mLbtnDown = false;
		}
	}
}


void CUIMgr::SetFocusUI(CUI* ui)
{
	// 이미 포커싱 중인 경우 || 포커싱 해제요청한 경우
	if (_focusedUI == ui || nullptr == ui)
	{
		_focusedUI = ui;
		return;
	}

	// 여기서 focusedUI 변경해준다.
	_focusedUI = ui;

	CScene* curScene = CSceneMgr::GetI()->GetCurScene();
	vector<CObject*>& vecUI = curScene->GetUIGroups();

	vector<CObject*>::iterator iter = vecUI.begin();

	// 적어도 왼쪽 클릭이 발생했다는 보장이 생긴다.
	for (; iter != vecUI.end(); ++iter)
	{
		if (_focusedUI == *iter)
			break;
	}

	// 벡터 내에서 맨 뒤로 순번교체
	vecUI.erase(iter);
	vecUI.push_back(_focusedUI);
}

CUI* CUIMgr::GetFocusUI()
{
	CScene* curScene = CSceneMgr::GetI()->GetCurScene();
	vector<CObject*>& vecUI = curScene->GetUIGroups();

	bool tapLbtn = KEY_TAP(KEY::LBTN);

	// 기존 포커싱 UI를 받아두고 변경되었는지 확인한다.
	CUI* focusedUI = _focusedUI;

	if (!tapLbtn)
	{
		return focusedUI;
	}

	vector<CObject*>::iterator targetIter = vecUI.end();
	vector<CObject*>::iterator iter = vecUI.begin();

	// 적어도 왼쪽 클릭이 발생했다는 보장이 생긴다.
	for (; iter != vecUI.end(); ++iter)
	{
		if (dynamic_cast<CUI*>(*iter)->IsMouseOn())
		{
			targetIter = iter;
		}
	}

	// 이번에 Focus된 UI가 없다.
	if (vecUI.end() == targetIter)
	{
		return nullptr;
	}

	focusedUI = dynamic_cast<CUI*>(*targetIter);

	// 벡터 내에서 맨 뒤로 순번교체
	vecUI.erase(targetIter);
	vecUI.push_back(focusedUI);

	return focusedUI;
}

// 부모 UI 내에서 실제로 타겟팅된 UI를 찾아서 반환한다.
CUI* CUIMgr::GetTargetUI(CUI* parentUI)
{
	bool awayLbtn = KEY_AWAY(KEY::LBTN);

	// 1. 부모 UI 포함, 모든 자식들을 검사 한다.
	CUI* targetUI = nullptr;

	static list<CUI*> queue;
	static vector<CUI*> vecNoneTargetUI;

	queue.clear();
	vecNoneTargetUI.clear();

	queue.push_back(parentUI);

	while (!queue.empty())
	{
		// queue 데이터 하나 꺼낸다.
		CUI* ui = queue.front();
		queue.pop_front();

		if (ui->IsMouseOn())
		{
			if (nullptr != targetUI)
			{
				vecNoneTargetUI.push_back(targetUI);
			}
			targetUI = ui;
		}
		else
		{
			vecNoneTargetUI.push_back(ui);
		}

		// 자식 UI를 다음 검사 목록에 추가
		const vector<CUI*>& vecChild = ui->GetChild();
		for (size_t i = 0; i < vecChild.size(); ++i)
		{
			queue.push_back(vecChild[i]);
		}
	}

	if (awayLbtn)
	{
		for (size_t i = 0; i < vecNoneTargetUI.size(); ++i)
		{
			vecNoneTargetUI[i]->mLbtnDown = false;
		}
	}

	return targetUI;
}
