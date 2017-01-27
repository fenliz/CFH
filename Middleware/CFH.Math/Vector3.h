#pragma once
#include "Common.h"
#include <initializer_list>

namespace CFH
{
	namespace Math
	{
		struct Vector2;
		struct Matrix4;
		struct Quaternion;

		struct DLL_API Vector3 final
		{
		public:
			static const Vector3 UnitX;
			static const Vector3 UnitY;
			static const Vector3 UnitZ;
			static const Vector3 One;
			static const Vector3 Zero;
			static const Vector3 Forward;
			static const Vector3 Backward;
			static const Vector3 Up;
			static const Vector3 Down;
			static const Vector3 Right;
			static const Vector3 Left;

			float X; float Y; float Z;

			Vector3();
			Vector3(float value);
			Vector3(Vector2 vector, float z);
			Vector3(float x, float y, float z);
			Vector3(std::initializer_list<float>);
			~Vector3();

			Vector3 operator+(Vector3 vector) const;
			Vector3 operator-(Vector3 vector) const;
			Vector3 operator-() const;
			Vector3 operator*(Vector3 vector) const;
			Vector3 operator*(float value) const;
			Vector3 operator/(Vector3 vector) const;
			Vector3 operator/(float value) const;
			Vector3 operator+=(Vector3 vector);
			Vector3 operator-=(Vector3 vector);
			Vector3 operator*=(Vector3 vector);
			Vector3 operator*=(float value);
			Vector3 operator/=(Vector3 vector);
			Vector3 operator/=(float value);
			bool operator==(Vector3 vector) const;
			bool operator!=(Vector3 vector) const;
			Vector3 operator=(Vector3 vector);

			static Vector3 Add(Vector3 lhs, Vector3 rhs);
			static void Add(Vector3 lhs, Vector3 rhs, Vector3& result);
			static Vector3 Subtract(Vector3 lhs, Vector3 rhs);
			static void Subtract(Vector3 lhs, Vector3 rhs, Vector3& result);
			static Vector3 Multiply(Vector3 lhs, Vector3 rhs);
			static void Multiply(Vector3 lhs, Vector3 rhs, Vector3& result);
			static Vector3 Multiply(Vector3 vector, float value);
			static void Multiply(Vector3 vector, float value, Vector3& result);
			static Vector3 Divide(Vector3 lhs, Vector3 rhs);
			static void Divide(Vector3 lhs, Vector3 rhs, Vector3& result);
			static Vector3 Divide(Vector3 vector, float value);
			static void Divide(Vector3 vector, float value, Vector3& result);
			static Vector3 Negate(Vector3 vector);
			static void Negate(Vector3 vector, Vector3& result);

			float Length() const;
			void Length(float& result) const;
			static float Length(Vector3 vector);
			static void Length(Vector3 vector, float& result);
			float LengthSquared() const;
			void LengthSquared(float& result) const;
			static float LengthSquared(Vector3 vector);
			static void LengthSquared(Vector3 vector, float& result);

			static float Distance(Vector3 lhs, Vector3 rhs);
			static void Distance(Vector3 lhs, Vector3 rhs, float& result);
			static float DistanceSquared(Vector3 lhs, Vector3 rhs);
			static void DistanceSquared(Vector3 lhs, Vector3 rhs, float& result);

			static float Dot(Vector3 lhs, Vector3 rhs);
			static void Dot(Vector3 lhs, Vector3 rhs, float& result);
			static Vector3 Cross(Vector3 lhs, Vector3 rhs);
			static void Cross(Vector3 lhs, Vector3 rhs, Vector3& result);

			static Vector3 Clamp(Vector3 value, Vector3 min, Vector3 max);
			static void Clamp(Vector3 value, Vector3 min, Vector3 max, Vector3& result);
			void Normalize();
			static Vector3 Normalize(Vector3 vector);
			static void Normalize(Vector3 vector, Vector3& result);

			static Vector3 Transform(Vector3 vector, Matrix4 matrix);
			static void Transform(Vector3 vector, Matrix4 matrix, Vector3& result);
			static Vector3 Vector3::Transform(Vector3 vector, Quaternion rotation);
			static void Vector3::Transform(Vector3 vector, Quaternion rotation, Vector3& result);
			static Vector3 Vector3::TransformNormal(Vector3 vector, Matrix4 matrix);
			static void Vector3::TransformNormal(Vector3 vector, Matrix4 matrix, Vector3& result);
		};
	}
}

