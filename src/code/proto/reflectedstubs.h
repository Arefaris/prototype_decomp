// Classes of the proto game that the factory registrations create (MetaObjectFactory, MetaInstanceCreatorImpl and
// MetaBehaviourCreatorImpl instances) and whose layout is not recovered yet: each has its base class from the RTTI,
// the constructor the factory calls, the reflection entry points and the rest of its bytes as one unknown block. A unit
// that reconstructs a class replaces its declaration here with the real one.
#ifndef PROTO_REFLECTEDSTUBS_H
#define PROTO_REFLECTEDSTUBS_H

#include "code/content/loadinventory.h"
#include "code/engine/gameobject/behaviour.h"
#include "code/content/loadinventory.h"
#include "code/engine/fight/behaviours/fighttreebehaviour.h"
#include "code/engine/gameobject/behaviour.h"
#include "code/engine/propbehaviour.h"
#include "code/engine/reflectedclasses2.h"
#include "code/proto/ai/ambientmanager/ambientspawners.h"
#include "code/proto/ai/ambientmanager/behaviours/vehiclebehaviourambient.h"
<<<<<<< HEAD
#include "code/proto/webofintrigue/webnodelocator.h"
=======
#include "code/proto/ai/ambientmanager/intersectionbehaviour.h"
#include "code/proto/behaviours/aiflyingpatrolbehaviour.h"
#include "code/proto/behaviours/randomdeadpedbehaviour.h"
#include "code/proto/behaviours/alertbehaviour.h"
#include "code/proto/behaviours/testwalkbehaviour.h"
#include "code/proto/behaviours/threatbehaviour.h"
#include "code/proto/behaviours/threatreceiverbehaviour.h"
#include "code/proto/behaviours/watertowerbehaviour.h"
>>>>>>> sn-bu

namespace proto
{
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

	class HeliPathfindingLoader : public content::MetaLoadObject
	{
	public:
		HeliPathfindingLoader();
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();
	
		unsigned char unknownTail[0x27114 - sizeof(content::MetaLoadObject)];
	};

	class HelicopterSolverGenericProperties : public content::MetaLoadObject
	{
	public:
		HelicopterSolverGenericProperties();
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();
	
		unsigned char unknownTail[0xD0 - sizeof(content::MetaLoadObject)];
	};

	class HelicopterSolverProperties : public content::MetaLoadObject
	{
	public:
		HelicopterSolverProperties();
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();
	
		unsigned char unknownTail[0x124 - sizeof(content::MetaLoadObject)];
	};

	class WheelConstraintParams : public content::MetaLoadObject
	{
	public:
		WheelConstraintParams();
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();
	
		unsigned char unknownTail[0x40 - sizeof(content::MetaLoadObject)];
	};

	class AlignedAxleConstraintProperties : public content::MetaLoadObject
	{
	public:
		AlignedAxleConstraintProperties();
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();
	
		unsigned char unknownTail[0x4C - sizeof(content::MetaLoadObject)];
	};

	class WorldBoundary : public content::MetaLoadObject
	{
	public:
		WorldBoundary();
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();
	
		unsigned char unknownTail[0x18 - sizeof(content::MetaLoadObject)];
	};

	class WorldTriggers : public content::MetaLoadObject
	{
	public:
		WorldTriggers();
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();
	
		unsigned char unknownTail[0x18 - sizeof(content::MetaLoadObject)];
	};

	class Heightmap : public content::MetaLoadObject
	{
	public:
		Heightmap();
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();
	
		unsigned char unknownTail[0x190 - sizeof(content::MetaLoadObject)];
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

	class TankSolverProperties : public content::MetaLoadObject
	{
	public:
		TankSolverProperties();
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();
	
		unsigned char unknownTail[0x20C - sizeof(content::MetaLoadObject)];
	};

	class CharacterBudgetPolicyList : public content::MetaLoadObject
	{
	public:
		CharacterBudgetPolicyList();
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();
	
		unsigned char unknownTail[0x18 - sizeof(content::MetaLoadObject)];
	};

	class VehicleWheelSuspensionProperties : public content::MetaLoadObject
	{
	public:
		VehicleWheelSuspensionProperties();
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();
	
		unsigned char unknownTail[0x1C - sizeof(content::MetaLoadObject)];
	};

	class VehicleDoorProperties : public content::MetaLoadObject
	{
	public:
		VehicleDoorProperties();
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();
	
		unsigned char unknownTail[0xC - sizeof(content::MetaLoadObject)];
	};

	class VehicleWheelList : public content::MetaLoadObject
	{
	public:
		VehicleWheelList();
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();
	
		unsigned char unknownTail[0x30 - sizeof(content::MetaLoadObject)];
	};

	class VehicleMassProperties : public content::MetaLoadObject
	{
	public:
		VehicleMassProperties();
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();
	
		unsigned char unknownTail[0x14 - sizeof(content::MetaLoadObject)];
	};

	class VehicleConstraintProperties : public content::MetaLoadObject
	{
	public:
		VehicleConstraintProperties();
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();
	
		unsigned char unknownTail[0x30 - sizeof(content::MetaLoadObject)];
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
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();
	
