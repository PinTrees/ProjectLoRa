#include "pch.h"
#include "LevelupUIMgr.h"
#include "LevelupUI.h"
#include "Random.h"
#include "Player.h"

LevelupUIMgr::LevelupUIMgr()
	: mArrLvupUI{}
	, mCurLvupUI{}
{

}

LevelupUIMgr::~LevelupUIMgr()
{
	for (UINT i = 0; i < (UINT)LEVELUP_EFFECT::END; ++i)
	{
		if (nullptr != mArrLvupUI[i])
		{
			delete mArrLvupUI[i];
		}
	}
}

void LevelupUIMgr::Init()
{
	for (UINT i = 0; i < (UINT)LEVELUP_EFFECT::END; ++i)
	{
		mArrLvupUI[i] = new LevelupUI;
		switch (i)
		{
		case (UINT)LEVELUP_EFFECT::FULL_HP_UP:
			mArrLvupUI[i]->SetString(L"�ִ� ü�� ����");
			mArrLvupUI[i]->SetEffect(LEVELUP_EFFECT::FULL_HP_UP);

			break;
		case (UINT)LEVELUP_EFFECT::REGENERATION_HP_UP:
			mArrLvupUI[i]->SetString(L"ü�� ��� ����");
			mArrLvupUI[i]->SetEffect(LEVELUP_EFFECT::REGENERATION_HP_UP);

			break;
		case (UINT)LEVELUP_EFFECT::MOVE_SPEED_UP:
			mArrLvupUI[i]->SetString(L"�̵��ӵ� ����");
			mArrLvupUI[i]->SetEffect(LEVELUP_EFFECT::MOVE_SPEED_UP);

			break;
		case (UINT)LEVELUP_EFFECT::ATK_DAMAGE_UP:
			mArrLvupUI[i]->SetString(L"���ݷ� ����");
			mArrLvupUI[i]->SetEffect(LEVELUP_EFFECT::ATK_DAMAGE_UP);

			break;
		case (UINT)LEVELUP_EFFECT::ATK_SPEED_UP:
			mArrLvupUI[i]->SetString(L"���ݼӵ� ����");
			mArrLvupUI[i]->SetEffect(LEVELUP_EFFECT::ATK_SPEED_UP);

			break;
		case (UINT)LEVELUP_EFFECT::ATK_RANGE_UP:
			mArrLvupUI[i]->SetString(L"��Ÿ� ����");
			mArrLvupUI[i]->SetEffect(LEVELUP_EFFECT::ATK_RANGE_UP);

			break;
		case (UINT)LEVELUP_EFFECT::SHOT_SPEED_UP:
			mArrLvupUI[i]->SetString(L"ź�� ����");
			mArrLvupUI[i]->SetEffect(LEVELUP_EFFECT::SHOT_SPEED_UP);

			break;
		case (UINT)LEVELUP_EFFECT::RELOAD_SPEED_UP:
			mArrLvupUI[i]->SetString(L"������ �ӵ� ����");
			mArrLvupUI[i]->SetEffect(LEVELUP_EFFECT::RELOAD_SPEED_UP);

			break;
		case (UINT)LEVELUP_EFFECT::SHOT_ANGLE_UP:
			mArrLvupUI[i]->SetString(L"���߷� ����");
			mArrLvupUI[i]->SetEffect(LEVELUP_EFFECT::SHOT_ANGLE_UP);

			break;
		case (UINT)LEVELUP_EFFECT::SHOT_COUNT_UP:
			mArrLvupUI[i]->SetString(L"�߻�Ǵ� �Ѿ� ���� ����");
			mArrLvupUI[i]->SetEffect(LEVELUP_EFFECT::SHOT_COUNT_UP);

			break;
		case (UINT)LEVELUP_EFFECT::PENETRATION_UP:
			mArrLvupUI[i]->SetString(L"�Ѿ��� ���� �����ϴ� Ƚ�� ����");
			mArrLvupUI[i]->SetEffect(LEVELUP_EFFECT::PENETRATION_UP);

			break;
		case (UINT)LEVELUP_EFFECT::SPLITCOUNT_UP:
			mArrLvupUI[i]->SetString(L"�п��Ǵ� �Ѿ��� ���� ����");
			mArrLvupUI[i]->SetEffect(LEVELUP_EFFECT::SPLITCOUNT_UP);
			
			break;
		case (UINT)LEVELUP_EFFECT::BOUNTCECOUNT_UP:
			mArrLvupUI[i]->SetString(L"�Ѿ��� ���� ƨ��� Ƚ�� ����");
			mArrLvupUI[i]->SetEffect(LEVELUP_EFFECT::BOUNTCECOUNT_UP);
			
			break;
		}
	}
}

void LevelupUIMgr::Choice(Player* _player)
{
	int a = 0;
	int rand[3];
	for (int i = 0; i < 3; ++i)
	{
		rand[i] = CRandom::GetI()->Next(0, (int)LEVELUP_EFFECT::END);
		for (int j = 0; j < i; ++j)
		{
			if (rand[j] == rand[i])
				--i;
		}
	}

	for (int i = 0; i < 3; ++i)
	{
		mCurLvupUI[i] = mArrLvupUI[rand[i]];
		mCurLvupUI[i]->CreateLevelupUI(_player, Vect2(230.f + (float)i * 400.f, 350.f));
	}
}

void LevelupUIMgr::Delete()
{
	for (int i = 0; i < 3; ++i)
	{
		DeleteObject(mCurLvupUI[i]->GetLeaderUI());
	}
}