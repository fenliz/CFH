#pragma once
#include "Common.h"

namespace CFH
{
	namespace Math
	{
		class DLL_API MathHelper
		{
		public:
			static const float PI;
			static const float PIOver2;
			static const float PIOver4;

			static float Sqrt(float value);
			static void Sqrt(float value, float& result);

			static float Sin(float value);
			static void Sin(float value, float& result);
			static float Cos(float value);
			static void Cos(float value, float& result);
			static float Tan(float value);
			static void Tan(float value, float& result);

			static float ASin(float value);
			static void ASin(float value, float& result);
			static float ACos(float value);
			static void ACos(float value, float& result);
			static float ATan(float value);
			static void ATan(float value, float& result);
			static void ATan2(float v1, float v2, float& result);
			static float ATan2(float v1, float v2);

			static float Max(float a, float b);
			static void Max(float a, float b, float& result);
			static float Min(float a, float b);
			static void Min(float a, float b, float& result);

			static float Clamp(float value, float min, float max);
			static void Clamp(float value, float min, float max, float& result);

			static float Abs(float value);
			static void Abs(float value, float& result);

			static float DegreesToRadians(float value);
			static void DegreesToRadians(float value, float& result);

			static float RadiansToDegrees(float value);
			static void RadiansToDegrees(float value, float& result);
		};
	}
}