#include "pch.h"
#include "CWrap.h"


CWrap::CWrap()
	: CUI(false)
{
}

CWrap::~CWrap()
{
}

void CWrap::Update()
{
	Vect2 vParentPos = GetPos();
	Vect2 vParentSize = GetScale();
	vector<CUI*> vecChild = GetChild();

	Vect2 vChildPos;
	Vect2 vChildOffset = Vect2(10.f, 10.f);

	Vect2 LongestChildSize;

	vChildPos = vChildOffset - vParentSize / 2.f;

	for (size_t i = 0; i < vecChild.size(); ++i)
	{
		vChildPos += vecChild[i]->GetScale() / 2.f;

		vecChild[i]->SetPos(vChildPos);

		if (vecChild[i]->GetScale().y > LongestChildSize.y)
		{
			LongestChildSize = vecChild[i]->GetScale();
		}
		
		if ((i + 1) != vecChild.size()
			&& vecChild[i + 1]->GetScale().x > (vParentSize.x / 2.f - abs(vChildPos.x + vecChild[i]->GetScale().x / 2.f + vChildOffset.x * 2.f)))
		{
			vChildPos.x = vChildOffset.x - vParentSize.x / 2.f;
			vChildPos.y += LongestChildSize.y - vecChild[i]->GetScale().y / 2.f + vChildOffset.y;
			LongestChildSize = Vect2(0.f, 0.f);
		}
		else
		{
			vChildPos.x += vecChild[i]->GetScale().x / 2.f + vChildOffset.x;
			vChildPos.y -= vecChild[i]->GetScale().y / 2.f;
		}
	}
}

void CWrap::Render(HDC dc)
{
	CUI::Render(dc);
}