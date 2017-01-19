#include "Buffer.h"

namespace CFH
{
	namespace Graphics
	{
#define GL_ENUM(x) \
	static_cast<GLenum>(x)

		Buffer::Data::Data() :
			Ptr(nullptr),
			Size(0)
		{
		}
		Buffer::Data::Data(GLvoid* data, GLsizeiptr size) :
			Ptr(data),
			Size(size)
		{
		}

		Buffer::Buffer() :
			Buffer(Target::Array, Usage::StaticDraw)
		{
		}
		Buffer::Buffer(Target target, Usage usage)
		{
			id_ = 0;
			created_ = false;

			target_ = target;
			usage_ = usage;
		}
		Buffer::~Buffer()
		{
			Destroy();
		}

		void Buffer::Create()
		{
			ASSERT(!created_);
			Destroy();

			glGenBuffers(1, &id_);
			created_ = true;
		}
		void Buffer::Destroy()
		{
			ASSERT(created_);
			if (!created_)
				return;

			glDeleteBuffers(1, &id_);
			created_ = false;
		}

		void Buffer::Bind() const
		{
			glBindBuffer(GL_ENUM(target_), id_);
		}
		void Buffer::Bind(Target target)
		{
			target_ = target;
			Bind();
		}
		void Buffer::Unbind() const
		{
			glBindBuffer(GL_ENUM(target_), 0);
		}

		void Buffer::Resize(int size)
		{
			glBufferData(GL_ENUM(target_), size, nullptr, GL_ENUM(usage_));
		}

		void Buffer::SetData(const Buffer::Data& data)
		{
			SetData(data.Size, data.Ptr);
		}
		void Buffer::SetData(int size, const void* data)
		{
			glBufferData(GL_ENUM(target_), size, data, GL_ENUM(usage_));
		}
		void Buffer::SetData(int size, const void* data, Usage usage)
		{
			usage_ = usage;
			SetData(size, data);
		}
		void Buffer::SetSubData(int offset, int size, const void* data)
		{
			glBufferSubData(GL_ENUM(target_), offset, size, data);
		}

		void Buffer::SetUsage(Usage usage)
		{
			usage_ = usage;
		}
		Buffer::Usage Buffer::GetUsage() const
		{
			return usage_;
		}

		void Buffer::SetTarget(Target target)
		{
			target_ = target;
		}
		Buffer::Target Buffer::GetTarget() const
		{
			return target_;
		}

		int Buffer::GetId() const
		{
			return id_;
		}
		bool Buffer::IsCreated() const
		{
			return created_;
		}
	}
}