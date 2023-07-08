#pragma once

class CTimeMgr
{
	SINGLE(CTimeMgr)
private:
	LARGE_INTEGER m_CurCount;
	LARGE_INTEGER m_PrevCount;
	LARGE_INTEGER m_frequency;

	
	double		m_dDT;//������ ���� �ð��� ��ŸŸ��
	double		m_dAcc;// 1�� ���� �ð� üũ
	UINT		m_iCallCount; // �ʴ� ȣ�� Ƚ��
	UINT		m_iFPS; //������
	//DeltaTime����


public:
	void Init();
	void Update();
	void Render();


public:
	double GetDT() { return m_dDT; }
	float GetfDT() { return (float)m_dDT; }
};

