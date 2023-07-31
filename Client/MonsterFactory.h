#pragma once

class Monster;

enum class MONSTER_TYPE
{
	NORMAL,
	BOSS,
};


class MonsterFactory
{
private:
	static int mCreateCount;

public:
	static Monster* CreateMonster(MONSTER_TYPE type, Vect2 pos);


// ������ ��ü�� �ƴϹǷ� ����
private:
	MonsterFactory() {};
	~MonsterFactory() {};
};

