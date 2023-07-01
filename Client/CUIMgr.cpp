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

	// 1. FocusedUI Ȯ��

	mpFocusedUI = GetFocusedUI();

	if (!mpFocusedUI)
		return;

	// 2. FocuedUI ������ ,  �θ� UI ���� �ڽ� UI �� �� ���� Ÿ���� �� UI �� �����´�.
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
			// ���� ��ư ��� ������ üũ�� �ٽ� �����Ѵ�.
			pTargetUI->mbLbtnDown = false;
		}
	}
}

void CUIMgr::SetFocusedUI(CUI* _pUI)
{
	// �̹� ��Ŀ�� ���� ���  or  ��Ŀ�� ������û�ΰ�� nullptr�ΰ��
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


	// ���� ������ �� �ڷ� ���� ��ü
	vecUI.erase(iter);
	vecUI.push_back(mpFocusedUI);
}

CUI* CUIMgr::GetFocusedUI()
{

	CScene* pCurScene = CSceneMgr::GetI()->GetCurScene();
	vector<CObject*>& vecUI = pCurScene->GetUIGroup();

	bool bLbtnTap = KEY_TAP(KEY::LBTN);

	// ���� ��Ŀ�� UI �� �޾Ƶΰ� ����Ǿ����� Ȯ���Ѵ�.
	CUI* pFocusedUI = mpFocusedUI;

	if (!bLbtnTap)
	{
		return pFocusedUI;
	}


	
	// ���ʹ�ư TAP �� �߻��ߴٴ� �����Ͽ� ����
	vector<CObject*>::iterator targetiter = vecUI.end();
	vector<CObject*>::iterator iter = vecUI.begin();


	for (; iter != vecUI.end(); ++iter)
	{
		if (((CUI*)*iter)->IsMouseOn())
		{
			targetiter = iter;
		}
	}

	// �̹��� focus �� UI�������� ����
	if (vecUI.end() == targetiter)
	{
		return nullptr;
	}

	pFocusedUI = (CUI*)*targetiter;
	
	// ���� ������ �� �ڷ� ���� ��ü
	vecUI.erase(targetiter);
	vecUI.push_back(pFocusedUI);

	return pFocusedUI;
}

CUI* CUIMgr::GetTargetedUI(CUI* _pParentUI)
{
	bool bLbtnAway = KEY_AWAY(KEY::LBTN);


	// 1. �θ� UI ����, ��� �ڽĵ��� �˻� �Ѵ�.
	CUI* pTargetUI = nullptr;

	static list<CUI*>queue;
	static vector<CUI*> vecNoneTarget;

	queue.clear();
	vecNoneTarget.clear();

	queue.push_back(_pParentUI);

	while (!queue.empty())
	{
		// ť���� ������ �ϳ� ������
		CUI* pUI = queue.front();
		queue.pop_front();

		// ť���� ������ UI �� TargetUI ���� Ȯ��
		// Ÿ�� UI �� ��, �� �켱������ ���� ������ �� ���� ������ �ڽ�
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
			//���� ��ư ���� ���ȴ� üũ�� �ٽ� �����Ѵ�.
			vecNoneTarget[i]->mbLbtnDown = false;
		}
	}

	return pTargetUI;
}
