#include "pch.h"
#include "FileMgr.h"
#include "CPathMgr.h"


SINGLE_HEADER(FileMgr);


void FileMgr::Wirte(const wstring& filePath, const wstring str)
{
	wstring strFilePath = CPathMgr::GetI()->GetContentPath();
	strFilePath += filePath;

	FILE* pFile = nullptr;
	_wfopen_s(&pFile, strFilePath.c_str(), L"ws");

	if (nullptr == pFile)
	{
		return;
	}

	fwrite(str.c_str(), 2, str.length(), pFile);
	fclose(pFile);
}

void FileMgr::WirteByte(const wstring& filePath, const uint8_t* data, int size)
{
	wstring strFilePath = CPathMgr::GetI()->GetContentPath();
	strFilePath += filePath;

	FILE* pFile = nullptr;
	_wfopen_s(&pFile, strFilePath.c_str(), L"wb");

	if (nullptr == pFile)
	{
		return;
	}

	fwrite(data, sizeof(uint8_t), size, pFile);
	fclose(pFile);
}

void FileMgr::WirteByteFullPath(const wstring& filePath, const uint8_t* data, int size)
{
	FILE* pFile = nullptr;
	_wfopen_s(&pFile, filePath.c_str(), L"wb");

	if (nullptr == pFile)
	{
		return;
	}

	fwrite(data, sizeof(uint8_t), size, pFile);
	fclose(pFile);
}

