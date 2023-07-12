#pragma once


struct tEvent
{
	EVENT_TYPE	eEven;
	DWORD_PTR		lParam;
	DWORD_PTR		wParam;
};


class CObject;




class CEventMgr
{
	SINGLE(CEventMgr)

private:
	vector<tEvent>		mVecEvent;
	vector<CObject*>	mVecDeadObj;


public:
	void Update();
private:
	void excute(const tEvent& _eve);
public:
	void AddEvent(const tEvent& _eve);
};

