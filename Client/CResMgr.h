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
	CTexture* CreateTexture(const wstring& _strKey, UINT _iWidth,UINT _iHeight);


	CTexture* FindTexture(const wstring& _strKey);

	friend class CObject;
};

