#pragma once

<<<<<<< Updated upstream
=======

>>>>>>> Stashed changes
struct tEvent
{
	EVENT_TYPE	eEven;
	DWORD_PTR		lParam;
	DWORD_PTR		wParam;
};

<<<<<<< Updated upstream
=======

class CObject;




>>>>>>> Stashed changes
class CEventMgr
{
	SINGLE(CEventMgr)

private:
	vector<tEvent>		mVecEvent;
	vector<CObject*>	mVecDeadObj;

<<<<<<< Updated upstream
=======

>>>>>>> Stashed changes
public:
	void Update();
private:
	void excute(const tEvent& _eve);
public:
	void AddEvent(const tEvent& _eve);
};

