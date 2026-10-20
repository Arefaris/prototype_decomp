// fight::ListObject (RTTI name, vftable 0x10E6EC24 with three pure slots): a source of a list of names the editor
// shows in a drop-down. The slot names are guesses.
#ifndef ENGINE_FIGHT_LISTOBJECT_H
#define ENGINE_FIGHT_LISTOBJECT_H

#include "code/core/name.h"

namespace fight
{
	class ListObject
	{
	public:
		// 0x1082FDA0
		ListObject()
		{
		}

		// The number of names
		virtual int GetCount() const = 0;
		// The name of that number; an empty one when there is none
		virtual const core::Name<core::CaseSensitiveKey>* GetName(int index) = 0;
		virtual void Slot2() = 0;
	};
}

#endif
