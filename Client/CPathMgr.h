#pragma once

class CPathMgr
{
	SINGLE(CPathMgr)
private:
	wchar_t		mSzContentPath[255];
	wchar_t		mSzRelativePath[255];

public:
	void Init();

	const wchar_t* GetContentPath() { return mSzContentPath; }


	wstring GetRelativePath(const wchar_t* _filepath);


};

