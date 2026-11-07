// proto::AmbientStreamPackage (RTTI and reflection names; a plain struct): one kind of ambient object (a package of
// pedestrians or vehicles that is streamed in) with how much of the population it makes up, how many of it may exist
// and in which order the packages are filled. The ambient manager keeps its packages in arrays of these (0x48 bytes
// each: the reflected members, and the counters the manager keeps with them). Unit 0x10421200 - 0x10425E20 (no assert
// path; the file name is a guess). The reflected names are original, the rest is guessed.
#ifndef PROTO_AI_AMBIENTMANAGER_AMBIENTSTREAMPACKAGE_H
#define PROTO_AI_AMBIENTMANAGER_AMBIENTSTREAMPACKAGE_H

#include "code/container/arraydynamicallocatornew.h"
#include "code/content/metatype.h"
#include "code/core/name.h"

namespace proto
{
	struct AmbientStreamPackage
	{
	public:
		AmbientStreamPackage()
		{
		}

		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();

		core::Name<core::CaseSensitiveKey> name;  // +0
		float percent;  // +8
		float unknownC;
		int maxNumberSpawned;  // +0x10
		int priority;  // +0x14
		unsigned int packageType;  // +0x18
		bool recycle;  // +0x1C
		bool unknown1D;
		int unknown20;
		int unknown24;
		int unknown28;
		int unknown2C;
		int unknown30;
		bool unknown34;
		bool unknown35;
		bool unknown36;
		bool unknown37;
		float unknown38;
		float unknown3C;
		int unknown40;
		int unknown44;
	};

	typedef container::ArrayDynamic<AmbientStreamPackage, container::AllocatorNew> AmbientStreamPackageArray;
}

namespace container
{
	template<> struct ArrayEraseInline<proto::AmbientStreamPackage>
	{
		enum
		{
			value = 0
		};
	};
}

#endif
