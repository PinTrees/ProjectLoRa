## 코드베이스
추후 웹으로 재구축

### 게임 내 오브젝트 클래스 생성
```c++
#pragma once

// 필수 인클루드
#include "CObject.h"

class Gun :
	public CObject
{
private:
	// 멤버 변수


public:
	// 접근자


public:
  	// 필수 오버라이드 및 매크로
	virtual void Update() override;
	virtual void Render(HDC _dc) override;
	CLONE(Gun);


public:
  // 생성자 및 소멸자
};

```

### 오브젝트를 게임 내에 배치
```c++
  	// CObject 를 상속받은 객체 생성
	Bullet* pBullet = new Bullet(L"3");
	pBullet->SetPos(Vec2(0.f, 0.f));
	// 오브젝트 구분자 (필수)
	pBullet->SetName(L"Bullet_Player");

  	// 객체를 관리되는 항목에 추가
	CreateObject(pBullet, GROUP_TYPE::DEFAULT);
```

### 생성된 오브젝트를 제거
```c++
	// 게임오브젝트 클래스 내에서 자기 자신을 제거
  	DeleteObject(this);
	// 객체를 소유하고 있는 위치에서 제거
  	DeleteObject(pPlayer);
```


### 스프라이트 애니메이션
```c++
// 애니메이터를 통해 애니매이션을 제어
// 해당 오브젝트에 애니메이션이 필요하다고 판단될 경우 생성자에서 초기화
Bullet::Bullet()
{
	// 애니메이션에 사용될 텍스쳐 로드
	CTexture* pTex = CResMgr::GetI()->LoadTexture(L"Effect" + _type, L"texture\\bullet\\" + _type + L".bmp");
	// 애니메이터 생성
	CreateAnimator();

	// 애니메이션 생성		   // 이미지,	시작 좌표,	사이즈,	스텝,	프레임,	길이
	GetAnimator()->CreateAnimation(L"IDLE", pTex, Vec2(0.f, 0.f), Vec2(48.f, 32.f), Vec2(48.f, 0.f), 0.5f, 4);
	
	// 초기 애니메이션 설정 (이름, 반복여부)
	GetAnimator()->Play(L"IDLE", true);


	// 오브젝트 크기 및 각도 조절
	SetScale(Vec2(48.f, 32.f) * 1.5f);
	SetAngleOffset(180);
}


void Bullet::Update()
{
	// 애니메이션이 적용된 오브젝트는 필수 작성
	GetAnimator()->Update();
}


void Bullet::Render(HDC _dc)
{
	// 애니메이션이 적용된 오브젝트는 필수 작성
	CompnentRender(_dc);
}
```

### 오브젝트에 충돌체 추가
```c++
// 오브젝트에 충돌처리가 필요하다고 판단될 경우 생성자에서 초기화
Bullet::Bullet()
{
	// 충돌체 생성
	CreateCollider();
	// 충돌체의 크기 설정
	GetCollider()->SetScale(Vec2(15.f, 15.f));
	// 충돌체의 오프셋 설정
	GetCollider()->SetOffsetPos(Vec2(0.f, 0.f));
}

// 충돌이 시작된 시점
void Bullet::OnCollisionEnter(CCollider* _pOther)
{

	CObject* pOtherObj = _pOther->GetObj();
	// 객체를 판별. 이름 또는 태그로 구분
	if (pOtherObj->GetName() == L"Monster")
	{
		// 충돌에 필요한 로직을 작성
	}
}

// 충돌이 진행중인 상태 (매 프레임마다 호출)
void Bullet::OnCollisionStay(CCollider* _pOther)
{
	// 충돌에 필요한 로직을 작성
}

// 충돌이 끝난 시점
void Bullet::OnCollisionExit(CCollider* _pOther)
{
	// 충돌에 필요한 로직을 작성
}
```

### 오브젝트에 겹침 불가 충돌체 추가 (강체) RigidBody
```c++
// 강체가 필요하다고 판단될 경우 생성자에서 초기화
Bullet::Bullet()
{
	// 강체의 기준 콜라이더 생성
	CreateCollider();
	// 강체 생성 (기준 콜라이더 필요) 추후 리스트로 받아 여러 충돌체를 기준으로 강체 설정
	this->CreateRigidBody(GetCollider());
	// 강체는 콜라이더의 정보를 공유하며 해당 값을 기준으로 계산됩니다.
}
```

### 오브젝트에 키 및 마우스 이벤트 추가
```c++
// 매 프레임마다 호출
void CPlayer::Update()
{
	// 키보드 입력을 1회 감지지
	if (KEY_TAP(KEY::SPACE))
	{
		// 필요한 로직을 작성
	}

	// 키보드 입력을 매 프레임마다 감지
	if (KEY_HOLD(KEY::RBTN))
	{
		// 필요한 로직을 작성
	}

	Vec2 vDir = Vec2::zero;
	if (KEY_HOLD(KEY::W)) vDir = Vec2::up; 
	if (KEY_HOLD(KEY::S)) vDir += Vec2::down;
	if (KEY_HOLD(KEY::A)) vDir += Vec2::left;
	if (KEY_HOLD(KEY::D)) vDir += Vec2::right;
}
```

### 마우스 위치 변환
```c++
// 마우스 위치를 화면좌표에서 월드좌표로 변환
Vec2 vDir = CCamera::GetI()->GetRealPos(MOUSE_POS);
```


### 오브젝트의 위치, 각도, 피봇 변경
```c++
Bullet* pObject = new Bullet(L"3");
// 위치 변경
pObject->SetPos(Vec2(0.f, 0.f));
// 피봇 변경
pObject->SetPivot(Vec2(0.f, 0.f));
// 각도 변경
pObject->SetAngle(180.f);
// 각도 오프셋 변경
pObject->SetAngleOffset(100.f);

// 오브젝트의 월드 좌표 획득
pObject->GetLocalPos();

// 벡터의 방향을 각도로 변환
Vec2 vDir = Vec2(50.f, 50.f);
vDir.ToAngle();
```

### 카메라 제어 - 게임 특성상 여러 카메라의 생성이 필요하지 않으므로 프레임워크에 고려되지 않음 (싱글톤 클래스)
- 월드좌표와 렌더링 좌표 분리 ()
```c++
// 카메라의 위치 설정 - 월드좌표로 입력
CCamera::GetI()->SetLookAt(vResolution / 2.f);

// 카메라가 항상 따라다니는 타겟 지정 (오브젝트*)
// 많이 사용되는 패턴으로 프레임워크에 추가됨
// 타겟이 지정되었을 경우 타겟을 최우선으로 이동
CCamera::GetI()->SetTarget(mPlayer);

// 반복자에서 카메라 제어
void CSceneStart::Update()
{
	CScene::Update();
	if (KEY_HOLD(KEY::LBTN)) 
	{
		// 월드좌표를 획득
		Vec2 vLookAt = CCamera::GetI()->GetRealPos(MOUSE_POS);
		// 카메라의 좌표를 변환
		CCamera::GetI()->SetLookAt(vLookAt);
	}
}
```

### 리소스 로드
```c++
	// Texture 로드 ( 저장명, 경로 )
	// (추후 같은 값으로 로드를 요청할 경우 미리 생성된 리소스 반환)
	CTexture* pTex = CResMgr::GetI()->LoadTexture(L"ENV_" + mType, L"texture\\map\\" + mType + L".bmp");

	// 사운드 개발중
```


