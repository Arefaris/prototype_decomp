// The factories and creators the proto game registers for its reflected classes (content/metafactory.h): the class meta
// type, the factory or creator and the registration function of each class, in the order the engine has them
// (0x10290630 on; no assert path names the unit, the file names are guesses).
#include "code/content/metafactory.h"
#include "code/proto/behaviours/doortriggerbehaviour.h"
#include "code/proto/behaviours/encounterspawnerbehaviour.h"
#include "code/proto/behaviours/grabbablebehaviour.h"
#include "code/proto/behaviours/grabbehaviour.h"
#include "code/proto/behaviours/poisonreactionbehaviour.h"
#include "code/proto/behaviours/shieldhitreactionbehaviour.h"
#include "code/proto/render/protocolourvariationbehaviour.h"
#include "code/proto/reflectedstubs.h"

namespace content
{
	template class MetaObjectFactory<proto::TransformationDescription, 1>;
	template ClassMetaType* GetClassMetaType<proto::TransformationDescription>();
	template void RegisterMetaObjectFactory<proto::TransformationDescription>();
	template class MetaObjectFactory<proto::AmbientNavMesh, 1>;
	template ClassMetaType* GetClassMetaType<proto::AmbientNavMesh>();
	template void RegisterMetaObjectFactory<proto::AmbientNavMesh>();
	template class MetaObjectFactory<proto::NPCAnimation, 1>;
	template ClassMetaType* GetClassMetaType<proto::NPCAnimation>();
	template void RegisterMetaObjectFactory<proto::NPCAnimation>();
	template class MetaObjectFactory<proto::NPCAnimationList, 1>;
	template ClassMetaType* GetClassMetaType<proto::NPCAnimationList>();
	template void RegisterMetaObjectFactory<proto::NPCAnimationList>();
	template class MetaObjectFactory<proto::NPCDrawable, 1>;
	template ClassMetaType* GetClassMetaType<proto::NPCDrawable>();
	template void RegisterMetaObjectFactory<proto::NPCDrawable>();
	template class MetaObjectFactory<proto::NPCInstancePool, 1>;
	template ClassMetaType* GetClassMetaType<proto::NPCInstancePool>();
	template void RegisterMetaObjectFactory<proto::NPCInstancePool>();
	template class MetaObjectFactory<proto::NPCRender, 1>;
	template ClassMetaType* GetClassMetaType<proto::NPCRender>();
	template void RegisterMetaObjectFactory<proto::NPCRender>();
	template class MetaObjectFactory<proto::NPCType, 1>;
	template ClassMetaType* GetClassMetaType<proto::NPCType>();
	template void RegisterMetaObjectFactory<proto::NPCType>();
	template class MetaObjectFactory<proto::HeliPathfindingLoader, 1>;
	template ClassMetaType* GetClassMetaType<proto::HeliPathfindingLoader>();
	template void RegisterMetaObjectFactory<proto::HeliPathfindingLoader>();
	template class MetaObjectFactory<proto::HelicopterSolverGenericProperties, 1>;
	template ClassMetaType* GetClassMetaType<proto::HelicopterSolverGenericProperties>();
	template void RegisterMetaObjectFactory<proto::HelicopterSolverGenericProperties>();
	template class MetaObjectFactory<proto::HelicopterSolverProperties, 1>;
	template ClassMetaType* GetClassMetaType<proto::HelicopterSolverProperties>();
	template void RegisterMetaObjectFactory<proto::HelicopterSolverProperties>();
	template class MetaObjectFactory<proto::WheelConstraintParams, 1>;
	template ClassMetaType* GetClassMetaType<proto::WheelConstraintParams>();
	template void RegisterMetaObjectFactory<proto::WheelConstraintParams>();
	template class MetaObjectFactory<proto::AlignedAxleConstraintProperties, 1>;
	template ClassMetaType* GetClassMetaType<proto::AlignedAxleConstraintProperties>();
	template void RegisterMetaObjectFactory<proto::AlignedAxleConstraintProperties>();
	template class MetaObjectFactory<proto::WorldBoundary, 1>;
	template ClassMetaType* GetClassMetaType<proto::WorldBoundary>();
	template void RegisterMetaObjectFactory<proto::WorldBoundary>();
	template class MetaObjectFactory<proto::WorldTriggers, 1>;
	template ClassMetaType* GetClassMetaType<proto::WorldTriggers>();
	template void RegisterMetaObjectFactory<proto::WorldTriggers>();
	template class MetaObjectFactory<proto::Heightmap, 1>;
	template ClassMetaType* GetClassMetaType<proto::Heightmap>();
	template void RegisterMetaObjectFactory<proto::Heightmap>();
	template class MetaObjectFactory<proto::DisguiseConfig, 1>;
	template ClassMetaType* GetClassMetaType<proto::DisguiseConfig>();
	template void RegisterMetaObjectFactory<proto::DisguiseConfig>();
	template class MetaObjectFactory<proto::BulletTracerProfile, 1>;
	template ClassMetaType* GetClassMetaType<proto::BulletTracerProfile>();
	template void RegisterMetaObjectFactory<proto::BulletTracerProfile>();
	template class MetaObjectFactory<proto::VehicleSpawner, 1>;
	template ClassMetaType* GetClassMetaType<proto::VehicleSpawner>();
	template void RegisterMetaObjectFactory<proto::VehicleSpawner>();
	template class MetaObjectFactory<proto::PedestrianSpawner, 1>;
	template ClassMetaType* GetClassMetaType<proto::PedestrianSpawner>();
	template void RegisterMetaObjectFactory<proto::PedestrianSpawner>();
	template class MetaObjectFactory<proto::TankSolverProperties, 1>;
	template ClassMetaType* GetClassMetaType<proto::TankSolverProperties>();
	template void RegisterMetaObjectFactory<proto::TankSolverProperties>();
	template class MetaObjectFactory<proto::CharacterBudgetPolicyList, 1>;
	template ClassMetaType* GetClassMetaType<proto::CharacterBudgetPolicyList>();
	template void RegisterMetaObjectFactory<proto::CharacterBudgetPolicyList>();
	template class MetaObjectFactory<proto::VehicleWheelSuspensionProperties, 1>;
	template ClassMetaType* GetClassMetaType<proto::VehicleWheelSuspensionProperties>();
	template void RegisterMetaObjectFactory<proto::VehicleWheelSuspensionProperties>();
	template class MetaObjectFactory<proto::VehicleDoorProperties, 1>;
	template ClassMetaType* GetClassMetaType<proto::VehicleDoorProperties>();
	template void RegisterMetaObjectFactory<proto::VehicleDoorProperties>();
	template class MetaObjectFactory<proto::VehicleWheelList, 1>;
	template ClassMetaType* GetClassMetaType<proto::VehicleWheelList>();
	template void RegisterMetaObjectFactory<proto::VehicleWheelList>();
	template class MetaObjectFactory<proto::VehicleMassProperties, 1>;
	template ClassMetaType* GetClassMetaType<proto::VehicleMassProperties>();
	template void RegisterMetaObjectFactory<proto::VehicleMassProperties>();
	template class MetaObjectFactory<proto::VehicleConstraintProperties, 1>;
	template ClassMetaType* GetClassMetaType<proto::VehicleConstraintProperties>();
	template void RegisterMetaObjectFactory<proto::VehicleConstraintProperties>();
	template class MetaObjectFactory<proto::LightDecalInfo, 1>;
	template ClassMetaType* GetClassMetaType<proto::LightDecalInfo>();
	template void RegisterMetaObjectFactory<proto::LightDecalInfo>();
	template class MetaObjectFactory<proto::PedBehaviourTunables, 1>;
	template ClassMetaType* GetClassMetaType<proto::PedBehaviourTunables>();
	template void RegisterMetaObjectFactory<proto::PedBehaviourTunables>();
	template class MetaObjectFactory<proto::ConsumableProperties, 1>;
	template ClassMetaType* GetClassMetaType<proto::ConsumableProperties>();
	template void RegisterMetaObjectFactory<proto::ConsumableProperties>();
	template class MetaObjectFactory<proto::WeaponUserProfile, 1>;
	template ClassMetaType* GetClassMetaType<proto::WeaponUserProfile>();
	template void RegisterMetaObjectFactory<proto::WeaponUserProfile>();
	template class MetaObjectFactory<proto::GunAmmoProfile, 1>;
	template ClassMetaType* GetClassMetaType<proto::GunAmmoProfile>();
	template void RegisterMetaObjectFactory<proto::GunAmmoProfile>();
	template class MetaObjectFactory<proto::MissileProfile, 1>;
	template ClassMetaType* GetClassMetaType<proto::MissileProfile>();
	template void RegisterMetaObjectFactory<proto::MissileProfile>();
	template class MetaObjectFactory<proto::MissileSpin, 1>;
	template ClassMetaType* GetClassMetaType<proto::MissileSpin>();
	template void RegisterMetaObjectFactory<proto::MissileSpin>();
	template class MetaObjectFactory<proto::MissileSpawnProfile, 1>;
	template ClassMetaType* GetClassMetaType<proto::MissileSpawnProfile>();
	template void RegisterMetaObjectFactory<proto::MissileSpawnProfile>();
	template class MetaObjectFactory<proto::FadeoutBehaviourProperties, 1>;
	template ClassMetaType* GetClassMetaType<proto::FadeoutBehaviourProperties>();
	template void RegisterMetaObjectFactory<proto::FadeoutBehaviourProperties>();
	template class MetaObjectFactory<proto::ShoulderConFixupProperties, 1>;
	template ClassMetaType* GetClassMetaType<proto::ShoulderConFixupProperties>();
	template void RegisterMetaObjectFactory<proto::ShoulderConFixupProperties>();
	template class MetaObjectFactory<proto::AmbientExclusionVolume, 1>;
	template ClassMetaType* GetClassMetaType<proto::AmbientExclusionVolume>();
	template void RegisterMetaObjectFactory<proto::AmbientExclusionVolume>();
	template class MetaObjectFactory<proto::TunnelVolume, 1>;
	template ClassMetaType* GetClassMetaType<proto::TunnelVolume>();
	template void RegisterMetaObjectFactory<proto::TunnelVolume>();
	template class MetaObjectFactory<proto::WebNodeLocator, 1>;
	template ClassMetaType* GetClassMetaType<proto::WebNodeLocator>();
	template void RegisterMetaObjectFactory<proto::WebNodeLocator>();
	template class MetaInstanceCreatorImpl<proto::MissileSpawnDrawSwap, 1>;
	template ClassMetaType* GetClassMetaType<proto::MissileSpawnDrawSwap>();
	template void RegisterMetaInstanceCreator<proto::MissileSpawnDrawSwap>();
	template class MetaInstanceCreatorImpl<proto::CharacterBudgetPolicy, 1>;
	template ClassMetaType* GetClassMetaType<proto::CharacterBudgetPolicy>();
	template void RegisterMetaInstanceCreator<proto::CharacterBudgetPolicy>();
	template class MetaInstanceCreatorImpl<proto::PatrolPoint, 1>;
	template ClassMetaType* GetClassMetaType<proto::PatrolPoint>();
	template void RegisterMetaInstanceCreator<proto::PatrolPoint>();
	template ClassMetaType* GetClassMetaType<proto::AiTreeBehaviour>();
	template ClassMetaType* GetClassMetaType<proto::CloudBehaviour>();
	template ClassMetaType* GetClassMetaType<proto::CloudEncounterSpawnerBehaviour>();
	template ClassMetaType* GetClassMetaType<proto::ConsumableBehaviour>();
	template ClassMetaType* GetClassMetaType<proto::CoOpBehaviour>();
	template ClassMetaType* GetClassMetaType<proto::DisguiseBehaviour>();
	template ClassMetaType* GetClassMetaType<proto::EmotionalStateBehaviour>();
	template ClassMetaType* GetClassMetaType<proto::EncounterSpawnerBehaviour>();
	template ClassMetaType* GetClassMetaType<proto::DoorTriggerBehaviour>();
	template ClassMetaType* GetClassMetaType<proto::FEDisplayBehaviour>();
	template ClassMetaType* GetClassMetaType<proto::FlyingBehaviour>();
	template ClassMetaType* GetClassMetaType<proto::GrabbableBehaviour>();
	template ClassMetaType* GetClassMetaType<proto::GrabbableStaticBehaviour>();
	template ClassMetaType* GetClassMetaType<proto::GrabBehaviour>();
	template ClassMetaType* GetClassMetaType<proto::GrabAutoSpawnBehaviour>();
	template ClassMetaType* GetClassMetaType<proto::GunBehaviour>();
	template ClassMetaType* GetClassMetaType<proto::HelicopterSolverBehaviour>();
	template ClassMetaType* GetClassMetaType<proto::LODAIBehaviour>();
	template ClassMetaType* GetClassMetaType<proto::AttachBillboardBehaviour>();
	template ClassMetaType* GetClassMetaType<proto::MobileSpawnerBehaviour>();
	template ClassMetaType* GetClassMetaType<proto::ProtoColourVariationBehaviour>();
	template ClassMetaType* GetClassMetaType<proto::LightDecalBehaviour>();
	template ClassMetaType* GetClassMetaType<proto::MissileBehaviour>();
	template ClassMetaType* GetClassMetaType<proto::BombBehaviour>();
	template ClassMetaType* GetClassMetaType<proto::DiscardedFirearmBehaviour>();
	template ClassMetaType* GetClassMetaType<proto::JavelinMissileBehaviour>();
	template ClassMetaType* GetClassMetaType<proto::MissileSpawnerBehaviour>();
	template ClassMetaType* GetClassMetaType<proto::RandomDeadPedBehaviour>();
	template ClassMetaType* GetClassMetaType<proto::PedBehaviour>();
	template ClassMetaType* GetClassMetaType<proto::AlertBehaviour>();
	template ClassMetaType* GetClassMetaType<proto::CharacterPedBehaviour>();
	template ClassMetaType* GetClassMetaType<proto::InfectedPedBehaviour>();
	template ClassMetaType* GetClassMetaType<proto::CopPedBehaviour>();
	template ClassMetaType* GetClassMetaType<proto::SoldierPedBehaviour>();
	template ClassMetaType* GetClassMetaType<proto::PerceptionBehaviour>();
	template ClassMetaType* GetClassMetaType<proto::ShieldHitReactionBehaviour>();
	template ClassMetaType* GetClassMetaType<proto::ShoulderConFixupBehaviour>();
	template ClassMetaType* GetClassMetaType<proto::SquadCommanderBehaviour>();
	template ClassMetaType* GetClassMetaType<proto::SquadMemberBehaviour>();
	template ClassMetaType* GetClassMetaType<proto::SquadPerceptionBehaviour>();
	template ClassMetaType* GetClassMetaType<proto::SquadBlackboardBehaviour>();
	template ClassMetaType* GetClassMetaType<proto::TankSolverBehaviour>();
	template ClassMetaType* GetClassMetaType<proto::ThreatBallBehaviour>();
	template ClassMetaType* GetClassMetaType<proto::ThreatReceiverBehaviour>();
	template ClassMetaType* GetClassMetaType<proto::TransformationBehaviour>();
	template ClassMetaType* GetClassMetaType<proto::VehicleBehaviourAICharacter>();
	template ClassMetaType* GetClassMetaType<proto::AIFlyingPatrolBehaviour>();
	template ClassMetaType* GetClassMetaType<proto::WalkingBehaviour>();
	template ClassMetaType* GetClassMetaType<proto::TankMovementBehaviour>();
	template ClassMetaType* GetClassMetaType<proto::HelicopterMovementBehaviour>();
	template ClassMetaType* GetClassMetaType<proto::HunterMovementBehaviour>();
	template ClassMetaType* GetClassMetaType<proto::TokenBehaviour>();
	template ClassMetaType* GetClassMetaType<proto::ScaryMonsterBehaviour>();
	template ClassMetaType* GetClassMetaType<proto::DriverBehaviour>();
	template ClassMetaType* GetClassMetaType<proto::TestWalkBehaviour>();
	template ClassMetaType* GetClassMetaType<proto::ExpiryTimeBehaviour>();
	template ClassMetaType* GetClassMetaType<proto::ThreatBehaviour>();
	template ClassMetaType* GetClassMetaType<proto::HydraMovementBehaviour>();
	template ClassMetaType* GetClassMetaType<proto::VehicleConstraintsBehaviour>();
	template ClassMetaType* GetClassMetaType<proto::GrabSelectionBehaviour>();
	template ClassMetaType* GetClassMetaType<proto::NPCRenderBehaviour>();
	template ClassMetaType* GetClassMetaType<proto::BloodtoxBehaviour>();
	template ClassMetaType* GetClassMetaType<proto::PoisonReactionBehaviour>();
	template ClassMetaType* GetClassMetaType<proto::FormationBehaviour>();
	template ClassMetaType* GetClassMetaType<proto::StayOnRooftopBehaviour>();
	template ClassMetaType* GetClassMetaType<proto::WaterTowerBehaviour>();
	template ClassMetaType* GetClassMetaType<proto::PowerWheelBehaviour>();
	template ClassMetaType* GetClassMetaType<proto::WeaponConfigurationBehaviour>();
	template ClassMetaType* GetClassMetaType<proto::AddToHeightmapBehaviour>();
	template ClassMetaType* GetClassMetaType<proto::HelicopterRotorAnimationBehaviour>();
	template ClassMetaType* GetClassMetaType<proto::AimBehaviour>();
	template ClassMetaType* GetClassMetaType<proto::TankAimBehaviour>();
	template ClassMetaType* GetClassMetaType<proto::HelicopterAimBehaviour>();
	template ClassMetaType* GetClassMetaType<proto::MusicTreeBehaviour>();
	template ClassMetaType* GetClassMetaType<proto::StayOnNavmeshBehaviour>();
	template ClassMetaType* GetClassMetaType<proto::FadeoutBehaviour>();
	template ClassMetaType* GetClassMetaType<proto::FadeBehaviour>();
	template ClassMetaType* GetClassMetaType<proto::FreeAimingBehaviour>();
	template ClassMetaType* GetClassMetaType<proto::BridgeCameraBehaviour>();
	template ClassMetaType* GetClassMetaType<proto::DrivableVehicleHealthModifierBehaviour>();
	template ClassMetaType* GetClassMetaType<proto::CameraFloorBehaviour>();
}

