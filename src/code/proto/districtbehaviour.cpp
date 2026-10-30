#include "code/proto/districtbehaviour.h"

namespace proto
{
	// FUNCTION: ENGINE 0x10571BC0
	content::ClassInfo* DistrictBehaviour::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "proto::DistrictBehaviour";
		sInfo.code = "pn";
		return &sInfo;
	}
}

// Kept copies (template instances and wrappers of this unit):
