// Classes of the proto game that the factory registrations create (MetaObjectFactory, MetaInstanceCreatorImpl and
// MetaBehaviourCreatorImpl instances) and whose layout is not recovered yet: each has its base class from the RTTI,
// the constructor the factory calls, the reflection entry points and the rest of its bytes as one unknown block. A unit
// that reconstructs a class replaces its declaration here with the real one.
#ifndef PROTO_REFLECTEDSTUBS_H
#define PROTO_REFLECTEDSTUBS_H

#include "code/proto/coopbehaviour.h"
#include "code/proto/shaders/shaderpalette.h"
#include "code/proto/behaviours/powerwheelbehaviour.h"
#include "code/proto/behaviours/fedisplaybehaviour.h"
#include "code/content/loadinventory.h"
#include "code/engine/gameobject/behaviour.h"
#include "code/content/loadinventory.h"
#include "code/engine/fight/behaviours/fighttreebehaviour.h"
#include "code/engine/gameobject/behaviour.h"
#include "code/engine/propbehaviour.h"
#include "code/engine/reflectedclasses2.h"
#include "code/proto/ai/ambientmanager/ambientexclusionvolume.h"
#include "code/proto/ai/ambientmanager/ambientspawners.h"
#include "code/proto/ai/ambientmanager/behaviours/vehiclebehaviourambient.h"
#include "code/proto/webofintrigue/webnodelocator.h"
#include "code/proto/ai/ambientmanager/intersectionbehaviour.h"
#include "code/proto/ai/ambientmanager/intersectiondata.h"
#include "code/proto/ai/ambientmanager/behaviours/pedalertreaction.h"
#include "code/proto/behaviours/aiflyingpatrolbehaviour.h"
#include "code/proto/behaviours/randomdeadpedbehaviour.h"
#include "code/proto/behaviours/alertbehaviour.h"
#include "code/proto/behaviours/testwalkbehaviour.h"
#include "code/proto/behaviours/threatbehaviour.h"
#include "code/proto/behaviours/threatreceiverbehaviour.h"
#include "code/proto/behaviours/tokenbehaviour.h"
#include "code/proto/behaviours/watertowerbehaviour.h"
#include "code/proto/characterbudgetpolicy.h"
#include "code/proto/heightmap.h"
#include "code/proto/helipathfindingloader.h"
#include "code/proto/behaviours/addtoheightmapbehaviour.h"
#include "code/proto/behaviours/aimbehaviour.h"
#include "code/proto/behaviours/scarymonsterbehaviour.h"
#include "code/proto/behaviours/camerafloorbehaviour.h"
#include "code/proto/behaviours/tanksolver.h"
#include "code/proto/behaviours/vehicleconstraints.h"
#include "code/proto/behaviours/wheelconstraint.h"
#include "code/proto/behaviours/helicopterrotor.h"
#include "code/proto/behaviours/cloudbehaviour.h"
#include "code/proto/behaviours/stayonnavmeshbehaviour.h"
#include "code/proto/behaviours/squadmemberbehaviour.h"
#include "code/proto/behaviours/squadblackboardbehaviour.h"
#include "code/proto/worldboundary.h"
#include "code/proto/tunnelvolume.h"

namespace ravenphysics
{
	class AbstractPhysicsObjectFactory;
	class PhysicsObjectFactory;
}

namespace proto
{
	struct TargetSelectionWeights;

	class TransformationDescription : public content::MetaLoadObject
	{
	public:
		TransformationDescription();
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();
	
		unsigned char unknownTail[0x68 - sizeof(content::MetaLoadObject)];
	};

	class AmbientNavMesh : public content::MetaLoadObject
	{
	public:
		AmbientNavMesh();
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();
	
		unsigned char unknownTail[0x4C - sizeof(content::MetaLoadObject)];
	};

	class NPCAnimation : public content::MetaLoadObject
	{
	public:
		NPCAnimation();
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();
	
		unsigned char unknownTail[0x30 - sizeof(content::MetaLoadObject)];
	};

	class NPCAnimationList : public content::MetaLoadObject
	{
	public:
		NPCAnimationList();
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();
	
