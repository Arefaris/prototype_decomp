// proto::AiTreeBehaviour (RTTI and reflection names; base engine::FightTreeBehaviour): the fight tree of the ai
// context of an object. It runs the branch the tree names, keeps the task and the goal that are reflected, two short
// lists of entries (a name and a mode each) the ai items fill and a word of flags the messages set. Unit 0x103C78E0 -
// 0x103C90C0 (no assert path; the file name is a guess). The reflected names are original, the rest is guessed; the
// update and the message handler are left to the engine.
#ifndef PROTO_BEHAVIOURS_AITREEBEHAVIOUR_H
#define PROTO_BEHAVIOURS_AITREEBEHAVIOUR_H

#include "code/container/arraycdynamic.h"
#include "code/content/metatype.h"
#include "code/core/name.h"
#include "code/engine/fight/behaviours/fighttreebehaviour.h"

namespace proto
{
	class AiTreeBehaviour : public engine::FightTreeBehaviour
	{
	public:
		// An entry of the two lists: a name and a mode (0x10 bytes)
		struct Entry
		{
			Entry() : mode(0), unknownC(0)
			{
			}
			Entry(const core::Name<core::CaseSensitiveKey>& newName, int newMode) : name(newName), mode(newMode), unknownC(0)
			{
			}
			Entry(const Entry& other) : name(other.name), mode(other.mode), unknownC(0)
			{
			}
			Entry& operator=(const Entry& other)
			{
				name = other.name;
				mode = other.mode;
				return *this;
			}

			core::Name<core::CaseSensitiveKey> name;
			int mode;  // +8
			int unknownC;
		};

		typedef container::ArrayCDynamic<Entry, 6> EntryList;

		// 0x103C8CA0
		explicit AiTreeBehaviour(engine::GameObject* newOwner);
		// 0x103C8820 (deleting destructor 0x103C8DA0)
		virtual ~AiTreeBehaviour();
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();

		// vftable slots 1 (0x103C7920), 3 (0x103C7980), 4 (0x103C8E50, left to the engine) and 6 (0x103C8880, left to
		// the engine)
		virtual void Slot1();
		virtual void OnActiveChanged(bool active);
		// vftable slot 5 (0x103C79F0): the base's
		virtual void OnPostedMessage(engine::Message* message);
		virtual void Update(float dt, unsigned short mask);
		virtual void OnMessage(engine::Message* message);

		// 0x103C8750: forgets what the tree ran
		void Reset();
		// 0x103C8870
		void ResetAndStop();

		bool autonomous;  // +0x68
		bool unknown69;
		bool unknown6A;
		bool registered;  // +0x6B
		bool unknown6C;
		bool unknown6D;
		char timeslicePeriod;  // +0x6E
		core::Name<core::CaseSensitiveKey> task;  // +0x70
		core::Name<core::CaseSensitiveKey> goal;  // +0x78
		EntryList entries;  // +0x80
		EntryList pendingEntries;  // +0xE4
		float unknown148;
		float tooltipOffset;  // +0x14C
		unsigned int flags;  // +0x150
	};
}

#endif
