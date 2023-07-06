#include "pch.h"
#include "CTimeMgr.h"
#include "CCore.h"


CTimeMgr::CTimeMgr()
	:m_CurCount{}
	, m_frequency{}
	, m_PrevCount{}
	, m_dDT(0.0f)
	, m_iCallCount(0)
	, m_dAcc(0)
{

}
CTimeMgr::~CTimeMgr()
{

}
void CTimeMgr::Init()
{
	QueryPerformanceCounter(&m_PrevCount);
	QueryPerformanceFrequency(&m_frequency);
}

void CTimeMgr::Update()
{
	QueryPerformanceCounter(&m_CurCount);
	// ���� �������� ī���ð�, ���� ������ ī���� ���� ���̸� ���Ѵ�.
	m_dDT = (double)(m_CurCount.QuadPart - m_PrevCount.QuadPart) / (double)m_frequency.QuadPart;

	// ����ī��Ʈ ���� ���簪���� ����(�������� ����� ���ؼ�)
	m_PrevCount = m_CurCount;

#ifdef _DEBUG
	//if (m_dDT > (1. / 60.))
	//	m_dDT = (1. / 60.);
#endif // DEBUG

}

void CTimeMgr::Render()
{
	++m_iCallCount;
	m_dAcc += m_dDT; //dt����

	if (m_dAcc >= 1.f)
	{
		m_iFPS = m_iCallCount;
		m_dAcc = 0.;
		m_iCallCount = 0;

		wchar_t szBuffer[255] = {};
		swprintf_s(szBuffer, L"FPS : %d, DT : %f", m_iFPS, m_dDT);
		SetWindowText(CCore::GetI()->GetMainHwnd(), szBuffer);

	}
}
