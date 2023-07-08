#pragma once

class CTexture;
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

	friend class CObject;
};

