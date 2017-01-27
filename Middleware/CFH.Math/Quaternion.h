#pragma once
#include "Common.h"

namespace CFH
{
	namespace Math
	{
		struct Vector3;
		struct Vector4;
		struct Matrix4;

		struct DLL_API Quaternion final
		{
		public:
			static const Quaternion Identity;
			float X, Y, Z, W;

			Quaternion();
			Quaternion(float x, float y, float z, float w);
			Quaternion(Vector3 vector, float w);
			Quaternion(Vector4 vector);
			~Quaternion();

			Quaternion operator+(Quaternion quaternion) const;
			Quaternion operator/(Quaternion quaternion) const;
			Quaternion operator/(float scaleFactor) const;
			Quaternion operator*(Quaternion quaternion) const;
			Quaternion operator*(float scaleFactor) const;
			Quaternion operator-(Quaternion quaternion) const;
			Quaternion operator-() const;
			Quaternion operator+=(Quaternion quaternion);
			Quaternion operator-=(Quaternion quaternion);
			Quaternion operator*=(Quaternion quaternion);
			Quaternion operator/=(Quaternion quaternion);
			Quaternion operator=(Quaternion quaternion);
			bool operator==(Quaternion quaternion) const;
			bool operator!=(Quaternion quaternion) const;

			Vector3 GetForward() const;
			void GetForward(Vector3& result) const;
			Vector3 GetBackward() const;
			void GetBackward(Vector3& result) const;
			Vector3 GetRight() const;
			void GetRight(Vector3& result) const;
			Vector3 GetLeft() const;
			void GetLeft(Vector3& result) const;
			Vector3 GetUp() const;
			void GetUp(Vector3& result) const;
			Vector3 GetDown() const;
			void GetDown(Vector3& result) const;

			static Quaternion Add(Quaternion quaternionA, Quaternion quaternionB);
			static void Add(Quaternion quaternionA, Quaternion quaternionB, Quaternion& result);
			static Quaternion Subtract(Quaternion quaternionA, Quaternion quaternionB);
			static void Subtract(Quaternion quaternionA, Quaternion quaternionB, Quaternion& result);
			static Quaternion Multiply(Quaternion quaternionA, Quaternion quaternionB);
			static void Multiply(Quaternion quaternionA, Quaternion quaternionB, Quaternion& result);
			static Quaternion Multiply(Quaternion quaternionA, float scaleFactor);
			static void Multiply(Quaternion quaternionA, float scaleFactor, Quaternion& result);
			static Quaternion Divide(Quaternion quaternionA, Quaternion quaternionB);
			static void Divide(Quaternion quaternionA, Quaternion quaternionB, Quaternion& result);
			static Quaternion Divide(Quaternion quaternionA, float scaleFactor);
			static void Divide(Quaternion quaternionA, float scaleFactor, Quaternion& result);
			static Quaternion Negate(Quaternion quaternion);
			static void Negate(Quaternion quaternion, Quaternion& result);

			static Quaternion CreateFromAxisAngle(Vector3 axis, float angle);
			static void CreateFromAxisAngle(Vector3 axis, float angle, Quaternion& result);
			static Quaternion CreateFromRotationMatrix(Matrix4 matrix);
			static void CreateFromRotationMatrix(Matrix4 matrix, Quaternion& result);
			static Quaternion CreateFromYawPitchRoll(float yaw, float pitch, float roll);
			static void CreateFromYawPitchRoll(float yaw, float pitch, float roll, Quaternion& result);

			static Quaternion Concatenate(Quaternion quaternion, Quaternion quaternion2);
			static void Concatenate(Quaternion quaternion, Quaternion quaternion2, Quaternion& result);
			void Conjugate();
			static Quaternion Conjugate(Quaternion quaternion);
			static void Conjugate(Quaternion quaternion, Quaternion& result);
			static float Dot(Quaternion quaternion, Quaternion quaternion2);
			static void Dot(Quaternion quaternion, Quaternion quaternion2, float& result);
			static Quaternion Inverse(Quaternion quaternion);
			static void Inverse(Quaternion quaternion, Quaternion& result);
			float Length() const;
			void Length(float& result) const;
			float LengthSquared() const;
			void LengthSquared(float& result) const;
			static Quaternion Lerp(Quaternion quaternion, Quaternion quaternion2, float amount);
			static void Lerp(Quaternion quaternion, Quaternion quaternion2, float amount, Quaternion& result);
			void Normalize();
			static Quaternion Normalize(Quaternion quaternion);
			static void Normalize(Quaternion quaternion, Quaternion& result);
			static Quaternion Slerp(Quaternion quaternion, Quaternion quaternion2, float amount);
			static void Slerp(Quaternion quaternion, Quaternion quaternion2, float amount, Quaternion& result);
			Vector3 ToEular() const;
			void ToEular(Vector3& result) const;
		};
	}
}

