#pragma once



struct Vec2
{
	float x;
	float y;

	static Vec2 zero;
	static Vec2 up;
	static Vec2 down;
	static Vec2 left;
	static Vec2 right;

public:
	static float Distance(const Vec2& a, const Vec2& b)
	{
		float dx = b.x - a.x;
		float dy = b.y - a.y;
		float result = std::sqrt(dx * dx + dy * dy);

		if (result < 0) result *= -1;

		return result;
	}



public:
	float Length()
	{

		return sqrt(x * x + y * y);
	}
	Vec2& Normalize()
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
	Vec2& Rotate(float angleDegrees)
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
	Vec2& operator =  (POINT _pt)
	{
		x = (float)_pt.x;
		y = (float)_pt.y;
	}

	Vec2 operator + (Vec2 _vOther)
	{
		return Vec2(x + _vOther.x, y + _vOther.y);
	}
	void operator += (Vec2 _vOther)
	{
		x += _vOther.x;
		y += _vOther.y;
	}
	void operator -= (Vec2 _vOther)
	{
		x -= _vOther.x;
		y -= _vOther.y;
	}

	Vec2 operator - (Vec2 _vOther)
	{
		return Vec2(x - _vOther.x, y - _vOther.y);
	}

	Vec2 operator * (Vec2 _vOther)
	{
		return Vec2(x * _vOther.x, y * _vOther.y);
	}
	Vec2 operator * (int _i)
	{
		return Vec2(x * (float)_i, y * (float)_i);
	}
	Vec2 operator*(float _f)
	{
		return Vec2(x * _f, y * _f);
	}
	Vec2 operator / (Vec2 _vOther)
	{
		assert(!(0.f == _vOther.x || 0.f == _vOther.y));
		return Vec2(x / _vOther.x , y / _vOther.y);
	}
	Vec2 operator / (float _f)
	{
		assert(!(0.f == _f));
		return Vec2(x / _f, y / _f);
	}



	bool operator == (Vec2 _vOther)
	{
		return x == _vOther.x && y == _vOther.y;
	}

	bool operator != (Vec2 _vOther)
	{
		return !(x == _vOther.x && y == _vOther.y);
	}
public:
	Vec2()
		: x(0.f)
		, y(0.f)
	{}

	Vec2(float _x, float _y)
		: x(_x)
		, y(_y)
	{}

	Vec2(int _x, int _y)
		: x(static_cast<float>(_x))
		, y(static_cast<float>(_y))
	{}

	Vec2(const POINT& _pt)
		:x((float)_pt.x)
		, y((float)_pt.y)
	{}
};



