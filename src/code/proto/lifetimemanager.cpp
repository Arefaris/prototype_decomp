// The lifetime manager (unit 0x10498200 - 0x1049A990).
#include "code/proto/lifetimemanager.h"

namespace proto
{
	// 0x1126BDF8
	LifetimeManager* gLifetimeManager;

	// FUNCTION: ENGINE 0x10498E70
	LifetimeManager::LifetimeManager()
	{
		gLifetimeManager = this;
	}

	// FUNCTION: ENGINE 0x10498EF0
	LifetimeManager::~LifetimeManager()
	{
		gLifetimeManager = 0;
	}
}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x10498630
// FUNCTION: ENGINE 0x10498E40
// FUNCTION: ENGINE 0x10499DD0
