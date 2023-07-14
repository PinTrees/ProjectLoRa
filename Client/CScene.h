#pragma once


struct tForce
{
	float radius;			// ��� �ݰ�
	float curRadius = 0;	// ���� �ݰ�
	float speed;			// ���� �ӵ�
	float force;			// ���߷�
	Vect2  pos;				// ���� ����
};


class CObject;
class Background;

class CScene
{
protected:
	vector<CObject*> mArrObj[(UINT)GROUP_TYPE::END];

private:
	wstring			 mStrName;		//Scene �̸�

	// �� ������Ʈ ���� ���� ����
	vector<tForce>	 mArrForce;


protected:
	void render_parallax(HDC dc);


public:
	void SetName(const wstring& _strName) { mStrName = _strName; }
	const wstring& GetName() { return mStrName; }

	// Life Cycle Point Function
	virtual void Update();			// �� ������ ���� ȣ��
	virtual void FinalUpdate();		// �� ������ ������ ���� ȣ��
	virtual void Render(HDC _dc);	// �� ������ ������ ���� ȣ��
	
	virtual void Enter() = 0;		// �� ���Խ� ȣ��
	virtual void Exit() = 0;		// �� Ż��� ȣ��


public:
	void AddObject(CObject* _pObj, GROUP_TYPE _eType);
	void AddForce(tForce& force);

	//void DeleteObject(CObject* _pObj, GROUP_TYPE _eType);
	//void DeleteForce(tForce force);

	const vector<CObject*>& GetGroupObject(GROUP_TYPE _eTYpe) { return mArrObj[(UINT)_eTYpe]; }
	vector<CObject*>& GetUIGroups() { return mArrObj[(UINT)GROUP_TYPE::UI]; }

	void DeleteGroup(GROUP_TYPE _eTarget);
	void DeleteAll();
public:
	CScene();
	virtual ~CScene();
};

