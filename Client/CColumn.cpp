#include "pch.h"
#include "CColumn.h"

CColumn::CColumn()
	: CUI(false)
	, mAlignment(ALIGNMENT::CENTER_LEFT)
{
}

CColumn::~CColumn()
{
}

void CColumn::Update()
{
	Vect2 vParentSize = GetScale();
	vector<CUI*> vecChild = GetChild();

	Vect2 vChildPos;

	if (mAlignment == ALIGNMENT::TOP_CENTER
		|| mAlignment == ALIGNMENT::CENTER
		|| mAlignment == ALIGNMENT::BOTTOM_CENTER)
		vChildPos.x = 0.f;

		vChildPos.y = -vParentSize.y / 2.f;

	for (size_t i = 0; i < vecChild.size(); ++i)
	{
		vChildPos.y += vecChild[i]->GetScale().y / 2.f;

		if (mAlignment == ALIGNMENT::TOP_LEFT
			|| mAlignment == ALIGNMENT::CENTER_LEFT
			|| mAlignment == ALIGNMENT::BOTTOM_LEFT)
		{
			vChildPos.x = vecChild[i]->GetScale().x / 2.f - vParentSize.x / 2.f;
		}

		else if (mAlignment == ALIGNMENT::TOP_RIGHT
			|| mAlignment == ALIGNMENT::CENTER_RIGHT
			|| mAlignment == ALIGNMENT::BOTTOM_RIGHT)
		{
			vChildPos.x = vParentSize.x / 2.f - vecChild[i]->GetScale().x / 2.f;
		}

		vecChild[i]->SetPos(vChildPos);
		vChildPos.y += vecChild[i]->GetScale().y / 2.f;
	}
}

void CColumn::Render(HDC dc)
{
	CUI::Render(dc);
}