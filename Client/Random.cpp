#include "pch.h"
#include "Random.h"


SINGLE_HEADER(CRandom);

CRandom::CRandom()
{

}
CRandom::~CRandom()
{

}
void CRandom::Init()
{
	srand(GetTickCount64());
}

int CRandom::Next(int start, int end)
{
    if (end <= start) {
        // start�� end�� ���ų� end�� start���� �۰ų� ���� ���
        // �� ���������� start�� ��ȯ�ϵ��� ó���մϴ�.
        return start;
    }

	return rand() % (end - start) + start;
}
