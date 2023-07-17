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
	srand(static_cast<unsigned int>(GetTickCount64()));
}

int CRandom::Next(int start, int end)
{
	return rand() % (end - start + 1) + start;
}
