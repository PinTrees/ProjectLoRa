#pragma once

class CObject;


class CCamera
{
	SINGLE(CCamera);
private:
	Vec2		mvLookAt;		//ī�޶� �ٶ󺸴� ���� ��ǥ
	Vec2		mvCurLookAt;
	Vec2		mvPrevLookAt;

	CObject*	mpTargetObj;	// ī�޶� Ÿ�� ������Ʈ
	Vec2		mvDiff;			// �ػ� �߽���ġ��, ī�޶� LookAt ���� ���̰�

	float		mfTime;		//Ÿ�� ���󰡴µ� �ɸ��� �ð�
	float		mfSpeed;	//���󰡴¼ӵ�
	float		mfAccTime;	//�����ð�

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
	Vec2	GetRealPos(Vec2 _vRenderPos	) { return _vRenderPos +mvDiff; }

public:
	void Update();


private:
	void calDiff();
};
