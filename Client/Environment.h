#pragma once

#include "CObject.h"


class Environment
	: public CObject
{
private:
	wstring mType;


public:
	virtual void Update()override;
	virtual void Render(HDC _dc) override;

	CLONE(Environment);


public:
	Environment(const wstring& _type);
	~Environment();
};

