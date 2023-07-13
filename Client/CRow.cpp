#include "pch.h"
#include "CRow.h"



CRow::CRow()
	: CUI(false)
	, mAlignment(ALIGNMENT::CENTER)
{
}

CRow::~CRow()
{
}


void CRow::Update()
{
	Vect2 size = GetScale();
	size.y = 0.f;
	vector<CUI*> children = GetChild();

	Vect2 spacing = size / (float)children.size();
	float totalWidth = spacing.x * (children.size() - 1);

	for (int i = 0; i < children.size(); ++i)
	{
		children[i]->SetPos(Vect2(-totalWidth * 0.5f + spacing.x * i, 0.f));
	}
}


void CRow::Render(HDC dc)
{
	CUI::Render(dc);
}

