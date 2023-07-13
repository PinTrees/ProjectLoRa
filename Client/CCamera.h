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
	Vect2		mvLookAt;		// ī�޶� �ٶ󺸴� ���� ��ǥ
	Vect2		mvCurLookAt;
	Vect2		mvPrevLookAt;

	CObject*	mpTargetObj;	// ī�޶� Ÿ�� ������Ʈ
	Vect2		mvDiff;			// �ػ� �߽���ġ��, ī�޶� LookAt ���� ���̰�

	float		mfTime;			// Ÿ�� ���󰡴µ� �ɸ��� �ð�
	float		mfSpeed;		// ���󰡴� �ӵ�
	float	 	mfAccTime;		// �����ð�

	list<tCamEffect> mEffects;
	CTexture*  mEffectTex;		// ī�޶� ��üȭ�� ȿ�� �ؽ��� ( FadeIn, FadeOut, Blur )

public:
	void SetLookAt(Vect2 _vLook) 
	{ 
		mvLookAt = _vLook;
		float fMoveDist = (mvLookAt - mvPrevLookAt).Length();
		mfSpeed = fMoveDist / mfTime;
		mfAccTime = 0.f;
	}
	void SetTarget(CObject* _pTarget) { mpTargetObj = _pTarget; }
	
	Vect2 GetLookAt() { return mvCurLookAt; }
	Vect2 GetRenderPos(Vect2 _vObjPos) { return _vObjPos - mvDiff; }
	Vect2 GetRealPos(Vect2 _vRenderPos	) { return _vRenderPos +mvDiff; }

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

