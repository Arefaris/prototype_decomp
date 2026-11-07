// proto::ShieldHitReactionBehaviour (RTTI and reflection names; base engine::Behaviour): the reaction of a shield to hits
// -- it keeps the object's intersection properties (reflectingIntersectionProperties) in effect while hits from the
// two sources are counted, and forwards attachment messages to the object it is attached to. Unit 0x102C4890 -
// 0x102C4F30 (no assert path; the file name is a guess). The reflected names are original, the rest is guessed.
#ifndef PROTO_BEHAVIOURS_SHIELDHITREACTIONBEHAVIOUR_H
#define PROTO_BEHAVIOURS_SHIELDHITREACTIONBEHAVIOUR_H

#include "code/content/metatype.h"
#include "code/engine/gameobject/behaviour.h"
#include "code/engine/gameobject/gameobjecthandle.h"
#include "code/engine/message.h"

namespace ravenphysics
{
	class IntersectionPropertiesLoader;
}

namespace proto
{
	class ShieldHitReactionBehaviour : public engine::Behaviour
	{
	public:
		// 0x102C48D0
		explicit ShieldHitReactionBehaviour(engine::GameObject* newOwner);
		// 0x102C4AB0 (deleting destructor 0x102C4AE0)
		virtual ~ShieldHitReactionBehaviour();
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();

		// vftable slot 6 (0x102C4C70)
		virtual void OnMessage(engine::Message* message);

		// 0x102C4930 / 0x102C49D0: hits of the two sources begin / end (the messages of type 0x1E, ids 0x20 and 0x21); the
		// object reflects while any hit goes on
		void OnHitsBegin(engine::Message* message);
		void OnHitsEnd(engine::Message* message);
		// 0x102C4B10: attachment messages go on to the object this one is attached to
		void OnAttachmentMessage(engine::Message* message);

		engine::HandleBase attachedTo;  // +0xC
		int hitsA;  // +0x10
		int hitsB;  // +0x14
		bool reflecting;  // +0x18
		ravenphysics::IntersectionPropertiesLoader* reflectingIntersectionProperties;  // +0x1C
	};
}

#endif
