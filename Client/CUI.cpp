#include "pch.h"
#include "CUI.h"

#include "CCamera.h"
#include "CKeyMgr.h"

#include "SelectGDI.h"
#include "CScene.h"

#include "CTexture.h"


CUI::CUI(bool cameraAffected)
	: mVecChildUI{}
	, mpParentUI(nullptr)
	, mvFinalPos{}
	, mCameraAffected(cameraAffected)
	, mOnMouseCheck(false)
	, mText(L"")
{

}

CUI::CUI(const CUI& origin)
	: CObject(origin)
	, mpParentUI(nullptr)
	, mCameraAffected(origin.mCameraAffected)
	, mOnMouseCheck(false)
	, mLbtnDown(false)
	, mText(origin.mText)
{
	for (size_t i = 0; i < origin.mVecChildUI.size(); ++i)
	{
		AddChild(origin.mVecChildUI[i]->Clone());
	}
}

CUI::~CUI()
{
	Safe_Delete_Vec(mVecChildUI);
}

void CUI::Update()
{
	// child update
	UpdateChild();
}

void CUI::FinalUpdate()
{
	// 부모의 finalUpdate호출 해야한다.
	// UI가 애니매이션 가질 수도 있기 때문에
	CObject::FinalUpdate();

	// UI의 최종좌표를 구한다.
	mvFinalPos = GetPos(); // 부모 좌표를 finalPos로 인식

	if (GetParentUI())
	{
		Vect2 parentPos = GetParentUI()->GetFinalPos();
		mvFinalPos += parentPos;
	}

	// UI Mouse체크
	OnMouseCheck();

	FinalUpdateChild();
}

void CUI::OnMouseCheck()
{
	Vect2 mousePos = MOUSE_POS;
	Vect2 uiScale = GetScale();

	if (mCameraAffected)
	{
		CCamera::GetI()->GetRealPos(mousePos);
	}

	if (mvFinalPos.x - uiScale.x * 0.5f <= mousePos.x && mousePos.x <= mvFinalPos.x + uiScale.x * 0.5f &&
		mvFinalPos.y - uiScale.x * 0.5f <= mousePos.y && mousePos.y <= mvFinalPos.y + uiScale.y * 0.5f)
	{
		mOnMouseCheck = true;
	}
	else
	{
		mOnMouseCheck = false;
	}
}

void CUI::Render(HDC dc)
{
	Vect2 vPos = GetFinalPos();
	Vect2 vScale = GetScale();

	if (mCameraAffected)
	{
		vPos = CCamera::GetI()->GetRenderPos(vPos);
	}

	if (mLbtnDown)
	{
		SelectGDI p(dc, PEN_TYPE::GREEN);
	}

	if(nullptr == mpTexture)
	{
		Rectangle
		(
			dc,
			int(vPos.x),
			int(vPos.y),
			int(vPos.x + vScale.x),
			int(vPos.y + vScale.y)
		);
	}
	else
	{
		float fWidth = (float)mpTexture->Width();
		float fHeight = (float)mpTexture->Heigth();

		if (mLbtnDown)
		{
			HBITMAP hPressedBitmap = CreateCompatibleBitmap(dc, fWidth, fHeight);
			HDC hdcPressedMem = CreateCompatibleDC(dc);
			HBITMAP hOldPressedBitmap = (HBITMAP)SelectObject(hdcPressedMem, hPressedBitmap);

			// 비트맵 복사
			BitBlt(hdcPressedMem, 0, 0, fWidth, fHeight, mpTexture->GetDC(), 0, 0, SRCCOPY);

			for (int y = 0; y < fWidth; ++y)
			{
				for (int x = 0; x < fHeight; ++x)
				{
					COLORREF pixel = GetPixel(hdcPressedMem, x, y);

					BYTE r = GetRValue(pixel);
					BYTE g = GetGValue(pixel);
					BYTE b = GetBValue(pixel);

					r = (BYTE)(((float)r * 200) / 255);				// 색상 곱하기
					g = (BYTE)(((float)g * 200) / 255);
					b = (BYTE)(((float)b * 200) / 255);

					COLORREF newPixel = RGB(r, g, b);
					SetPixel(hdcPressedMem, x, y, newPixel);
				}
			}

			TransparentBlt(dc,
				(int)(vPos.x - vScale.x * 0.5f),
				(int)(vPos.y - vScale.y * 0.5f),
				(int)vScale.x,
				(int)vScale.y,
				hdcPressedMem,
				0, 0,
				(int)fWidth, (int)fHeight,
				RGB(255, 0, 255));

			SelectObject(hdcPressedMem, hOldPressedBitmap);			// 메모리 해제 및 정리
			DeleteDC(hdcPressedMem);
			DeleteObject(hPressedBitmap);
		}
		else
		{
			TransparentBlt(dc
				, (int)(vPos.x - vScale.x * 0.5f)
				, (int)(vPos.y - vScale.y * 0.5f)
				, (int)vScale.x
				, (int)vScale.y
				, mpTexture->GetDC()
				, 0, 0
				, (int)fWidth, (int)fHeight
				, RGB(255, 0, 255));
		}
	}

	if (mText != L"")
	{
		SetBkMode(dc, TRANSPARENT);
		TextOut(dc, (int)(vPos.x + mvContentOffset.x), (int)(vPos.y + mvContentOffset.y), mText.c_str(), mText.size());
	}

	// child render
	RenderChild(dc);
}

void CUI::UpdateChild()
{
	for (size_t i = 0; i < mVecChildUI.size(); ++i)
	{
		mVecChildUI[i]->Update();
	}
}

void CUI::FinalUpdateChild()
{
	for (size_t i = 0; i < mVecChildUI.size(); ++i)
	{
		mVecChildUI[i]->FinalUpdate();
	}
}

void CUI::RenderChild(HDC dc)
{
	for (size_t i = 0; i < mVecChildUI.size(); ++i)
	{
		mVecChildUI[i]->Render(dc);
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
	// 밖에서 누르고 안에서 땟을 때도 인식이 된다.

}

void CUI::MouseLbtnClick()
{

}

CUI* CUI::GetFindChild(CUI* parentUI, const wstring& childUI)
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