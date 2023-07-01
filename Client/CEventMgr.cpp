#include "pch.h"
#include "CEventMgr.h"

#include "CObject.h"
#include "CSceneMgr.h"
#include "CScene.h"

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
	//	이전 프레임에서 등록해둔 DeadObject 들을 삭제한다.
	//	==============================================

	for (size_t i = 0; i < mVecDeadObj.size(); ++i)
	{
			delete mVecDeadObj[i];
	}
	mVecDeadObj.clear();
	//	========
	//	Event처리
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
	case CREATE_OBJECT:
	{
		// lParam : object Adress
		// wParam : Group TYPE
		CObject* pNewObj = (CObject*)_eve.lParam;

		GROUP_TYPE eType = (GROUP_TYPE)_eve.wParam;

		CSceneMgr::GetI()->GetCurScene()->AddObject(pNewObj, eType);
	}
		break;
	case DELETE_OBJECT:
	{
		// lParam : object Adress
		// Object 를 Dead 상태로 변경
		// 삭제예정 오브젝트들을 모아둔다.
		CObject* pDeadObj = (CObject*)_eve.lParam;
		pDeadObj->SetDead();
		mVecDeadObj.push_back(pDeadObj);

	}

		break;
	case SCENE_CHANGE:
		//lParam : NEXT SCENE TYPE
		// Scene 변경
		CSceneMgr::GetI()->ChangeScene((SCENE_TYPE)_eve.lParam);

		// 포커스 UI해제 (이전 Scene의 UI를 가르키고있기때문
		CUIMgr::GetI()->SetFocusedUI(nullptr);

		break;
	}
}