		unsigned char unknownTail[0xFC - sizeof(content::MetaLoadObject)];
	};

	class NPCDrawable : public content::MetaLoadObject
	{
	public:
		NPCDrawable();
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();
	
		unsigned char unknownTail[0x10 - sizeof(content::MetaLoadObject)];
	};

	class NPCInstancePool : public content::MetaLoadObject
	{
	public:
		NPCInstancePool();
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();
	
		unsigned char unknownTail[0x3C - sizeof(content::MetaLoadObject)];
	};

	class NPCRender : public content::MetaLoadObject
	{
	public:
		NPCRender();
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();
	
		unsigned char unknownTail[0x14 - sizeof(content::MetaLoadObject)];
	};

	class NPCType : public proto::NPCRender
	{
	public:
		NPCType();
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();
	
		unsigned char unknownTail[0x38 - sizeof(proto::NPCRender)];
	};

	class HelicopterSolverGenericProperties : public content::MetaLoadObject
	{
	public:
		class CameraParams
		{
		public:
			static content::ClassInfo* GetClassInfo(); //@0x1031DFE0
		};
		class EffectsParams
		{
		public:
			static content::ClassInfo* GetClassInfo(); //@0x1031E020
		};
		class HealthParams
		{
		public:
			static content::ClassInfo* GetClassInfo(); //@0x1031E060
		};
		class PowerParams
		{
		public:
			static content::ClassInfo* GetClassInfo(); //@0x1031E0A0
		};
		class RotorParams
		{
		public:
			static content::ClassInfo* GetClassInfo(); //@0x1031E0E0
		};
		class SoundParams
		{
		public:
			static content::ClassInfo* GetClassInfo(); //@0x1031E120
		};

		HelicopterSolverGenericProperties();
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();
	
		unsigned char unknownTail[0xD0 - sizeof(content::MetaLoadObject)];
	};

	class HelicopterSolverProperties : public content::MetaLoadObject
	{
	public:
		class AIParams
		{
		public:
			static content::ClassInfo* GetClassInfo(); //@0x1031E160
		};
		class HoverParams
		{
		public:
			static content::ClassInfo* GetClassInfo(); //@0x1031E1A0
		};
		class LateralAxisLinearParams
		{
		public:
			static content::ClassInfo* GetClassInfo(); //@0x1031E1E0
		};
		class LateralAxisAngularParams
		{
		public:
			static content::ClassInfo* GetClassInfo(); //@0x1031E220
		};
		class LongitudinalAxisLinearParams
		{
		public:
			static content::ClassInfo* GetClassInfo(); //@0x1031E260
		};
		class LongitudinalAxisAngularParams
		{
		public:
			static content::ClassInfo* GetClassInfo(); //@0x1031E2A0
		};
		class VerticalAxisParams
		{
		public:
			static content::ClassInfo* GetClassInfo(); //@0x1031E2E0
		};
		class YawAxisParams
		{
		public:
			static content::ClassInfo* GetClassInfo(); //@0x1031E320
		};

		HelicopterSolverProperties();
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();
	
		unsigned char unknownTail[0x124 - sizeof(content::MetaLoadObject)];
	};

	class WorldTriggers : public content::MetaLoadObject
	{
	public:
		WorldTriggers();
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();
	
		unsigned char unknownTail[0x18 - sizeof(content::MetaLoadObject)];
	};

	struct DisguiseConfig : public content::MetaLoadObject
	{
	public:
		DisguiseConfig();
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();
	
		unsigned char unknownTail[0x274 - sizeof(content::MetaLoadObject)];
	};

	struct BulletTracerProfile : public content::MetaLoadObject
	{
	public:
		BulletTracerProfile();
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();
	
		unsigned char unknownTail[0xD8 - sizeof(content::MetaLoadObject)];
	};

	class LightDecalInfo : public content::MetaLoadObject
	{
	public:
		LightDecalInfo();
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();
	
		unsigned char unknownTail[0x20 - sizeof(content::MetaLoadObject)];
	};

	class PedBehaviourTunables : public content::MetaLoadObject
	{
	public:
		PedBehaviourTunables();
		// 0x10434640: releases the factories and templates the object holds
		~PedBehaviourTunables();
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();

