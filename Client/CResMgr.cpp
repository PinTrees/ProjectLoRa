#include "pch.h"
#include "CResMgr.h"

#include "CCore.h"

#include "CPathMgr.h"
#include "CTexture.h"	
#include "CFont.h"


SINGLE_HEADER(CResMgr);


CResMgr::CResMgr()
{


}
CResMgr::~CResMgr()
{

	Safe_Delete_Map(mMapTex);
}

CTexture* CResMgr::LoadTexture(const wstring& _strKey, const wstring& _strRelativePath)
{
	CTexture* pTex = FindTexture(_strKey);
	if (nullptr != pTex)
	{
		return pTex;
	}

	wstring strFilePath = CPathMgr::GetI()->GetContentPath();
	strFilePath += _strRelativePath;

	pTex = new CTexture;
	pTex->Load(strFilePath);
	pTex->SetKey(_strKey);
	pTex->SetRelativePath(_strRelativePath);

	mMapTex.insert(make_pair(_strKey, pTex));

	return pTex;
}

CTexture* CResMgr::FindTexture(const wstring& _strKey)
{
	map<wstring, CRes*>::iterator iter = mMapTex.find(_strKey);

	if (iter == mMapTex.end())
	{
		return nullptr;
	}

	return (CTexture*)iter->second;
}

CTexture* CResMgr::CreateTexture(const wstring& strKey, UINT width, UINT height, COLORREF color)
{
	CTexture* pTex = FindTexture(strKey);
	if (nullptr != pTex)
	{
		return pTex;
	}

	pTex = new CTexture;
	pTex->Create(width, height, color);
	pTex->SetKey(strKey);

	mMapTex.insert(make_pair(strKey, pTex));

	return pTex;
}


CFont* CResMgr::LoadFont(const wstring& _strKey, const wstring& _strRelativePath, int _size, bool _border)
{
	wstring keyStr = _strKey + std::to_wstring(_size);
	CFont* pFont = FindFont(keyStr);

	if (nullptr != pFont)
		return pFont;

	wstring strFilePath = CPathMgr::GetI()->GetContentPath() + _strRelativePath;

	HDC dc = CCore::GetI()->GetMainDC();

	pFont = new CFont(dc);
	pFont->Load(strFilePath, _strKey, _size, _border);
	pFont->SetKey(keyStr);
	pFont->SetRelativePath(_strRelativePath);

	mMapTex.insert(make_pair(_strKey, pFont));
	return pFont;
}

CFont* CResMgr::FindFont(const wstring& _strKey)
{
	map<wstring, CRes*>::iterator iter = mMapTex.find(_strKey);

	if (iter == mMapTex.end())
	{
		return nullptr;
	}

	return (CFont*)iter->second;
}
