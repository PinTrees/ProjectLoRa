#include "pch.h"
#include "CPathMgr.h"

#include "CCore.h"

CPathMgr::CPathMgr()
	:mSzContentPath{}
{}

CPathMgr::~CPathMgr()
{}



void CPathMgr::Init()
{
	GetCurrentDirectory(255, mSzContentPath);

	int iLen = (int)wcslen(mSzContentPath);

	//상위 폴더로
	for (int i = iLen-1; 0 <= i; --i)
	{
		if ('\\' == mSzContentPath[i])
		{
			mSzContentPath[i] = '\0';
			break;
		}
	}

	wcscat_s(mSzContentPath, 255, L"\\bin\\content\\");
	// .. ->bin\\content\\

	// SetWindowText(CCore::GetI()->GetMainHwnd(), mSzContentPath);
}

 wstring CPathMgr::GetRelativePath(const wchar_t* _filepath)
{
	wstring strFilePath = _filepath;

	size_t iAbsLen = wcslen(mSzContentPath);
	size_t	iFullLen = strFilePath.length();

	wstring strRelativePath = strFilePath.substr(iAbsLen, iFullLen - iAbsLen);

	return strRelativePath;

}

