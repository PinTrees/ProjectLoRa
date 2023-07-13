#pragma once



<<<<<<< Updated upstream
struct Vec2
=======
struct Vect2
>>>>>>> Stashed changes
{
	float x;
	float y;

<<<<<<< Updated upstream
	static Vec2 zero;
	static Vec2 up;
	static Vec2 down;
	static Vec2 left;
	static Vec2 right;

public:
	static float Distance(const Vec2& a, const Vec2& b)
=======
	static Vect2 zero;
	static Vect2 up;
	static Vect2 down;
	static Vect2 left;
	static Vect2 right;

public:
	static float Distance(const Vect2& a, const Vect2& b)
>>>>>>> Stashed changes
	{
		float dx = b.x - a.x;
		float dy = b.y - a.y;
		float result = std::sqrt(dx * dx + dy * dy);

		if (result < 0) result *= -1;

		return result;
	}


<<<<<<< Updated upstream
	static Vec2 FromAngle(float angle)
=======
	static Vect2 FromAngle(float angle)
>>>>>>> Stashed changes
	{
		float radian = angle * PI / 180.0f;  // 각도를 라디안으로 변환

		float x = cos(radian);  // x축 좌표 계산
		float y = sin(radian);  // y축 좌표 계산

<<<<<<< Updated upstream
		return Vec2(x, y);
	}
	static Vec2 FromAngle(int angle) { return Vec2::FromAngle((float)angle); }
=======
		return Vect2(x, y);
	}
	static Vect2 FromAngle(int angle) { return Vect2::FromAngle((float)angle); }
>>>>>>> Stashed changes


public:
	float Length()
	{
		return sqrt(x * x + y * y);
	}
<<<<<<< Updated upstream
	Vec2& Normalize()
=======
	Vect2& Normalize()
>>>>>>> Stashed changes
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
<<<<<<< Updated upstream
	Vec2& Rotate(float angleDegrees)
=======
	Vect2& Rotate(float angleDegrees)
>>>>>>> Stashed changes
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
<<<<<<< Updated upstream
	Vec2& operator =  (POINT _pt)
=======
	Vect2& operator =  (POINT _pt)
>>>>>>> Stashed changes
	{
		x = (float)_pt.x;
		y = (float)_pt.y;
	}

<<<<<<< Updated upstream
	Vec2 operator + (Vec2 _vOther)
	{
		return Vec2(x + _vOther.x, y + _vOther.y);
	}
	void operator += (Vec2 _vOther)
=======
	Vect2 operator + (Vect2 _vOther)
	{
		return Vect2(x + _vOther.x, y + _vOther.y);
	}
	void operator += (Vect2 _vOther)
>>>>>>> Stashed changes
	{
		x += _vOther.x;
		y += _vOther.y;
	}
<<<<<<< Updated upstream
	void operator -= (Vec2 _vOther)
=======
	void operator -= (Vect2 _vOther)
>>>>>>> Stashed changes
	{
		x -= _vOther.x;
		y -= _vOther.y;
	}

<<<<<<< Updated upstream
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
=======
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
>>>>>>> Stashed changes
	}



<<<<<<< Updated upstream
	bool operator == (Vec2 _vOther)
=======
	bool operator == (Vect2 _vOther)
>>>>>>> Stashed changes
	{
		return x == _vOther.x && y == _vOther.y;
	}

<<<<<<< Updated upstream
	bool operator != (Vec2 _vOther)
=======
	bool operator != (Vect2 _vOther)
>>>>>>> Stashed changes
	{
		return !(x == _vOther.x && y == _vOther.y);
	}
public:
<<<<<<< Updated upstream
	Vec2()
=======
	Vect2()
>>>>>>> Stashed changes
		: x(0.f)
		, y(0.f)
	{}

<<<<<<< Updated upstream
	Vec2(float _x, float _y)
=======
	Vect2(float _x, float _y)
>>>>>>> Stashed changes
		: x(_x)
		, y(_y)
	{}

<<<<<<< Updated upstream
	Vec2(int _x, int _y)
=======
	Vect2(int _x, int _y)
>>>>>>> Stashed changes
		: x(static_cast<float>(_x))
		, y(static_cast<float>(_y))
	{}

<<<<<<< Updated upstream
	Vec2(const POINT& _pt)
=======
	Vect2(const POINT& _pt)
>>>>>>> Stashed changes
		:x((float)_pt.x)
		, y((float)_pt.y)
	{}
};



