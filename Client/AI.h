#pragma once

class CMonster;
class CState;


class AI
{
private:
	map<MON_STATE, CState*>	mMapState;
	CState*					mpCurstate;
	CMonster*				mpOwner;

public:
	void Update();



public:
	void AddState(CState* _pState);
	CState* GetState(MON_STATE _eState);
	void SetCurState(MON_STATE _eState);

	void ChangeState(MON_STATE _eNextState);

	CMonster* GetOwner() { return mpOwner; }
public:
	AI();
	~AI();

	friend class CMonster;
};

