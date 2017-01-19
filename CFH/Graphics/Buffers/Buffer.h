#pragma once
#include "CFH.h"

#include <GL\glew.h>

namespace CFH
{
	namespace Graphics
	{
		class CFH_API Buffer
		{
		public:
			enum class Usage
			{
				StaticDraw	= GL_STATIC_DRAW,
				StaticRead	= GL_STATIC_READ,
				StaticCopy	= GL_STATIC_COPY,
				DynamicDraw = GL_DYNAMIC_DRAW,
				DynamicRead = GL_DYNAMIC_READ,
				DynamicCopy = GL_DYNAMIC_COPY,
				StreamDraw	= GL_STREAM_DRAW,
				StreamRead	= GL_STREAM_READ,
				StreamCopy	= GL_STREAM_COPY
			};

			enum class Target
			{
				Array				= GL_ARRAY_BUFFER,
				AtomicCounter		= GL_ATOMIC_COUNTER_BUFFER,
				CopyRead			= GL_COPY_READ_BUFFER,
				CopyWrite			= GL_COPY_WRITE_BUFFER,
				DispatchIndirect	= GL_DISPATCH_INDIRECT_BUFFER,
				DrawIndirect		= GL_DRAW_INDIRECT_BUFFER,
				ElementArray		= GL_ELEMENT_ARRAY_BUFFER,
				PixelPack			= GL_PIXEL_PACK_BUFFER,
				PixelUnpack			= GL_PIXEL_UNPACK_BUFFER,
				Query				= GL_QUERY_BUFFER,
				ShaderStorage		= GL_SHADER_STORAGE_BUFFER,
				Texture				= GL_TEXTURE_BUFFER,
				TransformFeedback	= GL_TRANSFORM_FEEDBACK_BUFFER,
				Uniform				= GL_UNIFORM_BUFFER
			};

			struct Data
			{
			public:
				Data();
				Data(void* data, int size);

				void* Ptr;
				int Size;
			};


		public:
			Buffer();
			Buffer(Target target, Usage usage = Usage::StaticDraw);
			virtual ~Buffer();

			Buffer(const Buffer&) = delete;
			Buffer& operator=(const Buffer&) = delete;

			void Create();
			void Destroy();

			virtual void Bind() const;
			void Bind(Target target);
			void Unbind() const;

			void Resize(int size);

			void SetData(const Buffer::Data& data);
			void SetData(int size, const void* data);
			void SetData(int size, const void* data, Usage usage);
			void SetSubData(int offset, int size, const void* data);

			void SetUsage(Usage usage);
			Usage GetUsage() const;

			virtual void SetTarget(Target target);
			Target GetTarget() const;

			int GetId() const;
			bool IsCreated() const;

		protected:
			unsigned int id_;
			bool created_;
			Target target_;
			Usage usage_;
		};
	}
}

