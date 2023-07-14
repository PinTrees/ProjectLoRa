#include "pch.h"
#include "CColumn.h"




CColumn::CColumn()
	: CUI(false)
	, mAlignment(ALIGNMENT::CENTER)
    , mSpacing(0.f)
{
}

CColumn::~CColumn()
{
}



void CColumn::Update()
{
    if (GetChild().size() <= 0)
        return;

    Vect2 vParentSize = GetScale();
    vector<CUI*> children = GetChild();

    Vect2 vChildRootPos = Vect2::zero;

    if (IsAligmentCenter_Hor(mAlignment))
        vChildRootPos.x = 0.f;

    if (IsAligmentTop(mAlignment))
        vChildRootPos.y = -vParentSize.y * 0.5f;
    else if (IsAligmentBottom(mAlignment))
        vChildRootPos.y = vParentSize.y * 0.5f;
    else if (IsAligmentCenter(mAlignment))
    {
        float childrenHeight = 0.f;
        for (int i = 0; i < children.size(); ++i)
            childrenHeight += children[i]->GetScale().y;
        vChildRootPos.y = -childrenHeight * 0.5f - (mSpacing * (children.size() - 1) * 0.5f);
    }

    for (int i = 0; i < children.size(); ++i)
    {
        if (IsAligmentTop(mAlignment))
            vChildRootPos.y += children[i]->GetScale().y * 0.5f;
        else if (IsAligmentBottom(mAlignment))
            vChildRootPos.y -= children[i]->GetScale().y * 0.5f;
        else
            vChildRootPos.y += children[i]->GetScale().y * 0.5f;

        if (IsAligmentLeft(mAlignment))
        {
            Vect2 vChildSize = children[i]->GetScale();
            vChildRootPos.x = (vParentSize.x * 0.5f - vChildSize.x * 0.5f) * -1.f;
        }
        else if (IsAligmentRight(mAlignment))
        {
            Vect2 vChildSize = children[i]->GetScale();
            vChildRootPos.x = (vParentSize.x * 0.5f - vChildSize.x * 0.5f) * 1.f;
        }

        children[i]->SetPos(vChildRootPos);

        if (IsAligmentTop(mAlignment))
            vChildRootPos.y += children[i]->GetScale().y * 0.5f;
        else if (IsAligmentBottom(mAlignment))
            vChildRootPos.y -= children[i]->GetScale().y * 0.5f;
        else
            vChildRootPos.y += children[i]->GetScale().y * 0.5f;

        vChildRootPos.y += mSpacing;
    }
}

void CColumn::Render(HDC dc)
{
	CUI::Render(dc);
}