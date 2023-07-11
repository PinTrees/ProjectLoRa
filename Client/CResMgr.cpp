#include "pch.h"
#include "CResMgr.h"

#include "CCore.h"

#include "CPathMgr.h"
#include "CTexture.h"	
#include "CFont.h"


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
	CFont* pTex = FindFont(_strKey);
	if (nullptr != pTex)
	{
		pTex->SelectFont(_size, _strKey, _border);
		return pTex;
	}

	wstring strFilePath = CPathMgr::GetI()->GetContentPath();
	strFilePath += _strRelativePath;

	HDC dc = CCore::GetI()->GetMainDC();

	pTex = new CFont(dc);
	pTex->Create(strFilePath);
	pTex->SelectFont(_size, _strKey, _border);
	pTex->SetKey(_strKey);
	pTex->SetRelativePath(_strRelativePath);

	mMapTex.insert(make_pair(_strKey, pTex));
	return pTex;
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
