#pragma once

class CTexture;
class CFont;
class CRes;

class CResMgr
{
	SINGLE(CResMgr);

private:
	map<wstring, CRes*> mMapTex;

public:
	CTexture* LoadTexture(const wstring& _strKey, const wstring& _strRelativePath);
	CTexture* FindTexture(const wstring& _strKey);

	CTexture* CreateTexture(const wstring& strkey, UINT width, UINT height, COLORREF color=NULL);

	CFont* LoadFont(const wstring& _strKey, const wstring& _strRelativePath, int _size, bool _border);
	CFont* FindFont(const wstring& _strKey);

	friend class CObject;
};