namespace engine
{
	template class MetaBehaviourCreatorImpl<proto::AiTreeBehaviour>;
	template void RegisterMetaBehaviourCreator<proto::AiTreeBehaviour>();
	template class MetaBehaviourCreatorImpl<proto::CloudBehaviour>;
	template void RegisterMetaBehaviourCreator<proto::CloudBehaviour>();
	template class MetaBehaviourCreatorImpl<proto::CloudEncounterSpawnerBehaviour>;
	template void RegisterMetaBehaviourCreator<proto::CloudEncounterSpawnerBehaviour>();
	template class MetaBehaviourCreatorImpl<proto::ConsumableBehaviour>;
	template void RegisterMetaBehaviourCreator<proto::ConsumableBehaviour>();
	template class MetaBehaviourCreatorImpl<proto::CoOpBehaviour>;
	template void RegisterMetaBehaviourCreator<proto::CoOpBehaviour>();
	template class MetaBehaviourCreatorImpl<proto::DisguiseBehaviour>;
	template void RegisterMetaBehaviourCreator<proto::DisguiseBehaviour>();
	template class MetaBehaviourCreatorImpl<proto::EmotionalStateBehaviour>;
	template void RegisterMetaBehaviourCreator<proto::EmotionalStateBehaviour>();
	template class MetaBehaviourCreatorImpl<proto::EncounterSpawnerBehaviour>;
	template void RegisterMetaBehaviourCreator<proto::EncounterSpawnerBehaviour>();
	template class MetaBehaviourCreatorImpl<proto::DoorTriggerBehaviour>;
	template void RegisterMetaBehaviourCreator<proto::DoorTriggerBehaviour>();
	template class MetaBehaviourCreatorImpl<proto::FEDisplayBehaviour>;
	template void RegisterMetaBehaviourCreator<proto::FEDisplayBehaviour>();
	template class MetaBehaviourCreatorImpl<proto::FlyingBehaviour>;
	template void RegisterMetaBehaviourCreator<proto::FlyingBehaviour>();
	template class MetaBehaviourCreatorImpl<proto::GrabbableBehaviour>;
	template void RegisterMetaBehaviourCreator<proto::GrabbableBehaviour>();
	template class MetaBehaviourCreatorImpl<proto::GrabbableStaticBehaviour>;
	template void RegisterMetaBehaviourCreator<proto::GrabbableStaticBehaviour>();
	template class MetaBehaviourCreatorImpl<proto::GrabBehaviour>;
	template void RegisterMetaBehaviourCreator<proto::GrabBehaviour>();
	template class MetaBehaviourCreatorImpl<proto::GrabAutoSpawnBehaviour>;
	template void RegisterMetaBehaviourCreator<proto::GrabAutoSpawnBehaviour>();
	template class MetaBehaviourCreatorImpl<proto::GunBehaviour>;
	template void RegisterMetaBehaviourCreator<proto::GunBehaviour>();
	template class MetaBehaviourCreatorImpl<proto::HelicopterSolverBehaviour>;
	template void RegisterMetaBehaviourCreator<proto::HelicopterSolverBehaviour>();
	template class MetaBehaviourCreatorImpl<proto::LODAIBehaviour>;
	template void RegisterMetaBehaviourCreator<proto::LODAIBehaviour>();
	template class MetaBehaviourCreatorImpl<proto::AttachBillboardBehaviour>;
	template void RegisterMetaBehaviourCreator<proto::AttachBillboardBehaviour>();
	template class MetaBehaviourCreatorImpl<proto::MobileSpawnerBehaviour>;
	template void RegisterMetaBehaviourCreator<proto::MobileSpawnerBehaviour>();
	template class MetaBehaviourCreatorImpl<proto::ProtoColourVariationBehaviour>;
	template void RegisterMetaBehaviourCreator<proto::ProtoColourVariationBehaviour>();
	template class MetaBehaviourCreatorImpl<proto::LightDecalBehaviour>;
	template void RegisterMetaBehaviourCreator<proto::LightDecalBehaviour>();
	template class MetaBehaviourCreatorImpl<proto::MissileBehaviour>;
	template void RegisterMetaBehaviourCreator<proto::MissileBehaviour>();
	template class MetaBehaviourCreatorImpl<proto::BombBehaviour>;
	template void RegisterMetaBehaviourCreator<proto::BombBehaviour>();
	template class MetaBehaviourCreatorImpl<proto::DiscardedFirearmBehaviour>;
	template void RegisterMetaBehaviourCreator<proto::DiscardedFirearmBehaviour>();
	template class MetaBehaviourCreatorImpl<proto::JavelinMissileBehaviour>;
	template void RegisterMetaBehaviourCreator<proto::JavelinMissileBehaviour>();
	template class MetaBehaviourCreatorImpl<proto::MissileSpawnerBehaviour>;
	template void RegisterMetaBehaviourCreator<proto::MissileSpawnerBehaviour>();
	template class MetaBehaviourCreatorImpl<proto::RandomDeadPedBehaviour>;
	template void RegisterMetaBehaviourCreator<proto::RandomDeadPedBehaviour>();
	template class MetaBehaviourCreatorImpl<proto::PedBehaviour>;
	template void RegisterMetaBehaviourCreator<proto::PedBehaviour>();
	template class MetaBehaviourCreatorImpl<proto::AlertBehaviour>;
	template void RegisterMetaBehaviourCreator<proto::AlertBehaviour>();
	template class MetaBehaviourCreatorImpl<proto::CharacterPedBehaviour>;
	template void RegisterMetaBehaviourCreator<proto::CharacterPedBehaviour>();
	template class MetaBehaviourCreatorImpl<proto::InfectedPedBehaviour>;
	template void RegisterMetaBehaviourCreator<proto::InfectedPedBehaviour>();
	template class MetaBehaviourCreatorImpl<proto::CopPedBehaviour>;
	template void RegisterMetaBehaviourCreator<proto::CopPedBehaviour>();
	template class MetaBehaviourCreatorImpl<proto::SoldierPedBehaviour>;
	template void RegisterMetaBehaviourCreator<proto::SoldierPedBehaviour>();
	template class MetaBehaviourCreatorImpl<proto::PerceptionBehaviour>;
	template void RegisterMetaBehaviourCreator<proto::PerceptionBehaviour>();
	template class MetaBehaviourCreatorImpl<proto::ShieldHitReactionBehaviour>;
	template void RegisterMetaBehaviourCreator<proto::ShieldHitReactionBehaviour>();
	template class MetaBehaviourCreatorImpl<proto::ShoulderConFixupBehaviour>;
	template void RegisterMetaBehaviourCreator<proto::ShoulderConFixupBehaviour>();
	template class MetaBehaviourCreatorImpl<proto::SquadCommanderBehaviour>;
	template void RegisterMetaBehaviourCreator<proto::SquadCommanderBehaviour>();
	template class MetaBehaviourCreatorImpl<proto::SquadMemberBehaviour>;
	template void RegisterMetaBehaviourCreator<proto::SquadMemberBehaviour>();
	template class MetaBehaviourCreatorImpl<proto::SquadPerceptionBehaviour>;
	template void RegisterMetaBehaviourCreator<proto::SquadPerceptionBehaviour>();
	template class MetaBehaviourCreatorImpl<proto::SquadBlackboardBehaviour>;
	template void RegisterMetaBehaviourCreator<proto::SquadBlackboardBehaviour>();
	template class MetaBehaviourCreatorImpl<proto::TankSolverBehaviour>;
	template void RegisterMetaBehaviourCreator<proto::TankSolverBehaviour>();
	template class MetaBehaviourCreatorImpl<proto::ThreatBallBehaviour>;
	template void RegisterMetaBehaviourCreator<proto::ThreatBallBehaviour>();
	template class MetaBehaviourCreatorImpl<proto::ThreatReceiverBehaviour>;
	template void RegisterMetaBehaviourCreator<proto::ThreatReceiverBehaviour>();
	template class MetaBehaviourCreatorImpl<proto::TransformationBehaviour>;
	template void RegisterMetaBehaviourCreator<proto::TransformationBehaviour>();
	template class MetaBehaviourCreatorImpl<proto::VehicleBehaviourAICharacter>;
	template void RegisterMetaBehaviourCreator<proto::VehicleBehaviourAICharacter>();
	template class MetaBehaviourCreatorImpl<proto::AIFlyingPatrolBehaviour>;
	template void RegisterMetaBehaviourCreator<proto::AIFlyingPatrolBehaviour>();
	template class MetaBehaviourCreatorImpl<proto::WalkingBehaviour>;
	template void RegisterMetaBehaviourCreator<proto::WalkingBehaviour>();
	template class MetaBehaviourCreatorImpl<proto::TankMovementBehaviour>;
	template void RegisterMetaBehaviourCreator<proto::TankMovementBehaviour>();
	template class MetaBehaviourCreatorImpl<proto::HelicopterMovementBehaviour>;
	template void RegisterMetaBehaviourCreator<proto::HelicopterMovementBehaviour>();
	template class MetaBehaviourCreatorImpl<proto::HunterMovementBehaviour>;
	template void RegisterMetaBehaviourCreator<proto::HunterMovementBehaviour>();
	template class MetaBehaviourCreatorImpl<proto::TokenBehaviour>;
	template void RegisterMetaBehaviourCreator<proto::TokenBehaviour>();
	template class MetaBehaviourCreatorImpl<proto::ScaryMonsterBehaviour>;
	template void RegisterMetaBehaviourCreator<proto::ScaryMonsterBehaviour>();
	template class MetaBehaviourCreatorImpl<proto::DriverBehaviour>;
	template void RegisterMetaBehaviourCreator<proto::DriverBehaviour>();
	template class MetaBehaviourCreatorImpl<proto::TestWalkBehaviour>;
	template void RegisterMetaBehaviourCreator<proto::TestWalkBehaviour>();
	template class MetaBehaviourCreatorImpl<proto::ExpiryTimeBehaviour>;
	template void RegisterMetaBehaviourCreator<proto::ExpiryTimeBehaviour>();
	template class MetaBehaviourCreatorImpl<proto::ThreatBehaviour>;
	template void RegisterMetaBehaviourCreator<proto::ThreatBehaviour>();
	template class MetaBehaviourCreatorImpl<proto::HydraMovementBehaviour>;
	template void RegisterMetaBehaviourCreator<proto::HydraMovementBehaviour>();
	template class MetaBehaviourCreatorImpl<proto::VehicleConstraintsBehaviour>;
	template void RegisterMetaBehaviourCreator<proto::VehicleConstraintsBehaviour>();
	template class MetaBehaviourCreatorImpl<proto::GrabSelectionBehaviour>;
	template void RegisterMetaBehaviourCreator<proto::GrabSelectionBehaviour>();
	template class MetaBehaviourCreatorImpl<proto::NPCRenderBehaviour>;
	template void RegisterMetaBehaviourCreator<proto::NPCRenderBehaviour>();
	template class MetaBehaviourCreatorImpl<proto::BloodtoxBehaviour>;
	template void RegisterMetaBehaviourCreator<proto::BloodtoxBehaviour>();
	template class MetaBehaviourCreatorImpl<proto::PoisonReactionBehaviour>;
	template void RegisterMetaBehaviourCreator<proto::PoisonReactionBehaviour>();
	template class MetaBehaviourCreatorImpl<proto::FormationBehaviour>;
	template void RegisterMetaBehaviourCreator<proto::FormationBehaviour>();
	template class MetaBehaviourCreatorImpl<proto::StayOnRooftopBehaviour>;
	template void RegisterMetaBehaviourCreator<proto::StayOnRooftopBehaviour>();
	template class MetaBehaviourCreatorImpl<proto::WaterTowerBehaviour>;
	template void RegisterMetaBehaviourCreator<proto::WaterTowerBehaviour>();
	template class MetaBehaviourCreatorImpl<proto::PowerWheelBehaviour>;
	template void RegisterMetaBehaviourCreator<proto::PowerWheelBehaviour>();
	template class MetaBehaviourCreatorImpl<proto::WeaponConfigurationBehaviour>;
	template void RegisterMetaBehaviourCreator<proto::WeaponConfigurationBehaviour>();
	template class MetaBehaviourCreatorImpl<proto::AddToHeightmapBehaviour>;
	template void RegisterMetaBehaviourCreator<proto::AddToHeightmapBehaviour>();
	template class MetaBehaviourCreatorImpl<proto::HelicopterRotorAnimationBehaviour>;
	template void RegisterMetaBehaviourCreator<proto::HelicopterRotorAnimationBehaviour>();
	template class MetaBehaviourCreatorImpl<proto::AimBehaviour>;
	template void RegisterMetaBehaviourCreator<proto::AimBehaviour>();
	template class MetaBehaviourCreatorImpl<proto::TankAimBehaviour>;
	template void RegisterMetaBehaviourCreator<proto::TankAimBehaviour>();
	template class MetaBehaviourCreatorImpl<proto::HelicopterAimBehaviour>;
	template void RegisterMetaBehaviourCreator<proto::HelicopterAimBehaviour>();
	template class MetaBehaviourCreatorImpl<proto::MusicTreeBehaviour>;
	template void RegisterMetaBehaviourCreator<proto::MusicTreeBehaviour>();
	template class MetaBehaviourCreatorImpl<proto::StayOnNavmeshBehaviour>;
	template void RegisterMetaBehaviourCreator<proto::StayOnNavmeshBehaviour>();
	template class MetaBehaviourCreatorImpl<proto::FadeoutBehaviour>;
	template void RegisterMetaBehaviourCreator<proto::FadeoutBehaviour>();
	template class MetaBehaviourCreatorImpl<proto::FadeBehaviour>;
	template void RegisterMetaBehaviourCreator<proto::FadeBehaviour>();
	template class MetaBehaviourCreatorImpl<proto::FreeAimingBehaviour>;
	template void RegisterMetaBehaviourCreator<proto::FreeAimingBehaviour>();
	template class MetaBehaviourCreatorImpl<proto::BridgeCameraBehaviour>;
	template void RegisterMetaBehaviourCreator<proto::BridgeCameraBehaviour>();
	template class MetaBehaviourCreatorImpl<proto::DrivableVehicleHealthModifierBehaviour>;
	template void RegisterMetaBehaviourCreator<proto::DrivableVehicleHealthModifierBehaviour>();
	template class MetaBehaviourCreatorImpl<proto::CameraFloorBehaviour>;
	template void RegisterMetaBehaviourCreator<proto::CameraFloorBehaviour>();
}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x10290820
// FUNCTION: ENGINE 0x10290880
// FUNCTION: ENGINE 0x102908B0
// FUNCTION: ENGINE 0x102908D0
// FUNCTION: ENGINE 0x10290930
// FUNCTION: ENGINE 0x10290960
// FUNCTION: ENGINE 0x10290A10
// FUNCTION: ENGINE 0x10290A70
// FUNCTION: ENGINE 0x10290AA0
// FUNCTION: ENGINE 0x10290AC0
// FUNCTION: ENGINE 0x10290B20
// FUNCTION: ENGINE 0x10290B50
// FUNCTION: ENGINE 0x10290B80
// FUNCTION: ENGINE 0x10290BE0
// FUNCTION: ENGINE 0x10290C10
// FUNCTION: ENGINE 0x10290C30
// FUNCTION: ENGINE 0x10290C90
// FUNCTION: ENGINE 0x10290CC0
// FUNCTION: ENGINE 0x10290CE0
// FUNCTION: ENGINE 0x10290D40
// FUNCTION: ENGINE 0x10290D70
// FUNCTION: ENGINE 0x10290D90
// FUNCTION: ENGINE 0x10290DF0
// FUNCTION: ENGINE 0x10290E20
// FUNCTION: ENGINE 0x10290E40
// FUNCTION: ENGINE 0x10290EA0
// FUNCTION: ENGINE 0x10290ED0
// FUNCTION: ENGINE 0x10291050
// FUNCTION: ENGINE 0x102910B0
// FUNCTION: ENGINE 0x102910E0
// FUNCTION: ENGINE 0x10291110
// FUNCTION: ENGINE 0x10291170
// FUNCTION: ENGINE 0x102911A0
// FUNCTION: ENGINE 0x102911D0
// FUNCTION: ENGINE 0x10291230
// FUNCTION: ENGINE 0x10291260
// FUNCTION: ENGINE 0x10291280
// FUNCTION: ENGINE 0x102912E0
// FUNCTION: ENGINE 0x10291310
// FUNCTION: ENGINE 0x10291330
// FUNCTION: ENGINE 0x10291390
// FUNCTION: ENGINE 0x102913C0
// FUNCTION: ENGINE 0x102913E0
// FUNCTION: ENGINE 0x10291440
// FUNCTION: ENGINE 0x10291470
// FUNCTION: ENGINE 0x10291490
// FUNCTION: ENGINE 0x102914F0
// FUNCTION: ENGINE 0x10291520
// FUNCTION: ENGINE 0x10291550
// FUNCTION: ENGINE 0x102915B0
// FUNCTION: ENGINE 0x102915E0
// FUNCTION: ENGINE 0x102918F0
// FUNCTION: ENGINE 0x10291950
// FUNCTION: ENGINE 0x10291980
// FUNCTION: ENGINE 0x102919E0
// FUNCTION: ENGINE 0x10291A10
// FUNCTION: ENGINE 0x10291A30
// FUNCTION: ENGINE 0x10291A90
// FUNCTION: ENGINE 0x10291AC0
// FUNCTION: ENGINE 0x10291AE0
// FUNCTION: ENGINE 0x10291B40
// FUNCTION: ENGINE 0x10291B70
// FUNCTION: ENGINE 0x10291F00
// FUNCTION: ENGINE 0x10291F60
// FUNCTION: ENGINE 0x10291F90
// FUNCTION: ENGINE 0x10291FB0
// FUNCTION: ENGINE 0x10292010
// FUNCTION: ENGINE 0x10292040
// FUNCTION: ENGINE 0x10292060
// FUNCTION: ENGINE 0x102920C0
// FUNCTION: ENGINE 0x102920F0
// FUNCTION: ENGINE 0x10292110
// FUNCTION: ENGINE 0x10292170
// FUNCTION: ENGINE 0x102921A0
// FUNCTION: ENGINE 0x102921C0
// FUNCTION: ENGINE 0x10292220
// FUNCTION: ENGINE 0x10292250
// FUNCTION: ENGINE 0x10292270
// FUNCTION: ENGINE 0x102922D0
// FUNCTION: ENGINE 0x10292300
// FUNCTION: ENGINE 0x10292320
// FUNCTION: ENGINE 0x10292380
// FUNCTION: ENGINE 0x102923B0
// FUNCTION: ENGINE 0x102923D0
// FUNCTION: ENGINE 0x10292430
// FUNCTION: ENGINE 0x10292460
// FUNCTION: ENGINE 0x102927A0
// FUNCTION: ENGINE 0x10292800
// FUNCTION: ENGINE 0x10292830
// FUNCTION: ENGINE 0x10292850
// FUNCTION: ENGINE 0x102928B0
// FUNCTION: ENGINE 0x102928E0
// FUNCTION: ENGINE 0x10292910
// FUNCTION: ENGINE 0x10292970
// FUNCTION: ENGINE 0x102929A0
// FUNCTION: ENGINE 0x102929C0
// FUNCTION: ENGINE 0x10292A20
// FUNCTION: ENGINE 0x10292A50
// FUNCTION: ENGINE 0x10292A80
// FUNCTION: ENGINE 0x10292AE0
// FUNCTION: ENGINE 0x10292B10
// FUNCTION: ENGINE 0x10292B30
// FUNCTION: ENGINE 0x10292B90
// FUNCTION: ENGINE 0x10292BC0
// FUNCTION: ENGINE 0x10292C90
// FUNCTION: ENGINE 0x10292CF0
// FUNCTION: ENGINE 0x10292D20
// FUNCTION: ENGINE 0x10292D40
// FUNCTION: ENGINE 0x10292DA0
// FUNCTION: ENGINE 0x10292DD0
// FUNCTION: ENGINE 0x10292DF0
// FUNCTION: ENGINE 0x10292E50
// FUNCTION: ENGINE 0x10292E80
// FUNCTION: ENGINE 0x10292EA0
// FUNCTION: ENGINE 0x10292F00
// FUNCTION: ENGINE 0x10292F30
// FUNCTION: ENGINE 0x10293000
// FUNCTION: ENGINE 0x10293060
// FUNCTION: ENGINE 0x10293090
// FUNCTION: ENGINE 0x102935B0
// FUNCTION: ENGINE 0x10293610
// FUNCTION: ENGINE 0x10293640
// FUNCTION: ENGINE 0x10293660
// FUNCTION: ENGINE 0x102936C0
// FUNCTION: ENGINE 0x102936F0
// FUNCTION: ENGINE 0x10293710
// FUNCTION: ENGINE 0x10293770
// FUNCTION: ENGINE 0x102937A0
// FUNCTION: ENGINE 0x10293D30
// FUNCTION: ENGINE 0x10293D90
// FUNCTION: ENGINE 0x10293DC0
// FUNCTION: ENGINE 0x10294010
// FUNCTION: ENGINE 0x10294070
// FUNCTION: ENGINE 0x102940A0
// FUNCTION: ENGINE 0x102940C0
// FUNCTION: ENGINE 0x10294120
// FUNCTION: ENGINE 0x10294150
// FUNCTION: ENGINE 0x10294230
// FUNCTION: ENGINE 0x10294290
// FUNCTION: ENGINE 0x102942C0
// FUNCTION: ENGINE 0x102942F0
// FUNCTION: ENGINE 0x10294350
// FUNCTION: ENGINE 0x10294380
// FUNCTION: ENGINE 0x10294450
// FUNCTION: ENGINE 0x102944B0
// FUNCTION: ENGINE 0x102944E0
// FUNCTION: ENGINE 0x10294510
// FUNCTION: ENGINE 0x10294570
// FUNCTION: ENGINE 0x102945A0
// FUNCTION: ENGINE 0x102945C0
// FUNCTION: ENGINE 0x10294620
// FUNCTION: ENGINE 0x10294650
// FUNCTION: ENGINE 0x10294680
// FUNCTION: ENGINE 0x102946E0
// FUNCTION: ENGINE 0x10294710
// FUNCTION: ENGINE 0x10294740
// FUNCTION: ENGINE 0x102947A0
// FUNCTION: ENGINE 0x102947D0
// FUNCTION: ENGINE 0x102948A0
// FUNCTION: ENGINE 0x10294900
// FUNCTION: ENGINE 0x10294930
// FUNCTION: ENGINE 0x10294960
// FUNCTION: ENGINE 0x102949C0
// FUNCTION: ENGINE 0x102949F0
// FUNCTION: ENGINE 0x10294A10
// FUNCTION: ENGINE 0x10294A70
// FUNCTION: ENGINE 0x10294AA0
// FUNCTION: ENGINE 0x10294AD0
// FUNCTION: ENGINE 0x10294B30
// FUNCTION: ENGINE 0x10294B60
// FUNCTION: ENGINE 0x10294B80
// FUNCTION: ENGINE 0x10294BE0
// FUNCTION: ENGINE 0x10294C10
// FUNCTION: ENGINE 0x10294E10
// FUNCTION: ENGINE 0x10294E70
// FUNCTION: ENGINE 0x10294EA0
// FUNCTION: ENGINE 0x10295030
// FUNCTION: ENGINE 0x10295090
// FUNCTION: ENGINE 0x102950C0
// FUNCTION: ENGINE 0x10295550
// FUNCTION: ENGINE 0x102955B0
// FUNCTION: ENGINE 0x102955E0
// FUNCTION: ENGINE 0x102956D0
// FUNCTION: ENGINE 0x10295730
// FUNCTION: ENGINE 0x10295760
// FUNCTION: ENGINE 0x10295780
// FUNCTION: ENGINE 0x102957E0
// FUNCTION: ENGINE 0x10295810
// FUNCTION: ENGINE 0x10295900
// FUNCTION: ENGINE 0x10295960
// FUNCTION: ENGINE 0x10295990
// FUNCTION: ENGINE 0x102959B0
// FUNCTION: ENGINE 0x10295A10
// FUNCTION: ENGINE 0x10295A40
// FUNCTION: ENGINE 0x10295B10
// FUNCTION: ENGINE 0x10295B70
// FUNCTION: ENGINE 0x10295BA0
// FUNCTION: ENGINE 0x10295BD0
// FUNCTION: ENGINE 0x10295C30
// FUNCTION: ENGINE 0x10295C60
// FUNCTION: ENGINE 0x10295C90
// FUNCTION: ENGINE 0x10295CF0
// FUNCTION: ENGINE 0x10295D20
// FUNCTION: ENGINE 0x10295D40
// FUNCTION: ENGINE 0x10295DA0
// FUNCTION: ENGINE 0x10295DD0
// FUNCTION: ENGINE 0x10295E00
// FUNCTION: ENGINE 0x10295E60
// FUNCTION: ENGINE 0x10295E90
// FUNCTION: ENGINE 0x10295EC0
// FUNCTION: ENGINE 0x10295F20
// FUNCTION: ENGINE 0x10295F50
// FUNCTION: ENGINE 0x10295F70
// FUNCTION: ENGINE 0x10295FD0
// FUNCTION: ENGINE 0x10296000
// FUNCTION: ENGINE 0x10296030
// FUNCTION: ENGINE 0x10296090
// FUNCTION: ENGINE 0x102960C0
// FUNCTION: ENGINE 0x102960E0
// FUNCTION: ENGINE 0x10296140
// FUNCTION: ENGINE 0x10296170
// FUNCTION: ENGINE 0x10296190
// FUNCTION: ENGINE 0x102961F0
// FUNCTION: ENGINE 0x10296220
// FUNCTION: ENGINE 0x10296250
// FUNCTION: ENGINE 0x102962B0
// FUNCTION: ENGINE 0x102962E0
// FUNCTION: ENGINE 0x10296310
// FUNCTION: ENGINE 0x10296370
// FUNCTION: ENGINE 0x102963A0
// FUNCTION: ENGINE 0x102963D0
// FUNCTION: ENGINE 0x10296430
// FUNCTION: ENGINE 0x10296460
// FUNCTION: ENGINE 0x10296600
// FUNCTION: ENGINE 0x10296660
// FUNCTION: ENGINE 0x10296690
// FUNCTION: ENGINE 0x102966B0
// FUNCTION: ENGINE 0x10296710
// FUNCTION: ENGINE 0x10296740
// FUNCTION: ENGINE 0x10296810
// FUNCTION: ENGINE 0x10296870
// FUNCTION: ENGINE 0x102968A0
// FUNCTION: ENGINE 0x102968D0
// FUNCTION: ENGINE 0x10296930
// FUNCTION: ENGINE 0x10296960
// FUNCTION: ENGINE 0x10296980
// FUNCTION: ENGINE 0x102969E0
// FUNCTION: ENGINE 0x10296A10
// FUNCTION: ENGINE 0x10296A30
// FUNCTION: ENGINE 0x10296A90
// FUNCTION: ENGINE 0x10296AC0
// FUNCTION: ENGINE 0x10296BA0
// FUNCTION: ENGINE 0x10296C00
// FUNCTION: ENGINE 0x10296C30
// FUNCTION: ENGINE 0x10296F30
// FUNCTION: ENGINE 0x10296F90
// FUNCTION: ENGINE 0x10296FC0
// FUNCTION: ENGINE 0x10296FF0
// FUNCTION: ENGINE 0x10297050
// FUNCTION: ENGINE 0x10297080
// FUNCTION: ENGINE 0x102970A0
// FUNCTION: ENGINE 0x10297100
// FUNCTION: ENGINE 0x10297130
// FUNCTION: ENGINE 0x10297220
// FUNCTION: ENGINE 0x10297280
// FUNCTION: ENGINE 0x102972B0
// FUNCTION: ENGINE 0x102972E0
// FUNCTION: ENGINE 0x10297340
// FUNCTION: ENGINE 0x10297370
// FUNCTION: ENGINE 0x10297390
// FUNCTION: ENGINE 0x102973F0
// FUNCTION: ENGINE 0x10297420
// FUNCTION: ENGINE 0x10297450
// FUNCTION: ENGINE 0x102974B0
// FUNCTION: ENGINE 0x102974E0
// FUNCTION: ENGINE 0x10297510
// FUNCTION: ENGINE 0x10297570
// FUNCTION: ENGINE 0x102975A0
// FUNCTION: ENGINE 0x102975D0
// FUNCTION: ENGINE 0x10297630
// FUNCTION: ENGINE 0x10297660
// FUNCTION: ENGINE 0x10297690
// FUNCTION: ENGINE 0x102976F0
// FUNCTION: ENGINE 0x10297720
// FUNCTION: ENGINE 0x10297740
// FUNCTION: ENGINE 0x102977A0
// FUNCTION: ENGINE 0x102977D0
// FUNCTION: ENGINE 0x102977F0
// FUNCTION: ENGINE 0x10297850
// FUNCTION: ENGINE 0x10297880
// FUNCTION: ENGINE 0x102978A0
// FUNCTION: ENGINE 0x10297900
// FUNCTION: ENGINE 0x10297930
// FUNCTION: ENGINE 0x10297950
// FUNCTION: ENGINE 0x102979B0
// FUNCTION: ENGINE 0x102979E0
// FUNCTION: ENGINE 0x10297A00
// FUNCTION: ENGINE 0x10297A60
// FUNCTION: ENGINE 0x10297A90
// FUNCTION: ENGINE 0x10297AB0
// FUNCTION: ENGINE 0x10297B10
// FUNCTION: ENGINE 0x10297B40
// FUNCTION: ENGINE 0x10297D80
// FUNCTION: ENGINE 0x10297DE0
// FUNCTION: ENGINE 0x10297E10
// FUNCTION: ENGINE 0x10297E30
// FUNCTION: ENGINE 0x10297E90
// FUNCTION: ENGINE 0x10297EC0
// FUNCTION: ENGINE 0x10297F90
// FUNCTION: ENGINE 0x10297FF0
// FUNCTION: ENGINE 0x10298020
// FUNCTION: ENGINE 0x10298260
// FUNCTION: ENGINE 0x102982C0
// FUNCTION: ENGINE 0x102982F0
// FUNCTION: ENGINE 0x10298320
// FUNCTION: ENGINE 0x10298380
// FUNCTION: ENGINE 0x102983B0
// FUNCTION: ENGINE 0x102983D0
// FUNCTION: ENGINE 0x10298430
// FUNCTION: ENGINE 0x10298460
// FUNCTION: ENGINE 0x10298540
// FUNCTION: ENGINE 0x102985A0
// FUNCTION: ENGINE 0x102985D0
// FUNCTION: ENGINE 0x10298600
// FUNCTION: ENGINE 0x10298660
// FUNCTION: ENGINE 0x10298690
// FUNCTION: ENGINE 0x10298810
// FUNCTION: ENGINE 0x10298870
// FUNCTION: ENGINE 0x102988A0
// FUNCTION: ENGINE 0x102988C0
// FUNCTION: ENGINE 0x10298920
// FUNCTION: ENGINE 0x10298950
// FUNCTION: ENGINE 0x10298970
// FUNCTION: ENGINE 0x102989D0
// FUNCTION: ENGINE 0x10298A00
// FUNCTION: ENGINE 0x10298A20
// FUNCTION: ENGINE 0x10298A80
// FUNCTION: ENGINE 0x10298AB0
// FUNCTION: ENGINE 0x10298AD0
// FUNCTION: ENGINE 0x10298B30
// FUNCTION: ENGINE 0x10298B60
// FUNCTION: ENGINE 0x10298B80
// FUNCTION: ENGINE 0x10298BE0
// FUNCTION: ENGINE 0x10298C10
// FUNCTION: ENGINE 0x10298C30
// FUNCTION: ENGINE 0x10298C90
// FUNCTION: ENGINE 0x10298CC0
// FUNCTION: ENGINE 0x10298CE0
// FUNCTION: ENGINE 0x10298D40
// FUNCTION: ENGINE 0x10298D70
// FUNCTION: ENGINE 0x10298D90
// FUNCTION: ENGINE 0x10298DF0
// FUNCTION: ENGINE 0x10298E20
// FUNCTION: ENGINE 0x10298E40
// FUNCTION: ENGINE 0x10298EA0
// FUNCTION: ENGINE 0x10298ED0
// FUNCTION: ENGINE 0x10298EF0
// FUNCTION: ENGINE 0x10298F50
// FUNCTION: ENGINE 0x10298F80
// FUNCTION: ENGINE 0x10298FA0
// FUNCTION: ENGINE 0x10299000
// FUNCTION: ENGINE 0x10299030
// FUNCTION: ENGINE 0x10299050
// FUNCTION: ENGINE 0x102990B0
// FUNCTION: ENGINE 0x102990E0
// FUNCTION: ENGINE 0x10299270
// FUNCTION: ENGINE 0x102992D0
// FUNCTION: ENGINE 0x10299300
// FUNCTION: ENGINE 0x102993E0
// FUNCTION: ENGINE 0x10299440
// FUNCTION: ENGINE 0x10299470
// FUNCTION: ENGINE 0x10299C00
// FUNCTION: ENGINE 0x10299C60
// FUNCTION: ENGINE 0x10299D20
// FUNCTION: ENGINE 0x10299D80
// FUNCTION: ENGINE 0x10299DE0
// FUNCTION: ENGINE 0x10299E40
// FUNCTION: ENGINE 0x10299EA0
// FUNCTION: ENGINE 0x10299F00
// FUNCTION: ENGINE 0x10299F60
// FUNCTION: ENGINE 0x1029A080
// FUNCTION: ENGINE 0x1029A0E0
// FUNCTION: ENGINE 0x1029A140
// FUNCTION: ENGINE 0x1029A1A0
// FUNCTION: ENGINE 0x1029A200
// FUNCTION: ENGINE 0x1029A260
// FUNCTION: ENGINE 0x1029A2C0
// FUNCTION: ENGINE 0x1029A320
// FUNCTION: ENGINE 0x1029A4A0
// FUNCTION: ENGINE 0x1029A500
// FUNCTION: ENGINE 0x1029A560
// FUNCTION: ENGINE 0x1029A5C0
// FUNCTION: ENGINE 0x1029A740
// FUNCTION: ENGINE 0x1029A7A0
// FUNCTION: ENGINE 0x1029A800
// FUNCTION: ENGINE 0x1029A860
// FUNCTION: ENGINE 0x1029A8C0
// FUNCTION: ENGINE 0x1029A920
// FUNCTION: ENGINE 0x1029A980
// FUNCTION: ENGINE 0x1029A9E0
// FUNCTION: ENGINE 0x1029ABC0
// FUNCTION: ENGINE 0x1029AC20
// FUNCTION: ENGINE 0x1029AC80
// FUNCTION: ENGINE 0x1029ACE0
// FUNCTION: ENGINE 0x1029AD40
// FUNCTION: ENGINE 0x1029ADA0
// FUNCTION: ENGINE 0x1029AE60
// FUNCTION: ENGINE 0x1029AEC0
// FUNCTION: ENGINE 0x1029AF20
// FUNCTION: ENGINE 0x1029AF80
// FUNCTION: ENGINE 0x1029B040
// FUNCTION: ENGINE 0x1029B3A0
// FUNCTION: ENGINE 0x1029B400
// FUNCTION: ENGINE 0x1029B460
// FUNCTION: ENGINE 0x1029B760
// FUNCTION: ENGINE 0x1029B8E0
// FUNCTION: ENGINE 0x1029B940
// FUNCTION: ENGINE 0x1029BA00
// FUNCTION: ENGINE 0x1029BA60
// FUNCTION: ENGINE 0x1029BB20
// FUNCTION: ENGINE 0x1029BB80
// FUNCTION: ENGINE 0x1029BBE0
// FUNCTION: ENGINE 0x1029BC40
// FUNCTION: ENGINE 0x1029BCA0
// FUNCTION: ENGINE 0x1029BD60
// FUNCTION: ENGINE 0x1029BDC0
// FUNCTION: ENGINE 0x1029BE20
// FUNCTION: ENGINE 0x1029BE80
// FUNCTION: ENGINE 0x1029BEE0
// FUNCTION: ENGINE 0x1029C060
// FUNCTION: ENGINE 0x1029C180
// FUNCTION: ENGINE 0x1029C420
// FUNCTION: ENGINE 0x1029C4E0
// FUNCTION: ENGINE 0x1029C540
// FUNCTION: ENGINE 0x1029C600
// FUNCTION: ENGINE 0x1029C660
// FUNCTION: ENGINE 0x1029C720
// FUNCTION: ENGINE 0x1029C780
// FUNCTION: ENGINE 0x1029C7E0
// FUNCTION: ENGINE 0x1029C840
// FUNCTION: ENGINE 0x1029C8A0
// FUNCTION: ENGINE 0x1029C900
// FUNCTION: ENGINE 0x1029C960
// FUNCTION: ENGINE 0x1029C9C0
// FUNCTION: ENGINE 0x1029CA20
// FUNCTION: ENGINE 0x1029CA80
// FUNCTION: ENGINE 0x1029CAE0
// FUNCTION: ENGINE 0x1029CB40
// FUNCTION: ENGINE 0x1029CBA0
// FUNCTION: ENGINE 0x1029CCC0
// FUNCTION: ENGINE 0x1029CD20
// FUNCTION: ENGINE 0x1029CDE0
// FUNCTION: ENGINE 0x1029CE40
// FUNCTION: ENGINE 0x1029CEA0
// FUNCTION: ENGINE 0x1029CF00
// FUNCTION: ENGINE 0x1029CFC0
// FUNCTION: ENGINE 0x1029D1A0
// FUNCTION: ENGINE 0x1029D200
// FUNCTION: ENGINE 0x1029D260
// FUNCTION: ENGINE 0x1029D320
// FUNCTION: ENGINE 0x1029D380
// FUNCTION: ENGINE 0x1029D3E0
// FUNCTION: ENGINE 0x1029D440
// FUNCTION: ENGINE 0x1029D4A0
// FUNCTION: ENGINE 0x1029D500
// FUNCTION: ENGINE 0x1029D560
// FUNCTION: ENGINE 0x1029D5C0
// FUNCTION: ENGINE 0x1029D620
// FUNCTION: ENGINE 0x1029D680
// FUNCTION: ENGINE 0x1029D6E0
// FUNCTION: ENGINE 0x1029D740
// FUNCTION: ENGINE 0x1029D7A0
// FUNCTION: ENGINE 0x1029D920
// FUNCTION: ENGINE 0x1029D980
// FUNCTION: ENGINE 0x1029DA40
// FUNCTION: ENGINE 0x1029DBC0
// FUNCTION: ENGINE 0x1029DC20
// FUNCTION: ENGINE 0x1029DC80
// FUNCTION: ENGINE 0x1029DD40
// FUNCTION: ENGINE 0x1029DDA0
// FUNCTION: ENGINE 0x1029DEC0
// FUNCTION: ENGINE 0x1029DF20
// FUNCTION: ENGINE 0x1029DF80
// FUNCTION: ENGINE 0x1029DFE0
// FUNCTION: ENGINE 0x1029E040
// FUNCTION: ENGINE 0x1029E0A0
// FUNCTION: ENGINE 0x1029E100
// FUNCTION: ENGINE 0x1029E160
// FUNCTION: ENGINE 0x1029E1C0
// FUNCTION: ENGINE 0x1029E220
// FUNCTION: ENGINE 0x1029E280
// FUNCTION: ENGINE 0x1029E2E0
// FUNCTION: ENGINE 0x1029E340
// FUNCTION: ENGINE 0x1029E460
// FUNCTION: ENGINE 0x1029E520
