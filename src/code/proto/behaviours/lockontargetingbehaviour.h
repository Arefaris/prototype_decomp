// proto::AutoTargetingBehaviour and proto::LockOnTargetingBehaviour (RTTI and reflection names; bases
// proto::TargetingBehaviour and proto::AutoTargetingBehaviour): the automatic target of an object chosen by the priorities
// of a proto::AutoTargetPriorityList, and the lock-on targeting of the player with its lock cones and sounds. Unit
// 0x102A8350 - 0x102B1280 (no assert path; the file names are guesses). The layouts are not recovered: only the class
// info is reconstructed.
#ifndef PROTO_BEHAVIOURS_LOCKONTARGETINGBEHAVIOUR_H
#define PROTO_BEHAVIOURS_LOCKONTARGETINGBEHAVIOUR_H

#include "code/content/metatype.h"
#include "code/proto/behaviours/targetingbehaviour.h"

namespace proto
{
	class AutoTargetingBehaviour : public TargetingBehaviour
	{
	public:
		static content::ClassInfo* GetClassInfo();
	};

	class LockOnTargetingBehaviour : public AutoTargetingBehaviour
	{
	public:
		// The cone the lock-on takes its targets from (RTTI proto::LockOnTargetingBehaviour::TargetLockCone)
		struct TargetLockCone
		{
			static content::ClassInfo* GetClassInfo();
		};

		// The sounds of the lock-on (RTTI proto::LockOnTargetingBehaviour::SoundParams)
		struct SoundParams
		{
			static content::ClassInfo* GetClassInfo();
		};

		static content::ClassInfo* GetClassInfo();
	};
}

#endif
