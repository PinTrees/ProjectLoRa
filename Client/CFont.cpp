#include "pch.h"
#include "CFont.h"

#include "CUI.h"
#include "CPathMgr.h"
#include "TextUI.h"

CFont::CFont(HDC _dc)
	: mDefaultFont(0)
{
}

CFont::~CFont()
{
	wstring pathStr = CPathMgr::GetI()->GetContentPath() + GetRelativePath();
	RemoveFontResource(pathStr.c_str());
	DeleteObject(mDefaultFont);
}


void CFont::Load(const wstring& filePath, const wstring& name, int size)
{
	AddFontResource(filePath.c_str());
	
	// 폰트의 크기값을 리소스 키값 및 폰트 이름에 추가
	mDefaultFont = CreateFont(size, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS,
		CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, name.c_str());
}



// 최적화 필요
void CFont::Render(HDC dc, const wstring& str, Vect2 pos, Vect2 scale, const tTextStyle& style)
{
    HFONT hOldFont = (HFONT)SelectObject(dc, mDefaultFont);
    SetBkMode(dc, TRANSPARENT);

    SIZE textSize;
    GetTextExtentPoint32(dc, str.c_str(), (int)(str.size()), &textSize);

    int textX = (int)(pos.x - textSize.cx * 0.5f);
    int textY = (int)(pos.y - textSize.cy * 0.5f);

    vector<wstring> lines = {};
    wstring result;
    int lineWidth = 0;
    const int maxWidth = (int)scale.x == 0 ? 9999 : (int)scale.x;

    for (size_t i = 0; i < str.size(); ++i)
    {
        wchar_t character = str[i];
        SIZE charSize;

        GetTextExtentPoint32(dc, &character, 1, &charSize);

        if (lineWidth + charSize.cx > maxWidth)
        {
            lines.push_back(result);
            result.clear(); // Clear result wstring
            lineWidth = 0;
        }

        result += character;
        lineWidth += charSize.cx;
    }

    lines.push_back(result);


    if (style.boder)
    {
        SetTextColor(dc, style.outerColor);
        for (size_t l = 0; l < lines.size(); ++l)
        {
            SIZE lineSize;
            GetTextExtentPoint32(dc, lines[l].c_str(), (int)(lines[l].size()), &lineSize);
            int lineX = (int)(pos.x - lineSize.cx * 0.5f);

            for (int i = -(style.boderWidth); i <= style.boderWidth; ++i)
                for (int j = -(style.boderWidth); j <= style.boderWidth; ++j)
                    TextOut(dc, lineX + i, textY + j, lines[l].c_str(), (int)lines[l].size());

            textY += lineSize.cy;
        }
    }

    textY = (int)(pos.y - textSize.cy * 0.5f);
    SetTextColor(dc, style.color);

    for (size_t i = 0; i < lines.size(); ++i)
    {
        SIZE lineSize;
        GetTextExtentPoint32(dc, lines[i].c_str(), (int)(lines[i].size()), &lineSize);
        int lineX = (int)(pos.x - lineSize.cx * 0.5f);

        TextOut(dc, lineX, textY, lines[i].c_str(), (int)lines[i].size());

        textY += lineSize.cy;

        lines[i].clear(); // Clear each wstring element
    }
    lines.clear(); // Clear the vector

    SelectObject(dc, hOldFont);
}
