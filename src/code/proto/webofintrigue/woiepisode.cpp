#include "code/proto/webofintrigue/webofintriguemanager.h"

namespace proto
{
	// FUNCTION: ENGINE 0x10563080
	content::ClassInfo* WOIEpisode::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "proto::WOIEpisode";
		sInfo.code = "p";
		return &sInfo;
	}
}

// Kept copies (template instances and wrappers of this unit):
