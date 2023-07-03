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

```




