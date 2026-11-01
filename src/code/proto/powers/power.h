// proto::Power (RTTI and reflection names; base content::MetaLoadObject), proto::PowerInstance and
// proto::PowerBehaviour (base engine::Behaviour): a power is a loaded object with a set of virtual hooks (create an
// instance, start, update, react to a message, report the message types it listens to); a PowerBehaviour keeps one
// instance of each power its game object has and forwards the update and the messages to them. Unit 0x10089F50 -
// 0x1008AF10 (no assert path; directory and file name are guesses). The reflected names are original, the rest is
// guessed.
#ifndef PROTO_POWERS_POWER_H
#define PROTO_POWERS_POWER_H

#include "code/container/arraydynamicallocatornew.h"
#include "code/content/loadinventory.h"
#include "code/content/metatype.h"
#include "code/core/refptr.h"
#include "code/engine/gameobject/behaviour.h"
#include "code/engine/message.h"

namespace proto
{
	class Power : public content::MetaLoadObject
	{
	public:
		// 0x1008A0E0
		Power();
		// 0x10089FE0
		Power(const Power& other);
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();

		// 0x10089FD0
		virtual ~Power();
		// vftable slot 7 (0x1008A0B0): a copy of the power for one game object
		virtual Power* Clone();
		// vftable slots 8 - 14: the hooks of the instance (the base class does nothing)
		virtual void Slot8()
		{
		}
		virtual void Slot9(float unknown)
		{
		}
		virtual void Slot10(float dt)
		{
		}
		virtual void Slot11(engine::Message* message)
		{
		}
		virtual float Slot12()
		{
			return 0.0f;
		}
		virtual void Slot13()
		{
		}
		// Reports the message types the instance listens to
		virtual bool GetMessageMask(unsigned int* mask)
		{
			return false;
		}

		engine::GameObject* gameObject;  // +8: the game object an instance belongs to
	};

	// One power of a PowerBehaviour (RTTI proto::PowerInstance; reflected: the power) with the instance made from it
	class PowerInstance
	{
	public:
		// 0x1008A180
		PowerInstance();
		// 0x1008A290
		~PowerInstance();
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();

		Power* power;  // +0
		Power* instance;  // +4
	};

	class PowerBehaviour : public engine::Behaviour
	{
	public:
		typedef container::ArrayDynamic<PowerInstance, container::AllocatorNew> InstanceArray;

		// 0x1008ACF0
		explicit PowerBehaviour(engine::GameObject* newOwner);
		// 0x1008AD20
		virtual ~PowerBehaviour();
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();

		// vftable slots 1 (0x1008A2A0), 4 (0x1008A360) and 6 (0x1008A3B0)
		virtual void Slot1();
		virtual void Update(float dt, unsigned short mask);
		virtual void OnMessage(engine::Message* message);

		InstanceArray powerInstances;  // +0xC
		int unknown18;  // behind the array: its allocator word
	};
}

#endif
