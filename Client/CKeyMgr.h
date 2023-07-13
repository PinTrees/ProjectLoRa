#pragma once

enum class KEY_STATE
{
	NONE,
	TAP, //������
	HOLD,//������ ������
	AWAY, // �H����
};

enum class KEY
{
	LEFT,
	RIGHT,
	UP,
	DOWN,

	W,
	A,
	S,
	D,

	ALT,
	CTRL,
	LSHIFT,
	SPACE,
	ENTER,
	ESC,

	LBTN,
	RBTN,

	LAST
};



struct tKeyInfo
{
	KEY_STATE	eState; //Ű�� ���°�
	bool		bPrevPush;	//���������ӿ� �������� �ȴ�������
};

class CKeyMgr
{
	SINGLE(CKeyMgr)

private:
	vector<tKeyInfo>	m_vecKey;
<<<<<<< Updated upstream
	Vec2				mvCurMousePos;
=======
	Vect2				mvCurMousePos;
>>>>>>> Stashed changes

public:
	void Init();
	void Update();

public:
	KEY_STATE GetKeyState(KEY _eKey) { return m_vecKey[(int)_eKey].eState; };
<<<<<<< Updated upstream
	Vec2		GetMousePos() { return mvCurMousePos; }
=======
	Vect2		GetMousePos() { return mvCurMousePos; }
>>>>>>> Stashed changes
};

