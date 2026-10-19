// The effect manager's global and its getter (see effectmanager.h). The manager class itself is the unit that starts
// at 0x10819430; the getter is written apart from the code that calls it, as the engine's callers do not know it.
#include "code/engine/render/effectmanager.h"

namespace engine
{
	namespace render
	{
		// The global manager (0x1130CCE0)
		extern EffectManager* gEffectManager;

		// FUNCTION: ENGINE 0x108193A0
		EffectManager* GetEffectManager()
		{
			return gEffectManager;
		}
	}
}
