#pragma once
#include "Shader.h"
#include "Uniform.h"
#include "Core\Exceptions.h"

#include <string>
#include <unordered_map>

namespace CFH
{
	namespace Graphics
	{
		class CFH_API Program
		{
		public:
			Program();
			Program(const std::string& vertexShaderPath, const std::string& fragmentShaderPath);
			Program(const Shader& vertexShader, const Shader& fragmentShader);
			~Program();

			Program(const Program&) = delete;
			Program& operator=(const Program&) = delete;

			void Create();
			void Destroy();

			void Load(const Shader& vertexShader, const Shader& fragmentShader);

			void Bind() const;
			void Unbind() const;

			bool IsLinked() const;
			int GetId() const;

			Uniform& operator[](const std::string& uniformName) throw(std::out_of_range);
			const Uniform& operator[](const std::string& uniformName) const throw(std::out_of_range);
			int GetUniformLocation(const std::string& uniformName) const throw(std::out_of_range);
			const Uniform& GetUniform(const std::string& uniformName) const throw(std::out_of_range);

		private:
			void MapUniforms(const Shader& shader);
			bool Link(const Shader& vertexShader, const Shader& fragmentShader);

			int id_;
			bool created_;
			bool linked_;
			std::unordered_map<std::string, Uniform> uniforms_;
		};
	}
}

