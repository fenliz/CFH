#pragma once
#include "CFH.h"

#include <GL\glew.h>

namespace CFH
{
	namespace Graphics
	{
		class CFH_API VertexAttribute
		{
		public:
			enum class Type
			{
				Byte						= GL_BYTE,
				UnsignedByte				= GL_UNSIGNED_BYTE,
				Short						= GL_SHORT,
				UnsignedShort				= GL_UNSIGNED_SHORT,
				Int							= GL_INT,
				HalfFloat					= GL_HALF_FLOAT,
				Float						= GL_FLOAT,
				Double						= GL_DOUBLE,
				Fixed						= GL_FIXED,
				Int_2_10_10_10_Rev			= GL_INT_2_10_10_10_REV,
				UnsignedInt_2_10_10_10_Rev	= GL_UNSIGNED_INT_2_10_10_10_REV,
				UnsignedInt_10F_11F_11F_REV = GL_UNSIGNED_INT_10F_11F_11F_REV
			};

		public:
			VertexAttribute();
			VertexAttribute(unsigned int index, int size, Type type, int stride, void* offset);
			~VertexAttribute();

			void Set();

		private:
			unsigned int index_;
			int size_;
			Type type_;
			bool normalized_;
			int stride_;
			void* offset_;
		};
	}
}

