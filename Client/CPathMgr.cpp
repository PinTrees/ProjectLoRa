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
