#pragma once



class CRes
{
private:
    wstring mStrKey;               //���ҽ� Ű
    wstring mStrRelativePath;;     //���ҽ� �����

public:
    void SetKey(const wstring& _strKey) { mStrKey = _strKey; }
    void SetRelativePath(const wstring& _strPath) { mStrRelativePath = _strPath; }

    const wstring& GetKey() { return mStrKey; }
    const wstring& GetRelativePath() { return mStrRelativePath; }

public:
    CRes();
    virtual ~CRes();
};

