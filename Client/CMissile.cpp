#include "pch.h"
#include "CMissile.h"

#include "CScene.h"
#include "CSceneMgr.h"

#include "CTimeMgr.h"
#include "CCollider.h"



CMissile::CMissile()
	:m_tTheta(PI / 4.f)
	, m_vDir(Vec2(1.f, 1.f))
{
	m_vDir.Normalize();
	CreateCollider();
	GetCollider()->SetScale(Vec2(15,15));
}

CMissile::~CMissile()
{

}

void CMissile::Update()
{
	Vec2 vPos = GetPos();
	CScene* pCurScene = CSceneMgr::GetI()->GetCurScene();

	//vPos.x += 800.f * cosf(m_tTheta) * fDT;
	//vPos.y -= 800.f * sinf(m_tTheta) * fDT;

	vPos.x += 300.f * m_vDir.x * fDT;
	vPos.y += 300.f * m_vDir.y * fDT;

	if (vPos.y < 110)
		pCurScene->DeleteObject(this, GROUP_TYPE::PROJ_PLAYER);

	SetPos(vPos);
}

void CMissile::Render(HDC _dc)
{
	Vec2 vPos = GetPos();
	Vec2 vScale = GetScale();
	Ellipse(_dc, (int)(vPos.x - vScale.x / 2.f), (int)(vPos.y - vScale.y / 2.f)
		, (int)(vPos.x + vScale.x / 2.f), (int)(vPos.y + vScale.y / 2.f));

	CompnentRender(_dc);
}

void CMissile::OnCollisionEnter(CCollider* _pOther)
{
	CObject* pOtherObj = _pOther->GetObj();

	if (pOtherObj->GetName() == L"Monster")
	{
		DeleteObject(this);
	}
	
}