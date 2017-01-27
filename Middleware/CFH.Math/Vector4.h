#pragma once
#include "Common.h"
#include <initializer_list>

namespace CFH
{
	namespace Math
	{
		struct Vector2;
		struct Vector3;
		struct Matrix4;

		struct DLL_API Vector4 final
		{
		public:
			static const Vector4 UnitX;
			static const Vector4 UnitY;
			static const Vector4 UnitZ;
			static const Vector4 UnitW;
			static const Vector4 One;
			static const Vector4 Zero;

			float X; float Y; float Z; float W;

			Vector4();
			Vector4(float value);
			Vector4(Vector2 vector, float z, float w);
			Vector4(Vector3 vector, float w);
			Vector4(float x, float y, float z, float w);
			Vector4(std::initializer_list<float>);
			~Vector4();

			Vector4 operator+(Vector4 vector) const;
			Vector4 operator-(Vector4 vector) const;
			Vector4 operator-() const;
			Vector4 operator*(Vector4 vector) const;
			Vector4 operator*(float value) const;
			Vector4 operator/(Vector4 vector) const;
			Vector4 operator/(float value) const;
			Vector4 operator+=(Vector4 vector);
			Vector4 operator-=(Vector4 vector);
			Vector4 operator*=(Vector4 vector);
			Vector4 operator*=(float value);
			Vector4 operator/=(Vector4 vector);
			Vector4 operator/=(float value);
			bool operator==(Vector4 vector) const;
			bool operator!=(Vector4 vector) const;
			Vector4 operator=(Vector4 vector);

			static Vector4 Add(Vector4 lhs, Vector4 rhs);
			static void Add(Vector4 lhs, Vector4 rhs, Vector4& result);
			static Vector4 Subtract(Vector4 lhs, Vector4 rhs);
			static void Subtract(Vector4 lhs, Vector4 rhs, Vector4& result);
			static Vector4 Multiply(Vector4 lhs, Vector4 rhs);
			static void Multiply(Vector4 lhs, Vector4 rhs, Vector4& result);
			static Vector4 Multiply(Vector4 vector, float value);
			static void Multiply(Vector4 vector, float value, Vector4& result);
			static Vector4 Divide(Vector4 lhs, Vector4 rhs);
			static void Divide(Vector4 lhs, Vector4 rhs, Vector4& result);
			static Vector4 Divide(Vector4 vector, float value);
			static void Divide(Vector4 vector, float value, Vector4& result);
			static Vector4 Negate(Vector4 vector);
			static void Negate(Vector4 vector, Vector4& result);

			float Length() const;
			void Length(float& result) const;
			static float Length(Vector4 vector);
			static void Length(Vector4 vector, float& result);
			float LengthSquared() const;
			void LengthSquared(float& result) const;
			static float LengthSquared(Vector4 vector);
			static void LengthSquared(Vector4 vector, float& result);

			static float Distance(Vector4 lhs, Vector4 rhs);
			static void Distance(Vector4 lhs, Vector4 rhs, float& result);
			static float DistanceSquared(Vector4 lhs, Vector4 rhs);
			static void DistanceSquared(Vector4 lhs, Vector4 rhs, float& result);

			static float Dot(Vector4 lhs, Vector4 rhs);
			static void Dot(Vector4 lhs, Vector4 rhs, float& result);

			static Vector4 Clamp(Vector4 vector, Vector4 min, Vector4 max);
			static void Clamp(Vector4 vector, Vector4 min, Vector4 max, Vector4& result);
			void Normalize();
			static Vector4 Normalize(Vector4 vector);
			static void Normalize(Vector4 vector, Vector4& result);

			static Vector4 Transform(Vector4 vector, Matrix4 matrix);
			static void Transform(Vector4 vector, Matrix4 matrix, Vector4& result);
		};
	}
}

