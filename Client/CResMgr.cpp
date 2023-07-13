#include "pch.h"
#include "CResMgr.h"
#include "CCore.h"

#include "CCore.h"

#include "CPathMgr.h"
#include "CTexture.h"	
#include "CFont.h"
<<<<<<< Updated upstream
=======

>>>>>>> Stashed changes

CResMgr::CResMgr()
{


}
CResMgr::~CResMgr()
{
<<<<<<< Updated upstream
=======

>>>>>>> Stashed changes
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
<<<<<<< Updated upstream
	pTex->CREATE(width, height, color);
=======
	pTex->Create(width, height, color);
>>>>>>> Stashed changes
	pTex->SetKey(strKey);

	mMapTex.insert(make_pair(strKey, pTex));

	return pTex;
}

<<<<<<< Updated upstream
CFont* CResMgr::LoadFont(const wstring& _strKey, const wstring& _strRelativePath, int _size, bool _border)
{
	CFont* pTex = FindFont(_strKey);
	if (nullptr != pTex)
	{
		pTex->SelectFont(_size, _strKey, _border);
		return pTex;
=======

CFont* CResMgr::LoadFont(const wstring& _strKey, const wstring& _strRelativePath, int _size, bool _border)
{
	CFont* pFont = FindFont(_strKey);
	if (nullptr != pFont)
	{
		pFont->SelectFont(_size, _strKey, _border);
		return pFont;
>>>>>>> Stashed changes
	}

	wstring strFilePath = CPathMgr::GetI()->GetContentPath();
	strFilePath += _strRelativePath;

<<<<<<< Updated upstream
	HDC dc = CCore::GetI()->GetTexture()->GetDC();

	pTex = new CFont(dc);
	pTex->Create(strFilePath);
	pTex->SelectFont(_size, _strKey, _border);
	pTex->SetKey(_strKey);
	pTex->SetRelativePath(_strRelativePath);

	mMapTex.insert(make_pair(_strKey, pTex));
	return pTex;
=======
	HDC dc = CCore::GetI()->GetMainDC();

	pFont = new CFont(dc);
	pFont->Create(strFilePath);
	pFont->SelectFont(_size, _strKey, _border);
	pFont->SetKey(_strKey);
	pFont->SetRelativePath(_strRelativePath);

	mMapTex.insert(make_pair(_strKey, pFont));
	return pFont;
>>>>>>> Stashed changes
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
