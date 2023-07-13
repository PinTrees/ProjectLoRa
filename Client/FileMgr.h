#pragma once


class FileMgr
{
	SINGLE(FileMgr)

public:
	static void Wirte(const wstring& filePath, const wstring str);
	static void WirteByte(const wstring& filePath, const uint8_t* data, int size);

	static void WirteByteFullPath(const wstring& filePath, const uint8_t* data, int size);

	static wstring& Read(const wstring& filePath);

};

