// pure3d::DebugObjectManager (RTTI name, vftable 0x10E7DC3C, two slots): the base of the debug overlay's selection
// manager, and a header-only class whose constructor the unit that first needs it emits. Only the constructor is
// reconstructed; what the two slots do is unknown, so they stay empty here.
#ifndef PURE3D_DEBUGOBJECTMANAGER_H
#define PURE3D_DEBUGOBJECTMANAGER_H

namespace pure3d
{
	class DebugObjectManager
	{
	public:
		// 0x108BC8C0: the compiler emits it out of line in the unit that first needs the class, and inlines it into
		// the constructors of the classes below
		DebugObjectManager()
		{
		}

		virtual ~DebugObjectManager()
		{
		}

		// The second slot; nothing in the reconstructed units calls it
		virtual void Unknown4()
		{
		}
	};
}

#endif
