// engine::TagBehaviour (RTTI and reflection name; base engine::Behaviour): the tag names of a game object ("tags"). The
// tags are registered as message listener names with the message router when the behaviour starts (slot 1), which
// also empties the list. Unit 0x10929690 - 0x10929FF0 (no assert path; the directory and file name are guesses). The
// reflected names are original; the rest is guessed.
#ifndef ENGINE_TAGBEHAVIOUR_H
#define ENGINE_TAGBEHAVIOUR_H

#include "code/container/arraydynamicstatic.h"
#include "code/content/metatype.h"
#include "code/core/name.h"
#include "code/engine/gameobject/behaviour.h"

namespace engine
{
	class TagBehaviour : public Behaviour
	{
	public:
		// RTTI engine::TagBehaviour::TagWrapper (struct, 8 bytes): one tag name
		struct TagWrapper
		{
			// 0x10929690 / 0x109297D0
			static content::ClassInfo* GetClassInfo();
			static content::MemberList* GetMembers();

			core::Name<core::CaseSensitiveKey> name;  // +0
		};

		typedef container::ArrayDynamic<TagWrapper, container::AllocatorCoreStatic<1, 16> > TagArray;

		// 0x10929EE0
		explicit TagBehaviour(GameObject* newOwner);
		// 0x10929F10 (deleting destructor 0x10929FD0)
		virtual ~TagBehaviour();

		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();

		// vftable slot 1 (0x10929DC0): hands the tags to the message router and empties the list
		virtual void Slot1();

		TagArray tags;  // +0xC
	};
}

#endif
