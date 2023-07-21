#pragma once



struct Vect2
{
	float x;
	float y;

	static Vect2 zero;
	static Vect2 up;
	static Vect2 down;
	static Vect2 left;
	static Vect2 right;

public:
	static float Distance(const Vect2& a, const Vect2& b)
	{
		float dx = b.x - a.x;
		float dy = b.y - a.y;
		float result = std::sqrt(dx * dx + dy * dy);

		if (result < 0) result *= -1;

		return result;
	}


	static Vect2 FromAngle(float angle)
	{
		float radian = angle * PI / 180.0f;  // 각도를 라디안으로 변환

		float x = cos(radian);  // x축 좌표 계산
		float y = sin(radian);  // y축 좌표 계산

		return Vect2(x, y);
	}
	static Vect2 FromAngle(int angle) { return Vect2::FromAngle((float)angle); }


public:
	float Length()
	{
		return sqrt(x * x + y * y);
	}
	Vect2& Normalize()
	{
		float fLen = Length();
		if(fLen != 0.f)
		{
			x /= fLen;
			y /= fLen;
			return *this;
		}

		return *this;
	}
	Vect2& Rotate(float angleDegrees)
	{
		float angleRadians = angleDegrees * (PI / 180.0f); // 각도를 라디안으로 변환

		float cosAngle = cosf(angleRadians);
		float sinAngle = sinf(angleRadians);

		float newX = x * cosAngle - y * sinAngle;
		float newY = x * sinAngle + y * cosAngle;

		x = newX;
		y = newY;

		return *this;
	}

	float ToAngle()
	{
		Normalize();

		float angle = atan2f(y, x) * 180.0f / PI;
		if (angle < 0.0f)
		{
			angle += 360.0f;
		}
		return angle;
	}

public:
	Vect2& operator = (POINT _pt)
	{
		x = (float)_pt.x;
		y = (float)_pt.y;

		return *this;
	}

	Vect2 operator + (Vect2 _vOther)
	{
		return Vect2(x + _vOther.x, y + _vOther.y);
	}
	void operator += (Vect2 _vOther)
	{
		x += _vOther.x;
		y += _vOther.y;
	}
	void operator -= (Vect2 _vOther)
	{
		x -= _vOther.x;
		y -= _vOther.y;
	}

	Vect2 operator - (Vect2 _vOther)
	{
		return Vect2(x - _vOther.x, y - _vOther.y);
	}

	Vect2 operator * (Vect2 _vOther)
	{
		return Vect2(x * _vOther.x, y * _vOther.y);
	}
	Vect2 operator * (int _i)
	{
		return Vect2(x * (float)_i, y * (float)_i);
	}
	Vect2 operator*(float _f)
	{
		return Vect2(x * _f, y * _f);
	}
	Vect2 operator / (Vect2 _vOther)
	{
		assert(!(0.f == _vOther.x || 0.f == _vOther.y));
		return Vect2(x / _vOther.x , y / _vOther.y);
	}
	Vect2 operator / (float _f)
	{
		assert(!(0.f == _f));
		return Vect2(x / _f, y / _f);
	}



	bool operator == (Vect2 _vOther)
	{
		return x == _vOther.x && y == _vOther.y;
	}

	bool operator != (Vect2 _vOther)
	{
		return !(x == _vOther.x && y == _vOther.y);
	}
public:
	Vect2()
		: x(0.f)
		, y(0.f)
	{}

	Vect2(float _x, float _y)
		: x(_x)
		, y(_y)
	{}
	Vect2(float _x, UINT _y)
		: x(_x)
		, y(static_cast<float>(_y))
	{}
	Vect2(UINT _x, float _y)
		: x(static_cast<float>(_x))
		, y(_y)
	{}
	Vect2(int _x, int _y)
		: x(static_cast<float>(_x))
		, y(static_cast<float>(_y))
	{}
	Vect2(UINT _x, UINT _y)
		: x(static_cast<float>(_x))
		, y(static_cast<float>(_y))
	{}
	Vect2(const POINT& _pt)
		:x((float)_pt.x)
		, y((float)_pt.y)
	{}
};



