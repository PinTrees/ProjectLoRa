#pragma once

class CObject;
class CTexture;

enum class CAM_EFFECT
{
	FADE_IN,
	FADE_OUT,
	NONE
};


struct tCamEffect
{
	CAM_EFFECT effect;
	float	   duration;
	float	   time;
};




class CCamera
{
	SINGLE(CCamera);
private:
<<<<<<< Updated upstream
	Vec2		mvLookAt;		// 카메라가 바라보는 월드 좌표
	Vec2		mvCurLookAt;
	Vec2		mvPrevLookAt;

	CObject*	mpTargetObj;	// 카메라 타겟 오브젝트
	Vec2		mvDiff;			// 해상도 중심위치와, 카메라 LookAt 간의 차이값
=======
	Vect2		mvLookAt;		// 카메라가 바라보는 월드 좌표
	Vect2		mvCurLookAt;
	Vect2		mvPrevLookAt;

	CObject*	mpTargetObj;	// 카메라 타겟 오브젝트
	Vect2		mvDiff;			// 해상도 중심위치와, 카메라 LookAt 간의 차이값
>>>>>>> Stashed changes

	float		mfTime;			// 타겟 따라가는데 걸리는 시간
	float		mfSpeed;		// 따라가는 속도
	float	 	mfAccTime;		// 누적시간

	list<tCamEffect> mEffects;
	CTexture*  mEffectTex;		// 카메라 전체화면 효과 텍스쳐 ( FadeIn, FadeOut, Blur )

public:
<<<<<<< Updated upstream
	void SetLookAt(Vec2 _vLook) 
=======
	void SetLookAt(Vect2 _vLook) 
>>>>>>> Stashed changes
	{ 
		mvLookAt = _vLook;
		float fMoveDist = (mvLookAt - mvPrevLookAt).Length();
		mfSpeed = fMoveDist / mfTime;
		mfAccTime = 0.f;
	}
	void SetTarget(CObject* _pTarget) { mpTargetObj = _pTarget; }
	
<<<<<<< Updated upstream
	Vec2 GetLookAt() { return mvCurLookAt; }
	Vec2 GetRenderPos(Vec2 _vObjPos) { return _vObjPos - mvDiff; }
	Vec2 GetRealPos(Vec2 _vRenderPos	) { return _vRenderPos +mvDiff; }
=======
	Vect2 GetLookAt() { return mvCurLookAt; }
	Vect2 GetRenderPos(Vect2 _vObjPos) { return _vObjPos - mvDiff; }
	Vect2 GetRealPos(Vect2 _vRenderPos	) { return _vRenderPos +mvDiff; }
>>>>>>> Stashed changes

	void FadeIn(float duration)
	{
		tCamEffect ef = {};

		ef.time = 0.f;
		ef.effect = CAM_EFFECT::FADE_IN;
		ef.duration = duration;

		mEffects.push_back(ef);

		if (0.f >= duration)
			assert(nullptr);
	}
	void FadeOut(float duration)
	{
		tCamEffect ef = {};

		ef.time = 0.f;
		ef.effect = CAM_EFFECT::FADE_OUT;
		ef.duration = duration;

		mEffects.push_back(ef);

		if (0.f >= duration)
			assert(nullptr);
	}


public:
	void Init();
	void Update();
	void Render(HDC hdc);

private:
	void calDiff();
};

