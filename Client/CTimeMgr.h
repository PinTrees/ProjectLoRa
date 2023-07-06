#pragma once

class CTimeMgr
{
	SINGLE(CTimeMgr)
private:
	LARGE_INTEGER m_CurCount;
	LARGE_INTEGER m_PrevCount;
	LARGE_INTEGER m_frequency;

	
	double		m_dDT;//프레임 간의 시간값 델타타임
	double		m_dAcc;// 1초 누적 시간 체크
	UINT		m_iCallCount; // 초당 호출 횟수
	UINT		m_iFPS; //프레임
	//DeltaTime구현


public:
	void Init();
	void Update();
	void Render();


public:
	double GetDT() { return m_dDT; }
	float GetfDT() { return (float)m_dDT; }
};

