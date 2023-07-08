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
		// UI�����ִٰ� ����ش�.
		targetUI->MouseOn();

		if (tapLbtn)
		{
			targetUI->MouseLbtnDown();
			targetUI->_lbtnDown = true;
		}
		else if (awayLbtn)
		{
			targetUI->MouseLbtnUp();

			if (targetUI->_lbtnDown)
			{
				// ���콺 �ö��ִ� ���¿��� �������̶���� Ŭ���̴�.
				targetUI->MouseLbtnClick();
			}

			// ���ʹ�ư ����, ������ üũ�� �ٽ� �����Ѵ�.
			targetUI->_lbtnDown = false;
		}
	}
}

void CUIMgr::SetFocusUI(CUI* ui)
{
	// �̹� ��Ŀ�� ���� ��� || ��Ŀ�� ������û�� ���
	if (_focusedUI == ui || nullptr == ui)
	{
		_focusedUI = ui;
		return;
	}

	// ���⼭ focusedUI �������ش�.
	_focusedUI = ui;

	CScene* curScene = CSceneMgr::GetI()->GetCurScene();
	vector<CObject*>& vecUI = curScene->GetUIGroups(GROUP_TYPE::UI);

	vector<CObject*>::iterator iter = vecUI.begin();

	// ��� ���� Ŭ���� �߻��ߴٴ� ������ �����.
	for (; iter != vecUI.end(); ++iter)
	{
		if (_focusedUI == *iter)
			break;
	}

	// ���� ������ �� �ڷ� ������ü
	vecUI.erase(iter);
	vecUI.push_back(_focusedUI);
}

CUI* CUIMgr::GetFocusUI()
{
	CScene* curScene = CSceneMgr::GetI()->GetCurScene();
	vector<CObject*>& vecUI = curScene->GetUIGroups(GROUP_TYPE::UI);

	bool tapLbtn = KEY_TAP(KEY::LBTN);

	// ���� ��Ŀ�� UI�� �޾Ƶΰ� ����Ǿ����� Ȯ���Ѵ�.
	CUI* focusedUI = _focusedUI;

	if (!tapLbtn)
	{
		return focusedUI;
	}

	vector<CObject*>::iterator targetIter = vecUI.end();
	vector<CObject*>::iterator iter = vecUI.begin();

	// ��� ���� Ŭ���� �߻��ߴٴ� ������ �����.
	for (; iter != vecUI.end(); ++iter)
	{
		if (dynamic_cast<CUI*>(*iter)->IsMouseOn())
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
			vecNoneTargetUI[i]->_lbtnDown = false;
		}
	}

	return targetUI;
}