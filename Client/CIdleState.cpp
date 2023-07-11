#include "pch.h"
#include "CIdleState.h"

#include "CSceneMgr.h"
#include "CScene.h"

#include "CPlayer.h"
#include "CMonster.h"

CIdleState::CIdleState()
	: CState(MON_STATE::IDLE)
{
}

CIdleState::~CIdleState()
{


}

void CIdleState::Update()
{
	// Player �� ��ġüũ
	CPlayer* pPlayer  = (CPlayer*)CSceneMgr::GetI()->GetCurScene()->GetPlayer();
	Vec2 vPlayerPos = pPlayer->GetPos();

	// ������ ���� �ȿ� ������ �������·� ��ȯ
	CMonster* pMonster = GetMonster();
	Vec2 vMonPos = pMonster->GetPos();

	Vec2 vDiff = vPlayerPos - vMonPos;
	float fLen = vDiff.Length();

	// �÷��̾ ������ �νĹ��� ������ ����
	if (fLen < pMonster->GetInfo().mfDetectRange)
	{
		ChangeAIState(GetAI(), MON_STATE::TRACE);
	}

}

void CIdleState::Enter()
{


}

void CIdleState::Exit()
{


}