#pragma once

class Monster;


class MonsterFactory
{
private:
	static int mCreateCount;

public:
	static Monster* CreateMonster(MONSTER_TYPE type, Vect2 pos);


// 생성형 객체가 아니므로 제거
private:
	MonsterFactory() {};
	~MonsterFactory() {};
};

