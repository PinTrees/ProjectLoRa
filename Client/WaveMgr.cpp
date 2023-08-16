#include "pch.h"
#include "WaveMgr.h"

#include "CCore.h"
#include "PlayerMgr.h"
#include "Player.h"
#include "MonsterFactory.h"
#include "Monster.h"

SINGLE_HEADER(WaveMgr);


WaveMgr::WaveMgr()
	: mCurWaveCount(false)
{

}

WaveMgr::~WaveMgr()
{

}


void WaveMgr::Init()
{
}



void WaveMgr::CreateWave()
{
	Vect2 vResolution = CCore::GetI()->GetResolution();

	// 몬스터를 소환할 가장자리 위치 설정
	float edgeDistance = 250.f;  // 가장자리로부터의 거리

	float xPos = PlayerMgr::GetI()->GetPlayer()->GetPos().x - vResolution.x * 0.5f;
	float yPos = PlayerMgr::GetI()->GetPlayer()->GetPos().y - vResolution.y * 0.5f;

	int MonsterCount = 1 + (float)mCurWaveCount * 0.5f;
	MonsterCount = MonsterCount > 100 ? 100 : MonsterCount;

	float ellipseWidth = vResolution.x + edgeDistance * 2.0f;  // 타원형의 가로 크기
	float ellipseHeight = vResolution.y + edgeDistance * 2.0f; // 타원형의 세로 크기

	Vect2 vCenter(xPos + vResolution.x * 0.5f, yPos + vResolution.y * 0.5f);

	for (int i = 0; i < MonsterCount; ++i) // 화면의 끝에서 근거리 공격 몬스터를 생성 (4방면에서 생성됨)
	{
		float angle = i * (360.0f / MonsterCount) + 20.f;  // 각도를 계산

		float x = vCenter.x + (ellipseWidth * 0.45f) * cos(angle * PI / 180.0f);
		float y = vCenter.y - (ellipseHeight * 0.45f) * sin(angle * PI / 180.0f);

		Vect2 vCreatePos(x, y);

		// 몬스터 생성 및 추가
		Monster* pShort = MonsterFactory::CreateMonster(MONSTER_TYPE::SHORT, vCreatePos);
		CreateObject(pShort, GROUP_TYPE::MONSTER);
	}

	int eliteMonsterCount = MonsterCount * 0.33f;
	for (int i = 0; i < eliteMonsterCount; ++i) // 화면의 끝에서 근거리 공격 몬스터를 생성 (4방면에서 생성됨)
	{
		float angle = i * (360.0f / eliteMonsterCount) + 20.f;  // 각도를 계산

		float x = vCenter.x + (ellipseWidth / 2.f) * cos(angle * PI / 180.0f);
		float y = vCenter.y - (ellipseHeight / 2.f) * sin(angle * PI / 180.0f);

		Vect2 vCreatePos(x, y);

		// 몬스터 생성 및 추가
		Monster* pShort = MonsterFactory::CreateMonster(MONSTER_TYPE::ELITE, vCreatePos);
		CreateObject(pShort, GROUP_TYPE::MONSTER);
	}

	int rangeMonsterCount = MonsterCount * 0.5f;
	for (int i = 0; i < rangeMonsterCount; ++i) // 화면의 끝에서 원거리 공격 몬스터를 생성 (4방면에서 생성됨)
	{
		float angle = i * (360.0f / rangeMonsterCount);  // 각도를 계산

		float x = vCenter.x + (ellipseWidth / 2.0f) * cos(angle * PI / 180.0f);
		float y = vCenter.y - (ellipseHeight / 2.0f) * sin(angle * PI / 180.0f);

		Vect2 vCreatePos(x, y);

		// 몬스터 생성 및 추가
		Monster* pLong = MonsterFactory::CreateMonster(MONSTER_TYPE::LONG, vCreatePos);
		CreateObject(pLong, GROUP_TYPE::MONSTER);
	}

	if (mCurWaveCount % 5 == 0 && mCurWaveCount != 0)
	{
		for (int i = 0; i < 88; ++i) // 화면의 끝에서 근거리 공격 몬스터를 생성 (4방면에서 생성됨)
		{
			float angle = i * (360.0f / 88);  // 각도를 계산

			float x = vCenter.x + (ellipseWidth / 2.0f) * cos(angle * PI / 180.0f);
			float y = vCenter.y - (ellipseHeight / 2.0f) * sin(angle * PI / 180.0f);

			Vect2 vCreatePos(x, y);

			// 몬스터 생성 및 추가
			Monster* pLong = MonsterFactory::CreateMonster(MONSTER_TYPE::LOCK, vCreatePos);
			CreateObject(pLong, GROUP_TYPE::MONSTER);
		}
	}

	++mCurWaveCount;	// 몬스터 웨이브의 진행 상태만큼 몬스터를 증가하기 위해 사용
}
