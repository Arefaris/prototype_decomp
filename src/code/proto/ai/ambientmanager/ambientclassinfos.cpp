#include "code/proto/reflectedstubs.h"

// The ClassInfo of the ambient population's reflected classes that are declared in proto/reflectedstubs.h until
// their layouts are recovered. Unit 0x10409900, 0x104306B0 (no assert path; the file name is a guess).
namespace proto
{
	// FUNCTION: ENGINE 0x10409900
	content::ClassInfo* AmbientExclusionVolume::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "proto::AmbientExclusionVolume";
		sInfo.code = "p";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x104306B0
	content::ClassInfo* IntersectionData::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "proto::IntersectionData";
		sInfo.code = "p";
		return &sInfo;
	}
}
