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
        // start와 end가 같거나 end가 start보다 작거나 같은 경우
        // 이 예제에서는 start를 반환하도록 처리합니다.
        return start;
    }

	return rand() % (end - start) + start;
}
