// proto::ConsumableProperties (a load object, 0x38 bytes: how a consumed ragdoll is absorbed) and
// proto::ConsumableBehaviour (RTTI and reflection names; base engine::Behaviour): an object that is absorbed into
// another one (the ragdoll of a consumed pedestrian). Unit 0x1007A210 - 0x1007E7B0 (no assert path; the file name is a
// guess). The reflected names are original, the rest is guessed; the reflection, the constructor and the update
// dispatch are reconstructed.
#ifndef PROTO_BEHAVIOURS_CONSUMABLEBEHAVIOUR_H
#define PROTO_BEHAVIOURS_CONSUMABLEBEHAVIOUR_H

#include "code/content/loadinventory.h"
#include "code/content/metatype.h"
#include "code/core/name.h"
#include "code/engine/gameobject/behaviour.h"
#include "code/engine/gameobject/gameobject.h"

namespace ravenphysics
{
	class IntersectionPropertiesLoader;
}

namespace proto
{
	class TransformationDescription;

	// 0x10D977EC (symbols.txt): ten in the pooled constants
	extern const float gTen;

	struct ConsumableProperties : public content::MetaLoadObject
	{
	public:
		ConsumableProperties(); //@0x1007AD70
		virtual ~ConsumableProperties(); //@0x1007AE10 (deleting destructor 0x1007B900)
		static content::ClassInfo* GetClassInfo(); //@0x1007A210
		static content::MemberList* GetMembers(); //@0x1007C4A0

		float initialAbsorbSpeed;  // +8
		float absorbAcceleration;  // +0xC
		float maxAbsorbSpeed;  // +0x10
		float delayBeforeAcceleration;  // +0x14
		float jointScaleRate;  // +0x18
		float angularDampingY;  // +0x1C
		float angularDampingXZ;  // +0x20
		float maxConstraintDistance;  // +0x24
		float constraintDelay;  // +0x28
		float maxConstraintForce;  // +0x2C
		float maxConstraintErrorCorrectionForce;  // +0x30
		ravenphysics::IntersectionPropertiesLoader* ragdollIntersectionProperties;  // +0x34
	};

	class ConsumableBehaviour : public engine::Behaviour
	{
	public:
		explicit ConsumableBehaviour(engine::GameObject* newOwner); //@0x1007D560
		virtual ~ConsumableBehaviour(); //@0x1007D680 (deleting destructor 0x1007D9B0)
		static content::ClassInfo* GetClassInfo(); //@0x1007A250
		static content::MemberList* GetMembers(); //@0x1007C760

		// vftable slots 1 (0x1007B930), 4 (0x1007D740) and 6 (0x1007E030)
		virtual void Slot1();
		virtual void Update(float dt, unsigned short mask);
		virtual void OnMessage(engine::Message* message);

		// The two update passes (0x1007C8B0 for the pass 0x10, 0x1007B980 for the others)
		void UpdateRagdoll(float dt);
		void UpdateOther(float dt);

		// Four 16 byte records and the end of the used ones (0x44 bytes)
		struct FixedList
		{
			void Clear()
			{
				end = data;
			}

			unsigned char data[0x40];
			unsigned char* end;
		};

		struct FloatPair
		{
			FloatPair(float newFirst, float newSecond) : first(newFirst), second(newSecond)
			{
			}

			float first;
			float second;
		};

		TransformationDescription* description;  // +0xC
		int unknown10;
		ConsumableProperties* consumableProperties;  // +0x14
		float healthGained;  // +0x18
		int unknown1C;
		core::Name<core::CaseSensitiveKey> unknown20;
		engine::BaseAttribute* drawableAttribute;  // +0x28
		engine::BaseAttribute* physicsObjectAttribute;  // +0x2C
		engine::BaseAttribute* attachmentStateAttribute;  // +0x30
		int unknown34;
		int unknown38;
		int unknown3C;
		int unknown40;
		int unknown44;
		int unknown48;
		int unknown4C;
		int unknown50;
		int unknown54;
		int unknown58;
		int handle;  // +0x5C
		bool unknown60;
		FloatPair unknown64;
		FloatPair unknown6C;
		float unknown74;
		int unknown78;
		FixedList unknown7C;  // +0x7C
	};
}

#endif
