#include "code/proto/reflectedstubs.h"

namespace proto
{
	// FUNCTION: ENGINE 0x1007E7B0
	content::ClassInfo* TransformationBehaviour::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "proto::TransformationBehaviour";
		sInfo.code = "pn";
		return &sInfo;
	}
}
