#include "pch.h"
#include "CResMgr.h"

#include "CCore.h"

#include "CPathMgr.h"
#include "CTexture.h"	
#include "CFont.h"
#include "CSprite.h"
#include "CSound.h"


SINGLE_HEADER(CResMgr);


CResMgr::CResMgr()
{


}
CResMgr::~CResMgr()
{
	Safe_Delete_Map(mMapTex);
	Safe_Delete_Map(mMapFont);
	Safe_Delete_Map(mMapSound);
	Safe_Delete_Map(mMapSprite);
} 



CSound* CResMgr::LoadSound(const wstring& _strKey, const wstring& _strRelativePath)
{
	CSound* pSound = FindSound(_strKey);
	if (nullptr != pSound)
	{
		return pSound;
	}

	wstring strFilePath = CPathMgr::GetI()->GetContentPath();
	strFilePath += _strRelativePath;

	pSound = new CSound;
	pSound->Load(strFilePath);
	pSound->SetKey(_strKey);
	pSound->SetRelativePath(_strRelativePath);

	mMapSound.insert(make_pair(_strKey, pSound));

	return pSound;
}

CSound* CResMgr::FindSound(const wstring& _strKey)
{
	auto iter = mMapTex.find(_strKey);

	if (iter == mMapTex.end())
	{
		return nullptr;
	}

	return (CSound*)iter->second;
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


CFont* CResMgr::LoadFont(const wstring& strKey, const wstring& _strRelativePath, int size)
{
	wstring keyStr = strKey + std::to_wstring(size);
	CFont* pFont = FindFont(keyStr);

	if (nullptr != pFont)
		return pFont;

	wstring strFilePath = CPathMgr::GetI()->GetContentPath() + _strRelativePath;

	HDC dc = CCore::GetI()->GetMainDC();

	pFont = new CFont(dc);
	pFont->Load(strFilePath, strKey, size);
	pFont->SetKey(keyStr);
	pFont->SetRelativePath(_strRelativePath);

	mMapFont.insert(make_pair(keyStr, pFont));
	return pFont;
}

CFont* CResMgr::FindFont(const wstring& _strKey)
{
	map<wstring, CRes*>::iterator iter = mMapFont.find(_strKey);

	if (iter == mMapFont.end())
	{
		return nullptr;
	}

	return (CFont*)iter->second;
}


CSprite* CResMgr::LoadSprite(const wstring& _strKey, const wstring& _strRelativePath)
{
	CSprite* pSprite = FindSprite(_strKey);
	if (nullptr != pSprite)
	{
		return pSprite;
	}

	wstring strFilePath = CPathMgr::GetI()->GetContentPath();
	strFilePath += _strRelativePath;

	pSprite = new CSprite;
	pSprite->Load(strFilePath);
	pSprite->SetKey(_strKey);
	pSprite->SetRelativePath(_strRelativePath);

	mMapSprite.insert(make_pair(_strKey, pSprite));

	return pSprite;
}

CSprite* CResMgr::FindSprite(const wstring& _strKey)
{
	map<wstring, CRes*>::iterator iter = mMapSprite.find(_strKey);

	if (iter == mMapSprite.end())
	{
		return nullptr;
	}

	return (CSprite*)iter->second;
}
