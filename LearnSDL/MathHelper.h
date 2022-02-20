#pragma once
#include <math.h>

#define PI 3.14159265
#define DEG_TO_RAD PI/180.0f
namespace QuickSDL {


	struct Vector2
	{
		float x;
		float y;

		Vector2(float _x = 0.0f, float _y = 0.0f) : x(_x), y(_y) {}

		float MagnitudeSqrt()
		{
			return x * x + y * y;
		}

		float Magnitude()
		{
			return (float)sqrt(x * x + y * y);
		}

		Vector2 Normalized()
		{
			float mag = Magnitude();

			return Vector2(x / mag, y / mag);
		}

		Vector2& operator += (const Vector2& rhs)
		{
			x += rhs.x;
			y += rhs.y;

			return *this;
		}

		Vector2& operator -= (const Vector2& rhs)
		{
			x -= rhs.x;
			y -= rhs.y;

			return *this;
		}

		Vector2 operator -() const
		{
			return Vector2(-x, -y);
		}
	};

	inline Vector2 operator +(const Vector2& lhs, const Vector2& rhs)
	{
		return Vector2(lhs.x + rhs.x, lhs.y + rhs.y);
	}

	inline Vector2 operator -(const Vector2& lhs, const Vector2& rhs)
	{
		return Vector2(lhs.x - rhs.x, lhs.y - rhs.y);
	}

	inline Vector2 operator *(const Vector2& lhs, const float& rhs)
	{
		return Vector2(lhs.x * rhs, lhs.y * rhs);
	}

	inline Vector2 RotateVector(Vector2& vec, float angle)
	{
		float radAngle = (float)(angle * DEG_TO_RAD);

		float xComp = (float)((cos(radAngle) * vec.x) - (sin(radAngle) * vec.y));

		float yComp = (float)((sin(radAngle) * vec.x) + (cos(radAngle) * vec.y));

		return Vector2(xComp, yComp);
	}

	inline Vector2 Lerp(const Vector2& start, const Vector2& end, float time)
	{
		if (time <= 0) return start;
		if (time >= 1.0f) return end;

		Vector2 direction = (end - start).Normalized();
		float magnitude = (end - start).Magnitude();

		return start + direction * magnitude * time;
	}

	const Vector2 VEC2_ZERO = { 0.0f, 0.0f };
	const Vector2 VEC2_ONE = { 1.0f, 1.0f };
	const Vector2 VEC2_UP = { 0.0f, 1.0f };
	const Vector2 VEC2_Right = { 1.0f, 0.0f };

}