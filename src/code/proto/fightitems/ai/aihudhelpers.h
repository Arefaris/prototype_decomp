// The parts of the front end hud the actions of the ai fight items talk to (class and member names are guesses; only what the actions
// use is declared).
#ifndef PROTO_FIGHTITEMS_AI_AIHUDHELPERS_H
#define PROTO_FIGHTITEMS_AI_AIHUDHELPERS_H

#include "code/engine/gameobject/gameobjectsystem.h"
#include "code/proto/frontend/fehuddisguiseactions.h"

namespace proto
{
	// The markers the hud draws over objects
	class MarkerList
	{
	public:
		// 0x104B57D0 / 0x104B9400 / 0x104B57F0 / 0x104B8280: give an object's marker its look (name guesses)
		void Unknown104B57D0(engine::SerializedHandle handle, int kind);
		void Unknown104B9400(engine::SerializedHandle handle, int type, int displayType, int unknown1, int unknown2);
		void Unknown104B57F0(engine::SerializedHandle handle, int color);
		void Unknown104B8280(engine::SerializedHandle handle, int animation);
		// 0x104B94D0: takes the marker of an object away (name guess)
		void Unknown104B94D0(engine::SerializedHandle handle, int type);
	};

	class PopupController
	{
	public:
		unsigned char unknown0[0x20];
		FEHudDisguiseActions* disguiseActions;  // +0x20
	};

	class FrontEndHud
	{
	public:
		// 0x104B0CC0 / 0x104B0CE0
		MarkerList* GetMarkers();
		PopupController* GetPopups();
	};

	// 0x104B0A00
	FrontEndHud* GetFrontEndHud();
}

#endif
