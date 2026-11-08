// proto::GroundSpikeBehaviour, GroundSpikeMasterBehaviour and GroundSpikeShardBehaviour (RTTI and reflection names; base
// engine::Behaviour, the master derives from the spike): the ground spike attack, a master that spawns shards that emerge
// from the ground. Reflected: the height of a shard and its emerge offsets. Unit 0x10069010 - 0x1006F8E0 (no assert path; the
// file name is a guess). The reflected names are original, the rest is guessed; only the reflection is reconstructed.
#ifndef PROTO_GROUNDSPIKEBEHAVIOURS_H
#define PROTO_GROUNDSPIKEBEHAVIOURS_H

#include "code/content/metatype.h"
#include "code/core/name.h"
#include "code/engine/gameobject/behaviour.h"
#include "code/engine/message.h"
#include "code/math/vector.h"

namespace proto
{
	class GroundSpikeBehaviour : public engine::Behaviour
	{
	public:
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();

		// vftable slot 5 (0x10069F50; the master shares it)
		virtual void OnPostedMessage(engine::Message* message);
		// 0x10069F20 (name guess): answers the query of type 3, id 9 with a vector of the spike
		void GetQueriedVector(engine::Message* message);

		unsigned char unknownC[0x84];
	};

	class GroundSpikeMasterBehaviour : public GroundSpikeBehaviour
	{
	public:
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();

	};

	class GroundSpikeShardBehaviour : public engine::Behaviour
	{
	public:
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();

		// vftable slot 5 (0x10069FE0)
		virtual void OnPostedMessage(engine::Message* message);
		// 0x10069FB0 (name guess): the same query for a shard
		void GetQueriedVector(engine::Message* message);

		unsigned char unknownC[0x84];
		float height;  // +0x90
		float minEmergeOffset;  // +0x94
		float maxEmergeOffset;  // +0x98
	};

}

#endif
