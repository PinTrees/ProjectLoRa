## 기본원칙

1. 가독성
3. 자동완성 서식 준수 Ctrl + K + D

## 기초 코딩 표준

1. 클래스와 구조체의 이름에 파스칼 표기법 사용
```c++
class DatabaseManager
struct Vector2Int
```

2. 함수 내 지역변수 및 함수 매개변수에 카멜 표기법 사용
```c++
void Print(const int dataInfo)
{
  int dataIndex;
}
```

3. 함수의 이름은 동사를 선 작성 한다
```c++
void PlaySound();
```

4. 퍼블릭 함수에 파스칼 표기법 사용
```c++
public:
  void PlaySound();
```

5. 프라이빗 함수에 카멜 표기법 사용
```c++
private:
  void normalize();
```
   

7. 외부 변수가 동일한 이름을 사용중이라면 내부 변수에 _ 추가
```c++
class Class
{
private:
    int count;
public:
    void Func(const int _count)
    {
        count = _count;
    }
}
```

6. 상수 또는 #define 으로 정의된 변수의 이름은 대문자 언더바 표기법 사용
 ```c++
const int MAX_COUNT = 1;
#define MAX_LENGTH 50
```

6. 클래스 내부 멤버 변수명은 앞에 m 표기.
```c++
 class Item
 {
 protected:
     int mID;
 private:
     string mName;
 }
```

8. bool 변수는 앞에 b 사용
 ```c++
bool bDeath;	
bool isDeath;
```

8. 인터페이스를 선언할 때는 앞에 I 표기
 ```c++
class IComponent
```

9. 클래스 멤버 변수에 접근할 때는 항상 setter와 getter를 사용.
```c++
class Employee
{
private:
    string mName;
public:
    const string& GetName() const;
    void SetName(const string& name);
}
```

10. 인클루드 순서
 ```c++
#pragma once
#include <vector>
#include <stdlib.h>

#include "GameObject.h"
```

11. 가능한 모든 경우에 NULL 대신 nullptr 사용
 ```c++
Cobject* data = nullptr;
```

### 코드 포멧
1. 중괄호( {} )
 ```c++
class Data
{
}

if (true)
{

}

// Get Set 예외
public int GetInt() {}
```

2. 포인터나 참조 기호는 자료형 뒤에 표기
```c++
int&  number;
int*  number;
```

3. nullptr 비교연산은 항상 nullptr을 우선 작성한다.
```c++
if(nullptr == data)
{
}
```

### 함수
1. 함수의 명확한 행동 정의
2. cont 사용
```c++
const Monster* GetMonsterByIndex(const int index) const;

// 명확하지 않은 함수 이름
bool CheckHp();

// 명확한 함수 이름
bool IsDeath();
```

3. 함수에서 매개변수를 통해 값을 반환할 때(out 매개변수)는 포인터를 사용하며, 매개변수 이름 앞에 out_을 표기
```c++
void GetSceneSize(int* out_width, int* const out_height)
{
}
```

### Class
1. 생성자 작성법
2. 각 라인당 하나의 변수 초기화
```c++
MyClass::MyClass(const int var1, const int var2)
   : mVar1(var1)
   , mVar2(var2)
   , mVar3(0)
{
}
```


### Enum

1. 항상 enum class 를 사용.
2. enum 앞 E 표기.
 ```c++
enum class EDirection
{
    Top,
    Bottom,
    Left,
    Right
}
```

