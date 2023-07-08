#pragma once

class CObject;
class CTexture;

enum class CAM_EFFECT
{
	FADE_IN,
	FADE_OUT,
	NONE,
};


struct tCamEffect
{
	CAM_EFFECT eEffect;
	float		fDuration;
	float		fCurTime;
};


class CCamera
{
	SINGLE(CCamera);
private:
	Vec2					mvLookAt;		//ī�޶� �ٶ󺸴� ���� ��ǥ
	Vec2					mvCurLookAt;
	Vec2					mvPrevLookAt;

	CObject*				mpTargetObj;	// ī�޶� Ÿ�� ������Ʈ
	Vec2					mvDiff;			// �ػ� �߽���ġ��, ī�޶� LookAt ���� ���̰�

	float					mfTime;		//Ÿ�� ���󰡴µ� �ɸ��� �ð�
	float					mfSpeed;	//���󰡴¼ӵ�
	float					mfAccTime;	//�����ð�

	list<tCamEffect>		mListCamEffect;
	CTexture*				mpVeilTex;							// ī�޶� ������ �ؽ���(����������)
public:
	void SetLookAt(Vec2 _vLook)
	{
		mvLookAt = _vLook;
		float fMoveDist = (mvLookAt - mvPrevLookAt).Length();
		mfSpeed = fMoveDist / mfTime;
		mfAccTime = 0.f;
	}
	void SetTarget(CObject* _pTarget) { mpTargetObj = _pTarget; }
	Vec2	GetLookAt() { return mvCurLookAt; }
	Vec2 GetRenderPos(Vec2 _vObjPos) { return _vObjPos - mvDiff; }
	Vec2	GetRealPos(Vec2 _vRenderPos) { return _vRenderPos + mvDiff; }


	void FadeIn(float _fDuration)
	{
		tCamEffect ef = {};
		ef.eEffect = CAM_EFFECT::FADE_IN;
		ef.fDuration = _fDuration;
		ef.fCurTime = 0.f;

		mListCamEffect.push_back(ef);

		if (0.f == _fDuration)
			assert(nullptr);
	}
	void FadeOut(float _fDuration)
	{
		tCamEffect ef = {};
		ef.eEffect = CAM_EFFECT::FADE_OUT;
		ef.fDuration = _fDuration;
		ef.fCurTime = 0.f;

		mListCamEffect.push_back(ef);

		if (0.f == _fDuration)
			assert(nullptr);
	}



public:
	void Init();
	void Update();
	void Render(HDC _dc);

private:
	void calDiff();
};