		// 0x1108BC2C: the object that was made last (its constructor stores itself there)
		static PedBehaviourTunables* sInstance;

		PedAlertReactionTable pedAlertReactionTable;  // +8
		content::MetaObjectTemplate* pedestrianAlertTemplate;  // +0x488
		unsigned char unknown48C[0x518 - 0x48C];
		float unknown518;  // +0x518
		float characterFadeTime;  // +0x51C
		unsigned char unknown520[8];
		TargetSelectionWeights* weights;  // +0x528
		ravenphysics::AbstractPhysicsObjectFactory* alivePedestrianPhysicsObjectFactory;  // +0x52C
		ravenphysics::AbstractPhysicsObjectFactory* deadPedestrianPhysicsObjectFactory;  // +0x530
		ravenphysics::AbstractPhysicsObjectFactory* targetingPhysicsObjectFactory;  // +0x534
		float impulseScale;  // +0x538
		ravenphysics::PhysicsObjectFactory* maleRagdollFactory;  // +0x53C
		ravenphysics::PhysicsObjectFactory* femaleRagdollFactory;  // +0x540
		content::MetaObjectTemplate* pedestrianTemplate;  // +0x544
	};

	struct ConsumableProperties : public content::MetaLoadObject
	{
	public:
		ConsumableProperties();
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();
	
		unsigned char unknownTail[0x38 - sizeof(content::MetaLoadObject)];
	};

	struct WeaponUserProfile : public content::MetaLoadObject
	{
	public:
		WeaponUserProfile();
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();
	
		unsigned char unknownTail[0x88 - sizeof(content::MetaLoadObject)];
	};

	struct AmmoProfileBase : public content::MetaLoadObject
	{
	public:
	};

	struct GunAmmoProfile : public proto::AmmoProfileBase
	{
	public:
		GunAmmoProfile();
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();
	
		unsigned char unknownTail[0x70 - sizeof(proto::AmmoProfileBase)];
	};

	struct MissileProfile : public proto::AmmoProfileBase
	{
	public:
		MissileProfile();
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();
	
		unsigned char unknownTail[0xC8 - sizeof(proto::AmmoProfileBase)];
	};

	struct MissileSpin : public content::MetaLoadObject
	{
	public:
		MissileSpin();
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();
	
		unsigned char unknownTail[0x34 - sizeof(content::MetaLoadObject)];
	};

	struct MissileSpawnProfile : public content::MetaLoadObject
	{
	public:
		MissileSpawnProfile();
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();
	
		unsigned char unknownTail[0x20 - sizeof(content::MetaLoadObject)];
	};

	class FadeoutBehaviourProperties : public content::MetaLoadObject
	{
	public:
		FadeoutBehaviourProperties();
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();
	
		unsigned char unknownTail[0x14 - sizeof(content::MetaLoadObject)];
	};


	struct MissileSpawnDrawSwap
	{
	public:
		MissileSpawnDrawSwap();
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();
	
		unsigned char unknown0[0x28];
	};

	class PatrolPoint
	{
	public:
		PatrolPoint();
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();
	
		unsigned char unknown0[0x60];
	};

	class AiTreeBehaviour : public engine::FightTreeBehaviour
	{
	public:
		explicit AiTreeBehaviour(engine::GameObject* newOwner);
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();
	
		unsigned char unknownTail[0x158 - sizeof(engine::FightTreeBehaviour)];
	};

	class ConsumableBehaviour : public engine::Behaviour
	{
	public:
		explicit ConsumableBehaviour(engine::GameObject* newOwner);
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();
	
		unsigned char unknownTail[0xC0 - sizeof(engine::Behaviour)];
	};

	class DisguiseBehaviour : public engine::FightTreeBehaviour
	{
	public:
		explicit DisguiseBehaviour(engine::GameObject* newOwner);
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();
	
		unsigned char unknownTail[0x560 - sizeof(engine::FightTreeBehaviour)];
	};

	class EmotionalStateBehaviour : public engine::Behaviour
	{
	public:
		explicit EmotionalStateBehaviour(engine::GameObject* newOwner);
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();
	
