#include "Shader.h"
#include "Core\IO\File.h"
#include "Core\Logging\Log.h"

#include <vector>

namespace CFH
{
	namespace Graphics
	{
#define GL_ENUM(x) \
	static_cast<GLenum>(x)

		Shader::Shader(Type type) :
			id_(0),
			type_(type),
			created_(false),
			compiled_(false)
		{
		}
		Shader::Shader(const std::string& path, Type type) :
			Shader(type)
		{
			Load(path);
		}
		Shader::~Shader()
		{
			Destroy();
		}

		void Shader::Create()
		{
			id_ = glCreateShader(GL_ENUM(type_));
			created_ = true;
			compiled_ = false;
		}
		void Shader::Destroy()
		{
			ASSERT(created_);
			if (!created_)
				return;

			glDeleteShader(id_);
			created_ = false;
			compiled_ = false;
		}

		void Shader::Load(const std::string& path)
		{
			if (!created_)
				Create();

			if (compiled_)
				return;

			path_ = path;
			code_ = File::ReadText(path);
			compiled_ = Compile();
		}
		bool Shader::Compile()
		{
			const char* codePtr = code_.c_str();
			glShaderSource(id_, 1, &codePtr, nullptr);
			glCompileShader(id_);

			// Check for compilation errors.
			int result;
			glGetShaderiv(id_, GL_COMPILE_STATUS, &result);

			ASSERT(result == GL_TRUE);
			if (result != GL_TRUE)
			{
				// Get error log message
				int logLength;
				glGetShaderiv(id_, GL_INFO_LOG_LENGTH, &logLength);
				std::vector<char> errorMessage(logLength);
				glGetShaderInfoLog(id_, logLength, nullptr, errorMessage.data());

				LOG_ERROR(errorMessage.data());
				return false;
			}
			return true;
		}

		int Shader::GetId() const
		{
			return id_;
		}
		Shader::Type Shader::GetType() const
		{
			return type_;
		}
		std::string Shader::GetCode() const
		{
			return code_;
		}
		bool Shader::IsCreated() const
		{
			return created_;
		}
		bool Shader::IsCompiled() const
		{
			return compiled_;
		}
	}
}
