// proto::AutoTargetingBehaviour and proto::LockOnTargetingBehaviour (RTTI and reflection names; bases
// proto::TargetingBehaviour and proto::AutoTargetingBehaviour): the automatic target of an object chosen by the priorities
// of a proto::AutoTargetPriorityList, and the lock-on targeting of the player with its lock cones and sounds. Unit
// 0x102A8350 - 0x102B1280 (no assert path; the file names are guesses). The layouts are not recovered: only the class
// info is reconstructed.
#ifndef PROTO_BEHAVIOURS_LOCKONTARGETINGBEHAVIOUR_H
#define PROTO_BEHAVIOURS_LOCKONTARGETINGBEHAVIOUR_H

#include "code/content/metatype.h"
#include "code/core/name.h"
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
			// 0x102AB810
			SoundParams();
			static content::ClassInfo* GetClassInfo();
			static content::MemberList* GetMembers();

			// 0x102AB870 / 0x102AB8B0: plays the sound of a name (an audio patch), stops it
			void PlayName(const core::Name<core::CaseSensitiveKey>& name);
			void StopName(const core::Name<core::CaseSensitiveKey>& name);
			// 0x102AB8F0: switches the sounds on or off (off stops the sustained and the loop)
			void SetEnabled(bool on);
			// 0x102AB940 / 0x102AB970 / 0x102AB9A0 / 0x102AB9D0 / 0x102ABA00: the sound of each lock-on event
			void OnTargetAcquired();
			void OnTargetDestroyed();
			void OnTargetModeEntered();
			void OnTargetModeExited();
			void OnTargetAbandoned();

			bool enabled;  // +0x0
			__declspec(align(8)) core::Name<core::CaseSensitiveKey> targetAquired;  // +0x8
			core::Name<core::CaseSensitiveKey> targetDestroyed;  // +0x10
			core::Name<core::CaseSensitiveKey> targetSustained;  // +0x18
			core::Name<core::CaseSensitiveKey> targetModeEntered;  // +0x20
			core::Name<core::CaseSensitiveKey> targetModeExited;  // +0x28
			core::Name<core::CaseSensitiveKey> targetModeLoop;  // +0x30
			core::Name<core::CaseSensitiveKey> targetAbandoned;  // +0x38
		};

		static content::ClassInfo* GetClassInfo();
	};
}

#endif
