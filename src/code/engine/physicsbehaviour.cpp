// engine::PhysicsBehaviour (RTTI name; base engine::Behaviour and ravenphysics::BroadPhaseObjectNotifier): unit
// 0x10921620 - 0x10924AFE. Only the reflection's class description is reconstructed so far; the class is still
// described by reflectedclasses.h.
#include "code/engine/reflectedclasses.h"

namespace engine
{
	// FUNCTION: ENGINE 0x10921A10
	content::ClassInfo* PhysicsBehaviour::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "PhysicsBehaviour";
		sInfo.code = "p";
		return &sInfo;
	}
}
