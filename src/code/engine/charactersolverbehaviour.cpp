// engine::CharacterSolverBehaviour (RTTI and reflection names; base engine::Behaviour): unit 0x10907E90 - 0x1090C110
// (no assert path; the file name is a guess). Only the class information is reconstructed so far; the class itself is
// declared in reflectedclasses.h.
#include "code/engine/reflectedclasses.h"

namespace engine
{
	// FUNCTION: ENGINE 0x10907ED0
	content::ClassInfo* CharacterSolverBehaviour::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "CharacterSolverBehaviour";
		sInfo.code = "p";
		return &sInfo;
	}
}
