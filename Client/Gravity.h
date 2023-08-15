#pragma once

class CObject;

class CGravity
{
private:
	CObject*		mpOwner;
	bool		_ground;

public:
	static bool _onLand;

public:
	CGravity();
	~CGravity();

public:
	void FinalUpdate();

public:
	void SetOnGround(bool ground);

public:
	friend class CObject;
};
