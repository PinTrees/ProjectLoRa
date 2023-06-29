#pragma once

enum class KEY_STATE
{
	NONE,
	TAP, //누를떄
	HOLD,//누르고 있을때
	AWAY, // 똇을때
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
	KEY_STATE	eState; //키의 상태값
	bool		bPrevPush;	//이전프레임에 눌렀는지 안눌렀는지
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

