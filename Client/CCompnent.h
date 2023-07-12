#pragma once

class CObject;

class CCompnent
{
private:
	CObject* mpOwner;

public:

	CObject* GetO() { return mpOwner; }

public:
	virtual void Update() {};
	virtual void FinalUpdate() {};
	virtual void Render(HDC _dc) {};


public:
	CCompnent();
	virtual ~CCompnent();

	friend class CObject;

};

