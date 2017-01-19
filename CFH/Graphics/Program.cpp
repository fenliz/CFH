#include "Program.h"
#include "Core\Exceptions.h"
#include "Core\Logging\Log.h"

#include <GL\glew.h>

namespace CFH
{
	namespace Graphics
	{
		Program::Program() :
			id_(0),
			created_(false),
			linked_(false)
		{
		}
		Program::Program(const std::string& vertexShaderPath, const std::string& fragmentShaderPath)
		{
			Shader vertexShader(vertexShaderPath, Shader::Type::Vertex);
			Shader fragmentShader(fragmentShaderPath, Shader::Type::Fragment);

			Load(vertexShader, fragmentShader);
		}
		Program::Program(const Shader& vertexShader, const Shader& fragmentShader)
		{
			Load(vertexShader, fragmentShader);
		}
		Program::~Program()
		{
			Destroy();
		}

		void Program::Create()
		{
			ASSERT(!created_);
			Destroy();

			id_ = glCreateProgram();
			created_ = true;
			linked_ = false;
		}
		void Program::Destroy()
		{
			ASSERT(created_);
			if (created_)
				return;

			glDeleteProgram(id_);
			created_ = false;
			linked_ = false;
		}

		void Program::Load(const Shader& vertexShader, const Shader& fragmentShader)
		{
			ASSERT(created_);
			if (!created_)
				Create();

			if (linked_)
				return;

			linked_ = Link(vertexShader, fragmentShader);
			ASSERT(linked_);
			MapUniforms(vertexShader);
			MapUniforms(fragmentShader);
		}

		void Program::Bind() const
		{
			ASSERT(linked_);
			if (linked_)
				glUseProgram(id_);
			else
				LOG_ERROR("Loading the program is required before binding it.");
		}
		void Program::Unbind() const
		{
			glUseProgram(0);
		}

		bool Program::IsLinked() const
		{
			return linked_;
		}
		int Program::GetId() const
		{
			return id_;
		}

		Uniform& Program::operator[](const std::string& uniformName) throw(std::out_of_range)
		{
			return uniforms_.at(uniformName);
		}
		const Uniform& Program::operator[](const std::string& uniformName) const throw(std::out_of_range)
		{
			return uniforms_.at(uniformName);
		}
		int Program::GetUniformLocation(const std::string& uniformName) const throw(std::out_of_range)
		{
			return uniforms_.at(uniformName).GetLocation();
		}
		const Uniform& Program::GetUniform(const std::string& uniformName) const throw(std::out_of_range)
		{
			return uniforms_.at(uniformName);
		}

		void Program::MapUniforms(const Shader& shader)
		{
			std::stringstream stream;
			stream.str(shader.GetCode());
		
			std::string uniformName;
			std::string uniformType;
			while (stream.good())
			{
				// Looks for the word uniform in the shader code.
				stream >> uniformName;
				if (uniformName == "uniform")
				{
					// When it finds a uniform it reads the following values as type and name
					// e.g. uniform float Scale;
					//             [type][name]
					stream >> uniformType;
					stream >> uniformName;

					// Remove any possible semicolon from the name
					if (uniformName[uniformName.size() - 1] == ';')
						uniformName.erase(uniformName.size() - 1);

					// Remove brackets if it's an array variable.
					uniformName = uniformName.substr(0, uniformName.find_last_of("["));

					// Create a Uniform-instance in the Program so that we can bind values to it.
					uniforms_[uniformName] = Uniform(glGetUniformLocation(id_, uniformName.c_str()));
				}
			}
		}
		bool Program::Link(const Shader& vertexShader, const Shader& fragmentShader)
		{
			glAttachShader(id_, vertexShader.GetId());
			glAttachShader(id_, fragmentShader.GetId());
			glLinkProgram(id_);

			// Check for linker errors.
			int result;
			glGetProgramiv(id_, GL_LINK_STATUS, &result);

			ASSERT(result == GL_TRUE);
			if (result != GL_TRUE)
			{
				int logLength;
				glGetProgramiv(id_, GL_INFO_LOG_LENGTH, &logLength);
				std::vector<char> errorMessage(logLength);
				glGetProgramInfoLog(id_, logLength, nullptr, errorMessage.data());

				LOG_ERROR(errorMessage.data());
				return false;
			}
			return true;
		}
	}
}
