// proto::TokenBehaviour (RTTI and reflection names; base engine::Behaviour) and proto::TokenWeights (a reflected load
// object): the combat tokens of an object. Two kinds of token are kept (two arrays of the objects that hold one, with a
// count each that may do so); messages of type 0x2E hand them out, take them back, read and set the limits and the
// weights that rate a target by its distance and by its class name. Reflected: tokenWeights, tooFar, distanceWeight,
// classnameWeight, consumeProbability. Unit 0x10403740 - 0x10405380 (no assert path; the file name is a guess). The
// reflected names are original, the rest is guessed.
#ifndef PROTO_BEHAVIOURS_TOKENBEHAVIOUR_H
#define PROTO_BEHAVIOURS_TOKENBEHAVIOUR_H

#include "code/container/arraydynamicallocatornew.h"
#include "code/content/loadinventory.h"
#include "code/content/metatype.h"
#include "code/core/name.h"
#include "code/math/vector.h"
#include "code/engine/gameobject/behaviour.h"

namespace proto
{
	// RTTI proto::TokenWeights: how much a class of target is worth to the token score (0x1C bytes)
	struct TokenWeights : public content::MetaLoadObject
	{
		// One class name and its weight (RTTI proto::TokenWeights::Weight; 0x10 bytes, copies leave the last word alone)
		struct Weight
		{
			Weight()
			{
			}
			Weight(const Weight& other) : classname(other.classname), weight(other.weight)
			{
			}
			Weight& operator=(const Weight& other)
			{
				classname = other.classname;
				weight = other.weight;
				return *this;
			}
			static content::ClassInfo* GetClassInfo();
			static content::MemberList* GetMembers();

			core::Name<core::CaseSensitiveKey> classname;  // +0
			float weight;  // +8
			int unknownC;
		};

		typedef container::ArrayDynamic<Weight, container::AllocatorNew> WeightArray;

		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();

		WeightArray weights;  // +8
		int unknown14;  // behind the array: its allocator word
		float defaultWeight;  // +0x18
	};
}

namespace container
{
	template<> struct ArrayEraseInline<proto::TokenWeights::Weight>
	{
		enum
		{
			value = 0
		};
	};
}

namespace proto
{
	class TokenBehaviour : public engine::Behaviour
	{
	public:
		// The holder of a kind of token: the objects that have one with a rating each (8 bytes), in room for ten
		struct TokenGroup
		{
			struct Holder
			{
				unsigned int handle;  // +0
				float score;  // +4
			};

			container::ArrayDynamic<Holder, container::AllocatorNew> holders;  // +0
			int unknownC;  // the array's allocator word
		};

		// 0x104047D0
		explicit TokenBehaviour(engine::GameObject* newOwner);
		// 0x104048D0 (the deleting destructor is 0x10405180)
		virtual ~TokenBehaviour();
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();

		// vftable slot 1 (0x10403820)
		virtual void Slot1();
		// vftable slot 4 (0x104051B0)
		virtual void Update(float dt, unsigned short mask);
		// vftable slot 6 (0x10404930)
		virtual void OnMessage(engine::Message* message);

		// 0x104040D0: takes back all tokens
		void ClearTokens();
		// 0x10404220: gives the object a token of the kind when one is free (or it has one); 0x104042B0: takes it back
		bool AcquireToken(int kind, unsigned int handle);
		bool ReleaseToken(int kind, unsigned int handle);
		// 0x10403AA0: the weight of a class name (the default weight when the name is not listed)
		float GetClassnameWeight(const core::Name<core::CaseSensitiveKey>& name) const;
		// 0x10404100: how well the target suits a token from a position
		float ScoreTarget(const math::Vector* from, engine::GameObject* target);
		// 0x10404B40: hands the tokens to the best targets around
		void DistributeTokens();

		int maxTokens[2];  // +0xC
		TokenGroup groups[2];  // +0x14
		float unknown34;  // +0x34
		float tooFar;  // +0x38
		float distanceWeight;  // +0x3C
		float classnameWeight;  // +0x40
		TokenWeights* tokenWeights;  // +0x44
		int unknown48;
		float unknown4C;
		float consumeProbability;  // +0x50
		bool unknown54;
		bool unknown55;
	};
}

#endif
