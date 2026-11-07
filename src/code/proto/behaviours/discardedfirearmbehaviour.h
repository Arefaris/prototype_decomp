// proto::DiscardedFirearmBehaviour (RTTI and reflection names; base engine::Behaviour): a firearm that someone dropped.
// When it is attached to a new owner it can reload the ammunition it holds or fade out and disappear. Unit 0x10464EF0 -
// 0x10465B50 (no assert path; the file name is a guess). The reflected names are original, the rest is guessed; the
// reflection, the construction and the destruction are reconstructed, the fading and the handling of the messages are
// left to the engine.
#ifndef PROTO_BEHAVIOURS_DISCARDEDFIREARMBEHAVIOUR_H
#define PROTO_BEHAVIOURS_DISCARDEDFIREARMBEHAVIOUR_H

#include "code/content/metatype.h"
#include "code/engine/gameobject/behaviour.h"
#include "code/engine/message.h"
#include "code/proto/behaviours/weaponbehaviour.h"

namespace proto
{
	class DiscardedFirearmBehaviour : public engine::Behaviour
	{
	public:
		// What happens to the ammunition when the firearm is attached (RTTI-less enumeration; the names are from the
		// values 0x1108DA64)
		enum AmmoActionOnAttachmentChange
		{
			AMMO_ACTION_NONE = 0,
			AMMO_ACTION_RELOAD = 1,
			AMMO_ACTION_FADE = 2
		};

		// 0x10464FB0
		explicit DiscardedFirearmBehaviour(engine::GameObject* newOwner);
		// 0x104652A0 (the deleting destructor is 0x104653A0)
		virtual ~DiscardedFirearmBehaviour();
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();

		// vftable slot 1 (0x10465950; it jumps to the setup of the fade at 0x104653D0), 4 (0x10465010) and 6 (0x10465960),
		// left to the engine
		virtual void Slot1();
		virtual void Update(float dt, unsigned short mask);
		virtual void OnMessage(engine::Message* message);

		int ammoActionOnAttach;  // +0xC
		AmmoProfileBase* ammoProfileOnAttach;  // +0x10
		float timeBeforeFade;  // +0x14
		float timeToFade;  // +0x18
		float timeElapsed;  // +0x1C
	};
}

namespace content
{
	template<> struct EnumInfo<proto::DiscardedFirearmBehaviour::AmmoActionOnAttachmentChange>
	{
		static void Get(const char** name, const EnumValue** values, int* count, const char** code);
	};
}

#endif
