#include "code/proto/reflectedstubs.h"

// proto::WalkingBehaviour (RTTI name; the ClassInfo names it without the namespace; base proto::MovementBehaviour): the class itself is declared
// in proto/reflectedstubs.h until its layout is recovered. Unit 0x104053A0 - 0x10406A70 (no assert path; the file
// name is a guess).
namespace proto
{
	// FUNCTION: ENGINE 0x104053A0
	content::ClassInfo* WalkingBehaviour::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "WalkingBehaviour";
		sInfo.code = "pn";
		return &sInfo;
	}
}
