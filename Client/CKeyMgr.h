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
	vector<tKeyInfo> m_vecKey;
public:
	void Init();
	void Update();

public:
	KEY_STATE GetKeyState(KEY _eKey)
	{ 
		return m_vecKey[(int)_eKey].eState;
	}
};

