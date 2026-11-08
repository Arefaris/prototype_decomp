// proto::FrontEndHud and proto::MarkerList: the head-up display of the front end and its list of markers. Only the
// members the reconstructed code calls are declared.
#ifndef PROTO_FRONTEND_FRONTENDHUD_H
#define PROTO_FRONTEND_FRONTENDHUD_H

#include "code/engine/gameobject/gameobjectsystem.h"

namespace proto
{
	class MarkerList
	{
	public:
		// 0x104B94D0 (name unknown): takes the marker of the object (the handle in its saved form) out, giving it an icon type
		void Unknown104B94D0(engine::LuaGOH handle, int iconType);
	};

	class FrontEndHud
	{
	public:
		// 0x104B0CC0
		MarkerList* GetMarkers();
	};

	// 0x104B0A00
	FrontEndHud* GetFrontEndHud();
}

#endif
