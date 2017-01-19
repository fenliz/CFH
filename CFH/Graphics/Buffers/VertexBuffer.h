#pragma once
#include "Buffer.h"
#include "Graphics\VertexAttribute.h"

#include <list>

namespace CFH
{
	namespace Graphics
	{
		class CFH_API VertexBuffer : Buffer
		{
		public:
			class Data
			{
			public:
				Data() : Ptr(nullptr), Size(0) {}
				Data(void* data, int size) : Ptr(data), Size(size) {}

				void* Ptr;
				int Size;
				std::list<VertexAttribute> Attributes;
			};

		public:
			VertexBuffer();
			VertexBuffer(Usage usage);
			~VertexBuffer();

			VertexBuffer(const VertexBuffer&) = delete;
			VertexBuffer& operator=(const VertexBuffer&) = delete;

			void Bind() const;

			void SetData(const VertexBuffer::Data& data);

			void SetTarget();
			Target GetTarget() const;

			void SetAttributes(const std::list<VertexAttribute>& attributes);
			const std::list<VertexAttribute>& GetAttributes() const;

			using Buffer::SetData;

		private:
			std::list<VertexAttribute> attributes_;

			using Buffer::SetTarget;
		};
	}
}

