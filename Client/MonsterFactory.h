#pragma once

<<<<<<< Updated upstream
class CMonster;
=======
class Monster;
>>>>>>> Stashed changes

enum class MONSTER_TYPE
{
	NORMAL,
	BOSS,
};


class MonsterFactory
{
public:
<<<<<<< Updated upstream
	static CMonster* CreateMonster(MONSTER_TYPE type, Vec2 pos);
=======
	static Monster* CreateMonster(MONSTER_TYPE type, Vect2 pos);
>>>>>>> Stashed changes


// 생성형 객체가 아니므로 제거
private:
	MonsterFactory() {};
	~MonsterFactory() {};
};

