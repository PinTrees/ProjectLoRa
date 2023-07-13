#include "pch.h"
#include "CAnimator.h"

#include "CAnimation.h"

CAnimator::CAnimator()
	: mpOwner(nullptr)
	, mpCurAnim(nullptr)
	, mbRepeat(false)
{
}

CAnimator::~CAnimator()
{
	Safe_Delete_Map(mMapAnim);
}

<<<<<<< Updated upstream
=======

>>>>>>> Stashed changes
void CAnimator::Update()
{
	if (nullptr != mpCurAnim)
	{
		mpCurAnim->Update();

		if (mbRepeat && mpCurAnim->IsFinish())
		{
			mpCurAnim->SetFrame(0);
		}
	}
}

<<<<<<< Updated upstream
=======

>>>>>>> Stashed changes
void CAnimator::Render(HDC _dc)
{
	if (nullptr != mpCurAnim)
		mpCurAnim->Render(_dc);
}

<<<<<<< Updated upstream
void CAnimator::CreateAnimation(const wstring& _strName,CTexture* _pTex
	, Vec2 _vLT, Vec2 _vSliceSize, Vec2 _vStep, float _fDuration, UINT _iFreamCount)
=======

void CAnimator::CreateAnimation(const wstring& _strName,CTexture* _pTex
	, Vect2 _vLT, Vect2 _vSliceSize, Vect2 _vStep, float _fDuration, UINT _iFreamCount)
>>>>>>> Stashed changes
{

	CAnimation* pAnim  = FindAnimation(_strName);
	assert(nullptr == pAnim);

	pAnim = new CAnimation;

	pAnim->SetName(_strName);
	pAnim->mpAnimator = this;
<<<<<<< Updated upstream
	pAnim->CREATE(_pTex, _vLT, _vSliceSize, _vStep, _fDuration, _iFreamCount);
=======
	pAnim->Create(_pTex, _vLT, _vSliceSize, _vStep, _fDuration, _iFreamCount);
>>>>>>> Stashed changes

	mMapAnim.insert(make_pair(_strName, pAnim));
}

<<<<<<< Updated upstream
=======

>>>>>>> Stashed changes
CAnimation* CAnimator::FindAnimation(const wstring& _strName)
{
	map<wstring, CAnimation*>::iterator iter = mMapAnim.find(_strName);

	if (iter == mMapAnim.end())
		return nullptr;

	return iter->second;
}

<<<<<<< Updated upstream
=======

>>>>>>> Stashed changes
void CAnimator::Play(const wstring& _strName, bool _bRepeat)
{
	mpCurAnim =  FindAnimation(_strName);
	mbRepeat = _bRepeat;

	if (!_bRepeat)
	{
		mpCurAnim->SetFrame(0);
	}
}
