#include "VertexBuffer.h"

namespace CFH
{
	namespace Graphics
	{
#define GL_ENUM(x) \
	static_cast<GLenum>(x)

		VertexBuffer::VertexBuffer() :
			Buffer(Target::Array)
		{
		}
		VertexBuffer::VertexBuffer(Usage usage) :
			Buffer(Target::Array, usage)
		{
		}
		VertexBuffer::~VertexBuffer()
		{
		}

		void VertexBuffer::Bind() const
		{
			glBindBuffer(GL_ENUM(Target::Array), id_);
		}

		void VertexBuffer::SetData(const VertexBuffer::Data& data)
		{
			Buffer::SetData(data.Size, data.Ptr);
			SetAttributes(data.Attributes);
		}

		void VertexBuffer::SetTarget()
		{
			target_ = Target::Array;
		}

		void VertexBuffer::SetAttributes(const std::list<VertexAttribute>& attributes)
		{
			attributes_ = attributes;
		}

		Buffer::Target VertexBuffer::GetTarget() const
		{
			return Target::Array;
		}
	}
}

