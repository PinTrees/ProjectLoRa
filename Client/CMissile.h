#pragma once
#include "CObject.h"

class CMissile :
	public CObject
{
private:
	float     m_tTheta; // 이동 방향
	Vec2		m_vDir;
	wstring		mType;

	float		mDelay;
	float		mCurDelay;

public:
	void SetDir(float _tTheta) { m_tTheta = _tTheta; }
	void SetDir(Vec2	_vDir) 
	{
		m_vDir = _vDir;
		m_vDir.Normalize();
	}
	void SetType(const wstring& _str) { mType = _str; }

public:
	virtual void Update() override;
	virtual void Render(HDC _dc) override;
	CLONE(CMissile);

public:
	virtual void OnCollisionEnter(CCollider* _pOther);
public:
	CMissile();
	CMissile(const wstring& _type);
	~CMissile();
};

