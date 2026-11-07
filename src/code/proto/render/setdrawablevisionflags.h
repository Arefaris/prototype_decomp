// proto::SetDrawableVisionFlags (RTTI name, base engine::render::DrawableModifier, one virtual): the modifier the render
// thread applies to a drawable to change how the senses see it (two floats and a word; 0x10 bytes). Its unit
// (0x102E88D0, constructor 0x102E8E80 for the virtual) is not reconstructed; the modifier is made in the render event
// memory.
#ifndef PROTO_RENDER_SETDRAWABLEVISIONFLAGS_H
#define PROTO_RENDER_SETDRAWABLEVISIONFLAGS_H

#include "code/engine/render/async/private/drawableimpl.h"

namespace engine
{
	namespace render
	{
		void* AllocRenderEvent(unsigned int size);
		void FreeRenderEvent(void* event);
	}
}

namespace proto
{
	class SetDrawableVisionFlags : public engine::render::DrawableModifier
	{
	public:
		// 0x102E88D0
		SetDrawableVisionFlags(float newNear, float newFar, int newFlags);
		// 0x102E8E80
		virtual void Apply(engine::render::DrawableImpl* drawable);

		static void* operator new(unsigned int size)
		{
			return engine::render::AllocRenderEvent(size);
		}
		static void operator delete(void* memory)
		{
			engine::render::FreeRenderEvent(memory);
		}

		float nearValue;  // +4
		float farValue;  // +8
		int flags;  // +0xC
	};
}

#endif