		unsigned char unknownTail[0x548 - sizeof(content::MetaLoadObject)];
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

	class ShoulderConFixupProperties : public content::MetaLoadObject
	{
	public:
		ShoulderConFixupProperties();
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();
	
		unsigned char unknownTail[0x18 - sizeof(content::MetaLoadObject)];
	};

	class AmbientExclusionVolume : public content::MetaLoadObject
	{
	public:
		AmbientExclusionVolume();
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();
	
		unsigned char unknownTail[0x60 - sizeof(content::MetaLoadObject)];
	};

	struct TunnelVolume : public content::MetaLoadObject
	{
	public:
		TunnelVolume();
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();
	
		unsigned char unknownTail[0x5C - sizeof(content::MetaLoadObject)];
	};

	struct IntersectionData
	{
	public:
		IntersectionData();
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();
	
		IntersectionPhase* phasesBegin;  // +0
		IntersectionPhase* phasesEnd;  // +4
		unsigned char unknown8[0x18 - 8];
	};

	struct MissileSpawnDrawSwap
	{
	public:
		MissileSpawnDrawSwap();
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();
	
		unsigned char unknown0[0x28];
	};

	class CharacterBudgetPolicy
	{
	public:
		CharacterBudgetPolicy();
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

	struct ShaderInputPatch
	{
	public:
	};

	struct ShaderInputPatchBool : public proto::ShaderInputPatch
	{
	public:
		ShaderInputPatchBool();
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();
	
		unsigned char unknownTail[0x14 - sizeof(proto::ShaderInputPatch)];
	};

	struct ShaderInputPatchFloat1 : public proto::ShaderInputPatch
	{
	public:
		ShaderInputPatchFloat1();
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();
	
		unsigned char unknownTail[0x14 - sizeof(proto::ShaderInputPatch)];
	};

	struct ShaderInputPatchFloat4 : public proto::ShaderInputPatch
	{
	public:
		ShaderInputPatchFloat4();
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();
	
		unsigned char unknownTail[0x20 - sizeof(proto::ShaderInputPatch)];
	};

	class AiTreeBehaviour : public engine::FightTreeBehaviour
	{
	public:
		explicit AiTreeBehaviour(engine::GameObject* newOwner);
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();
	
		unsigned char unknownTail[0x158 - sizeof(engine::FightTreeBehaviour)];
	};

	class CloudBehaviour : public engine::PropBehaviour
	{
	public:
		explicit CloudBehaviour(engine::GameObject* newOwner);
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();
	
		unsigned char unknownTail[0x10 - sizeof(engine::PropBehaviour)];
	};

	class SpawnerBehaviour : public engine::Behaviour
	{
	public:
	};

	class EncounterSpawnerBehaviour : public proto::SpawnerBehaviour
	{
	public:
		explicit EncounterSpawnerBehaviour(engine::GameObject* newOwner);
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();
	
		unsigned char unknownTail[0x480 - sizeof(proto::SpawnerBehaviour)];
	};

	class CloudEncounterSpawnerBehaviour : public proto::EncounterSpawnerBehaviour
	{
	public:
		explicit CloudEncounterSpawnerBehaviour(engine::GameObject* newOwner);
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();
	
		unsigned char unknownTail[0x528 - sizeof(proto::EncounterSpawnerBehaviour)];
	};

	class ConsumableBehaviour : public engine::Behaviour
	{
	public:
		explicit ConsumableBehaviour(engine::GameObject* newOwner);
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();
	
		unsigned char unknownTail[0xC0 - sizeof(engine::Behaviour)];
	};

	class CoOpBehaviour : public engine::Behaviour
	{
	public:
		explicit CoOpBehaviour(engine::GameObject* newOwner);
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();
	
		unsigned char unknownTail[0x18 - sizeof(engine::Behaviour)];
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

	class DoorTriggerBehaviour : public engine::Behaviour
	{
	public:
		explicit DoorTriggerBehaviour(engine::GameObject* newOwner);
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();
	
		unsigned char unknownTail[0xE0 - sizeof(engine::Behaviour)];
	};

	class FEDisplayBehaviour : public engine::Behaviour
	{
	public:
		explicit FEDisplayBehaviour(engine::GameObject* newOwner);
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();
	
		unsigned char unknownTail[0x24 - sizeof(engine::Behaviour)];
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

	class MobileSpawnerBehaviour : public proto::EncounterSpawnerBehaviour
	{
	public:
		explicit MobileSpawnerBehaviour(engine::GameObject* newOwner);
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();
	
		unsigned char unknownTail[0x488 - sizeof(proto::EncounterSpawnerBehaviour)];
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
	
		unsigned char unknownTail[0xE4 - sizeof(engine::Behaviour)];
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
	
		unsigned char unknownTail[0xE4 - sizeof(proto::PedBehaviour)];
	};

	class CopPedBehaviour : public proto::PedBehaviour
	{
	public:
		explicit CopPedBehaviour(engine::GameObject* newOwner);
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();
	
		unsigned char unknownTail[0xEC - sizeof(proto::PedBehaviour)];
	};

