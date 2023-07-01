#pragma once
#include "CObject.h"

class CUI : public CObject
{
	virtual CUI* Clone() = 0;

private:
	vector<CUI*> _vecChildUI; // 깊은 복사 진행 해야함.
	CUI* p_parentUI;

	Vec2		_finalPos;

	bool		_cameraAffected; 
	bool		_onMouseCheck;
	bool		_lbtnDown;

public:
	CUI(bool cameraAffected);
	CUI(const CUI& origin);
	virtual ~CUI() override;

public:
	virtual void Update() override;
	virtual void FinalUpdate() override;
	virtual void Render(HDC _dc) override;

	void UpdateChild();
	void FinalUpdateChild();
	void RenderChild(HDC dc);

public:
	void OnMouseCheck();
	bool IsMouseOn() { return _onMouseCheck; };
	bool IsLbtnDown() { return _lbtnDown; }

public:
	virtual void MouseOn();
	virtual void MouseLbtnDown();
	virtual void MouseLbtnUp();
	virtual void MouseLbtnClick();

public:
	void AddChild(CUI* ui)
	{
		_vecChildUI.push_back(ui);
		ui->p_parentUI = this;
	}

public:
	CUI* GetParentUI() { return p_parentUI; }
	Vec2	GetFinalPos() { return _finalPos; }
	const vector<CUI*> GetChild() { return _vecChildUI; }

	bool GetLbtnDown() { return _lbtnDown; }
	bool GetIsMouseOn() { return _onMouseCheck; }

	CUI* GetFindChild(CUI* parentUI, const wstring& childUI)
	{
		for (UINT i = 0; i < parentUI->GetChild().size(); ++i)
		{
			if (parentUI->GetChild()[i]->GetName() == childUI)
			{
				if (parentUI->GetChild()[i] == nullptr)
					assert(nullptr);

				return parentUI->GetChild()[i];
			}
		}

		return nullptr;
	}

	friend class CUIMgr;
};

