#include "Uniform.h"

#include <GL\glew.h>

namespace CFH
{
	namespace Graphics
	{
		Uniform::Uniform() :
			location_(-1)
		{
		}
		Uniform::Uniform(int location) :
			location_(location)
		{
		}
		Uniform::~Uniform()
		{
		}

		int Uniform::GetLocation() const
		{
			return location_;
		}

		void Uniform::SetSampler(int value) const
		{
			glUniform1i(location_, value);
		}

		void Uniform::operator=(const float& value) const
		{
			glUniform1f(location_, value);
		}
		void Uniform::operator=(const int& value) const
		{
			glUniform1i(location_, value);
		}
		void Uniform::operator=(const unsigned int& value) const
		{
			glUniform1ui(location_, value);
		}

		/*void Uniform::operator=(const Vector2& value) const
		{
			glUniform2fv(location_, GL_FALSE, value);
		}

		void Uniform::operator=(const Vector3& value) const
		{
			glUniform3fv(location_, GL_FALSE, value);
		}

		void Uniform::operator(const Matrix4& value) const
		{
			glUniformMatrix4fv(location_, 1, GL_FALSE, value);
		}*/
	}
}


