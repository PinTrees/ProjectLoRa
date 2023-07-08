#pragma once

class CMonster;

enum class MONSTER_TYPE
{
	NORMAL,
	BOSS,
};


class MonsterFactory
{
public:
	static CMonster* CreateMonster(MONSTER_TYPE type, Vec2 pos);


// 생성형 객체가 아니므로 제거
private:
	MonsterFactory() {};
	~MonsterFactory() {};
};

