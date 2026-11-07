// proto::NPCInstancePool (RTTI and reflection names; base content::MetaLoadObject): the pool of NPC instances an NPC
// type draws from. It keeps three lists of instance pointers (the names of the lists are guessed) in the heap 0xA1 and
// the number of instances it makes up front ("poolSize"). Unit 0x1047A150 - 0x1047A8D0 (no assert path; the file name
// is a guess); the reflection, the construction and the destruction are reconstructed, the creation of the instances
// is left to the engine.
#ifndef PROTO_NPCINSTANCEPOOL_H
#define PROTO_NPCINSTANCEPOOL_H

#include "code/container/arraydynamicstatic.h"
#include "code/content/loadinventory.h"
#include "code/content/metatype.h"

namespace proto
{
	class NPCInstance;

	class NPCInstancePool : public content::MetaLoadObject
	{
	public:
		typedef container::ArrayDynamic<NPCInstance*, container::AllocatorCoreStatic<0xa1, 16> > InstanceArray;

		// 0x1047A7F0
		NPCInstancePool();
		// 0x1047A830 (the deleting destructor is 0x1047A8A0)
		virtual ~NPCInstancePool();
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();

		// vftable slot 3 (0x1047A600) and 4 (0x1047A6A0), left to the engine
		virtual void Slot3(int unused);
		virtual bool IsReady();

		int poolSize;  // +8
		InstanceArray unknownC;
		InstanceArray unknown1C;
		InstanceArray unknown2C;
	};
}

#endif
