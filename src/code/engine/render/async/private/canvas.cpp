// The game thread's calls on the canvas (see the header): each queues a call of one of the canvas' members on the render
// thread.
#include "code/engine/render/async/canvas.h"
#include "code/engine/render/async/renderevent.h"

namespace engine
{
	namespace render
	{
		class RenderObject;

		// 0x10817B00 (renderglobals.cpp)
		RenderObject* GetRenderObject();

		// The canvas is the render object (every call below casts what GetRenderObject() returns)
		// FUNCTION: ENGINE 0x10829000
		void QueueCanvas108BCA10(float a, bool b, float c, bool d, float e, bool f, bool g)
		{
			QueueObjRenderEvent((Canvas*)GetRenderObject(), &Canvas::Unknown108BCA10, a, b, c, d, e, f, g);
		}

		// FUNCTION: ENGINE 0x10829040
		void QueueCanvas108BCA80(bool a, float b, bool c, float d, bool e)
		{
			QueueObjRenderEvent((Canvas*)GetRenderObject(), &Canvas::Unknown108BCA80, a, b, c, d, e);
		}

		// FUNCTION: ENGINE 0x10829080
		void QueueCanvas108BCAC0(float a, bool b, float c, bool d, float e)
		{
			QueueObjRenderEvent((Canvas*)GetRenderObject(), &Canvas::Unknown108BCAC0, a, b, c, d, e);
		}

		// FUNCTION: ENGINE 0x108290C0
		void QueueCanvas108BCB00(bool a, float b, bool c, float d)
		{
			QueueObjRenderEvent((Canvas*)GetRenderObject(), &Canvas::Unknown108BCB00, a, b, c, d);
		}

		// FUNCTION: ENGINE 0x108290F0
		void QueueSetCurrentContext(const core::Name<core::CaseSensitiveKey>& name)
		{
			core::Name<core::CaseSensitiveKey> copy(name);
			QueueObjRenderEvent((Canvas*)GetRenderObject(), &Canvas::SetCurrentContext, copy);
		}

		// FUNCTION: ENGINE 0x10829180
		void QueueCanvas108BCE40(const core::Name<core::CaseSensitiveKey>& name, bool value)
		{
			QueueObjRenderEvent((Canvas*)GetRenderObject(), &Canvas::Unknown108BCE40, core::Name<core::CaseSensitiveKey>(name), value);
		}

		// FUNCTION: ENGINE 0x108291B0
		void QueueCanvas108BCA00(bool value)
		{
			QueueObjRenderEvent((Canvas*)GetRenderObject(), &Canvas::Unknown108BCA00, value);
		}

		// The event classes the calls queue
		// FUNCTION: ENGINE 0x108271D0
		// FUNCTION: ENGINE 0x10827230
		template class ObjRenderEvent7<Canvas, float, bool, float, bool, float, bool, bool>;
		// FUNCTION: ENGINE 0x10827270
		// FUNCTION: ENGINE 0x108272C0
		template class ObjRenderEvent5<Canvas, bool, float, bool, float, bool>;
		// FUNCTION: ENGINE 0x10827300
		// FUNCTION: ENGINE 0x10827350
		template class ObjRenderEvent5<Canvas, float, bool, float, bool, float>;
		// FUNCTION: ENGINE 0x10827390
		// FUNCTION: ENGINE 0x108273D0
		template class ObjRenderEvent4<Canvas, bool, float, bool, float>;
		// FUNCTION: ENGINE 0x10827400
		// FUNCTION: ENGINE 0x10827430
		// FUNCTION: ENGINE 0x10828790
		template class ObjRenderEvent1<Canvas, core::Name<core::CaseSensitiveKey> >;
		// FUNCTION: ENGINE 0x10827480
		// FUNCTION: ENGINE 0x108274C0
		// FUNCTION: ENGINE 0x108287E0
		template class ObjRenderEvent2<Canvas, core::Name<core::CaseSensitiveKey>, bool>;
		// FUNCTION: ENGINE 0x108274D0
		// FUNCTION: ENGINE 0x108274F0
		template class ObjRenderEvent1<Canvas, bool>;
	}
}
