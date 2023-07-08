#include "pch.h"
#include "CEventMgr.h"

#include "CObject.h"
#include "CSceneMgr.h"
#include "CScene.h"

#include "AI.h"
#include "CState.h"

#include "CUIMgr.h"

CEventMgr::CEventMgr()
{

}
CEventMgr::~CEventMgr()
{

}

void CEventMgr::Update()
{
	//	==============================================
	//	���� �����ӿ��� ����ص� DeadObject ���� �����Ѵ�.
	//	==============================================

	for (size_t i = 0; i < mVecDeadObj.size(); ++i)
	{
		delete mVecDeadObj[i];
	}
	mVecDeadObj.clear();
	//	========
	//	Eventó��
	//	========

	for (size_t i = 0; i < mVecEvent.size(); ++i)
	{
		excute(mVecEvent[i]);
	}
	mVecEvent.clear();
}

void CEventMgr::excute(const tEvent& _eve)
{
	_eve.eEven;

	switch (_eve.eEven)
	{
	case EVENT_TYPE::CREATE_OBJECT:
	{
		// lParam : object Adress
		// wParam : Group TYPE
		CObject* pNewObj = (CObject*)_eve.lParam;

		GROUP_TYPE eType = (GROUP_TYPE)_eve.wParam;

		CSceneMgr::GetI()->GetCurScene()->AddObject(pNewObj, eType);
	}
	break;
	case EVENT_TYPE::DELETE_OBJECT:
	{
		// lParam : object Adress
		// Object �� Dead ���·� ����
		// �������� ������Ʈ���� ��Ƶд�.
		CObject* pDeadObj = (CObject*)_eve.lParam;
		pDeadObj->SetDead();
		mVecDeadObj.push_back(pDeadObj);

	}

	break;
	case EVENT_TYPE::SCENE_CHANGE:
		//lParam : NEXT SCENE TYPE
		// Scene ����
		CSceneMgr::GetI()->ChangeScene((SCENE_TYPE)_eve.lParam);

		// ��Ŀ�� UI���� (���� Scene�� UI�� ����Ű���ֱ⶧��
		CUIMgr::GetI()->SetFocusedUI(nullptr);

		break;

	case EVENT_TYPE::CHANGE_AI_STATE:
	{
		// lParam : AI
		// wParam : Next Type
		AI* pAI = (AI*)_eve.lParam;
		MON_STATE eNextState = (MON_STATE)_eve.wParam;
		pAI->ChangeState(eNextState);
	}
	}

}

