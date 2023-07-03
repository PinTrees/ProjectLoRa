## 코드베이스
추후 웹으로 재구축

게임 내 오브젝트 클래스 생성
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

오브젝트를 게임 내에 배치
```c++
  	// CObject 를 상속받은 객체 생성
	Bullet* pBullet = new Bullet(L"3");
	pBullet->SetPos(Vec2(0.f, 0.f));
	pBullet->SetName(L"Bullet_Player");

  	// 객체를 관리되는 항목에 추가
	CreateObject(pBullet, GROUP_TYPE::DEFAULT);
```


스프라이트 애니메이션
```c++
// 애니메이터를 통해 애니매이션을 제어
// 해당 오브젝트에 애니메이션이 필요하다고 판단될 경우 생성자에서 초기화
Bullet::Bullet()
{
	// 충돌체 생성
	CreateCollider();
	GetCollider()->SetScale(Vec2(15, 15));

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
```