		unsigned char unknownTail[0x18 - sizeof(engine::Behaviour)];
	};

	class MovementBehaviour : public engine::Behaviour
	{
	public:
	};

	class FlyingBehaviour : public proto::MovementBehaviour
	{
	public:
		explicit FlyingBehaviour(engine::GameObject* newOwner);
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();
	
		unsigned char unknownTail[0x534 - sizeof(proto::MovementBehaviour)];
	};

	class WeaponBehaviour : public engine::Behaviour
	{
	public:
	};

	class GunBehaviour : public proto::WeaponBehaviour
	{
	public:
		explicit GunBehaviour(engine::GameObject* newOwner);
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();
	
		unsigned char unknownTail[0x84 - sizeof(proto::WeaponBehaviour)];
	};

	class HelicopterSolverBehaviour : public engine::Behaviour
	{
	public:
		explicit HelicopterSolverBehaviour(engine::GameObject* newOwner);
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();
	
		unsigned char unknownTail[0x180 - sizeof(engine::Behaviour)];
	};

	class LODAIBehaviour : public engine::Behaviour
	{
	public:
		explicit LODAIBehaviour(engine::GameObject* newOwner);
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();
	
		unsigned char unknownTail[0xAC - sizeof(engine::Behaviour)];
	};

	class AttachBillboardBehaviour : public engine::Behaviour
	{
	public:
		explicit AttachBillboardBehaviour(engine::GameObject* newOwner);
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();
	
		unsigned char unknownTail[0x38 - sizeof(engine::Behaviour)];
	};

	class LightDecalBehaviour : public engine::Behaviour
	{
	public:
		explicit LightDecalBehaviour(engine::GameObject* newOwner);
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();
	
		unsigned char unknownTail[0x20 - sizeof(engine::Behaviour)];
	};

	class MissileBehaviour : public proto::WeaponBehaviour
	{
	public:
		explicit MissileBehaviour(engine::GameObject* newOwner);
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();
	
		unsigned char unknownTail[0x108 - sizeof(proto::WeaponBehaviour)];
	};

	class BombBehaviour : public proto::MissileBehaviour
	{
	public:
		explicit BombBehaviour(engine::GameObject* newOwner);
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();
	
		unsigned char unknownTail[0x118 - sizeof(proto::MissileBehaviour)];
	};

	class DiscardedFirearmBehaviour : public engine::Behaviour
	{
	public:
		explicit DiscardedFirearmBehaviour(engine::GameObject* newOwner);
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();
	
		unsigned char unknownTail[0x20 - sizeof(engine::Behaviour)];
	};

	class JavelinMissileBehaviour : public proto::MissileBehaviour
	{
	public:
		explicit JavelinMissileBehaviour(engine::GameObject* newOwner);
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();
	
		unsigned char unknownTail[0x12C - sizeof(proto::MissileBehaviour)];
	};

	class MissileSpawnerBehaviour : public proto::WeaponBehaviour
	{
	public:
		explicit MissileSpawnerBehaviour(engine::GameObject* newOwner);
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();
	
		unsigned char unknownTail[0x88 - sizeof(proto::WeaponBehaviour)];
	};

	class PedBehaviour : public engine::Behaviour
	{
	public:
		explicit PedBehaviour(engine::GameObject* newOwner);
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();

		// vftable slot 1 (0x10433280): nothing to do
		virtual void Slot1();
		// vftable slot 3 (0x10433290): also listens to message type 4 while active
		virtual void OnActiveChanged(bool active);
		// vftable slots 8 .. 20 (the pedestrian's own; the arguments of the ones not reconstructed are unknown)
		// 0x1042FC10: how fast the pedestrian moves
		virtual float GetSpeed();
		// 0x1042FC20
		virtual bool Slot9();
		virtual void Slot10();
		// 0x1043B700 / 0x1043C570
		virtual bool Slot11();
		virtual void Slot12();
		virtual void Slot13();
		virtual void Slot14();
		virtual void Slot15();
		// 0x10435360
		virtual void Slot16();
		// 0x1043BD30: takes the new state
		virtual void SetState(int newState);
		// 0x10433370: which kind of pedestrian this is (0 pedestrian, 1 cop, 2 infected, 3 soldier)
		virtual int GetPedType();
		virtual void Slot19();
		virtual void Slot20();

