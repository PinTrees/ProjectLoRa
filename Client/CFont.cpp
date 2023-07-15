#include "pch.h"
#include "CFont.h"

#include "CUI.h"
#include "CPathMgr.h"
#include "TextUI.h"

CFont::CFont(HDC _dc)
	: mDC(_dc)
	, mDefaultFont(0)
{
}

CFont::~CFont()
{
	wstring pathStr = CPathMgr::GetI()->GetContentPath() + GetRelativePath();
	RemoveFontResource(pathStr.c_str());

	DeleteDC(mDC);
	DeleteObject(mDefaultFont);
}


void CFont::Load(const wstring& filePath, const wstring& name, int size)
{
	AddFontResource(filePath.c_str());
	
	// 폰트의 크기값을 리소스 키값 및 폰트 이름에 추가
	// 같은 폰트라도 다른 크기로 출력될 수 있음
	// name.c_str() 을 변경할 수 없음. 외부에서 리소스 Key 값에 추가
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

	vector<wstring> lines;
	wstring result;
	int lineWidth = 0;
	// 텍스트 출력 범위가 0으로 설정되어 있을경우 (설정 안됨) 오버플로우 모드로 강제 인식
	const int maxWidth = (int)scale.x == 0 ? 9999 : (int)scale.x;

	// 텍스트의 가로가 출력 범위를 넘어설 경우 줄바꿈 문자를 강제 추가
	for (size_t i = 0; i < str.size(); ++i)
	{
		wchar_t character = str[i];
		SIZE charSize;

		GetTextExtentPoint32(dc, &character, 1, &charSize);

		if (lineWidth + charSize.cx > maxWidth)
		{
			lines.push_back(result);
			result = L"";
			lineWidth = 0;
		}

		result += character;
		lineWidth += charSize.cx;
	}

	lines.push_back(result);


	if (style.boder)
	{
		SetTextColor(dc, style.outerColor);
		// 각 줄을 개별적으로 출력
		for (size_t l = 0; l < lines.size(); ++l)
		{
			SIZE lineSize;
			GetTextExtentPoint32(dc, lines[l].c_str(), (int)(lines[l].size()), &lineSize);
			int lineX = (int)(pos.x - lineSize.cx * 0.5f);

			for (int i = -1; i <= 1; ++i)
				for (int j = -1; j <= 1; ++j)
					TextOut(dc, lineX + i, textY + j, lines[l].c_str(), (int)lines[l].size());
		
			// 다음 줄의 y 좌표 간격 조정
			textY += lineSize.cy;
		}
		
	}

	// textY Pos Clear
	textY = (int)(pos.y - textSize.cy * 0.5f);
	SetTextColor(dc, style.color);

	// 각 줄을 개별적으로 출력
	for (size_t i = 0; i < lines.size(); ++i)
	{
		SIZE lineSize;
		GetTextExtentPoint32(dc, lines[i].c_str(), (int)(lines[i].size()), &lineSize);
		int lineX = (int)(pos.x - lineSize.cx * 0.5f);

		TextOut(dc, lineX, textY, lines[i].c_str(), (int)lines[i].size());

		// 다음 줄의 y 좌표 간격 조정
		textY += lineSize.cy;
	}

	SelectObject(dc, hOldFont);
}
