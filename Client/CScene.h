#pragma once


struct tForce
{
	float radius;			// ��� �ݰ�
	float curRadius = 0;	// ���� �ݰ�
	float speed;			// ���� �ӵ�
	float force;			// ���߷�
<<<<<<< Updated upstream
	Vec2  pos;				// ���� ����
=======
	Vect2  pos;				// ���� ����
>>>>>>> Stashed changes
};


class CObject;
class Background;

class CScene
{
private:
	vector<CObject*> mArrObj[(UINT)GROUP_TYPE::END];
<<<<<<< Updated upstream
	wstring			 m_strName; //Scene �̸�
=======
	wstring			 mStrName;		//Scene �̸�
>>>>>>> Stashed changes

	// �� ������Ʈ ���� ���� ����
	vector<tForce> mArrForce;


protected:
<<<<<<< Updated upstream
	void _render_parallax(HDC dc);
=======
	void render_parallax(HDC dc);
>>>>>>> Stashed changes


public:
	void SetName(const wstring& _strName) { mStrName = _strName; }
	const wstring& GetName() { return mStrName; }

<<<<<<< Updated upstream
	virtual void Update();
	virtual void FinalUpdate();
	virtual void Render(HDC _dc);

	virtual void Enter() = 0; // �ش� �� ���Խ� ȣ��
	virtual void Exit() = 0;  // �ش�� Ż��� ȣ��
=======
	// Life Cycle Point Function
	virtual void Update();			// �� ������ ���� ȣ��
	virtual void FinalUpdate();		// �� ������ ������ ���� ȣ��
	virtual void Render(HDC _dc);	// �� ������ ������ ���� ȣ��
	
	virtual void Enter() = 0;		// �� ���Խ� ȣ��
	virtual void Exit() = 0;		// �� Ż��� ȣ��

>>>>>>> Stashed changes


public:
	void AddObject(CObject* _pObj, GROUP_TYPE _eType);
	void AddForce(tForce& force);

	//void DeleteObject(CObject* _pObj, GROUP_TYPE _eType);
	//void DeleteForce(tForce force);

	const vector<CObject*>& GetGroupObject(GROUP_TYPE _eTYpe) { return mArrObj[(UINT)_eTYpe]; }
<<<<<<< Updated upstream
	vector<CObject*>& GetUIGroups(const GROUP_TYPE& type) { return mArrObj[static_cast<UINT>(GROUP_TYPE::UI)]; }
=======
	vector<CObject*>& GetUIGroups() { return mArrObj[(UINT)GROUP_TYPE::UI]; }
>>>>>>> Stashed changes

	void DeleteGroup(GROUP_TYPE _eTarget);
	void DeleteAll();
public:
	CScene();
	virtual ~CScene();
};

