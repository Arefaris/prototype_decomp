// proto::ThreatReceiverBehaviour (RTTI and reflection names; base engine::Behaviour): collects the threats that other
// objects report to its object (message type 0x35: reports, queries and clears) and forgets them when it is told to
// (message type 2, or automatically). Reflected: automaticallyClearThreats. Unit 0x10403000 - 0x10403760 (no assert
// path; the file name is a guess). The reflected name is original, the rest is guessed; only the construction, the
// reflection and the update are reconstructed.
#ifndef PROTO_BEHAVIOURS_THREATRECEIVERBEHAVIOUR_H
#define PROTO_BEHAVIOURS_THREATRECEIVERBEHAVIOUR_H

#include "code/container/arrayfixed.h"
#include "code/content/metatype.h"
#include "code/engine/gameobject/behaviour.h"
#include "code/engine/gameobject/gameobjecthandle.h"

namespace proto
{
	class ThreatReceiverBehaviour : public engine::Behaviour
	{
	public:
		// One reported threat (8 bytes; member names guessed)
		struct ThreatEntry
		{
			engine::GameObjectHandle handle;
			int amount;
		};

		// 0x10403690
		explicit ThreatReceiverBehaviour(engine::GameObject* newOwner);
		// 0x104036F0 (the deleting destructor is 0x10403710)
		virtual ~ThreatReceiverBehaviour();
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();

		// vftable slot 1 (0x10403040): nothing to do
		virtual void Slot1()
		{
		}
		// vftable slot 4 (0x10403650)
		virtual void Update(float dt, unsigned short mask);
		// vftable slot 6 (0x10403590)
		virtual void OnMessage(engine::Message* message);

		// 0x10403580: forgets the threatening objects
		void ClearThreatenedBy();
		// 0x104033D0: an object reports that it threatens (the threat memory and the list of the threatened are updated)
		void OnThreatReported(engine::GameObjectHandle handle);
		// 0x10403190: whether the memory holds a threat of that object with another second word than the argument
		bool HasThreat(unsigned int handle, int other);

		container::ArrayFixed<engine::GameObjectHandle, 5> threatenedBy;  // +0xC
		container::ArrayFixed<ThreatEntry, 4> threats;  // +0x24
		bool automaticallyClearThreats;  // +0x48
	};
}

#endif
