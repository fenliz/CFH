#pragma once
#include "CFH.h"

#include <GL\glew.h>
#include <string>

namespace CFH
{
	namespace Graphics
	{
		class CFH_API Shader
		{
		public:
			enum class Type
			{
				Vertex = GL_VERTEX_SHADER,
				Fragment = GL_FRAGMENT_SHADER,
				Geometry = GL_GEOMETRY_SHADER
			};

		public:
			Shader(Type type);
			Shader(const std::string& path, Type type);
			~Shader();

			Shader(const Shader&) = delete;
			Shader& operator=(const Shader&) = delete;

			void Create();
			void Destroy();

			void Load(const std::string& path);
			bool Compile();

			int GetId() const;
			Type GetType() const;
			std::string GetCode() const;
			bool IsCreated() const;
			bool IsCompiled() const;

		private:
			int id_;
			Type type_;
			bool created_;
			bool compiled_;
			std::string path_;
			std::string code_;
		};
	}
}

