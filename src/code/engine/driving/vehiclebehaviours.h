// The behaviours of the cars and helicopters (RTTI and reflection names; engine::driving::CarIntentionBehaviour and
// HelicopterIntentionBehaviour derive from VehicleIntentionBehaviour, CarPhysicsBehaviour and
// HelicopterPhysicsBehaviour from VehiclePhysicsBehaviour): the intention behaviours turn the controlling player's input
// into the vehicle's, the physics behaviours hold the attributes of the vehicle (and a car's wheels) and drive its
// physics object. Unit 0x1091CD30 - 0x1091E000 (no assert path; the file name is a guess); the base
// VehiclePhysicsBehaviour is in the unit 0x10938420 - 0x10938B70 and only declared here. The reflected member names are
// original; the rest is guessed.
#ifndef ENGINE_DRIVING_VEHICLEBEHAVIOURS_H
#define ENGINE_DRIVING_VEHICLEBEHAVIOURS_H

#include "code/content/metatype.h"
#include "code/engine/driving/physicsattributes.h"
#include "code/engine/driving/vehicleintentionbehaviour.h"
#include "code/engine/driving/wheelcollectiondata.h"
#include "code/engine/gameobject/behaviour.h"

namespace engine
{
	namespace driving
	{
		// The base of the physics behaviours (0xFC bytes; the constructor is 0x10938B70, the destructor body 0x10938500)
		class VehiclePhysicsBehaviour : public Behaviour
		{
		public:
			explicit VehiclePhysicsBehaviour(GameObject* newOwner);

			// 0x10938420 / 0x10938AC0
			static content::ClassInfo* GetClassInfo();
			static content::MemberList* GetMembers();

			unsigned char unknownC[0xF0];
		};

		class CarIntentionBehaviour : public VehicleIntentionBehaviour
		{
		public:
			// 0x1091CEA0 (not reconstructed)
			explicit CarIntentionBehaviour(GameObject* newOwner);

			static content::ClassInfo* GetClassInfo();
			static content::MemberList* GetMembers();

			// vftable slot 6 (0x1091CD80, not reconstructed): resets the input
			virtual void OnMessage(Message* message);
			// vftable slot 8 (0x1091CDC0, not reconstructed)
			virtual void ApplyInput(void* input);

			// The input the player's controls produce (three floats; their constructor and setters are
			// 0x10937870 - 0x109379C0)
			unsigned char unknown14[0xC];
		};

		class HelicopterIntentionBehaviour : public VehicleIntentionBehaviour
		{
		public:
			// 0x1091DAC0 (not reconstructed)
			explicit HelicopterIntentionBehaviour(GameObject* newOwner);

			static content::ClassInfo* GetClassInfo();
			static content::MemberList* GetMembers();

			// vftable slot 6 (0x1091D9C0, not reconstructed)
			virtual void OnMessage(Message* message);
			// vftable slot 8 (0x1091DA00, not reconstructed)
			virtual void ApplyInput(void* input);

			unsigned char unknown14[0xC];
		};

		class CarPhysicsBehaviour : public VehiclePhysicsBehaviour
		{
		public:
			// 0x1091D920 (not reconstructed)
			explicit CarPhysicsBehaviour(GameObject* newOwner);

			static content::ClassInfo* GetClassInfo();
			static content::MemberList* GetMembers();

			CarPhysicsAttributes* carPhysics;  // +0xFC
			WheelCollectionData* wheelsData;  // +0x100
			unsigned char unknown104[0x10];
		};

		class HelicopterPhysicsBehaviour : public VehiclePhysicsBehaviour
		{
		public:
			// 0x1091DC40 (not reconstructed)
			explicit HelicopterPhysicsBehaviour(GameObject* newOwner);

			static content::ClassInfo* GetClassInfo();
			static content::MemberList* GetMembers();

			HelicopterPhysicsAttributes* helicopterPhysics;  // +0xFC
			unsigned char unknown100[4];
		};
	}
}

#endif
