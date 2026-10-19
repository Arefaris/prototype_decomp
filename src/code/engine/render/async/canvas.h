// engine::render::Canvas (RTTI name, from the ObjRenderEventN template arguments): the object the render thread's
// canvas calls run on; it is the one the renderer keeps behind GetRenderObject() (renderglobals.cpp, 0x40 bytes, built
// by 0x108BD150, its letterbox flag is the byte at +0x16). The game thread's calls queue a call of one of its
// members; the members are in another unit (0x108BCA00 - 0x108BCE40). All names are guesses.
#ifndef ENGINE_RENDER_ASYNC_CANVAS_H
#define ENGINE_RENDER_ASYNC_CANVAS_H

#include "code/core/name.h"

namespace engine
{
	namespace render
	{
		class Canvas
		{
		public:
			// The members the game thread queues
			void Unknown108BCA00(bool value);
			void Unknown108BCA10(float a, bool b, float c, bool d, float e, bool f, bool g);
			void Unknown108BCA80(bool a, float b, bool c, float d, bool e);
			void Unknown108BCAC0(float a, bool b, float c, bool d, float e);
			void Unknown108BCB00(bool a, float b, bool c, float d);
			// 0x108BCE10: makes the render context of the name the current one
			void SetCurrentContext(core::Name<core::CaseSensitiveKey> name);
			// 0x108BCE40: sets a bool parameter of the canvas' shader
			void Unknown108BCE40(core::Name<core::CaseSensitiveKey> name, bool value);
		};

		// The game thread's calls (0x10829000 - 0x108291B0): each queues the member of the same address
		void QueueCanvas108BCA10(float a, bool b, float c, bool d, float e, bool f, bool g);
		void QueueCanvas108BCA80(bool a, float b, bool c, float d, bool e);
		void QueueCanvas108BCAC0(float a, bool b, float c, bool d, float e);
		void QueueCanvas108BCB00(bool a, float b, bool c, float d);
		void QueueSetCurrentContext(const core::Name<core::CaseSensitiveKey>& name);
		void QueueCanvas108BCE40(const core::Name<core::CaseSensitiveKey>& name, bool value);
		void QueueCanvas108BCA00(bool value);
	}
}

#endif
