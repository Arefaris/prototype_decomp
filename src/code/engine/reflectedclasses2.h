// More reflected classes of other units that the engine's factories (metafactories.cpp) construct, as in
// reflectedclasses.h: a class is its size, its constructor and the two functions of its reflection, all of them in
// the units of the classes. Replace an entry by the real class when its unit is reconstructed.
#ifndef ENGINE_REFLECTEDCLASSES2_H
#define ENGINE_REFLECTEDCLASSES2_H

#include "code/content/loadinventory.h"
#include "code/engine/contentmanager.h"
#include "code/engine/gameobject/behaviour.h"

namespace engine
{
	namespace animation
	{
		// AttachableBehaviour: constructor 0x1083E5C0, reflection 0x1083BBA0 / 0x1083CB80
		class AttachableBehaviour : public engine::Behaviour
		{
		public:
			AttachableBehaviour(engine::GameObject* owner);
			// 0x1083C070 (the deleting destructor is 0x1083C960)
			virtual ~AttachableBehaviour();
			static content::ClassInfo* GetClassInfo();
			static content::MemberList* GetMembers();

			// The vftable (0x10E6F74C): slots 1 (0x1083C980), 4 (0x1083E1F0), 5 (0x1083C9A0) and 6 (0x1083E460)
			virtual void Slot1();
			virtual void Update(float dt, unsigned short mask);
			virtual void OnPostedMessage(engine::Message* message);
			virtual void OnMessage(engine::Message* message);

			unsigned char unknownC[0x38];
		};
	}

	namespace camera
	{
		// Cinematographer: constructor 0x1084E150, reflection 0x1084DE70 / 0x1084E7E0
		class Cinematographer
		{
		public:
			Cinematographer();
			static content::ClassInfo* GetClassInfo();
			static content::MemberList* GetMembers();

			unsigned char unknown0[0x7B0];
		};
	}

	// HealthBehaviour: constructor 0x10847F30, reflection 0x10847EF0 / 0x108486A0 (the real class: healthbehaviour.h)
	class HealthBehaviour : public engine::Behaviour
	{
	public:
		explicit HealthBehaviour(engine::GameObject* owner);
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();

		unsigned char unknownC[0x1C];
	};

	namespace trigger
	{
		class Volume;
	}

	// TriggerBehaviour: constructor 0x1083B6C0, reflection 0x1083AD50 / 0x1083B4E0
	class TriggerBehaviour : public engine::Behaviour
	{
	public:
		TriggerBehaviour(engine::GameObject* owner);
		// 0x1083B760 / 0x1083B860: the constructors that take the volume (stored at +0xC) and a mode (+0x10)
		TriggerBehaviour(engine::GameObject* owner, trigger::Volume* volume);
		TriggerBehaviour(engine::GameObject* owner, trigger::Volume* volume, int mode);
		// 0x1083AFC0 (the deleting destructor is 0x1083B290)
		virtual ~TriggerBehaviour();
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();

		// The vftable (0x10E6F534): slots 0 (0x1083ADD0), 1 (0x1083B060), 3 (0x1083B100), 4 (0x1083ADE0), 5 (0x1083AE00)
		// and 6 (0x1083B1D0)
		virtual void Slot0();
		virtual void Slot1();
		virtual void OnActiveChanged(bool active);
		virtual void Update(float dt, unsigned short mask);
		virtual void OnPostedMessage(engine::Message* message);
		virtual void OnMessage(engine::Message* message);

		unsigned char unknownC[0x98];
	};

	// MovingTriggerBehaviour: reflection 0x1083AD90 / 0x1083B660 (only its meta type is made here)
	class MovingTriggerBehaviour : public engine::Behaviour
	{
	public:
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();
	};
}

#include "code/ravenphysics/physicsobjectfactory.h"

#endif
