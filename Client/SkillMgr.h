#pragma once


class Skill;


// 추후 데이터베이스 메니저로 통합
// 게임 내 존재하는 모든 데이터 정보 집합 관리
// Item, Skill, Bullet, Monster
class SkillMgr
{
	SINGLE(SkillMgr);

private:
	Skill* mArrSkill[(UINT)SKILL_TYPE::END];


public:
	Skill* GetSkill(SKILL_TYPE type);


public:
	void Init();
};

