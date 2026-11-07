#include "code/proto/behaviours/lockontargetingbehaviour.h"

namespace proto
{
	// FUNCTION: ENGINE 0x102A8350
	content::ClassInfo* AutoTargetingBehaviour::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "proto::AutoTargetingBehaviour";
		sInfo.code = "pn";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x102AA300
	content::ClassInfo* LockOnTargetingBehaviour::TargetLockCone::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "proto::LockOnTargetingBehaviour::TargetLockCone";
		sInfo.code = "p";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x102AA340
	content::ClassInfo* LockOnTargetingBehaviour::SoundParams::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "proto::LockOnTargetingBehaviour::SoundParams";
		sInfo.code = "p";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x102AA380
	content::ClassInfo* LockOnTargetingBehaviour::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "proto::LockOnTargetingBehaviour";
		sInfo.code = "pn";
		return &sInfo;
	}
}
