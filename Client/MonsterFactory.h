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


// ������ ��ü�� �ƴϹǷ� ����
private:
	MonsterFactory() {};
	~MonsterFactory() {};
};

