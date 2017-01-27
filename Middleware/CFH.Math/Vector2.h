#pragma once
#include "Common.h"
#include <initializer_list>

namespace CFH 
{
	namespace Math
	{
		struct DLL_API Vector2 final
		{
		public:
			static const Vector2 UnitX;
			static const Vector2 UnitY;
			static const Vector2 One;
			static const Vector2 Zero;
			static const Vector2 Up;
			static const Vector2 Down;
			static const Vector2 Right;
			static const Vector2 Left;

			float X; float Y;

			Vector2();
			Vector2(float value);
			Vector2(float x, float y);
			Vector2(std::initializer_list<float>);
			~Vector2();

			Vector2 operator+(Vector2 vector) const;
			Vector2 operator-(Vector2 vector) const;
			Vector2 operator-() const;
			Vector2 operator*(Vector2 vector) const;
			Vector2 operator*(float value) const;
			Vector2 operator/(Vector2 vector) const;
			Vector2 operator/(float value) const;
			Vector2 operator+=(Vector2 vector);
			Vector2 operator-=(Vector2 vector);
			Vector2 operator*=(Vector2 vector);
			Vector2 operator*=(float value);
			Vector2 operator/=(Vector2 vector);
			Vector2 operator/=(float value);
			bool operator==(Vector2 vector) const;
			bool operator!=(Vector2 vector) const;
			Vector2 operator=(Vector2 vector);

			static Vector2 Add(Vector2 lhs, Vector2 rhs);
			static void Add(Vector2 lhs, Vector2 rhs, Vector2& result);
			static Vector2 Subtract(Vector2 lhs, Vector2 rhs);
			static void Subtract(Vector2 lhs, Vector2 rhs, Vector2& result);
			static Vector2 Multiply(Vector2 lhs, Vector2 rhs);
			static void Multiply(Vector2 lhs, Vector2 rhs, Vector2& result);
			static Vector2 Multiply(Vector2 vector, float value);
			static void Multiply(Vector2 vector, float value, Vector2& result);
			static Vector2 Divide(Vector2 lhs, Vector2 rhs);
			static void Divide(Vector2 lhs, Vector2 rhs, Vector2& result);
			static Vector2 Divide(Vector2 vector, float value);
			static void Divide(Vector2 vector, float value, Vector2& result);
			static Vector2 Negate(Vector2 vector);
			static void Negate(Vector2 vector, Vector2& result);

			float Length() const;
			void Length(float& result) const;
			static float Length(Vector2 vector);
			static void Length(Vector2 vector, float& result);
			float LengthSquared() const;
			void LengthSquared(float& result) const;
			static float LengthSquared(Vector2 vector);
			static void LengthSquared(Vector2 vector, float& result);

			static float Distance(Vector2 lhs, Vector2 rhs);
			static void Distance(Vector2 lhs, Vector2 rhs, float& result);
			static float DistanceSquared(Vector2 lhs, Vector2 rhs);
			static void DistanceSquared(Vector2 lhs, Vector2 rhs, float& result);

			static float Dot(Vector2 lhs, Vector2 rhs);
			static void Dot(Vector2 lhs, Vector2 rhs, float& result);

			static Vector2 Clamp(Vector2 value, Vector2 min, Vector2 max);
			static void Clamp(Vector2 value, Vector2 min, Vector2 max, Vector2& result);
			void Normalize();
			static Vector2 Normalize(Vector2 vector);
			static void Normalize(Vector2 vector, Vector2& result);
		};
	}
}

