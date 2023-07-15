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
	
	// ��Ʈ�� ũ�Ⱚ�� ���ҽ� Ű�� �� ��Ʈ �̸��� �߰�
	// ���� ��Ʈ�� �ٸ� ũ��� ��µ� �� ����
	// name.c_str() �� ������ �� ����. �ܺο��� ���ҽ� Key ���� �߰�
	mDefaultFont = CreateFont(size, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS,
		CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, name.c_str());
}



// ����ȭ �ʿ�
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
	// �ؽ�Ʈ ��� ������ 0���� �����Ǿ� ������� (���� �ȵ�) �����÷ο� ���� ���� �ν�
	const int maxWidth = (int)scale.x == 0 ? 9999 : (int)scale.x;

	// �ؽ�Ʈ�� ���ΰ� ��� ������ �Ѿ ��� �ٹٲ� ���ڸ� ���� �߰�
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
		// �� ���� ���������� ���
		for (size_t l = 0; l < lines.size(); ++l)
		{
			SIZE lineSize;
			GetTextExtentPoint32(dc, lines[l].c_str(), (int)(lines[l].size()), &lineSize);
			int lineX = (int)(pos.x - lineSize.cx * 0.5f);

			for (int i = -1; i <= 1; ++i)
				for (int j = -1; j <= 1; ++j)
					TextOut(dc, lineX + i, textY + j, lines[l].c_str(), (int)lines[l].size());
		
			// ���� ���� y ��ǥ ���� ����
			textY += lineSize.cy;
		}
		
	}

	// textY Pos Clear
	textY = (int)(pos.y - textSize.cy * 0.5f);
	SetTextColor(dc, style.color);

	// �� ���� ���������� ���
	for (size_t i = 0; i < lines.size(); ++i)
	{
		SIZE lineSize;
		GetTextExtentPoint32(dc, lines[i].c_str(), (int)(lines[i].size()), &lineSize);
		int lineX = (int)(pos.x - lineSize.cx * 0.5f);

		TextOut(dc, lineX, textY, lines[i].c_str(), (int)lines[i].size());

		// ���� ���� y ��ǥ ���� ����
		textY += lineSize.cy;
	}

	SelectObject(dc, hOldFont);
}