		unsigned char unknownC[0x18 - sizeof(engine::Behaviour)];
		int unknown18;  // +0x18
		unsigned char unknown1C[0x5C - 0x1C];
		float speed;  // +0x5C
		int unknown60;  // +0x60
		int state;  // +0x64
		unsigned char unknown68[0xE4 - 0x68];
	};

	class CharacterPedBehaviour : public engine::Behaviour
	{
	public:
		explicit CharacterPedBehaviour(engine::GameObject* newOwner);
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();
	
		unsigned char unknownTail[0x18 - sizeof(engine::Behaviour)];
	};

	class InfectedPedBehaviour : public proto::PedBehaviour
	{
	public:
		explicit InfectedPedBehaviour(engine::GameObject* newOwner);
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();

		// 0x1042FC40 / 0x1042FC80
		virtual int GetPedType();
		virtual void SetState(int newState);
	
		unsigned char unknownTail[0xE4 - sizeof(proto::PedBehaviour)];
	};

	class CopPedBehaviour : public proto::PedBehaviour
	{
	public:
		explicit CopPedBehaviour(engine::GameObject* newOwner);
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();

		// the overrides: 0x1042F040, 0x1042F070, 0x1042F090, 0x1042EFE0, 0x1042F0D0, 0x1042EFF0, 0x1042EFD0
		virtual float GetSpeed();
		virtual bool Slot9();
		virtual bool Slot11();
		virtual void Slot12();
		virtual void Slot16();
		virtual void SetState(int newState);
		virtual int GetPedType();

		bool unknownE4;  // +0xE4
		unsigned char unknownE5[3];
		int unknownE8;
	};

	class SoldierPedBehaviour : public proto::CopPedBehaviour
	{
	public:
		explicit SoldierPedBehaviour(engine::GameObject* newOwner);
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();

		// 0x1042EF60
		virtual int GetPedType();
	
		unsigned char unknownTail[0xEC - sizeof(proto::CopPedBehaviour)];
	};

	class PerceptionBehaviour : public engine::Behaviour
	{
	public:
		explicit PerceptionBehaviour(engine::GameObject* newOwner);
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();
	
		unsigned char unknownTail[0x15C - sizeof(engine::Behaviour)];
	};

	class SquadCommanderBehaviour : public engine::Behaviour
	{
	public:
		explicit SquadCommanderBehaviour(engine::GameObject* newOwner);
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();
	
		unsigned char unknownTail[0xA0 - sizeof(engine::Behaviour)];
	};

	class SquadPerceptionBehaviour : public engine::Behaviour
	{
	public:
		explicit SquadPerceptionBehaviour(engine::GameObject* newOwner);
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();
	
		unsigned char unknownTail[0x1C - sizeof(engine::Behaviour)];
	};

	class ThreatBallBehaviour : public engine::TriggerBehaviour
	{
	public:
		explicit ThreatBallBehaviour(engine::GameObject* newOwner);
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();
	
		unsigned char unknownTail[0x100 - sizeof(engine::TriggerBehaviour)];
	};

	class TransformationBehaviour : public engine::Behaviour
	{
	public:
		explicit TransformationBehaviour(engine::GameObject* newOwner);
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();
	
		unsigned char unknownTail[0x1F8 - sizeof(engine::Behaviour)];
	};

	class VehicleBehaviourAICharacter : public proto::VehicleBehaviour
	{
	public:
		explicit VehicleBehaviourAICharacter(engine::GameObject* newOwner);
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();
	
		unsigned char unknownTail[0xD0 - sizeof(proto::VehicleBehaviour)];
	};

	class WalkingBehaviour : public proto::MovementBehaviour
	{
	public:
		explicit WalkingBehaviour(engine::GameObject* newOwner);
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();
	
		unsigned char unknownTail[0x558 - sizeof(proto::MovementBehaviour)];
	};

	class TankMovementBehaviour : public proto::MovementBehaviour
	{
	public:
		explicit TankMovementBehaviour(engine::GameObject* newOwner);
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();
	
