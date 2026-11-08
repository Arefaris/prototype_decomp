// More reflected classes of other units that the engine's factories (metafactories.cpp) construct, as in
// reflectedclasses.h: a class is its size, its constructor and the two functions of its reflection, all of them in
// the units of the classes. Replace an entry by the real class when its unit is reconstructed.
#ifndef ENGINE_REFLECTEDCLASSES2_H
#define ENGINE_REFLECTEDCLASSES2_H

#include "code/content/loadinventory.h"
#include "code/engine/contentmanager.h"
#include "code/engine/gameobject/behaviour.h"
#include "code/engine/triggerbehaviour.h"

namespace engine
{
	class BaseAttribute;

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

			// Slot 1 looks the owner's drawable attribute up (0x1083C980)
			BaseAttribute* drawableAttribute;  // +0xC
			unsigned char unknown10[0x34];
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
}

#include "code/ravenphysics/physicsobjectfactory.h"

#endif
