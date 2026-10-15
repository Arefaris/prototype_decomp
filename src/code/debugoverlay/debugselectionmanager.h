// debugoverlay::DebugSelectionManager (RTTI name, vftable 0x10E7DC4C, two slots): the object the debug overlay picks
// game objects through. It derives from pure3d::DebugObjectManager and adds nothing to the layout, so its constructor
// only installs the derived vftable.
#ifndef DEBUGOVERLAY_DEBUGSELECTIONMANAGER_H
#define DEBUGOVERLAY_DEBUGSELECTIONMANAGER_H

#include "code/pure3d/debugobjectmanager.h"

namespace debugoverlay
{
	class DebugSelectionManager : public pure3d::DebugObjectManager
	{
	public:
		DebugSelectionManager();
	};
}

#endif