		unsigned char unknownTail[0x848 - sizeof(proto::MovementBehaviour)];
	};

	class HelicopterMovementBehaviour : public proto::FlyingBehaviour
	{
	public:
		explicit HelicopterMovementBehaviour(engine::GameObject* newOwner);
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();
	
		unsigned char unknownTail[0x618 - sizeof(proto::FlyingBehaviour)];
	};

	class HunterMovementBehaviour : public proto::MovementBehaviour
	{
	public:
		explicit HunterMovementBehaviour(engine::GameObject* newOwner);
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();
	
		unsigned char unknownTail[0x5F4 - sizeof(proto::MovementBehaviour)];
	};


	class DriverBehaviour : public engine::Behaviour
	{
	public:
		explicit DriverBehaviour(engine::GameObject* newOwner);
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();
	
		unsigned char unknownTail[0x20 - sizeof(engine::Behaviour)];
	};

	class HydraMovementBehaviour : public proto::MovementBehaviour
	{
	public:
		explicit HydraMovementBehaviour(engine::GameObject* newOwner);
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();
	
		unsigned char unknownTail[0x164 - sizeof(proto::MovementBehaviour)];
	};

	class NPCRenderBehaviour : public engine::Behaviour
	{
	public:
		explicit NPCRenderBehaviour(engine::GameObject* newOwner);
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();
	
		unsigned char unknownTail[0x38 - sizeof(engine::Behaviour)];
	};

	class BloodtoxBehaviour : public engine::TriggerBehaviour
	{
	public:
		explicit BloodtoxBehaviour(engine::GameObject* newOwner);
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();
	
		unsigned char unknownTail[0xE4 - sizeof(engine::TriggerBehaviour)];
	};

	class FormationBehaviour : public proto::SquadCommanderBehaviour
	{
	public:
		explicit FormationBehaviour(engine::GameObject* newOwner);
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();
	
		unsigned char unknownTail[0xE4 - sizeof(proto::SquadCommanderBehaviour)];
	};

	class StayOnRooftopBehaviour : public engine::Behaviour
	{
	public:
		explicit StayOnRooftopBehaviour(engine::GameObject* newOwner);
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();
	
		unsigned char unknownTail[0x90 - sizeof(engine::Behaviour)];
	};

	class WeaponConfigurationBehaviour : public engine::Behaviour
	{
	public:
		explicit WeaponConfigurationBehaviour(engine::GameObject* newOwner);
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();
	
		unsigned char unknownTail[0x20 - sizeof(engine::Behaviour)];
	};

	class MusicTreeBehaviour : public engine::FightTreeBehaviour
	{
	public:
		explicit MusicTreeBehaviour(engine::GameObject* newOwner);
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();
	
		unsigned char unknownTail[0x70 - sizeof(engine::FightTreeBehaviour)];
	};

	class FadeoutBehaviour : public engine::Behaviour
	{
	public:
		explicit FadeoutBehaviour(engine::GameObject* newOwner);
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();
	
		unsigned char unknownTail[0x14 - sizeof(engine::Behaviour)];
	};

	class FadeBehaviour : public engine::Behaviour
	{
	public:
		explicit FadeBehaviour(engine::GameObject* newOwner);
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();
	
		unsigned char unknownTail[0x20 - sizeof(engine::Behaviour)];
	};

	class FreeAimingBehaviour : public engine::Behaviour
	{
	public:
		explicit FreeAimingBehaviour(engine::GameObject* newOwner);
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();
	
		unsigned char unknownTail[0x20 - sizeof(engine::Behaviour)];
	};

	class BridgeCameraBehaviour : public engine::Behaviour
	{
	public:
		explicit BridgeCameraBehaviour(engine::GameObject* newOwner);
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();
	
		unsigned char unknownTail[0x1C - sizeof(engine::Behaviour)];
	};

	class DrivableVehicleHealthModifierBehaviour : public engine::Behaviour
	{
	public:
		explicit DrivableVehicleHealthModifierBehaviour(engine::GameObject* newOwner);
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();
	
		unsigned char unknownTail[0xC0 - sizeof(engine::Behaviour)];
	};

}

#endif
