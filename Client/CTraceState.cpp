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
	// Ÿ���� �� Player �� �Ѿư���.
	CPlayer* pPlayer= (CPlayer*)CSceneMgr::GetI()->GetCurScene()->GetPlayer();
	Vec2 vPlayerPos = pPlayer->GetPos();

	Vec2 vMonPos = GetMonster()->GetPos();

	// *** �÷��̾�� ��������ġ�� 0, 0 �̳����⶧���� ������ �����ʿ�
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
