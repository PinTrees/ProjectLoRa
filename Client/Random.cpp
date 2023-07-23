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
	return rand() % (end - start) + start;
}
