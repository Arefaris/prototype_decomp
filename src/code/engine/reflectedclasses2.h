// More reflected classes of other units that the engine's factories (metafactories.cpp) construct, as in
// reflectedclasses.h: a class is its size, its constructor and the two functions of its reflection, all of them in
// the units of the classes. Replace an entry by the real class when its unit is reconstructed.
#ifndef ENGINE_REFLECTEDCLASSES2_H
#define ENGINE_REFLECTEDCLASSES2_H

#include "code/content/loadinventory.h"
#include "code/engine/gameobject/behaviour.h"

namespace engine
{
	// The content manager's nested definitions (RTTI: engine::ContentManager::...)
	class ContentManager
	{
	public:
		// ContentPackageDefinition: constructor 0x108E7910, reflection 0x108E6940 / 0x108E7490
		class ContentPackageDefinition : public content::MetaLoadObject
		{
		public:
			ContentPackageDefinition();
			static content::ClassInfo* GetClassInfo();
			static content::MemberList* GetMembers();

			unsigned char unknown8[0x34];
		};

		// ContentPackageKey: constructor 0x108E77F0, reflection 0x108E6980 / 0x108E7290
		class ContentPackageKey : public content::MetaLoadObject
		{
		public:
			ContentPackageKey();
			static content::ClassInfo* GetClassInfo();
			static content::MemberList* GetMembers();

			unsigned char unknown8[0x18];
		};
	};

	namespace animation
	{
		// AttachableBehaviour: constructor 0x1083E5C0, reflection 0x1083BBA0 / 0x1083CB80
		class AttachableBehaviour : public engine::Behaviour
		{
		public:
			AttachableBehaviour(engine::GameObject* owner);
			static content::ClassInfo* GetClassInfo();
			static content::MemberList* GetMembers();

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

	// TriggerBehaviour: constructor 0x1083B6C0, reflection 0x1083AD50 / 0x1083B4E0
	class TriggerBehaviour : public engine::Behaviour
	{
	public:
		TriggerBehaviour(engine::GameObject* owner);
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();

		unsigned char unknownC[0x98];
	};
}

namespace ravenphysics
{
	// PhysicsObjectFactory: constructor 0x1066F430, reflection 0x1066C7E0 / 0x1066EE80
	class PhysicsObjectFactory : public content::MetaLoadObject
	{
	public:
		PhysicsObjectFactory();
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();

		unsigned char unknown8[0x28];
	};
}

#endif
