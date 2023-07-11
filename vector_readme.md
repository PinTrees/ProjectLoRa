### 방향 벡터의 각도 변경
```c++
Vect2 vDir = Vect2(1.f, 0.f);
// 각도 변경 ( 360 도 기반 )
vDir.Rotate(15.f);
```
### 크기 벡터의 방향 벡터 변환
```c++
Vect2 vDir = GetPos() - pObj->GetPos();
// 크기 벡터 노멀라이즈
vDir.Normalize();
```
### 벡터간 거리 구하기
```c++
// Vect2 내장 스테틱 함수
if(Vect2::Distance(GetPos(), pObj->GetPos()) > 3.f)
{
}

// 또는
Vect2 vDir = GetPos() - pObj->GetPos();
if(vDir.Length() > 3.f)
{
}

// 항상 절댓값으로 반환됨
```

### 방향 벡터를 각도값으로 변경
```c++
Vect2 vDir = GetPos() - pObj->GetPos();
float angle = vDir.ToAngle();
```




