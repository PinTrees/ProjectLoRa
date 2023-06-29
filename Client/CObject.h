#pragma once

class CCollider;

class CObject
{
private:
	Vec2 m_vPos;
	Vec2 m_vScale;

	CCollider* mpCollider;

public:
	void SetPos(Vec2 _vPos) { m_vPos = _vPos; }
	void SetScale(Vec2 _vScale) { m_vScale = _vScale; }

	Vec2 GetPos() { return m_vPos; }
	Vec2 GetScale() { return m_vScale; }

	void CreateCollider();

public:
	virtual void Update() = 0;
	virtual void FinalUpdate() final;
	virtual void Render(HDC _dc);
	CCollider* GetCollider() { return mpCollider; }

	void CompnentRender(HDC _dc);
public:
	CObject();
	virtual ~CObject();
};

