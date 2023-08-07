#pragma once

class Monster;


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

