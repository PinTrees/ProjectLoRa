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

	Q,

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
	Vect2				mvCurMousePos;
	float				mWheelAxis;


public:
	void Init();
	void Update();

public:
	KEY_STATE	GetKeyState(KEY _eKey) { return m_vecKey[(int)_eKey].eState; };
	Vect2		GetMousePos() { return mvCurMousePos; }

	void		SetWheelAxis(float amount) { mWheelAxis = amount; }
	float		GetWheelAxis() 
	{ 
		float result = mWheelAxis;
		mWheelAxis = 0.f;
		return result; 
	}
};

