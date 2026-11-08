#include "code/engine/render/viewhandle.h"
#include "code/engine/render/letterboxrenderpass.h"

namespace engine
{
	namespace render
	{
		class RenderObject;

		// 0x10817B00 (renderglobals.cpp)
		RenderObject* GetRenderObject();
	}

	// 0x1074ED00 (another unit; name guess): sets the range the shadows are drawn to (0x111B8E44)
	void SetShadowRange(float range);

	// The renderer's table of views (0x1130D344; names guessed): the serial numbers of the views by table index
	struct ViewTable
	{
		unsigned char unknown0[0x1C];
		unsigned int* serials;  // +0x1C
		unsigned char unknown20[8];
		unsigned int count;  // +0x28
	};
	extern ViewTable* gViewTable;

	// FUNCTION: ENGINE 0x10826820
	float GetAspect()
	{
		return ((render::Letterbox*)render::GetRenderObject())->GetAspectRatio();
	}

	// FUNCTION: ENGINE 0x10826850
	void SetGlobalShadowRangeHack(float range)
	{
		SetShadowRange(range);
	}

	// FUNCTION: ENGINE 0x10826E40
	// NONMATCHING: the engine masks the whole word and answers through eax (best 12.5 %)
#ifdef NONMATCHING
	bool ViewHandle::IsValid() const
	{
		unsigned int index = value & 0xFFFF;
		if (index < gViewTable->count && *((unsigned short*)&value + 1) == gViewTable->serials[index])
		{
			return true;
		}
		return false;
	}
#endif
}
