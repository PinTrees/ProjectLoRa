#pragma once

class CObject;


class CCamera
{
	SINGLE(CCamera);
private:
	Vec2		mvLookAt;		//카메라가 바라보는 실제 좌표
	Vec2		mvCurLookAt;
	Vec2		mvPrevLookAt;

	CObject*	mpTargetObj;	// 카메라 타겟 오브젝트
	Vec2		mvDiff;			// 해상도 중심위치와, 카메라 LookAt 간의 차이값

	float		mfTime;		//타겟 따라가는데 걸리는 시간
	float		mfSpeed;	//따라가는속도
	float		mfAccTime;	//누적시간

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

