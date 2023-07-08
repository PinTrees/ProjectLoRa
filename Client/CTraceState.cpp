#include "pch.h"
#include "CTraceState.h"

#include "CSceneMgr.h"
#include "CScene.h"
#include "CPlayer.h"
#include "CMonster.h"

#include "CTimeMgr.h"

CTraceState::CTraceState()
	:CState(MON_STATE::TRACE)
{
}

CTraceState::~CTraceState()
{
}
void CTraceState::Update()
{
	// 타겟팅 된 Player 를 쫓아간다.
	CPlayer* pPlayer= (CPlayer*)CSceneMgr::GetI()->GetCurScene()->GetPlayer();
	Vec2 vPlayerPos = pPlayer->GetPos();

	Vec2 vMonPos = GetMonster()->GetPos();

	// *** 플레이어랑 완전히겹치면 0, 0 이나오기때문에 오류뜸 수정필요
	Vec2 vMonDir =  vPlayerPos - vMonPos;
	
	vMonDir.Normalize();

	vMonPos += vMonDir * GetMonster()->GetInfo().mfSpeed* fDT;

	GetMonster()->SetPos(vMonPos);
}

void CTraceState::Enter()
{
}

void CTraceState::Exit()
{
}