	class SoldierPedBehaviour : public proto::CopPedBehaviour
	{
	public:
		explicit SoldierPedBehaviour(engine::GameObject* newOwner);
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();
	
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

	class ShoulderConFixupBehaviour : public engine::Behaviour
	{
	public:
		explicit ShoulderConFixupBehaviour(engine::GameObject* newOwner);
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();
	
		unsigned char unknownTail[0x2C - sizeof(engine::Behaviour)];
	};

	class SquadCommanderBehaviour : public engine::Behaviour
	{
	public:
		explicit SquadCommanderBehaviour(engine::GameObject* newOwner);
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();
	
		unsigned char unknownTail[0xA0 - sizeof(engine::Behaviour)];
	};

	class SquadMemberBehaviour : public engine::Behaviour
	{
	public:
		explicit SquadMemberBehaviour(engine::GameObject* newOwner);
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();
	
		unsigned char unknownTail[0x10 - sizeof(engine::Behaviour)];
	};

	class SquadPerceptionBehaviour : public engine::Behaviour
	{
	public:
		explicit SquadPerceptionBehaviour(engine::GameObject* newOwner);
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();
	
		unsigned char unknownTail[0x1C - sizeof(engine::Behaviour)];
	};

	class SquadBlackboardBehaviour : public engine::Behaviour
	{
	public:
		explicit SquadBlackboardBehaviour(engine::GameObject* newOwner);
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();
	
		unsigned char unknownTail[0x154 - sizeof(engine::Behaviour)];
	};

	class TankSolverBehaviour : public engine::Behaviour
	{
	public:
		explicit TankSolverBehaviour(engine::GameObject* newOwner);
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();
	
		unsigned char unknownTail[0x1D8 - sizeof(engine::Behaviour)];
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

	class TokenBehaviour : public engine::Behaviour
	{
	public:
		explicit TokenBehaviour(engine::GameObject* newOwner);
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();
	
		unsigned char unknownTail[0x58 - sizeof(engine::Behaviour)];
	};

	class ScaryMonsterBehaviour : public engine::Behaviour
	{
	public:
		explicit ScaryMonsterBehaviour(engine::GameObject* newOwner);
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();
	
		unsigned char unknownTail[0x14 - sizeof(engine::Behaviour)];
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

	class VehicleConstraintsBehaviour : public engine::Behaviour
	{
	public:
		explicit VehicleConstraintsBehaviour(engine::GameObject* newOwner);
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();
	
		unsigned char unknownTail[0x1C - sizeof(engine::Behaviour)];
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

	class PowerWheelBehaviour : public engine::Behaviour
	{
	public:
		explicit PowerWheelBehaviour(engine::GameObject* newOwner);
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();
	
		unsigned char unknownTail[0x10 - sizeof(engine::Behaviour)];
	};

	class WeaponConfigurationBehaviour : public engine::Behaviour
	{
	public:
		explicit WeaponConfigurationBehaviour(engine::GameObject* newOwner);
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();
	
		unsigned char unknownTail[0x20 - sizeof(engine::Behaviour)];
	};

	class AddToHeightmapBehaviour : public engine::Behaviour
	{
	public:
		explicit AddToHeightmapBehaviour(engine::GameObject* newOwner);
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();
	
		unsigned char unknownTail[0x28 - sizeof(engine::Behaviour)];
	};

	class HelicopterRotorAnimationBehaviour : public engine::Behaviour
	{
	public:
		explicit HelicopterRotorAnimationBehaviour(engine::GameObject* newOwner);
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();
	
		unsigned char unknownTail[0x28 - sizeof(engine::Behaviour)];
	};

	class AimBehaviour : public engine::Behaviour
	{
	public:
		explicit AimBehaviour(engine::GameObject* newOwner);
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();
	
		unsigned char unknownTail[0x58 - sizeof(engine::Behaviour)];
	};

	class TankAimBehaviour : public proto::AimBehaviour
	{
	public:
		explicit TankAimBehaviour(engine::GameObject* newOwner);
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();
	
		unsigned char unknownTail[0x58 - sizeof(proto::AimBehaviour)];
	};

	class HelicopterAimBehaviour : public proto::AimBehaviour
	{
	public:
		explicit HelicopterAimBehaviour(engine::GameObject* newOwner);
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();
	
		unsigned char unknownTail[0x58 - sizeof(proto::AimBehaviour)];
	};

	class MusicTreeBehaviour : public engine::FightTreeBehaviour
	{
	public:
		explicit MusicTreeBehaviour(engine::GameObject* newOwner);
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();
	
		unsigned char unknownTail[0x70 - sizeof(engine::FightTreeBehaviour)];
	};

	class StayOnNavmeshBehaviour : public engine::Behaviour
	{
	public:
		explicit StayOnNavmeshBehaviour(engine::GameObject* newOwner);
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();
	
		unsigned char unknownTail[0x24 - sizeof(engine::Behaviour)];
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

	class CameraFloorBehaviour : public engine::Behaviour
	{
	public:
		explicit CameraFloorBehaviour(engine::GameObject* newOwner);
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();
	
		unsigned char unknownTail[0x18 - sizeof(engine::Behaviour)];
	};

}

#endif
