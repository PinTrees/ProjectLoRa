#pragma once

class CPathMgr
{
	SINGLE(CPathMgr)
private:
	wchar_t		mSzContentPath[256];
	wchar_t		mSzRelativePath[256];

public:
	void Init();

	const wchar_t* GetContentPath() { return mSzContentPath; }

	wstring GetRelativePath(const wchar_t* filePath);
};

