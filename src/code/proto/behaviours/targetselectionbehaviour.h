// proto::TargetSelectionBehaviour (RTTI and reflection names; base proto::TargetingBehaviour) and proto::TargetSelectionWeights
// (a reflected load object): the behaviour that picks the target of an AI character among the objects it knows of, rating each
// by its distance, whether it can be seen, whether it targets the character, whether it was the last to damage it, whether it
// holds a token and whether it is no ally; the weights of the classes of target come from a TargetSelectionWeights object.
// Reflected: forgetTime, tooFar, weightDistance, weightHysteresis, weightCanSee, weightTargetingMe, weightLastDamager,
// weightHaveToken, weightIsNotAlly, acquireOnIdleTime, weights, ignorePatsy, gameIntensityContribution. Unit 0x103FED30 -
// 0x10402D00 (no assert path; the file name is a guess). The reflected names are original, the rest is guessed.
#ifndef PROTO_BEHAVIOURS_TARGETSELECTIONBEHAVIOUR_H
#define PROTO_BEHAVIOURS_TARGETSELECTIONBEHAVIOUR_H

#include "code/container/arrayfixed.h"
#include "code/container/arraydynamicallocatornew.h"
#include "code/content/loadinventory.h"
#include "code/content/metatype.h"
#include "code/engine/gameobject/gameobjecthandle.h"
#include "code/proto/arrayhelper.h"
#include "code/proto/autotargetprioritylist.h"
#include "code/proto/behaviours/targetingbehaviour.h"

namespace proto
{
	// RTTI proto::TargetSelectionWeights: how much a class of target is worth to the selection
	struct TargetSelectionWeights : public content::MetaLoadObject
	{
		// RTTI proto::TargetSelectionWeights::Pair (8 bytes)
		struct Pair
		{
			static content::ClassInfo* GetClassInfo();
			static content::MemberList* GetMembers();

			TargetClass targetClass;  // +0
			float weight;  // +4
		};

		typedef container::ArrayDynamic<Pair, container::AllocatorNew> PairArray;

		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();

		PairArray weights;  // +8
	};

}

// The engine's helper of the pair array: its Insert (the count form is not expanded) and Erase differ from the generic ones, they
// stay the engine's (0x10402640 and 0x104010E0)
namespace content
{
	template<> class ArrayDynamicHelper<container::ArrayDynamic<proto::TargetSelectionWeights::Pair, container::AllocatorNew> >
		: public ArrayDynamicHelperBase
	{
	public:
		typedef container::ArrayDynamic<proto::TargetSelectionWeights::Pair, container::AllocatorNew> A;

		virtual int Size(void* array)
		{
			return ((A*)array)->Size();
		}
		virtual void* Get(void* array, int index)
		{
			return ((A*)array)->begin + index;
		}
		virtual void* GetConst(void* array, int index)
		{
			return ((A*)array)->begin + index;
		}
		virtual void Insert(void* array, int index, int unused);
		virtual void Erase(void* array, int index, int unused);
		virtual int Capacity(void* array)
		{
			return ((A*)array)->Capacity();
		}
		virtual void Expand(void* array, unsigned int count)
		{
			A* a = (A*)array;
			if (a->Capacity() == 0)
			{
				a->Allocate(count);
			}
			else if (count + a->Size() > a->Capacity())
			{
				a->Reserve(count + a->Size());
			}
		}
	};
}

namespace proto
{
	class TargetSelectionBehaviour : public TargetingBehaviour
	{
	public:
		// One object known to the selection with its rating (8 bytes)
		struct Candidate
		{
			engine::GameObjectHandle handle;
			float score;
		};

		// 0x10402150
		explicit TargetSelectionBehaviour(engine::GameObject* newOwner);
		// 0x10401680 (the deleting destructor is 0x10402380)
		virtual ~TargetSelectionBehaviour();
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();

		// vftable slot 1 (0x103FEEB0)
		virtual void Slot1();
		// vftable slot 3 (0x104025A0)
		virtual void OnActiveChanged(bool active);
		// vftable slot 4 (0x104023B0)
		virtual void Update(float dt, unsigned short mask);
		// vftable slot 6 (0x10402750)
		virtual void OnMessage(engine::Message* message);

		// 0x10401A50: forgets the selection
		void Reset();
		// 0x103FF260: puts the behaviour on / takes it off the manager's list (name guess)
		void SetRegistered(bool registered);
		// 0x104009A0: takes the object as the one the selection works on (name guess)
		void SetCurrent(engine::HandleBase handle);

		engine::HandleBase unknown10;  // +0x10
		bool unknown14;
		bool unknown15;
		bool unknown16;
		bool unknown17;
		engine::GameObject* current;  // +0x18: the object that carries the target lock of the selection
		int unknown1C;
		engine::HandleBase unknown20;
		float unknown24;
		bool unknown28;
		bool unknown29;
		bool unknown2A;
		bool registered;  // +0x2B
		engine::HandleBase unknown2C;
		engine::HandleBase unknown30;
		bool unknown34;
		bool unknown35;
		bool ignorePatsy;  // +0x36
		unsigned char unknown37;
		TargetSelectionWeights* weights;  // +0x38
		container::ArrayFixed<Candidate, 8> candidates;  // +0x3C
		float forgetTime;  // +0x80
		float tooFar;  // +0x84
		float weightDistance;  // +0x88
		float weightHysteresis;  // +0x8C
		float weightCanSee;  // +0x90
		float weightTargetingMe;  // +0x94
		float weightLastDamager;  // +0x98
		float weightHaveToken;  // +0x9C
		float weightIsNotAlly;  // +0xA0
		float acquireOnIdleTime;  // +0xA4
		float unknownA8;
		float unknownAC;
		bool unknownB0;
		float unknownB4;
		unsigned char unknownB8[0x18];
		int unknownD0;
		int unknownD4;
		float unknownD8;
		float unknownDC;
		int unknownE0;
		engine::HandleBase unknownE4;
		float gameIntensityContribution;  // +0xE8
	};
}

#endif
