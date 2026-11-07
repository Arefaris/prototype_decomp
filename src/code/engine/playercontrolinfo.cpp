// engine::PlayerControlInfo: which player controls an object (declared in driving/vehicleintentionbehaviour.h). Unit
// 0x108622E0 - 0x10862350 (no assert path; the file name is a guess).
#include "code/engine/controller/inputsystem.h"
#include "code/engine/driving/vehicleintentionbehaviour.h"

namespace engine
{
	// FUNCTION: ENGINE 0x108622E0
	void PlayerControlInfo::Reset()
	{
		slot = -1;
		unknown4 = 0;
	}

	// FUNCTION: ENGINE 0x108622F0
	void* PlayerControlInfo::Get() const
	{
		int index = slot;
		if (index != -1)
		{
			return controller::InputSystem::Get()->slots[index].info;
		}
		return 0;
	}

	// FUNCTION: ENGINE 0x10862310
	// NONMATCHING: the engine reuses eax for the out pointer where ours takes edx (95.3 %)
#ifdef NONMATCHING
	void PlayerControlInfo::GetPlayerId(unsigned int* id) const
	{
		int index = slot;
		if (index != -1)
		{
			*id = controller::InputSystem::Get()->slots[index].id;
			return;
		}
		*id = 0xffffffff;
	}
#endif

	// FUNCTION: ENGINE 0x10862340
	PlayerControlInfo::PlayerControlInfo()
	{
		Reset();
	}
}
