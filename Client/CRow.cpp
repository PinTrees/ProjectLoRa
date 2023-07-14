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
    Vect2 vParentSize = GetScale();
    vector<CUI*> children = GetChild();

    Vect2 vChildRootPos;
    float spacing = vParentSize.x / children.size();

    if (   mAlignment == ALIGNMENT::CENTER
        || mAlignment == ALIGNMENT::CENTER_LEFT
        || mAlignment == ALIGNMENT::CENTER_RIGHT)
        vChildRootPos.y = 0.f;

 
    vChildRootPos.x = -vParentSize.x * 0.5f;

    for (int i = 0; i < children.size(); ++i)
    {
        vChildRootPos.x += children[i]->GetScale().x * 0.5f;

        if (   mAlignment == ALIGNMENT::TOP_CENTER
            || mAlignment == ALIGNMENT::TOP_LEFT
            || mAlignment == ALIGNMENT::TOP_RIGHT)
        {
            Vect2 vChildSize = children[i]->GetScale();
            vChildRootPos.y = (vParentSize.y * 0.5f - vChildSize.y * 0.5f) * -1.f;
        }
        
        children[i]->SetPos(vChildRootPos);
        vChildRootPos.x += children[i]->GetScale().x * 0.5f;
    }
}


void CRow::Render(HDC dc)
{
	CUI::Render(dc);
}

