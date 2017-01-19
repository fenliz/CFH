#include "VertexAttribute.h"

namespace CFH
{
	namespace Graphics
	{
#define GL_ENUM(x) \
	static_cast<GLenum>(x)

		VertexAttribute::VertexAttribute() :
			VertexAttribute(0, 0, Type::Float, 0, nullptr)
		{
			normalized_ = false;
		}
		VertexAttribute::VertexAttribute(unsigned int index, int size, Type type, int stride, void* offset) :
			index_(index),
			size_(size),
			type_(type),
			normalized_(false),
			stride_(stride),
			offset_(offset)
		{
		}
		VertexAttribute::~VertexAttribute()
		{
		}

		void VertexAttribute::Set()
		{
			glVertexAttribPointer(index_, size_, GL_ENUM(type_), normalized_, stride_, offset_);
		}
	}
}

