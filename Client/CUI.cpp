#include "CUI.h"

#include "CKeyMgr.h"
#include "CCamera.h"

#include "SelectGDI.h"

CUI::CUI(bool _bCamAff)
	:mpParentUI(nullptr)
	,mbCamAffected(_bCamAff)
	, mbMouseOn(false)
{
}

CUI::CUI(const CUI& _origin)
	:CObject(_origin)
	,mpParentUI(nullptr)
	,mbCamAffected(_origin.mbCamAffected)
	,mbMouseOn(false)
	,mbLbtnDown(false)
{
	for (size_t i = 0; i < _origin.mVecChildUI.size(); i++)
	{
		AddChild(_origin.mVecChildUI[i]->Clone());
	}
}

CUI::~CUI()
{
	Safe_Delete_Vec(mVecChildUI);
}

void CUI::Update()
{
	// child ui update
	update_child();
}

void CUI::FinalUpdate()
{
	// ui도 콜라이더나 애니메이션있을수있으니 부모쪽으로 해서 실행함
	CObject::FinalUpdate();


	// UI 의 최종 좌표를 구한다.
	mvFinalPos = GetPos();

	if (GetParent())
	{
		Vec2 vParentPos = GetParent()->GetFinalPos();
		mvFinalPos += vParentPos;
	}

	// UI Mouse 체크
	MouseOnCheck();

	finalupdate_child();
}

void CUI::Render(HDC _dc)
{
	Vec2 vPos = GetFinalPos();
	Vec2 vScale = GetScale();

	if (mbCamAffected)
	{
		vPos = CCamera::GetI()->GetRenderPos(vPos);
	}

	if (mbLbtnDown)
	{
		SelectGDI select(_dc, PEN_TYPE::GREEN);

		Rectangle(_dc
			, int(vPos.x)
			, int(vPos.y)
			, int(vPos.x + vScale.x)
			, int(vPos.y + vScale.y));
	}
	else
	{
		Rectangle(_dc
			, int(vPos.x)
			, int(vPos.y)
			, int(vPos.x + vScale.x)
			, int(vPos.y + vScale.y));
	}

	

	// child ui render
	render_child(_dc);

}

void CUI::render_child(HDC _dc)
{
	for (size_t i = 0; i < mVecChildUI.size(); ++i)
	{
		mVecChildUI[i]->Render(_dc);
	}
}

void CUI::update_child()
{
	for (size_t i = 0; i < mVecChildUI.size(); ++i)
	{
		mVecChildUI[i]->Update();
	}
}

void CUI::finalupdate_child()
{
	for (size_t i = 0; i < mVecChildUI.size(); ++i)
	{
		mVecChildUI[i]->FinalUpdate();
	}
}



void CUI::MouseOnCheck()
{
	Vec2 vMousePos = MOUSE_POS;
	Vec2 vScale = GetScale();
	if (mbCamAffected)
	{
		vMousePos = CCamera::GetI()->GetRealPos(vMousePos);
	}

	if (mvFinalPos.x <= vMousePos.x && vMousePos.x <= mvFinalPos.x + vScale.x
		&& mvFinalPos.y <= vMousePos.y && vMousePos.y <= mvFinalPos.y + vScale.y)
	{
		mbMouseOn = true;
	}
	else
	{
		mbMouseOn = false;
	}
}
void CUI::MouseOn()
{

}

void CUI::MouseLbtnDown()
{

}

void CUI::MouseLbtnUp()
{

}

void CUI::MouseLbtnClicked()
{

}