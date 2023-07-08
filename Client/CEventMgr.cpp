#include "pch.h"
#include "CEventMgr.h"

#include "CObject.h"
#include "CSceneMgr.h"
#include "CScene.h"
#include "AI.h"

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
		if (nullptr != mVecDeadObj[i])
		{
			delete mVecDeadObj[i];
		}
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
	case EVENT_TYPE::CHANGE_AI_STATE:
	{
		// lParam : AI
		// wParam : Next State
		AI* pAI = (AI*)_eve.lParam;
		MONSTER_STATE nextState = (MONSTER_STATE)_eve.wParam;
		pAI->ChangeState(nextState);
	}
		break;
	case EVENT_TYPE::SCENE_CHANGE:
		//lParam : NEXT SCENE TYPE
		CSceneMgr::GetI()->ChangeScene((SCENE_TYPE)_eve.lParam);
		break;
	} 
}

void CEventMgr::AddEvent(const tEvent& _eve)
{
	for (int i = 0; i < mVecEvent.size(); ++i)
	{
		if (_eve.eEven == EVENT_TYPE::DELETE_OBJECT
			&& (CObject*)mVecEvent[i].lParam == (CObject*)_eve.lParam)
		{
			return;
		}
	}

	mVecEvent.push_back(_eve);
}