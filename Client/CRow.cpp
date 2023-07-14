#include "pch.h"
#include "CRow.h"



CRow::CRow()
	: CUI(false)
	, mAlignment(ALIGNMENT::CENTER)
    , mSpacing(0.f)
{
}

CRow::~CRow()
{
}




void CRow::Update()
{
    if (GetChild().size() <= 0)
        return;

    Vect2 vParentSize = GetScale();
    vector<CUI*> children = GetChild();

    Vect2 vChildRootPos = Vect2::zero;

    if (IsAligmentCenter_Ver(mAlignment))
        vChildRootPos.y = 0.f;
 
    if(IsAligmentLeft(mAlignment))
        vChildRootPos.x = -vParentSize.x * 0.5f;
    else if(IsAligmentRight(mAlignment))
        vChildRootPos.x = vParentSize.x * 0.5f;
    else if (IsAligmentCenter(mAlignment))
    {
        float childrenWidth = 0.f;
        for (int i = 0; i < children.size(); ++i)
            childrenWidth += children[i]->GetScale().x;
        vChildRootPos.x = -childrenWidth * 0.5f - (mSpacing * (children.size() - 1) * 0.5f);
    }

    for (int i = 0; i < children.size(); ++i)
    {
        if(IsAligmentLeft(mAlignment))
            vChildRootPos.x += children[i]->GetScale().x * 0.5f;
        else if (IsAligmentRight(mAlignment))
            vChildRootPos.x -= children[i]->GetScale().x * 0.5f;
        else if (IsAligmentCenter(mAlignment))
            vChildRootPos.x += children[i]->GetScale().x * 0.5f;

        if (IsAligmentTop(mAlignment))
        {
            Vect2 vChildSize = children[i]->GetScale();
            vChildRootPos.y = (vParentSize.y * 0.5f - vChildSize.y * 0.5f) * -1.f;
        }
        else if (IsAligmentBottom(mAlignment))
        {
            Vect2 vChildSize = children[i]->GetScale();
            vChildRootPos.y = (vParentSize.y * 0.5f - vChildSize.y * 0.5f) * 1.f;
        }

        children[i]->SetPos(vChildRootPos);
       
        if (IsAligmentLeft(mAlignment))
            vChildRootPos.x += children[i]->GetScale().x * 0.5f;
        else if (IsAligmentRight(mAlignment))
            vChildRootPos.x -= children[i]->GetScale().x * 0.5f;
        else if (IsAligmentCenter(mAlignment))
            vChildRootPos.x += children[i]->GetScale().x * 0.5f;

        vChildRootPos.x += mSpacing;
    }
}


void CRow::Render(HDC dc)
{
	CUI::Render(dc);
}

