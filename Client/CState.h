#pragma once

class AI;
class CMonster;


class CState
{
private:
	AI* mpAI;
	MON_STATE meState;



public:
	AI* GetAI() { return mpAI; }
	MON_STATE GetType() { return meState; }
	CMonster* GetMonster();

public:
	virtual void Update() = 0;
	virtual void Enter() = 0;
	virtual void Exit() = 0;


public:
	CState(MON_STATE _eState);
	virtual ~CState();

	friend class AI;
};

