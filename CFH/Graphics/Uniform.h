#pragma once
#include "CFH.h"

namespace CFH
{
	namespace Graphics
	{
		class CFH_API Uniform
		{
		public:
			Uniform();
			Uniform(int location);
			~Uniform();

			int GetLocation() const;
			void SetSampler(int value) const;

			void operator=(const int& value) const;
			void operator=(const unsigned int& value) const;
			void operator=(const float& value) const;
			/*void operator=(const Vector2& value) const;
			void operator=(const Vector3& value) const;
			void operator=(const Matrix4& value) const;*/

			template<typename T>
			void Set(T v0) const;

			template<typename T>
			void Set(T v0, T v1) const;

			template<typename T>
			void Set(T v0, T v1, T v2) const;

			template<typename T>
			void Set(T v0, T v1, T v2, T v3) const;

			//template<typename T>
			//void SetVector3(const T& value, int count = 1) const;

			//template<typename T>
			//void SetMatrix(const T& value, int cound = 1, bool transpose = false) const;

		private:
			int location_;
		};
	}
}

