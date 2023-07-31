#include "pch.h"
#include "UIMgr.h"

#include "CSceneMgr.h"
#include "CKeyMgr.h"
#include "CScene.h"
#include "CUI.h"


SINGLE_HEADER(CUIMgr);


CUIMgr::CUIMgr()
	: mFocusedUI(nullptr)
	, mbMouseOnUI(false)
{

}

CUIMgr::~CUIMgr()
{

}

void CUIMgr::Update()
{
	mFocusedUI = GetFocusUI();

	if (nullptr == mFocusedUI)
	{
		return;
	}

	CUI* targetUI = GetTargetUI(mFocusedUI);

	bool tapLbtn = KEY_TAP(KEY::LBTN);
	bool awayLbtn = KEY_AWAY(KEY::LBTN);

	if (nullptr != targetUI)
	{
		if (targetUI->IsDead() || !targetUI->IsVisible())
			return;

		// UI�����ִٰ� �˷��ش�.
		targetUI->MouseOn();

		if (tapLbtn)
		{
			targetUI->MouseLbtnDown();
			targetUI->mLbtnDown = true;
		}
		else if (awayLbtn)
		{
			targetUI->MouseLbtnUp();

			// ���콺 �ö��ִ� ���¿��� �������̶���� Ŭ���̴�.
			if (targetUI->mLbtnDown)
			{
				targetUI->MouseLbtnClick();
			}

			// ���ʹ�ư ����, ������ üũ�� �ٽ� �����Ѵ�.
			targetUI->mLbtnDown = false;
		}
	}

	mbMouseOnUI = nullptr != targetUI;
}


// �ش� UI�� �ֻ����� �����մϴ�.
void CUIMgr::SetTop(CUI* ui)
{
	if (nullptr == ui)
		return;

	CScene* curScene = CSceneMgr::GetI()->GetCurScene();
	vector<CObject*>& vecUI = curScene->GetUIGroups();

	vector<CObject*>::iterator iter = vecUI.begin();

	for (; iter != vecUI.end(); ++iter)
	{
		if (ui == *iter)
			break;
	}

	vecUI.erase(iter);
	vecUI.push_back(ui);
}

// �ش� UI�� ���� ��Ŀ���� �ο��մϴ�.
void CUIMgr::SetFocusUI(CUI* ui)
{
	// �̹� ��Ŀ�� ���� ��� || ��Ŀ�� ������û�� ���
	if (mFocusedUI == ui || nullptr == ui)
	{
		mFocusedUI = ui;
		return;
	}

	// ���⼭ focusedUI �������ش�.
	mFocusedUI = ui;

	CScene* curScene = CSceneMgr::GetI()->GetCurScene();
	vector<CObject*>& vecUI = curScene->GetUIGroups();

	vector<CObject*>::iterator iter = vecUI.begin();

	// ��� ���� Ŭ���� �߻��ߴٴ� ������ �����.
	for (; iter != vecUI.end(); ++iter)
	{
		if (mFocusedUI == *iter)
			break;
	}

	// ���� ������ �� �ڷ� ������ü
	vecUI.erase(iter);
	vecUI.push_back(mFocusedUI);
}

// ���� ��Ŀ�̵� UI�� ��ȯ�մϴ�.
CUI* CUIMgr::GetFocusUI()
{
	CScene* curScene = CSceneMgr::GetI()->GetCurScene();
	vector<CObject*>& vecUI = curScene->GetUIGroups();

	bool tapLbtn = KEY_TAP(KEY::LBTN);

	// ���� ��Ŀ�� UI�� �޾Ƶΰ� ����Ǿ����� Ȯ���Ѵ�.
	CUI* focusedUI = mFocusedUI;

	if (!tapLbtn)
	{
		return focusedUI;
	}

	vector<CObject*>::iterator targetIter = vecUI.end();
	vector<CObject*>::iterator iter = vecUI.begin();

	// ��� ���� Ŭ���� �߻��ߴٴ� ������ �����.
	for (; iter != vecUI.end(); ++iter)
	{
		if ((*iter)->IsDead() || !(*iter)->IsVisible())
			continue;

		if (dynamic_cast<CUI*>(*iter)->IsMouseOnUI())
		{
			targetIter = iter;
		}
	}

	// �̹��� Focus�� UI�� ����.
	if (vecUI.end() == targetIter)
	{
		return nullptr;
	}

	focusedUI = dynamic_cast<CUI*>(*targetIter);

	// ���� ������ �� �ڷ� ������ü
	vecUI.erase(targetIter);
	vecUI.push_back(focusedUI);

	return focusedUI;
}


// �θ� UI ������ ������ Ÿ���õ� UI�� ã�Ƽ� ��ȯ�Ѵ�.
// �θ� ������ ������ �ɷ����� ��� �ش� �������� �����մϴ�.
CUI* CUIMgr::GetTargetUI(CUI* parentUI)
{
	bool awayLbtn = KEY_AWAY(KEY::LBTN);

	// 1. �θ� UI ����, ��� �ڽĵ��� �˻� �Ѵ�.
	CUI* targetUI = nullptr;

	static list<CUI*> queue;
	static vector<CUI*> vecNoneTargetUI;

	queue.clear();
	vecNoneTargetUI.clear();

	queue.push_back(parentUI);

	while (!queue.empty())
	{
		// queue ������ �ϳ� ������.
		CUI* ui = queue.front();
		queue.pop_front();

		if (ui->IsMouseOnUI())
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

		// �ڽ� UI�� ���� �˻� ��Ͽ� �߰�
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