#include "code/proto/reflectedstubs.h"

// proto::TokenBehaviour (RTTI and reflection names; base engine::Behaviour): the class itself is declared in
// proto/reflectedstubs.h until its layout is recovered. Unit 0x10403760 - 0x10405380 (no assert path; the file name
// is a guess).
namespace proto
{
	// FUNCTION: ENGINE 0x10403760
	content::ClassInfo* TokenBehaviour::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "proto::TokenBehaviour";
		sInfo.code = "pn";
		return &sInfo;
	}
}
