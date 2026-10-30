// The factories the content library loads the engine's reflected classes through (see content/metafactory.h): the
// class meta type, the factory (or instance creator) and its registration of each class, in the order the engine has
// them (0x108D6E20 on).
#include "code/content/metafactory.h"
#include "code/engine/reflectedclasses.h"
#include "code/engine/nisplayerbehaviour.h"
#include "code/engine/characterintentionbehaviour.h"
#include "code/engine/reflectedclasses2.h"
#include "code/engine/camera/camera.h"
#include "code/engine/gameobject/genericscriptvalue.h"
#include "code/engine/lightbehaviour.h"
#include "code/engine/nis/nis.h"
#include "code/engine/propspawner.h"
#include "code/math/aabb.h"
#include "code/math/obb.h"
#include "code/math/plane.h"
#include "code/math/sphere.h"
#include "code/engine/fight/behaviours/proplogictreebehaviour.h"
#include "code/engine/gameobject/behaviours/pathbehaviour.h"
#include "code/engine/firstpersoncontrolbehaviour.h"
#include "code/engine/knockbehaviour.h"
#include "code/engine/propbehaviour.h"
#include "code/engine/world/locationrendersettings.h"
#include "code/engine/actorspawner.h"
#include "code/engine/driving/physicsattributes.h"
#include "code/engine/driving/wheelcollectiondata.h"
#include "code/engine/splinepath.h"
#include "code/engine/surfacedefinition.h"
#include "code/engine/animation/behaviours/jawflapbehaviour.h"
#include "code/engine/camera/cameraloader.h"
#include "code/engine/camera/fpscamera.h"
#include "code/engine/camera/onfootcamera.h"
#include "code/engine/charactersolverproperties.h"
#include "code/engine/fight/behaviours/motiontreebehaviour.h"
#include "code/engine/fmv/fmvsubtitlemanager.h"
#include "code/engine/gameobject/gameobject.h"
#include "code/engine/motiontrackingfilter.h"
#include "code/engine/namedinventorycreator.h"
#include "code/engine/secondaryphysicsproperties.h"
#include "code/ravenphysics/massproperties.h"
#include "code/engine/remotecamera.h"
#include "code/engine/secondaryphysicsjoints.h"
#include "code/engine/scenariomessage.h"
#include "code/engine/trackedmotiontoexpressionmap.h"

namespace content
{
	template class MetaObjectFactory<engine::animation::AttachmentPhysicsProperties, 1>;
	template ClassMetaType* GetClassMetaType<engine::animation::AttachmentPhysicsProperties>();
	template void RegisterMetaObjectFactory<engine::animation::AttachmentPhysicsProperties>();
	template class MetaObjectFactory<engine::ActorSpawner, 1>;
	template ClassMetaType* GetClassMetaType<engine::ActorSpawner>();
	template void RegisterMetaObjectFactory<engine::ActorSpawner>();
	template class MetaObjectFactory<engine::ActorCrowdSpawner, 1>;
	template ClassMetaType* GetClassMetaType<engine::ActorCrowdSpawner>();
	template void RegisterMetaObjectFactory<engine::ActorCrowdSpawner>();
	template class MetaObjectFactory<engine::camera::CameraLoader, 1>;
	template ClassMetaType* GetClassMetaType<engine::camera::CameraLoader>();
	template void RegisterMetaObjectFactory<engine::camera::CameraLoader>();
	template class MetaObjectFactory<engine::CharacterIntentionInputMap, 1>;
	template ClassMetaType* GetClassMetaType<engine::CharacterIntentionInputMap>();
	template void RegisterMetaObjectFactory<engine::CharacterIntentionInputMap>();
	template class MetaObjectFactory<engine::driving::CarPhysicsAttributes, 1>;
	template ClassMetaType* GetClassMetaType<engine::driving::CarPhysicsAttributes>();
	template void RegisterMetaObjectFactory<engine::driving::CarPhysicsAttributes>();
	template class MetaObjectFactory<engine::driving::HelicopterPhysicsAttributes, 1>;
	template ClassMetaType* GetClassMetaType<engine::driving::HelicopterPhysicsAttributes>();
	template void RegisterMetaObjectFactory<engine::driving::HelicopterPhysicsAttributes>();
	template class MetaObjectFactory<engine::driving::VehiclePhysicsAttributes, 1>;
	template ClassMetaType* GetClassMetaType<engine::driving::VehiclePhysicsAttributes>();
	template void RegisterMetaObjectFactory<engine::driving::VehiclePhysicsAttributes>();
	template class MetaObjectFactory<engine::driving::WheelCollectionData, 1>;
	template ClassMetaType* GetClassMetaType<engine::driving::WheelCollectionData>();
	template void RegisterMetaObjectFactory<engine::driving::WheelCollectionData>();
	template class MetaObjectFactory<engine::CharacterSolverProperties, 1>;
	template ClassMetaType* GetClassMetaType<engine::CharacterSolverProperties>();
	template void RegisterMetaObjectFactory<engine::CharacterSolverProperties>();
	template class MetaObjectFactory<engine::GameObject, 1>;
	template ClassMetaType* GetClassMetaType<engine::GameObject>();
	template void RegisterMetaObjectFactory<engine::GameObject>();
	template class MetaObjectFactory<engine::GameObjectTemplateBuilder, 1>;
	template ClassMetaType* GetClassMetaType<engine::GameObjectTemplateBuilder>();
	template void RegisterMetaObjectFactory<engine::GameObjectTemplateBuilder>();
	template class MetaObjectFactory<engine::NamedInventoryCreator, 1>;
	template ClassMetaType* GetClassMetaType<engine::NamedInventoryCreator>();
	template void RegisterMetaObjectFactory<engine::NamedInventoryCreator>();
	template class MetaObjectFactory<ravenphysics::ConstraintAngularSpringSharedProperties, 1>;
	template ClassMetaType* GetClassMetaType<ravenphysics::ConstraintAngularSpringSharedProperties>();
	template void RegisterMetaObjectFactory<ravenphysics::ConstraintAngularSpringSharedProperties>();
	template class MetaObjectFactory<ravenphysics::ConstraintAngularVelocitySharedProperties, 1>;
	template ClassMetaType* GetClassMetaType<ravenphysics::ConstraintAngularVelocitySharedProperties>();
	template void RegisterMetaObjectFactory<ravenphysics::ConstraintAngularVelocitySharedProperties>();
	template class MetaObjectFactory<ravenphysics::ConstraintListFactory, 1>;
	template ClassMetaType* GetClassMetaType<ravenphysics::ConstraintListFactory>();
	template void RegisterMetaObjectFactory<ravenphysics::ConstraintListFactory>();
	template class MetaObjectFactory<ravenphysics::ConstraintSpringAlongAxisSharedProperties, 1>;
	template ClassMetaType* GetClassMetaType<ravenphysics::ConstraintSpringAlongAxisSharedProperties>();
	template void RegisterMetaObjectFactory<ravenphysics::ConstraintSpringAlongAxisSharedProperties>();
	template class MetaObjectFactory<ravenphysics::DeformableOrientationConstraintSharedProperties, 1>;
	template ClassMetaType* GetClassMetaType<ravenphysics::DeformableOrientationConstraintSharedProperties>();
	template void RegisterMetaObjectFactory<ravenphysics::DeformableOrientationConstraintSharedProperties>();
	template class MetaObjectFactory<ravenphysics::DeformableSliderConstraintSharedProperties, 1>;
	template ClassMetaType* GetClassMetaType<ravenphysics::DeformableSliderConstraintSharedProperties>();
	template void RegisterMetaObjectFactory<ravenphysics::DeformableSliderConstraintSharedProperties>();
	template class MetaObjectFactory<ravenphysics::IntersectionPropertiesLoader, 1>;
	template ClassMetaType* GetClassMetaType<ravenphysics::IntersectionPropertiesLoader>();
	template void RegisterMetaObjectFactory<ravenphysics::IntersectionPropertiesLoader>();
	template class MetaObjectFactory<ravenphysics::MassProperties, 1>;
	template ClassMetaType* GetClassMetaType<ravenphysics::MassProperties>();
	template void RegisterMetaObjectFactory<ravenphysics::MassProperties>();
	template class MetaObjectFactory<ravenphysics::MaterialLoader, 1>;
	template ClassMetaType* GetClassMetaType<ravenphysics::MaterialLoader>();
	template void RegisterMetaObjectFactory<ravenphysics::MaterialLoader>();
	template class MetaObjectFactory<ravenphysics::PoweredConstraintSharedProperties, 1>;
	template ClassMetaType* GetClassMetaType<ravenphysics::PoweredConstraintSharedProperties>();
	template void RegisterMetaObjectFactory<ravenphysics::PoweredConstraintSharedProperties>();
	template class MetaObjectFactory<ravenphysics::SimplePhysicsObjectFactory, 1>;
	template ClassMetaType* GetClassMetaType<ravenphysics::SimplePhysicsObjectFactory>();
	template void RegisterMetaObjectFactory<ravenphysics::SimplePhysicsObjectFactory>();
	template class MetaObjectFactory<engine::RemoteCamera, 1>;
	template ClassMetaType* GetClassMetaType<engine::RemoteCamera>();
	template void RegisterMetaObjectFactory<engine::RemoteCamera>();
	template class MetaObjectFactory<engine::SecondaryPhysicsProperties, 1>;
	template ClassMetaType* GetClassMetaType<engine::SecondaryPhysicsProperties>();
	template void RegisterMetaObjectFactory<engine::SecondaryPhysicsProperties>();
	template class MetaObjectFactory<engine::SkuInfo, 1>;
	template ClassMetaType* GetClassMetaType<engine::SkuInfo>();
	template void RegisterMetaObjectFactory<engine::SkuInfo>();
	template class MetaObjectFactory<engine::SplinePath, 1>;
	template ClassMetaType* GetClassMetaType<engine::SplinePath>();
	template void RegisterMetaObjectFactory<engine::SplinePath>();
	template class MetaObjectFactory<engine::StreamPackage, 1>;
	template ClassMetaType* GetClassMetaType<engine::StreamPackage>();
	template void RegisterMetaObjectFactory<engine::StreamPackage>();
	template class MetaObjectFactory<engine::StreamSlotGroup, 1>;
	template ClassMetaType* GetClassMetaType<engine::StreamSlotGroup>();
	template void RegisterMetaObjectFactory<engine::StreamSlotGroup>();
	template class MetaObjectFactory<engine::StreamTrigger, 1>;
	template ClassMetaType* GetClassMetaType<engine::StreamTrigger>();
	template void RegisterMetaObjectFactory<engine::StreamTrigger>();
	template class MetaObjectFactory<engine::SupportingLimbDefinition, 1>;
	template ClassMetaType* GetClassMetaType<engine::SupportingLimbDefinition>();
	template void RegisterMetaObjectFactory<engine::SupportingLimbDefinition>();
	template class MetaObjectFactory<engine::SupportingLimbDefinitionList, 1>;
	template ClassMetaType* GetClassMetaType<engine::SupportingLimbDefinitionList>();
	template void RegisterMetaObjectFactory<engine::SupportingLimbDefinitionList>();
	template class MetaObjectFactory<SurfaceDefinition, 1>;
	template ClassMetaType* GetClassMetaType<SurfaceDefinition>();
	template void RegisterMetaObjectFactory<SurfaceDefinition>();
	template class MetaObjectFactory<engine::TrackedMotionToExpressionMap, 1>;
	template ClassMetaType* GetClassMetaType<engine::TrackedMotionToExpressionMap>();
	template void RegisterMetaObjectFactory<engine::TrackedMotionToExpressionMap>();
	template class MetaObjectFactory<engine::world::Location, 1>;
	template ClassMetaType* GetClassMetaType<engine::world::Location>();
	template void RegisterMetaObjectFactory<engine::world::Location>();
	template class MetaObjectFactory<engine::world::LocationRenderSettings, 1>;
	template ClassMetaType* GetClassMetaType<engine::world::LocationRenderSettings>();
	template void RegisterMetaObjectFactory<engine::world::LocationRenderSettings>();
	template class MetaObjectFactory<engine::NISExclusionVolume, 1>;
	template ClassMetaType* GetClassMetaType<engine::NISExclusionVolume>();
	template void RegisterMetaObjectFactory<engine::NISExclusionVolume>();
	template class MetaObjectFactory<engine::FmvSubtitleManager, 1>;
	template ClassMetaType* GetClassMetaType<engine::FmvSubtitleManager>();
	template void RegisterMetaObjectFactory<engine::FmvSubtitleManager>();
	template class MetaInstanceCreatorImpl<engine::camera::FPSCamera, 1>;
	template ClassMetaType* GetClassMetaType<engine::camera::FPSCamera>();
	template void RegisterMetaInstanceCreator<engine::camera::FPSCamera>();
	template class MetaInstanceCreatorImpl<engine::camera::OnFootCamera, 1>;
	template ClassMetaType* GetClassMetaType<engine::camera::OnFootCamera>();
	template void RegisterMetaInstanceCreator<engine::camera::OnFootCamera>();
	template class MetaInstanceCreatorImpl<engine::camera::ScriptedCamera, 1>;
	template ClassMetaType* GetClassMetaType<engine::camera::ScriptedCamera>();
	template void RegisterMetaInstanceCreator<engine::camera::ScriptedCamera>();
	template class MetaInstanceCreatorImpl<engine::DampedAngularMotionTrackingFilter, 1>;
	template ClassMetaType* GetClassMetaType<engine::DampedAngularMotionTrackingFilter>();
	template void RegisterMetaInstanceCreator<engine::DampedAngularMotionTrackingFilter>();
	template class MetaInstanceCreatorImpl<engine::DampedLinearMotionTrackingFilter, 1>;
	template ClassMetaType* GetClassMetaType<engine::DampedLinearMotionTrackingFilter>();
	template void RegisterMetaInstanceCreator<engine::DampedLinearMotionTrackingFilter>();
	template class MetaInstanceCreatorImpl<engine::SplinePathCV, 1>;
	template ClassMetaType* GetClassMetaType<engine::SplinePathCV>();
	template void RegisterMetaInstanceCreator<engine::SplinePathCV>();
	template class MetaInstanceCreatorImpl<engine::EnterTriggerMessage, 1>;
	template ClassMetaType* GetClassMetaType<engine::EnterTriggerMessage>();
	template void RegisterMetaInstanceCreator<engine::EnterTriggerMessage>();
	template class MetaInstanceCreatorImpl<engine::ExitTriggerMessage, 1>;
	template ClassMetaType* GetClassMetaType<engine::ExitTriggerMessage>();
	template void RegisterMetaInstanceCreator<engine::ExitTriggerMessage>();
	template class MetaInstanceCreatorImpl<engine::SecondaryPhysicsAmbientWind, 1>;
	template ClassMetaType* GetClassMetaType<engine::SecondaryPhysicsAmbientWind>();
	template void RegisterMetaInstanceCreator<engine::SecondaryPhysicsAmbientWind>();
	template class MetaInstanceCreatorImpl<engine::SecondaryPhysicsPinJoint, 1>;
	template ClassMetaType* GetClassMetaType<engine::SecondaryPhysicsPinJoint>();
	template void RegisterMetaInstanceCreator<engine::SecondaryPhysicsPinJoint>();
	template class MetaInstanceCreatorImpl<engine::SecondaryPhysicsPoweredJoint, 1>;
	template ClassMetaType* GetClassMetaType<engine::SecondaryPhysicsPoweredJoint>();
	template void RegisterMetaInstanceCreator<engine::SecondaryPhysicsPoweredJoint>();
	template class MetaInstanceCreatorImpl<engine::SpringBasedAngularMotionFilter, 1>;
	template ClassMetaType* GetClassMetaType<engine::SpringBasedAngularMotionFilter>();
	template void RegisterMetaInstanceCreator<engine::SpringBasedAngularMotionFilter>();
	template class MetaInstanceCreatorImpl<engine::SpringBasedLinearMotionFilter, 1>;
	template ClassMetaType* GetClassMetaType<engine::SpringBasedLinearMotionFilter>();
	template void RegisterMetaInstanceCreator<engine::SpringBasedLinearMotionFilter>();
	template class MetaInstanceCreatorImpl<engine::trigger::OBBVolume, 1>;
	template ClassMetaType* GetClassMetaType<engine::trigger::OBBVolume>();
	template void RegisterMetaInstanceCreator<engine::trigger::OBBVolume>();
	template class MetaInstanceCreatorImpl<engine::trigger::SphereVolume, 1>;
	template ClassMetaType* GetClassMetaType<engine::trigger::SphereVolume>();
	template void RegisterMetaInstanceCreator<engine::trigger::SphereVolume>();
	template ClassMetaType* GetClassMetaType<engine::AdvertisementBehaviour>();
	template ClassMetaType* GetClassMetaType<engine::animation::JawFlapBehaviour>();
	template ClassMetaType* GetClassMetaType<engine::animation::PuppetBehaviour>();
	template ClassMetaType* GetClassMetaType<engine::camera::CameraBehaviour>();
	template ClassMetaType* GetClassMetaType<engine::camera::CinematographerBehaviour>();
	template ClassMetaType* GetClassMetaType<engine::CharacterIntentionBehaviour>();
	template ClassMetaType* GetClassMetaType<engine::CharacterSolverBehaviour>();
	template ClassMetaType* GetClassMetaType<engine::driving::CarIntentionBehaviour>();
	template ClassMetaType* GetClassMetaType<engine::driving::CarPhysicsBehaviour>();
	template ClassMetaType* GetClassMetaType<engine::driving::HelicopterIntentionBehaviour>();
	template ClassMetaType* GetClassMetaType<engine::driving::HelicopterPhysicsBehaviour>();
	template ClassMetaType* GetClassMetaType<engine::FirstPersonControlBehaviour>();
	template ClassMetaType* GetClassMetaType<engine::KnockBehaviour>();
	template ClassMetaType* GetClassMetaType<engine::MotionTreeBehaviour>();
	template ClassMetaType* GetClassMetaType<engine::NISPlayerBehaviour>();
	template ClassMetaType* GetClassMetaType<engine::PatrolPathBehaviour>();
	template ClassMetaType* GetClassMetaType<engine::PlaybackTreeBehaviour>();
	template ClassMetaType* GetClassMetaType<engine::PoseAnimationBehaviour>();
	template ClassMetaType* GetClassMetaType<engine::PropLogicTreeBehaviour>();
	template ClassMetaType* GetClassMetaType<engine::PhysicsBehaviour>();
	template ClassMetaType* GetClassMetaType<engine::PropBehaviour>();
	template ClassMetaType* GetClassMetaType<engine::RagdollBehaviour>();
	template ClassMetaType* GetClassMetaType<engine::RagdollLODBehaviour>();
	template ClassMetaType* GetClassMetaType<engine::RenderBehaviour>();
	template ClassMetaType* GetClassMetaType<engine::SecondaryPhysicsBehaviour>();
	template ClassMetaType* GetClassMetaType<engine::SplineBehaviour>();
	template ClassMetaType* GetClassMetaType<engine::TagBehaviour>();
	template ClassMetaType* GetClassMetaType<engine::TouchBehaviour>();
	template ClassMetaType* GetClassMetaType<engine::TrackedMotionToExpressionBehaviour>();
}

namespace engine
{
	template class MetaBehaviourCreatorImpl<engine::AdvertisementBehaviour>;
	template void RegisterMetaBehaviourCreator<engine::AdvertisementBehaviour>();
	template class MetaBehaviourCreatorImpl<engine::animation::JawFlapBehaviour>;
	template void RegisterMetaBehaviourCreator<engine::animation::JawFlapBehaviour>();
	template class MetaBehaviourCreatorImpl<engine::animation::PuppetBehaviour>;
	template void RegisterMetaBehaviourCreator<engine::animation::PuppetBehaviour>();
	template class MetaBehaviourCreatorImpl<engine::camera::CameraBehaviour>;
	template void RegisterMetaBehaviourCreator<engine::camera::CameraBehaviour>();
	template class MetaBehaviourCreatorImpl<engine::camera::CinematographerBehaviour>;
	template void RegisterMetaBehaviourCreator<engine::camera::CinematographerBehaviour>();
	template class MetaBehaviourCreatorImpl<engine::CharacterIntentionBehaviour>;
	template void RegisterMetaBehaviourCreator<engine::CharacterIntentionBehaviour>();
	template class MetaBehaviourCreatorImpl<engine::CharacterSolverBehaviour>;
	template void RegisterMetaBehaviourCreator<engine::CharacterSolverBehaviour>();
	template class MetaBehaviourCreatorImpl<engine::driving::CarIntentionBehaviour>;
	template void RegisterMetaBehaviourCreator<engine::driving::CarIntentionBehaviour>();
	template class MetaBehaviourCreatorImpl<engine::driving::CarPhysicsBehaviour>;
	template void RegisterMetaBehaviourCreator<engine::driving::CarPhysicsBehaviour>();
	template class MetaBehaviourCreatorImpl<engine::driving::HelicopterIntentionBehaviour>;
	template void RegisterMetaBehaviourCreator<engine::driving::HelicopterIntentionBehaviour>();
	template class MetaBehaviourCreatorImpl<engine::driving::HelicopterPhysicsBehaviour>;
	template void RegisterMetaBehaviourCreator<engine::driving::HelicopterPhysicsBehaviour>();
	template class MetaBehaviourCreatorImpl<engine::FirstPersonControlBehaviour>;
	template void RegisterMetaBehaviourCreator<engine::FirstPersonControlBehaviour>();
	template class MetaBehaviourCreatorImpl<engine::KnockBehaviour>;
	template void RegisterMetaBehaviourCreator<engine::KnockBehaviour>();
	template class MetaBehaviourCreatorImpl<engine::MotionTreeBehaviour>;
	template void RegisterMetaBehaviourCreator<engine::MotionTreeBehaviour>();
	template class MetaBehaviourCreatorImpl<engine::NISPlayerBehaviour>;
	template void RegisterMetaBehaviourCreator<engine::NISPlayerBehaviour>();
	template class MetaBehaviourCreatorImpl<engine::PatrolPathBehaviour>;
	template void RegisterMetaBehaviourCreator<engine::PatrolPathBehaviour>();
	template class MetaBehaviourCreatorImpl<engine::PlaybackTreeBehaviour>;
	template void RegisterMetaBehaviourCreator<engine::PlaybackTreeBehaviour>();
	template class MetaBehaviourCreatorImpl<engine::PoseAnimationBehaviour>;
	template void RegisterMetaBehaviourCreator<engine::PoseAnimationBehaviour>();
	template class MetaBehaviourCreatorImpl<engine::PropLogicTreeBehaviour>;
	template void RegisterMetaBehaviourCreator<engine::PropLogicTreeBehaviour>();
	template class MetaBehaviourCreatorImpl<engine::PhysicsBehaviour>;
	template void RegisterMetaBehaviourCreator<engine::PhysicsBehaviour>();
	template class MetaBehaviourCreatorImpl<engine::PropBehaviour>;
	template void RegisterMetaBehaviourCreator<engine::PropBehaviour>();
	template class MetaBehaviourCreatorImpl<engine::RagdollBehaviour>;
	template void RegisterMetaBehaviourCreator<engine::RagdollBehaviour>();
	template class MetaBehaviourCreatorImpl<engine::RagdollLODBehaviour>;
	template void RegisterMetaBehaviourCreator<engine::RagdollLODBehaviour>();
	template class MetaBehaviourCreatorImpl<engine::RenderBehaviour>;
	template void RegisterMetaBehaviourCreator<engine::RenderBehaviour>();
	template class MetaBehaviourCreatorImpl<engine::SecondaryPhysicsBehaviour>;
	template void RegisterMetaBehaviourCreator<engine::SecondaryPhysicsBehaviour>();
	template class MetaBehaviourCreatorImpl<engine::SplineBehaviour>;
	template void RegisterMetaBehaviourCreator<engine::SplineBehaviour>();
	template class MetaBehaviourCreatorImpl<engine::TagBehaviour>;
	template void RegisterMetaBehaviourCreator<engine::TagBehaviour>();
	template class MetaBehaviourCreatorImpl<engine::TouchBehaviour>;
	template void RegisterMetaBehaviourCreator<engine::TouchBehaviour>();
	template class MetaBehaviourCreatorImpl<engine::TrackedMotionToExpressionBehaviour>;
	template void RegisterMetaBehaviourCreator<engine::TrackedMotionToExpressionBehaviour>();
}



// BEGIN GENERATED INSTANTIATIONS
namespace content
{
	template class MetaObjectFactory<engine::ContentManager::ContentPackageDefinition, 1>;
	template ClassMetaType* GetClassMetaType<engine::ContentManager::ContentPackageDefinition>();
	template void RegisterMetaObjectFactory<engine::ContentManager::ContentPackageDefinition>();
	template class MetaObjectFactory<engine::ContentManager::ContentPackageKey, 1>;
	template ClassMetaType* GetClassMetaType<engine::ContentManager::ContentPackageKey>();
	template void RegisterMetaObjectFactory<engine::ContentManager::ContentPackageKey>();
	template class MetaObjectFactory<engine::PropSpawner, 1>;
	template ClassMetaType* GetClassMetaType<engine::PropSpawner>();
	template void RegisterMetaObjectFactory<engine::PropSpawner>();
	template<> LoadObject* MetaObjectFactory<ravenphysics::ColliderTypeNames, 1>::Create();
	template MetaObjectFactory<ravenphysics::ColliderTypeNames, 1>::MetaObjectFactory(const char*, unsigned short, ClassMetaType*);
	template ClassMetaType* GetClassMetaType<ravenphysics::ColliderTypeNames>();
	template void RegisterMetaObjectFactory<ravenphysics::ColliderTypeNames>();
	template class MetaObjectFactory<ravenphysics::PhysicsObjectFactory, 1>;
	template ClassMetaType* GetClassMetaType<ravenphysics::PhysicsObjectFactory>();
	template void RegisterMetaObjectFactory<ravenphysics::PhysicsObjectFactory>();
	template class MetaInstanceCreatorImpl<engine::camera::Camera, 1>;
	template ClassMetaType* GetClassMetaType<engine::camera::Camera>();
	template void RegisterMetaInstanceCreator<engine::camera::Camera>();
	template class MetaInstanceCreatorImpl<engine::camera::Cinematographer, 1>;
	template ClassMetaType* GetClassMetaType<engine::camera::Cinematographer>();
	template void RegisterMetaInstanceCreator<engine::camera::Cinematographer>();
	template class MetaInstanceCreatorImpl<engine::PatrolPoint, 1>;
	template ClassMetaType* GetClassMetaType<engine::PatrolPoint>();
	template void RegisterMetaInstanceCreator<engine::PatrolPoint>();
	template class MetaInstanceCreatorImpl<engine::SplineCV, 1>;
	template ClassMetaType* GetClassMetaType<engine::SplineCV>();
	template void RegisterMetaInstanceCreator<engine::SplineCV>();
	template class MetaInstanceCreatorImpl<math::AABB, 1>;
	template ClassMetaType* GetClassMetaType<math::AABB>();
	template void RegisterMetaInstanceCreator<math::AABB>();
	template class MetaInstanceCreatorImpl<math::OBB, 1>;
	template ClassMetaType* GetClassMetaType<math::OBB>();
	template void RegisterMetaInstanceCreator<math::OBB>();
	template class MetaInstanceCreatorImpl<math::Plane, 1>;
	template ClassMetaType* GetClassMetaType<math::Plane>();
	template void RegisterMetaInstanceCreator<math::Plane>();
	template ClassMetaType* GetClassMetaType<engine::animation::AttachableBehaviour>();
	template ClassMetaType* GetClassMetaType<engine::BehaviourController>();
	template ClassMetaType* GetClassMetaType<engine::HealthBehaviour>();
	template ClassMetaType* GetClassMetaType<engine::LightBehaviour>();
	template ClassMetaType* GetClassMetaType<engine::TriggerBehaviour>();
}

namespace engine
{
	template class MetaBehaviourCreatorImpl<engine::animation::AttachableBehaviour>;
	template void RegisterMetaBehaviourCreator<engine::animation::AttachableBehaviour>();
	template class MetaBehaviourCreatorImpl<engine::BehaviourController>;
	template void RegisterMetaBehaviourCreator<engine::BehaviourController>();
	template class MetaBehaviourCreatorImpl<engine::HealthBehaviour>;
	template void RegisterMetaBehaviourCreator<engine::HealthBehaviour>();
	template class MetaBehaviourCreatorImpl<engine::LightBehaviour>;
	template void RegisterMetaBehaviourCreator<engine::LightBehaviour>();
	template class MetaBehaviourCreatorImpl<engine::TriggerBehaviour>;
	template void RegisterMetaBehaviourCreator<engine::TriggerBehaviour>();
}
// END GENERATED INSTANTIATIONS

// The classes whose objects another unit makes (their Create is the engine's: declared, not defined here)
namespace content
{
	template<> LoadObject* MetaObjectFactory<engine::NIS, 1>::Create();
	template MetaObjectFactory<engine::NIS, 1>::MetaObjectFactory(const char*, unsigned short, ClassMetaType*);
	template ClassMetaType* GetClassMetaType<engine::NIS>();
	template void RegisterMetaObjectFactory<engine::NIS>();
	template<> void* MetaInstanceCreatorImpl<engine::AngularAccelerationExtractor, 1>::Create();
	template MetaInstanceCreatorImpl<engine::AngularAccelerationExtractor, 1>::MetaInstanceCreatorImpl(const char*, unsigned short, ClassMetaType*);
	template ClassMetaType* GetClassMetaType<engine::AngularAccelerationExtractor>();
	template void RegisterMetaInstanceCreator<engine::AngularAccelerationExtractor>();
	template<> void* MetaInstanceCreatorImpl<engine::AngularDisplacementExtractor, 1>::Create();
	template MetaInstanceCreatorImpl<engine::AngularDisplacementExtractor, 1>::MetaInstanceCreatorImpl(const char*, unsigned short, ClassMetaType*);
	template ClassMetaType* GetClassMetaType<engine::AngularDisplacementExtractor>();
	template void RegisterMetaInstanceCreator<engine::AngularDisplacementExtractor>();
	template<> void* MetaInstanceCreatorImpl<engine::AngularSpeedExtractor, 1>::Create();
	template MetaInstanceCreatorImpl<engine::AngularSpeedExtractor, 1>::MetaInstanceCreatorImpl(const char*, unsigned short, ClassMetaType*);
	template ClassMetaType* GetClassMetaType<engine::AngularSpeedExtractor>();
	template void RegisterMetaInstanceCreator<engine::AngularSpeedExtractor>();
	template<> void* MetaInstanceCreatorImpl<engine::Attribute<bool>, 1>::Create();
	template MetaInstanceCreatorImpl<engine::Attribute<bool>, 1>::MetaInstanceCreatorImpl(const char*, unsigned short, ClassMetaType*);
	template ClassMetaType* GetClassMetaType<engine::Attribute<bool>>();
	template void RegisterMetaInstanceCreator<engine::Attribute<bool>>();
	template<> void* MetaInstanceCreatorImpl<engine::ConstAttribute<bool>, 1>::Create();
	template MetaInstanceCreatorImpl<engine::ConstAttribute<bool>, 1>::MetaInstanceCreatorImpl(const char*, unsigned short, ClassMetaType*);
	template ClassMetaType* GetClassMetaType<engine::ConstAttribute<bool>>();
	template void RegisterMetaInstanceCreator<engine::ConstAttribute<bool>>();
	template<> void* MetaInstanceCreatorImpl<engine::Attribute<int>, 1>::Create();
	template MetaInstanceCreatorImpl<engine::Attribute<int>, 1>::MetaInstanceCreatorImpl(const char*, unsigned short, ClassMetaType*);
	template ClassMetaType* GetClassMetaType<engine::Attribute<int>>();
	template void RegisterMetaInstanceCreator<engine::Attribute<int>>();
	template<> void* MetaInstanceCreatorImpl<engine::ConstAttribute<int>, 1>::Create();
	template MetaInstanceCreatorImpl<engine::ConstAttribute<int>, 1>::MetaInstanceCreatorImpl(const char*, unsigned short, ClassMetaType*);
	template ClassMetaType* GetClassMetaType<engine::ConstAttribute<int>>();
	template void RegisterMetaInstanceCreator<engine::ConstAttribute<int>>();
	template<> void* MetaInstanceCreatorImpl<engine::Attribute<float>, 1>::Create();
	template MetaInstanceCreatorImpl<engine::Attribute<float>, 1>::MetaInstanceCreatorImpl(const char*, unsigned short, ClassMetaType*);
	template ClassMetaType* GetClassMetaType<engine::Attribute<float>>();
	template void RegisterMetaInstanceCreator<engine::Attribute<float>>();
	template<> void* MetaInstanceCreatorImpl<engine::ConstAttribute<float>, 1>::Create();
	template MetaInstanceCreatorImpl<engine::ConstAttribute<float>, 1>::MetaInstanceCreatorImpl(const char*, unsigned short, ClassMetaType*);
	template ClassMetaType* GetClassMetaType<engine::ConstAttribute<float>>();
	template void RegisterMetaInstanceCreator<engine::ConstAttribute<float>>();
	template<> void* MetaInstanceCreatorImpl<engine::Attribute<core::Name<core::CaseSensitiveKey> >, 1>::Create();
	template MetaInstanceCreatorImpl<engine::Attribute<core::Name<core::CaseSensitiveKey> >, 1>::MetaInstanceCreatorImpl(const char*, unsigned short, ClassMetaType*);
	template ClassMetaType* GetClassMetaType<engine::Attribute<core::Name<core::CaseSensitiveKey> >>();
	template void RegisterMetaInstanceCreator<engine::Attribute<core::Name<core::CaseSensitiveKey> >>();
	template<> void* MetaInstanceCreatorImpl<engine::ConstAttribute<core::Name<core::CaseSensitiveKey> >, 1>::Create();
	template MetaInstanceCreatorImpl<engine::ConstAttribute<core::Name<core::CaseSensitiveKey> >, 1>::MetaInstanceCreatorImpl(const char*, unsigned short, ClassMetaType*);
	template ClassMetaType* GetClassMetaType<engine::ConstAttribute<core::Name<core::CaseSensitiveKey> >>();
	template void RegisterMetaInstanceCreator<engine::ConstAttribute<core::Name<core::CaseSensitiveKey> >>();
	template<> void* MetaInstanceCreatorImpl<engine::Attribute<pure3d::Pose *>, 1>::Create();
	template MetaInstanceCreatorImpl<engine::Attribute<pure3d::Pose *>, 1>::MetaInstanceCreatorImpl(const char*, unsigned short, ClassMetaType*);
	template ClassMetaType* GetClassMetaType<engine::Attribute<pure3d::Pose *>>();
	template void RegisterMetaInstanceCreator<engine::Attribute<pure3d::Pose *>>();
	template<> void* MetaInstanceCreatorImpl<engine::ConstAttribute<pure3d::Pose *>, 1>::Create();
	template MetaInstanceCreatorImpl<engine::ConstAttribute<pure3d::Pose *>, 1>::MetaInstanceCreatorImpl(const char*, unsigned short, ClassMetaType*);
	template ClassMetaType* GetClassMetaType<engine::ConstAttribute<pure3d::Pose *>>();
	template void RegisterMetaInstanceCreator<engine::ConstAttribute<pure3d::Pose *>>();
	template<> void* MetaInstanceCreatorImpl<engine::Attribute<math::Matrix>, 1>::Create();
	template MetaInstanceCreatorImpl<engine::Attribute<math::Matrix>, 1>::MetaInstanceCreatorImpl(const char*, unsigned short, ClassMetaType*);
	template ClassMetaType* GetClassMetaType<engine::Attribute<math::Matrix>>();
	template void RegisterMetaInstanceCreator<engine::Attribute<math::Matrix>>();
	template<> void* MetaInstanceCreatorImpl<engine::ConstAttribute<math::Matrix>, 1>::Create();
	template MetaInstanceCreatorImpl<engine::ConstAttribute<math::Matrix>, 1>::MetaInstanceCreatorImpl(const char*, unsigned short, ClassMetaType*);
	template ClassMetaType* GetClassMetaType<engine::ConstAttribute<math::Matrix>>();
	template void RegisterMetaInstanceCreator<engine::ConstAttribute<math::Matrix>>();
	template<> void* MetaInstanceCreatorImpl<engine::GameObject::DynamicAttributeList, 1>::Create();
	template MetaInstanceCreatorImpl<engine::GameObject::DynamicAttributeList, 1>::MetaInstanceCreatorImpl(const char*, unsigned short, ClassMetaType*);
	template ClassMetaType* GetClassMetaType<engine::GameObject::DynamicAttributeList>();
	template void RegisterMetaInstanceCreator<engine::GameObject::DynamicAttributeList>();
	template<> void* MetaInstanceCreatorImpl<engine::LinearAccelerationExtractor, 1>::Create();
	template MetaInstanceCreatorImpl<engine::LinearAccelerationExtractor, 1>::MetaInstanceCreatorImpl(const char*, unsigned short, ClassMetaType*);
	template ClassMetaType* GetClassMetaType<engine::LinearAccelerationExtractor>();
	template void RegisterMetaInstanceCreator<engine::LinearAccelerationExtractor>();
	template<> void* MetaInstanceCreatorImpl<engine::LinearDisplacementExtractor, 1>::Create();
	template MetaInstanceCreatorImpl<engine::LinearDisplacementExtractor, 1>::MetaInstanceCreatorImpl(const char*, unsigned short, ClassMetaType*);
	template ClassMetaType* GetClassMetaType<engine::LinearDisplacementExtractor>();
	template void RegisterMetaInstanceCreator<engine::LinearDisplacementExtractor>();
	template<> void* MetaInstanceCreatorImpl<engine::LinearSpeedExtractor, 1>::Create();
	template MetaInstanceCreatorImpl<engine::LinearSpeedExtractor, 1>::MetaInstanceCreatorImpl(const char*, unsigned short, ClassMetaType*);
	template ClassMetaType* GetClassMetaType<engine::LinearSpeedExtractor>();
	template void RegisterMetaInstanceCreator<engine::LinearSpeedExtractor>();
	template<> void* MetaInstanceCreatorImpl<engine::RigidMotionTrackingFilter, 1>::Create();
	template MetaInstanceCreatorImpl<engine::RigidMotionTrackingFilter, 1>::MetaInstanceCreatorImpl(const char*, unsigned short, ClassMetaType*);
	template ClassMetaType* GetClassMetaType<engine::RigidMotionTrackingFilter>();
	template void RegisterMetaInstanceCreator<engine::RigidMotionTrackingFilter>();
	template<> void* MetaInstanceCreatorImpl<engine::Attribute<math::Vector>, 1>::Create();
	template MetaInstanceCreatorImpl<engine::Attribute<math::Vector>, 1>::MetaInstanceCreatorImpl(const char*, unsigned short, ClassMetaType*);
	template ClassMetaType* GetClassMetaType<engine::Attribute<math::Vector>>();
	template void RegisterMetaInstanceCreator<engine::Attribute<math::Vector>>();
	template<> void* MetaInstanceCreatorImpl<engine::ConstAttribute<math::Vector>, 1>::Create();
	template MetaInstanceCreatorImpl<engine::ConstAttribute<math::Vector>, 1>::MetaInstanceCreatorImpl(const char*, unsigned short, ClassMetaType*);
	template ClassMetaType* GetClassMetaType<engine::ConstAttribute<math::Vector>>();
	template void RegisterMetaInstanceCreator<engine::ConstAttribute<math::Vector>>();
	template<> void* MetaInstanceCreatorImpl<engine::Attribute<engine::GenericScriptValue>, 1>::Create();
	template MetaInstanceCreatorImpl<engine::Attribute<engine::GenericScriptValue>, 1>::MetaInstanceCreatorImpl(const char*, unsigned short, ClassMetaType*);
	template ClassMetaType* GetClassMetaType<engine::Attribute<engine::GenericScriptValue>>();
	template void RegisterMetaInstanceCreator<engine::Attribute<engine::GenericScriptValue>>();
	template<> void* MetaInstanceCreatorImpl<engine::ConstAttribute<engine::GenericScriptValue>, 1>::Create();
	template MetaInstanceCreatorImpl<engine::ConstAttribute<engine::GenericScriptValue>, 1>::MetaInstanceCreatorImpl(const char*, unsigned short, ClassMetaType*);
	template ClassMetaType* GetClassMetaType<engine::ConstAttribute<engine::GenericScriptValue>>();
	template void RegisterMetaInstanceCreator<engine::ConstAttribute<engine::GenericScriptValue>>();
	template<> LoadObject* MetaObjectFactory<engine::ContentManager::ContentCementFileDefinition, 1>::Create();
	template MetaObjectFactory<engine::ContentManager::ContentCementFileDefinition, 1>::MetaObjectFactory(const char*, unsigned short, ClassMetaType*);
	template ClassMetaType* GetClassMetaType<engine::ContentManager::ContentCementFileDefinition>();
	template void RegisterMetaObjectFactory<engine::ContentManager::ContentCementFileDefinition>();
	template class MetaInstanceCreatorImpl<engine::ChangeLightColourMessage, 1>;
	template ClassMetaType* GetClassMetaType<engine::ChangeLightColourMessage>();
	template void RegisterMetaInstanceCreator<engine::ChangeLightColourMessage>();
	template class MetaInstanceCreatorImpl<engine::EnableLightMessage, 1>;
	template ClassMetaType* GetClassMetaType<engine::EnableLightMessage>();
	template void RegisterMetaInstanceCreator<engine::EnableLightMessage>();
	template<> void* MetaInstanceCreatorImpl<math::Sphere, 1>::Create();
	template MetaInstanceCreatorImpl<math::Sphere, 1>::MetaInstanceCreatorImpl(const char*, unsigned short, ClassMetaType*);
	template ClassMetaType* GetClassMetaType<math::Sphere>();
	template void RegisterMetaInstanceCreator<math::Sphere>();
}

namespace engine
{
	template<> Behaviour* MetaBehaviourCreatorImpl<engine::MovingTriggerBehaviour>::CreateBehaviour(GameObject* owner);
	template MetaBehaviourCreatorImpl<engine::MovingTriggerBehaviour>::MetaBehaviourCreatorImpl(const char*, unsigned short, content::ClassMetaType*);
	template content::ClassMetaType* content::GetClassMetaType<engine::MovingTriggerBehaviour>();
	template void RegisterMetaBehaviourCreator<engine::MovingTriggerBehaviour>();
}

// The class meta types, factories, creators and registrations, in address order:
// FUNCTION: ENGINE 0x108D6E20 @ GetClassMetaType<animation::AttachmentPhysicsProperties>
// FUNCTION: ENGINE 0x108D6E70 @ MetaObjectFactory<animation::AttachmentPhysicsProperties,1>::MetaObjectFactory
// FUNCTION: ENGINE 0x108D6EA0 @ MetaObjectFactory<animation::AttachmentPhysicsProperties,1>::Create
// FUNCTION: ENGINE 0x108D6EC0 @ GetClassMetaType<ActorSpawner>
// FUNCTION: ENGINE 0x108D6F10 @ MetaObjectFactory<ActorSpawner,1>::MetaObjectFactory
// FUNCTION: ENGINE 0x108D6F40 @ MetaObjectFactory<ActorSpawner,1>::Create
// FUNCTION: ENGINE 0x108D6F60 @ GetClassMetaType<ActorCrowdSpawner>
// FUNCTION: ENGINE 0x108D6FB0 @ MetaObjectFactory<ActorCrowdSpawner,1>::MetaObjectFactory
// FUNCTION: ENGINE 0x108D6FE0 @ MetaObjectFactory<ActorCrowdSpawner,1>::Create
// FUNCTION: ENGINE 0x108D7000 @ GetClassMetaType<camera::CameraLoader>
// FUNCTION: ENGINE 0x108D7050 @ MetaObjectFactory<camera::CameraLoader,1>::MetaObjectFactory
// FUNCTION: ENGINE 0x108D7080 @ MetaObjectFactory<camera::CameraLoader,1>::Create
// FUNCTION: ENGINE 0x108D70A0 @ GetClassMetaType<CharacterIntentionInputMap>
// FUNCTION: ENGINE 0x108D70F0 @ MetaObjectFactory<CharacterIntentionInputMap,1>::MetaObjectFactory
// FUNCTION: ENGINE 0x108D7120 @ MetaObjectFactory<CharacterIntentionInputMap,1>::Create
// FUNCTION: ENGINE 0x108D7140 @ GetClassMetaType<driving::CarPhysicsAttributes>
// FUNCTION: ENGINE 0x108D7190 @ MetaObjectFactory<driving::CarPhysicsAttributes,1>::MetaObjectFactory
// FUNCTION: ENGINE 0x108D71C0 @ MetaObjectFactory<driving::CarPhysicsAttributes,1>::Create
// FUNCTION: ENGINE 0x108D71E0 @ GetClassMetaType<driving::HelicopterPhysicsAttributes>
// FUNCTION: ENGINE 0x108D7230 @ MetaObjectFactory<driving::HelicopterPhysicsAttributes,1>::MetaObjectFactory
// FUNCTION: ENGINE 0x108D7260 @ MetaObjectFactory<driving::HelicopterPhysicsAttributes,1>::Create
// FUNCTION: ENGINE 0x108D7280 @ GetClassMetaType<driving::VehiclePhysicsAttributes>
// FUNCTION: ENGINE 0x108D72D0 @ MetaObjectFactory<driving::VehiclePhysicsAttributes,1>::MetaObjectFactory
// FUNCTION: ENGINE 0x108D7300 @ MetaObjectFactory<driving::VehiclePhysicsAttributes,1>::Create
// FUNCTION: ENGINE 0x108D7320 @ GetClassMetaType<driving::WheelCollectionData>
// FUNCTION: ENGINE 0x108D7370 @ MetaObjectFactory<driving::WheelCollectionData,1>::MetaObjectFactory
// FUNCTION: ENGINE 0x108D73A0 @ MetaObjectFactory<driving::WheelCollectionData,1>::Create
// FUNCTION: ENGINE 0x108D73C0 @ GetClassMetaType<CharacterSolverProperties>
// FUNCTION: ENGINE 0x108D7410 @ MetaObjectFactory<CharacterSolverProperties,1>::MetaObjectFactory
// FUNCTION: ENGINE 0x108D7440 @ MetaObjectFactory<CharacterSolverProperties,1>::Create
// FUNCTION: ENGINE 0x108D7690 @ GetClassMetaType<GameObject>
// FUNCTION: ENGINE 0x108D76E0 @ MetaObjectFactory<GameObject,1>::MetaObjectFactory
// FUNCTION: ENGINE 0x108D7710 @ MetaObjectFactory<GameObject,1>::Create
// FUNCTION: ENGINE 0x108D7730 @ GetClassMetaType<GameObjectTemplateBuilder>
// FUNCTION: ENGINE 0x108D7780 @ MetaObjectFactory<GameObjectTemplateBuilder,1>::MetaObjectFactory
// FUNCTION: ENGINE 0x108D77B0 @ MetaObjectFactory<GameObjectTemplateBuilder,1>::Create
// FUNCTION: ENGINE 0x108D77D0 @ GetClassMetaType<NamedInventoryCreator>
// FUNCTION: ENGINE 0x108D7820 @ MetaObjectFactory<NamedInventoryCreator,1>::MetaObjectFactory
// FUNCTION: ENGINE 0x108D7850 @ MetaObjectFactory<NamedInventoryCreator,1>::Create
// FUNCTION: ENGINE 0x108D7940 @ GetClassMetaType<ravenphysics::ConstraintAngularSpringSharedProperties>
// FUNCTION: ENGINE 0x108D7990 @ MetaObjectFactory<ravenphysics::ConstraintAngularSpringSharedProperties,1>::MetaObjectFactory
// FUNCTION: ENGINE 0x108D79C0 @ MetaObjectFactory<ravenphysics::ConstraintAngularSpringSharedProperties,1>::Create
// FUNCTION: ENGINE 0x108D79E0 @ GetClassMetaType<ravenphysics::ConstraintAngularVelocitySharedProperties>
// FUNCTION: ENGINE 0x108D7A30 @ MetaObjectFactory<ravenphysics::ConstraintAngularVelocitySharedProperties,1>::MetaObjectFactory
// FUNCTION: ENGINE 0x108D7A60 @ MetaObjectFactory<ravenphysics::ConstraintAngularVelocitySharedProperties,1>::Create
// FUNCTION: ENGINE 0x108D7A80 @ GetClassMetaType<ravenphysics::ConstraintListFactory>
// FUNCTION: ENGINE 0x108D7AD0 @ MetaObjectFactory<ravenphysics::ConstraintListFactory,1>::MetaObjectFactory
// FUNCTION: ENGINE 0x108D7B00 @ MetaObjectFactory<ravenphysics::ConstraintListFactory,1>::Create
// FUNCTION: ENGINE 0x108D7B20 @ GetClassMetaType<ravenphysics::ConstraintSpringAlongAxisSharedProperties>
// FUNCTION: ENGINE 0x108D7B70 @ MetaObjectFactory<ravenphysics::ConstraintSpringAlongAxisSharedProperties,1>::MetaObjectFactory
// FUNCTION: ENGINE 0x108D7BA0 @ MetaObjectFactory<ravenphysics::ConstraintSpringAlongAxisSharedProperties,1>::Create
// FUNCTION: ENGINE 0x108D7BC0 @ GetClassMetaType<ravenphysics::DeformableOrientationConstraintSharedProperties>
// FUNCTION: ENGINE 0x108D7C10 @ MetaObjectFactory<ravenphysics::DeformableOrientationConstraintSharedProperties,1>::MetaObjectFactory
// FUNCTION: ENGINE 0x108D7C40 @ MetaObjectFactory<ravenphysics::DeformableOrientationConstraintSharedProperties,1>::Create
// FUNCTION: ENGINE 0x108D7C60 @ GetClassMetaType<ravenphysics::DeformableSliderConstraintSharedProperties>
// FUNCTION: ENGINE 0x108D7CB0 @ MetaObjectFactory<ravenphysics::DeformableSliderConstraintSharedProperties,1>::MetaObjectFactory
// FUNCTION: ENGINE 0x108D7CE0 @ MetaObjectFactory<ravenphysics::DeformableSliderConstraintSharedProperties,1>::Create
// FUNCTION: ENGINE 0x108D7D00 @ GetClassMetaType<ravenphysics::IntersectionPropertiesLoader>
// FUNCTION: ENGINE 0x108D7D50 @ MetaObjectFactory<ravenphysics::IntersectionPropertiesLoader,1>::MetaObjectFactory
// FUNCTION: ENGINE 0x108D7D80 @ MetaObjectFactory<ravenphysics::IntersectionPropertiesLoader,1>::Create
// FUNCTION: ENGINE 0x108D7DA0 @ GetClassMetaType<ravenphysics::MassProperties>
// FUNCTION: ENGINE 0x108D7DF0 @ MetaObjectFactory<ravenphysics::MassProperties,1>::MetaObjectFactory
// FUNCTION: ENGINE 0x108D7E20 @ MetaObjectFactory<ravenphysics::MassProperties,1>::Create
// FUNCTION: ENGINE 0x108D7E40 @ GetClassMetaType<ravenphysics::MaterialLoader>
// FUNCTION: ENGINE 0x108D7E90 @ MetaObjectFactory<ravenphysics::MaterialLoader,1>::MetaObjectFactory
// FUNCTION: ENGINE 0x108D7EC0 @ MetaObjectFactory<ravenphysics::MaterialLoader,1>::Create
// FUNCTION: ENGINE 0x108D7F80 @ GetClassMetaType<ravenphysics::PoweredConstraintSharedProperties>
// FUNCTION: ENGINE 0x108D7FD0 @ MetaObjectFactory<ravenphysics::PoweredConstraintSharedProperties,1>::MetaObjectFactory
// FUNCTION: ENGINE 0x108D8000 @ MetaObjectFactory<ravenphysics::PoweredConstraintSharedProperties,1>::Create
// FUNCTION: ENGINE 0x108D8020 @ GetClassMetaType<ravenphysics::SimplePhysicsObjectFactory>
// FUNCTION: ENGINE 0x108D8070 @ MetaObjectFactory<ravenphysics::SimplePhysicsObjectFactory,1>::MetaObjectFactory
// FUNCTION: ENGINE 0x108D80A0 @ MetaObjectFactory<ravenphysics::SimplePhysicsObjectFactory,1>::Create
// FUNCTION: ENGINE 0x108D80C0 @ GetClassMetaType<RemoteCamera>
// FUNCTION: ENGINE 0x108D8110 @ MetaObjectFactory<RemoteCamera,1>::MetaObjectFactory
// FUNCTION: ENGINE 0x108D8140 @ MetaObjectFactory<RemoteCamera,1>::Create
// FUNCTION: ENGINE 0x108D8160 @ GetClassMetaType<SecondaryPhysicsProperties>
// FUNCTION: ENGINE 0x108D81B0 @ MetaObjectFactory<SecondaryPhysicsProperties,1>::MetaObjectFactory
// FUNCTION: ENGINE 0x108D81E0 @ MetaObjectFactory<SecondaryPhysicsProperties,1>::Create
// FUNCTION: ENGINE 0x108D8200 @ GetClassMetaType<SkuInfo>
// FUNCTION: ENGINE 0x108D8250 @ MetaObjectFactory<SkuInfo,1>::MetaObjectFactory
// FUNCTION: ENGINE 0x108D8280 @ MetaObjectFactory<SkuInfo,1>::Create
// FUNCTION: ENGINE 0x108D82A0 @ GetClassMetaType<SplinePath>
// FUNCTION: ENGINE 0x108D82F0 @ MetaObjectFactory<SplinePath,1>::MetaObjectFactory
// FUNCTION: ENGINE 0x108D8320 @ MetaObjectFactory<SplinePath,1>::Create
// FUNCTION: ENGINE 0x108D8340 @ GetClassMetaType<StreamPackage>
// FUNCTION: ENGINE 0x108D8390 @ MetaObjectFactory<StreamPackage,1>::MetaObjectFactory
// FUNCTION: ENGINE 0x108D83C0 @ MetaObjectFactory<StreamPackage,1>::Create
// FUNCTION: ENGINE 0x108D83E0 @ GetClassMetaType<StreamSlotGroup>
// FUNCTION: ENGINE 0x108D8430 @ MetaObjectFactory<StreamSlotGroup,1>::MetaObjectFactory
// FUNCTION: ENGINE 0x108D8460 @ MetaObjectFactory<StreamSlotGroup,1>::Create
// FUNCTION: ENGINE 0x108D8480 @ GetClassMetaType<StreamTrigger>
// FUNCTION: ENGINE 0x108D84D0 @ MetaObjectFactory<StreamTrigger,1>::MetaObjectFactory
// FUNCTION: ENGINE 0x108D8500 @ MetaObjectFactory<StreamTrigger,1>::Create
// FUNCTION: ENGINE 0x108D8520 @ GetClassMetaType<SupportingLimbDefinition>
// FUNCTION: ENGINE 0x108D8570 @ MetaObjectFactory<SupportingLimbDefinition,1>::MetaObjectFactory
// FUNCTION: ENGINE 0x108D85A0 @ MetaObjectFactory<SupportingLimbDefinition,1>::Create
// FUNCTION: ENGINE 0x108D85C0 @ GetClassMetaType<SupportingLimbDefinitionList>
// FUNCTION: ENGINE 0x108D8610 @ MetaObjectFactory<SupportingLimbDefinitionList,1>::MetaObjectFactory
// FUNCTION: ENGINE 0x108D8640 @ MetaObjectFactory<SupportingLimbDefinitionList,1>::Create
// FUNCTION: ENGINE 0x108D8660 @ GetClassMetaType<SurfaceDefinition>
// FUNCTION: ENGINE 0x108D86B0 @ MetaObjectFactory<SurfaceDefinition,1>::MetaObjectFactory
// FUNCTION: ENGINE 0x108D86E0 @ MetaObjectFactory<SurfaceDefinition,1>::Create
// FUNCTION: ENGINE 0x108D8700 @ GetClassMetaType<TrackedMotionToExpressionMap>
// FUNCTION: ENGINE 0x108D8750 @ MetaObjectFactory<TrackedMotionToExpressionMap,1>::MetaObjectFactory
// FUNCTION: ENGINE 0x108D8780 @ MetaObjectFactory<TrackedMotionToExpressionMap,1>::Create
// FUNCTION: ENGINE 0x108D87A0 @ GetClassMetaType<world::Location>
// FUNCTION: ENGINE 0x108D87F0 @ MetaObjectFactory<world::Location,1>::MetaObjectFactory
// FUNCTION: ENGINE 0x108D8820 @ MetaObjectFactory<world::Location,1>::Create
// FUNCTION: ENGINE 0x108D8840 @ GetClassMetaType<world::LocationRenderSettings>
// FUNCTION: ENGINE 0x108D8890 @ MetaObjectFactory<world::LocationRenderSettings,1>::MetaObjectFactory
// FUNCTION: ENGINE 0x108D88C0 @ MetaObjectFactory<world::LocationRenderSettings,1>::Create
// FUNCTION: ENGINE 0x108D8A40 @ GetClassMetaType<NISExclusionVolume>
// FUNCTION: ENGINE 0x108D8A90 @ MetaObjectFactory<NISExclusionVolume,1>::MetaObjectFactory
// FUNCTION: ENGINE 0x108D8AC0 @ GetClassMetaType<FmvSubtitleManager>
// FUNCTION: ENGINE 0x108D8B10 @ MetaObjectFactory<FmvSubtitleManager,1>::MetaObjectFactory
// FUNCTION: ENGINE 0x108D8B40 @ MetaObjectFactory<FmvSubtitleManager,1>::Create
// FUNCTION: ENGINE 0x108D91D0 @ GetClassMetaType<camera::FPSCamera>
// FUNCTION: ENGINE 0x108D9220 @ MetaInstanceCreatorImpl<camera::FPSCamera,1>::MetaInstanceCreatorImpl
// FUNCTION: ENGINE 0x108D9250 @ MetaInstanceCreatorImpl<camera::FPSCamera,1>::Create
// FUNCTION: ENGINE 0x108D9270 @ GetClassMetaType<camera::OnFootCamera>
// FUNCTION: ENGINE 0x108D92C0 @ MetaInstanceCreatorImpl<camera::OnFootCamera,1>::MetaInstanceCreatorImpl
// FUNCTION: ENGINE 0x108D92F0 @ MetaInstanceCreatorImpl<camera::OnFootCamera,1>::Create
// FUNCTION: ENGINE 0x108D9310 @ GetClassMetaType<camera::ScriptedCamera>
// FUNCTION: ENGINE 0x108D9360 @ MetaInstanceCreatorImpl<camera::ScriptedCamera,1>::MetaInstanceCreatorImpl
// FUNCTION: ENGINE 0x108D9390 @ MetaInstanceCreatorImpl<camera::ScriptedCamera,1>::Create
// FUNCTION: ENGINE 0x108D9490 @ GetClassMetaType<DampedAngularMotionTrackingFilter>
// FUNCTION: ENGINE 0x108D94E0 @ MetaInstanceCreatorImpl<DampedAngularMotionTrackingFilter,1>::MetaInstanceCreatorImpl
// FUNCTION: ENGINE 0x108D9510 @ MetaInstanceCreatorImpl<DampedAngularMotionTrackingFilter,1>::Create
// FUNCTION: ENGINE 0x108D9530 @ GetClassMetaType<DampedLinearMotionTrackingFilter>
// FUNCTION: ENGINE 0x108D9580 @ MetaInstanceCreatorImpl<DampedLinearMotionTrackingFilter,1>::MetaInstanceCreatorImpl
// FUNCTION: ENGINE 0x108D95B0 @ MetaInstanceCreatorImpl<DampedLinearMotionTrackingFilter,1>::Create
// FUNCTION: ENGINE 0x108D96A0 @ GetClassMetaType<SplinePathCV>
// FUNCTION: ENGINE 0x108D96F0 @ MetaInstanceCreatorImpl<SplinePathCV,1>::MetaInstanceCreatorImpl
// FUNCTION: ENGINE 0x108D9720 @ MetaInstanceCreatorImpl<SplinePathCV,1>::Create
// FUNCTION: ENGINE 0x108D9820 @ GetClassMetaType<EnterTriggerMessage>
// FUNCTION: ENGINE 0x108D9870 @ MetaInstanceCreatorImpl<EnterTriggerMessage,1>::MetaInstanceCreatorImpl
// FUNCTION: ENGINE 0x108D98A0 @ GetClassMetaType<ExitTriggerMessage>
// FUNCTION: ENGINE 0x108D98F0 @ MetaInstanceCreatorImpl<ExitTriggerMessage,1>::MetaInstanceCreatorImpl
// FUNCTION: ENGINE 0x108D9C40 @ GetClassMetaType<SecondaryPhysicsAmbientWind>
// FUNCTION: ENGINE 0x108D9C90 @ MetaInstanceCreatorImpl<SecondaryPhysicsAmbientWind,1>::MetaInstanceCreatorImpl
// FUNCTION: ENGINE 0x108D9CC0 @ MetaInstanceCreatorImpl<SecondaryPhysicsAmbientWind,1>::Create
// FUNCTION: ENGINE 0x108D9CE0 @ GetClassMetaType<SecondaryPhysicsPinJoint>
// FUNCTION: ENGINE 0x108D9D30 @ MetaInstanceCreatorImpl<SecondaryPhysicsPinJoint,1>::MetaInstanceCreatorImpl
// FUNCTION: ENGINE 0x108D9D60 @ MetaInstanceCreatorImpl<SecondaryPhysicsPinJoint,1>::Create
// FUNCTION: ENGINE 0x108D9D80 @ GetClassMetaType<SecondaryPhysicsPoweredJoint>
// FUNCTION: ENGINE 0x108D9DD0 @ MetaInstanceCreatorImpl<SecondaryPhysicsPoweredJoint,1>::MetaInstanceCreatorImpl
// FUNCTION: ENGINE 0x108D9E00 @ MetaInstanceCreatorImpl<SecondaryPhysicsPoweredJoint,1>::Create
// FUNCTION: ENGINE 0x108D9E20 @ GetClassMetaType<SpringBasedAngularMotionFilter>
// FUNCTION: ENGINE 0x108D9E70 @ MetaInstanceCreatorImpl<SpringBasedAngularMotionFilter,1>::MetaInstanceCreatorImpl
// FUNCTION: ENGINE 0x108D9EA0 @ MetaInstanceCreatorImpl<SpringBasedAngularMotionFilter,1>::Create
// FUNCTION: ENGINE 0x108D9EC0 @ GetClassMetaType<SpringBasedLinearMotionFilter>
// FUNCTION: ENGINE 0x108D9F10 @ MetaInstanceCreatorImpl<SpringBasedLinearMotionFilter,1>::MetaInstanceCreatorImpl
// FUNCTION: ENGINE 0x108D9F40 @ MetaInstanceCreatorImpl<SpringBasedLinearMotionFilter,1>::Create
// FUNCTION: ENGINE 0x108D9F60 @ GetClassMetaType<trigger::OBBVolume>
// FUNCTION: ENGINE 0x108D9FB0 @ MetaInstanceCreatorImpl<trigger::OBBVolume,1>::MetaInstanceCreatorImpl
// FUNCTION: ENGINE 0x108D9FE0 @ MetaInstanceCreatorImpl<trigger::OBBVolume,1>::Create
// FUNCTION: ENGINE 0x108DA000 @ GetClassMetaType<trigger::SphereVolume>
// FUNCTION: ENGINE 0x108DA050 @ MetaInstanceCreatorImpl<trigger::SphereVolume,1>::MetaInstanceCreatorImpl
// FUNCTION: ENGINE 0x108DA080 @ MetaInstanceCreatorImpl<trigger::SphereVolume,1>::Create
// FUNCTION: ENGINE 0x108DA200 @ GetClassMetaType<AdvertisementBehaviour>
// FUNCTION: ENGINE 0x108DA250 @ MetaBehaviourCreatorImpl<AdvertisementBehaviour>::MetaBehaviourCreatorImpl
// FUNCTION: ENGINE 0x108DA280 @ MetaBehaviourCreatorImpl<AdvertisementBehaviour>::CreateBehaviour
// FUNCTION: ENGINE 0x108DA2F0 @ GetClassMetaType<animation::JawFlapBehaviour>
// FUNCTION: ENGINE 0x108DA340 @ MetaBehaviourCreatorImpl<animation::JawFlapBehaviour>::MetaBehaviourCreatorImpl
// FUNCTION: ENGINE 0x108DA370 @ MetaBehaviourCreatorImpl<animation::JawFlapBehaviour>::CreateBehaviour
// FUNCTION: ENGINE 0x108DA390 @ GetClassMetaType<animation::PuppetBehaviour>
// FUNCTION: ENGINE 0x108DA3E0 @ MetaBehaviourCreatorImpl<animation::PuppetBehaviour>::MetaBehaviourCreatorImpl
// FUNCTION: ENGINE 0x108DA410 @ MetaBehaviourCreatorImpl<animation::PuppetBehaviour>::CreateBehaviour
// FUNCTION: ENGINE 0x108DA480 @ GetClassMetaType<camera::CameraBehaviour>
// FUNCTION: ENGINE 0x108DA4D0 @ MetaBehaviourCreatorImpl<camera::CameraBehaviour>::MetaBehaviourCreatorImpl
// FUNCTION: ENGINE 0x108DA500 @ MetaBehaviourCreatorImpl<camera::CameraBehaviour>::CreateBehaviour
// FUNCTION: ENGINE 0x108DA520 @ GetClassMetaType<camera::CinematographerBehaviour>
// FUNCTION: ENGINE 0x108DA570 @ MetaBehaviourCreatorImpl<camera::CinematographerBehaviour>::MetaBehaviourCreatorImpl
// FUNCTION: ENGINE 0x108DA5A0 @ MetaBehaviourCreatorImpl<camera::CinematographerBehaviour>::CreateBehaviour
// FUNCTION: ENGINE 0x108DA5C0 @ GetClassMetaType<CharacterIntentionBehaviour>
// FUNCTION: ENGINE 0x108DA610 @ MetaBehaviourCreatorImpl<CharacterIntentionBehaviour>::MetaBehaviourCreatorImpl
// FUNCTION: ENGINE 0x108DA640 @ MetaBehaviourCreatorImpl<CharacterIntentionBehaviour>::CreateBehaviour
// FUNCTION: ENGINE 0x108DA660 @ GetClassMetaType<CharacterSolverBehaviour>
// FUNCTION: ENGINE 0x108DA6B0 @ MetaBehaviourCreatorImpl<CharacterSolverBehaviour>::MetaBehaviourCreatorImpl
// FUNCTION: ENGINE 0x108DA6E0 @ MetaBehaviourCreatorImpl<CharacterSolverBehaviour>::CreateBehaviour
// FUNCTION: ENGINE 0x108DA700 @ GetClassMetaType<driving::CarIntentionBehaviour>
// FUNCTION: ENGINE 0x108DA750 @ MetaBehaviourCreatorImpl<driving::CarIntentionBehaviour>::MetaBehaviourCreatorImpl
// FUNCTION: ENGINE 0x108DA780 @ MetaBehaviourCreatorImpl<driving::CarIntentionBehaviour>::CreateBehaviour
// FUNCTION: ENGINE 0x108DA7A0 @ GetClassMetaType<driving::CarPhysicsBehaviour>
// FUNCTION: ENGINE 0x108DA7F0 @ MetaBehaviourCreatorImpl<driving::CarPhysicsBehaviour>::MetaBehaviourCreatorImpl
// FUNCTION: ENGINE 0x108DA820 @ MetaBehaviourCreatorImpl<driving::CarPhysicsBehaviour>::CreateBehaviour
// FUNCTION: ENGINE 0x108DA840 @ GetClassMetaType<driving::HelicopterIntentionBehaviour>
// FUNCTION: ENGINE 0x108DA890 @ MetaBehaviourCreatorImpl<driving::HelicopterIntentionBehaviour>::MetaBehaviourCreatorImpl
// FUNCTION: ENGINE 0x108DA8C0 @ MetaBehaviourCreatorImpl<driving::HelicopterIntentionBehaviour>::CreateBehaviour
// FUNCTION: ENGINE 0x108DA8E0 @ GetClassMetaType<driving::HelicopterPhysicsBehaviour>
// FUNCTION: ENGINE 0x108DA930 @ MetaBehaviourCreatorImpl<driving::HelicopterPhysicsBehaviour>::MetaBehaviourCreatorImpl
// FUNCTION: ENGINE 0x108DA960 @ MetaBehaviourCreatorImpl<driving::HelicopterPhysicsBehaviour>::CreateBehaviour
// FUNCTION: ENGINE 0x108DA980 @ GetClassMetaType<FirstPersonControlBehaviour>
// FUNCTION: ENGINE 0x108DA9D0 @ MetaBehaviourCreatorImpl<FirstPersonControlBehaviour>::MetaBehaviourCreatorImpl
// FUNCTION: ENGINE 0x108DAA00 @ MetaBehaviourCreatorImpl<FirstPersonControlBehaviour>::CreateBehaviour
// FUNCTION: ENGINE 0x108DAA70 @ GetClassMetaType<KnockBehaviour>
// FUNCTION: ENGINE 0x108DAAC0 @ MetaBehaviourCreatorImpl<KnockBehaviour>::MetaBehaviourCreatorImpl
// FUNCTION: ENGINE 0x108DAAF0 @ MetaBehaviourCreatorImpl<KnockBehaviour>::CreateBehaviour
// FUNCTION: ENGINE 0x108DABC0 @ GetClassMetaType<MotionTreeBehaviour>
// FUNCTION: ENGINE 0x108DAC10 @ MetaBehaviourCreatorImpl<MotionTreeBehaviour>::MetaBehaviourCreatorImpl
// FUNCTION: ENGINE 0x108DAC40 @ MetaBehaviourCreatorImpl<MotionTreeBehaviour>::CreateBehaviour
// FUNCTION: ENGINE 0x108DAC60 @ GetClassMetaType<NISPlayerBehaviour>
// FUNCTION: ENGINE 0x108DACB0 @ MetaBehaviourCreatorImpl<NISPlayerBehaviour>::MetaBehaviourCreatorImpl
// FUNCTION: ENGINE 0x108DACE0 @ MetaBehaviourCreatorImpl<NISPlayerBehaviour>::CreateBehaviour
// FUNCTION: ENGINE 0x108DAD00 @ GetClassMetaType<PatrolPathBehaviour>
// FUNCTION: ENGINE 0x108DAD50 @ MetaBehaviourCreatorImpl<PatrolPathBehaviour>::MetaBehaviourCreatorImpl
// FUNCTION: ENGINE 0x108DAD80 @ MetaBehaviourCreatorImpl<PatrolPathBehaviour>::CreateBehaviour
// FUNCTION: ENGINE 0x108DADA0 @ GetClassMetaType<PlaybackTreeBehaviour>
// FUNCTION: ENGINE 0x108DADF0 @ MetaBehaviourCreatorImpl<PlaybackTreeBehaviour>::MetaBehaviourCreatorImpl
// FUNCTION: ENGINE 0x108DAE20 @ MetaBehaviourCreatorImpl<PlaybackTreeBehaviour>::CreateBehaviour
// FUNCTION: ENGINE 0x108DAE40 @ GetClassMetaType<PoseAnimationBehaviour>
// FUNCTION: ENGINE 0x108DAE90 @ MetaBehaviourCreatorImpl<PoseAnimationBehaviour>::MetaBehaviourCreatorImpl
// FUNCTION: ENGINE 0x108DAEC0 @ MetaBehaviourCreatorImpl<PoseAnimationBehaviour>::CreateBehaviour
// FUNCTION: ENGINE 0x108DAEE0 @ GetClassMetaType<PropLogicTreeBehaviour>
// FUNCTION: ENGINE 0x108DAF30 @ MetaBehaviourCreatorImpl<PropLogicTreeBehaviour>::MetaBehaviourCreatorImpl
// FUNCTION: ENGINE 0x108DAF60 @ MetaBehaviourCreatorImpl<PropLogicTreeBehaviour>::CreateBehaviour
// FUNCTION: ENGINE 0x108DAF80 @ GetClassMetaType<PhysicsBehaviour>
// FUNCTION: ENGINE 0x108DAFD0 @ MetaBehaviourCreatorImpl<PhysicsBehaviour>::MetaBehaviourCreatorImpl
// FUNCTION: ENGINE 0x108DB000 @ MetaBehaviourCreatorImpl<PhysicsBehaviour>::CreateBehaviour
// FUNCTION: ENGINE 0x108DB020 @ GetClassMetaType<PropBehaviour>
// FUNCTION: ENGINE 0x108DB070 @ MetaBehaviourCreatorImpl<PropBehaviour>::MetaBehaviourCreatorImpl
// FUNCTION: ENGINE 0x108DB0A0 @ MetaBehaviourCreatorImpl<PropBehaviour>::CreateBehaviour
// FUNCTION: ENGINE 0x108DB0C0 @ GetClassMetaType<RagdollBehaviour>
// FUNCTION: ENGINE 0x108DB110 @ MetaBehaviourCreatorImpl<RagdollBehaviour>::MetaBehaviourCreatorImpl
// FUNCTION: ENGINE 0x108DB140 @ MetaBehaviourCreatorImpl<RagdollBehaviour>::CreateBehaviour
// FUNCTION: ENGINE 0x108DB160 @ GetClassMetaType<RagdollLODBehaviour>
// FUNCTION: ENGINE 0x108DB1B0 @ MetaBehaviourCreatorImpl<RagdollLODBehaviour>::MetaBehaviourCreatorImpl
// FUNCTION: ENGINE 0x108DB1E0 @ MetaBehaviourCreatorImpl<RagdollLODBehaviour>::CreateBehaviour
// FUNCTION: ENGINE 0x108DB200 @ GetClassMetaType<RenderBehaviour>
// FUNCTION: ENGINE 0x108DB250 @ MetaBehaviourCreatorImpl<RenderBehaviour>::MetaBehaviourCreatorImpl
// FUNCTION: ENGINE 0x108DB280 @ MetaBehaviourCreatorImpl<RenderBehaviour>::CreateBehaviour
// FUNCTION: ENGINE 0x108DB2A0 @ GetClassMetaType<SecondaryPhysicsBehaviour>
// FUNCTION: ENGINE 0x108DB2F0 @ MetaBehaviourCreatorImpl<SecondaryPhysicsBehaviour>::MetaBehaviourCreatorImpl
// FUNCTION: ENGINE 0x108DB320 @ MetaBehaviourCreatorImpl<SecondaryPhysicsBehaviour>::CreateBehaviour
// FUNCTION: ENGINE 0x108DB340 @ GetClassMetaType<SplineBehaviour>
// FUNCTION: ENGINE 0x108DB390 @ MetaBehaviourCreatorImpl<SplineBehaviour>::MetaBehaviourCreatorImpl
// FUNCTION: ENGINE 0x108DB3C0 @ MetaBehaviourCreatorImpl<SplineBehaviour>::CreateBehaviour
// FUNCTION: ENGINE 0x108DB3E0 @ GetClassMetaType<TagBehaviour>
// FUNCTION: ENGINE 0x108DB430 @ MetaBehaviourCreatorImpl<TagBehaviour>::MetaBehaviourCreatorImpl
// FUNCTION: ENGINE 0x108DB460 @ MetaBehaviourCreatorImpl<TagBehaviour>::CreateBehaviour
// FUNCTION: ENGINE 0x108DB480 @ GetClassMetaType<TouchBehaviour>
// FUNCTION: ENGINE 0x108DB4D0 @ MetaBehaviourCreatorImpl<TouchBehaviour>::MetaBehaviourCreatorImpl
// FUNCTION: ENGINE 0x108DB500 @ MetaBehaviourCreatorImpl<TouchBehaviour>::CreateBehaviour
// FUNCTION: ENGINE 0x108DB520 @ GetClassMetaType<TrackedMotionToExpressionBehaviour>
// FUNCTION: ENGINE 0x108DB570 @ MetaBehaviourCreatorImpl<TrackedMotionToExpressionBehaviour>::MetaBehaviourCreatorImpl
// FUNCTION: ENGINE 0x108DB5A0 @ MetaBehaviourCreatorImpl<TrackedMotionToExpressionBehaviour>::CreateBehaviour
// FUNCTION: ENGINE 0x108DB930 @ RegisterMetaObjectFactory<animation::AttachmentPhysicsProperties>
// FUNCTION: ENGINE 0x108DB980 @ RegisterMetaObjectFactory<ActorSpawner>
// FUNCTION: ENGINE 0x108DB9D0 @ RegisterMetaObjectFactory<ActorCrowdSpawner>
// FUNCTION: ENGINE 0x108DBA20 @ RegisterMetaObjectFactory<camera::CameraLoader>
// FUNCTION: ENGINE 0x108DBA70 @ RegisterMetaObjectFactory<CharacterIntentionInputMap>
// FUNCTION: ENGINE 0x108DBAC0 @ RegisterMetaObjectFactory<driving::CarPhysicsAttributes>
// FUNCTION: ENGINE 0x108DBB10 @ RegisterMetaObjectFactory<driving::HelicopterPhysicsAttributes>
// FUNCTION: ENGINE 0x108DBB60 @ RegisterMetaObjectFactory<driving::VehiclePhysicsAttributes>
// FUNCTION: ENGINE 0x108DBBB0 @ RegisterMetaObjectFactory<driving::WheelCollectionData>
// FUNCTION: ENGINE 0x108DBC00 @ RegisterMetaObjectFactory<CharacterSolverProperties>
// FUNCTION: ENGINE 0x108DBD40 @ RegisterMetaObjectFactory<GameObject>
// FUNCTION: ENGINE 0x108DBD90 @ RegisterMetaObjectFactory<GameObjectTemplateBuilder>
// FUNCTION: ENGINE 0x108DBDE0 @ RegisterMetaObjectFactory<NamedInventoryCreator>
// FUNCTION: ENGINE 0x108DBED0 @ RegisterMetaObjectFactory<ravenphysics::ConstraintAngularSpringSharedProperties>
// FUNCTION: ENGINE 0x108DBF20 @ RegisterMetaObjectFactory<ravenphysics::ConstraintAngularVelocitySharedProperties>
// FUNCTION: ENGINE 0x108DBF70 @ RegisterMetaObjectFactory<ravenphysics::ConstraintListFactory>
// FUNCTION: ENGINE 0x108DBFC0 @ RegisterMetaObjectFactory<ravenphysics::ConstraintSpringAlongAxisSharedProperties>
// FUNCTION: ENGINE 0x108DC010 @ RegisterMetaObjectFactory<ravenphysics::DeformableOrientationConstraintSharedProperties>
// FUNCTION: ENGINE 0x108DC060 @ RegisterMetaObjectFactory<ravenphysics::DeformableSliderConstraintSharedProperties>
// FUNCTION: ENGINE 0x108DC0B0 @ RegisterMetaObjectFactory<ravenphysics::IntersectionPropertiesLoader>
// FUNCTION: ENGINE 0x108DC100 @ RegisterMetaObjectFactory<ravenphysics::MassProperties>
// FUNCTION: ENGINE 0x108DC150 @ RegisterMetaObjectFactory<ravenphysics::MaterialLoader>
// FUNCTION: ENGINE 0x108DC1F0 @ RegisterMetaObjectFactory<ravenphysics::PoweredConstraintSharedProperties>
// FUNCTION: ENGINE 0x108DC240 @ RegisterMetaObjectFactory<ravenphysics::SimplePhysicsObjectFactory>
// FUNCTION: ENGINE 0x108DC290 @ RegisterMetaObjectFactory<RemoteCamera>
// FUNCTION: ENGINE 0x108DC2E0 @ RegisterMetaObjectFactory<SecondaryPhysicsProperties>
// FUNCTION: ENGINE 0x108DC330 @ RegisterMetaObjectFactory<SkuInfo>
// FUNCTION: ENGINE 0x108DC380 @ RegisterMetaObjectFactory<SplinePath>
// FUNCTION: ENGINE 0x108DC3D0 @ RegisterMetaObjectFactory<StreamPackage>
// FUNCTION: ENGINE 0x108DC420 @ RegisterMetaObjectFactory<StreamSlotGroup>
// FUNCTION: ENGINE 0x108DC470 @ RegisterMetaObjectFactory<StreamTrigger>
// FUNCTION: ENGINE 0x108DC4C0 @ RegisterMetaObjectFactory<SupportingLimbDefinition>
// FUNCTION: ENGINE 0x108DC510 @ RegisterMetaObjectFactory<SupportingLimbDefinitionList>
// FUNCTION: ENGINE 0x108DC560 @ RegisterMetaObjectFactory<SurfaceDefinition>
// FUNCTION: ENGINE 0x108DC5B0 @ RegisterMetaObjectFactory<TrackedMotionToExpressionMap>
// FUNCTION: ENGINE 0x108DC600 @ RegisterMetaObjectFactory<world::Location>
// FUNCTION: ENGINE 0x108DC650 @ RegisterMetaObjectFactory<world::LocationRenderSettings>
// FUNCTION: ENGINE 0x108DC6F0 @ RegisterMetaObjectFactory<NISExclusionVolume>
// FUNCTION: ENGINE 0x108DC740 @ RegisterMetaObjectFactory<FmvSubtitleManager>
// FUNCTION: ENGINE 0x108DCCE0 @ RegisterMetaInstanceCreator<camera::FPSCamera>
// FUNCTION: ENGINE 0x108DCD30 @ RegisterMetaInstanceCreator<camera::OnFootCamera>
// FUNCTION: ENGINE 0x108DCD80 @ RegisterMetaInstanceCreator<camera::ScriptedCamera>
// FUNCTION: ENGINE 0x108DCE20 @ RegisterMetaInstanceCreator<DampedAngularMotionTrackingFilter>
// FUNCTION: ENGINE 0x108DCE70 @ RegisterMetaInstanceCreator<DampedLinearMotionTrackingFilter>
// FUNCTION: ENGINE 0x108DCFB0 @ RegisterMetaInstanceCreator<SplinePathCV>
// FUNCTION: ENGINE 0x108DD050 @ RegisterMetaInstanceCreator<EnterTriggerMessage>
// FUNCTION: ENGINE 0x108DD0A0 @ RegisterMetaInstanceCreator<ExitTriggerMessage>
// FUNCTION: ENGINE 0x108DD370 @ RegisterMetaInstanceCreator<SecondaryPhysicsAmbientWind>
// FUNCTION: ENGINE 0x108DD3C0 @ RegisterMetaInstanceCreator<SecondaryPhysicsPinJoint>
// FUNCTION: ENGINE 0x108DD410 @ RegisterMetaInstanceCreator<SecondaryPhysicsPoweredJoint>
// FUNCTION: ENGINE 0x108DD460 @ RegisterMetaInstanceCreator<SpringBasedAngularMotionFilter>
// FUNCTION: ENGINE 0x108DD4B0 @ RegisterMetaInstanceCreator<SpringBasedLinearMotionFilter>
// FUNCTION: ENGINE 0x108DD500 @ RegisterMetaInstanceCreator<trigger::OBBVolume>
// FUNCTION: ENGINE 0x108DD550 @ RegisterMetaInstanceCreator<trigger::SphereVolume>
// FUNCTION: ENGINE 0x108DD6E0 @ RegisterMetaBehaviourCreator<AdvertisementBehaviour>
// FUNCTION: ENGINE 0x108DD780 @ RegisterMetaBehaviourCreator<animation::JawFlapBehaviour>
// FUNCTION: ENGINE 0x108DD7D0 @ RegisterMetaBehaviourCreator<animation::PuppetBehaviour>
// FUNCTION: ENGINE 0x108DD870 @ RegisterMetaBehaviourCreator<camera::CameraBehaviour>
// FUNCTION: ENGINE 0x108DD8C0 @ RegisterMetaBehaviourCreator<camera::CinematographerBehaviour>
// FUNCTION: ENGINE 0x108DD910 @ RegisterMetaBehaviourCreator<CharacterIntentionBehaviour>
// FUNCTION: ENGINE 0x108DD960 @ RegisterMetaBehaviourCreator<CharacterSolverBehaviour>
// FUNCTION: ENGINE 0x108DD9B0 @ RegisterMetaBehaviourCreator<driving::CarIntentionBehaviour>
// FUNCTION: ENGINE 0x108DDA00 @ RegisterMetaBehaviourCreator<driving::CarPhysicsBehaviour>
// FUNCTION: ENGINE 0x108DDA50 @ RegisterMetaBehaviourCreator<driving::HelicopterIntentionBehaviour>
// FUNCTION: ENGINE 0x108DDAA0 @ RegisterMetaBehaviourCreator<driving::HelicopterPhysicsBehaviour>
// FUNCTION: ENGINE 0x108DDAF0 @ RegisterMetaBehaviourCreator<FirstPersonControlBehaviour>
// FUNCTION: ENGINE 0x108DDB90 @ RegisterMetaBehaviourCreator<KnockBehaviour>
// FUNCTION: ENGINE 0x108DDC30 @ RegisterMetaBehaviourCreator<MotionTreeBehaviour>
// FUNCTION: ENGINE 0x108DDC80 @ RegisterMetaBehaviourCreator<NISPlayerBehaviour>
// FUNCTION: ENGINE 0x108DDCD0 @ RegisterMetaBehaviourCreator<PatrolPathBehaviour>
// FUNCTION: ENGINE 0x108DDD20 @ RegisterMetaBehaviourCreator<PlaybackTreeBehaviour>
// FUNCTION: ENGINE 0x108DDD70 @ RegisterMetaBehaviourCreator<PoseAnimationBehaviour>
// FUNCTION: ENGINE 0x108DDDC0 @ RegisterMetaBehaviourCreator<PropLogicTreeBehaviour>
// FUNCTION: ENGINE 0x108DDE10 @ RegisterMetaBehaviourCreator<PhysicsBehaviour>
// FUNCTION: ENGINE 0x108DDE60 @ RegisterMetaBehaviourCreator<PropBehaviour>
// FUNCTION: ENGINE 0x108DDEB0 @ RegisterMetaBehaviourCreator<RagdollBehaviour>
// FUNCTION: ENGINE 0x108DDF00 @ RegisterMetaBehaviourCreator<RagdollLODBehaviour>
// FUNCTION: ENGINE 0x108DDF50 @ RegisterMetaBehaviourCreator<RenderBehaviour>
// FUNCTION: ENGINE 0x108DDFA0 @ RegisterMetaBehaviourCreator<SecondaryPhysicsBehaviour>
// FUNCTION: ENGINE 0x108DDFF0 @ RegisterMetaBehaviourCreator<SplineBehaviour>
// FUNCTION: ENGINE 0x108DE040 @ RegisterMetaBehaviourCreator<TagBehaviour>
// FUNCTION: ENGINE 0x108DE090 @ RegisterMetaBehaviourCreator<TouchBehaviour>
// FUNCTION: ENGINE 0x108DE0E0 @ RegisterMetaBehaviourCreator<TrackedMotionToExpressionBehaviour>
// FUNCTION: ENGINE 0x108DE1D0 @ MetaObjectFactory<NISExclusionVolume,1>::Create
// FUNCTION: ENGINE 0x108DE1F0 @ MetaInstanceCreatorImpl<EnterTriggerMessage,1>::Create
// FUNCTION: ENGINE 0x108DE220 @ MetaInstanceCreatorImpl<ExitTriggerMessage,1>::Create
// BEGIN GENERATED ANNOTATIONS
// FUNCTION: ENGINE 0x108C69B0 @ GetClassMetaType<math::Plane>
// FUNCTION: ENGINE 0x108D7460 @ GetClassMetaType<ContentManager::ContentPackageDefinition>
// FUNCTION: ENGINE 0x108D74B0 @ MetaObjectFactory<ContentManager::ContentPackageDefinition,1>::MetaObjectFactory
// FUNCTION: ENGINE 0x108D74E0 @ MetaObjectFactory<ContentManager::ContentPackageDefinition,1>::Create
// FUNCTION: ENGINE 0x108D7500 @ GetClassMetaType<ContentManager::ContentPackageKey>
// FUNCTION: ENGINE 0x108D7550 @ MetaObjectFactory<ContentManager::ContentPackageKey,1>::MetaObjectFactory
// FUNCTION: ENGINE 0x108D7580 @ MetaObjectFactory<ContentManager::ContentPackageKey,1>::Create
// FUNCTION: ENGINE 0x108D7870 @ MetaObjectFactory<PropSpawner,1>::MetaObjectFactory
// FUNCTION: ENGINE 0x108D78A0 @ MetaObjectFactory<PropSpawner,1>::Create
// FUNCTION: ENGINE 0x108D7EE0 @ GetClassMetaType<ravenphysics::PhysicsObjectFactory>
// FUNCTION: ENGINE 0x108D7F30 @ MetaObjectFactory<ravenphysics::PhysicsObjectFactory,1>::MetaObjectFactory
// FUNCTION: ENGINE 0x108D7F60 @ MetaObjectFactory<ravenphysics::PhysicsObjectFactory,1>::Create
// FUNCTION: ENGINE 0x108D9130 @ MetaInstanceCreatorImpl<camera::Camera,1>::MetaInstanceCreatorImpl
// FUNCTION: ENGINE 0x108D9160 @ MetaInstanceCreatorImpl<camera::Camera,1>::Create
// FUNCTION: ENGINE 0x108D9180 @ MetaInstanceCreatorImpl<camera::Cinematographer,1>::MetaInstanceCreatorImpl
// FUNCTION: ENGINE 0x108D91B0 @ MetaInstanceCreatorImpl<camera::Cinematographer,1>::Create
// FUNCTION: ENGINE 0x108D9600 @ MetaInstanceCreatorImpl<PatrolPoint,1>::MetaInstanceCreatorImpl
// FUNCTION: ENGINE 0x108D9630 @ MetaInstanceCreatorImpl<PatrolPoint,1>::Create
// FUNCTION: ENGINE 0x108D9650 @ MetaInstanceCreatorImpl<SplineCV,1>::MetaInstanceCreatorImpl
// FUNCTION: ENGINE 0x108D9680 @ MetaInstanceCreatorImpl<SplineCV,1>::Create
// FUNCTION: ENGINE 0x108D9AA0 @ MetaInstanceCreatorImpl<math::AABB,1>::MetaInstanceCreatorImpl
// FUNCTION: ENGINE 0x108D9AD0 @ MetaInstanceCreatorImpl<math::AABB,1>::Create
// FUNCTION: ENGINE 0x108D9AE0 @ MetaInstanceCreatorImpl<math::OBB,1>::MetaInstanceCreatorImpl
// FUNCTION: ENGINE 0x108D9B10 @ MetaInstanceCreatorImpl<math::OBB,1>::Create
// FUNCTION: ENGINE 0x108D9B20 @ MetaInstanceCreatorImpl<math::Plane,1>::MetaInstanceCreatorImpl
// FUNCTION: ENGINE 0x108D9B50 @ MetaInstanceCreatorImpl<math::Plane,1>::Create
// FUNCTION: ENGINE 0x108DA2A0 @ MetaBehaviourCreatorImpl<animation::AttachableBehaviour>::MetaBehaviourCreatorImpl
// FUNCTION: ENGINE 0x108DA2D0 @ MetaBehaviourCreatorImpl<animation::AttachableBehaviour>::CreateBehaviour
// FUNCTION: ENGINE 0x108DA430 @ MetaBehaviourCreatorImpl<BehaviourController>::MetaBehaviourCreatorImpl
// FUNCTION: ENGINE 0x108DA460 @ MetaBehaviourCreatorImpl<BehaviourController>::CreateBehaviour
// FUNCTION: ENGINE 0x108DAA20 @ MetaBehaviourCreatorImpl<HealthBehaviour>::MetaBehaviourCreatorImpl
// FUNCTION: ENGINE 0x108DAA50 @ MetaBehaviourCreatorImpl<HealthBehaviour>::CreateBehaviour
// FUNCTION: ENGINE 0x108DAB10 @ GetClassMetaType<LightBehaviour>
// FUNCTION: ENGINE 0x108DAB60 @ MetaBehaviourCreatorImpl<LightBehaviour>::MetaBehaviourCreatorImpl
// FUNCTION: ENGINE 0x108DAB90 @ MetaBehaviourCreatorImpl<LightBehaviour>::CreateBehaviour
// FUNCTION: ENGINE 0x108DB5C0 @ MetaBehaviourCreatorImpl<TriggerBehaviour>::MetaBehaviourCreatorImpl
// FUNCTION: ENGINE 0x108DB5F0 @ MetaBehaviourCreatorImpl<TriggerBehaviour>::CreateBehaviour
// FUNCTION: ENGINE 0x108DBC50 @ RegisterMetaObjectFactory<ContentManager::ContentPackageDefinition>
// FUNCTION: ENGINE 0x108DBCA0 @ RegisterMetaObjectFactory<ContentManager::ContentPackageKey>
// FUNCTION: ENGINE 0x108DBE30 @ RegisterMetaObjectFactory<PropSpawner>
// FUNCTION: ENGINE 0x108DC1A0 @ RegisterMetaObjectFactory<ravenphysics::PhysicsObjectFactory>
// FUNCTION: ENGINE 0x108DCC40 @ RegisterMetaInstanceCreator<camera::Camera>
// FUNCTION: ENGINE 0x108DCC90 @ RegisterMetaInstanceCreator<camera::Cinematographer>
// FUNCTION: ENGINE 0x108DCF10 @ RegisterMetaInstanceCreator<PatrolPoint>
// FUNCTION: ENGINE 0x108DCF60 @ RegisterMetaInstanceCreator<SplineCV>
// FUNCTION: ENGINE 0x108DD1E0 @ RegisterMetaInstanceCreator<math::AABB>
// FUNCTION: ENGINE 0x108DD230 @ RegisterMetaInstanceCreator<math::OBB>
// FUNCTION: ENGINE 0x108DD280 @ RegisterMetaInstanceCreator<math::Plane>
// FUNCTION: ENGINE 0x108DD730 @ RegisterMetaBehaviourCreator<animation::AttachableBehaviour>
// FUNCTION: ENGINE 0x108DD820 @ RegisterMetaBehaviourCreator<BehaviourController>
// FUNCTION: ENGINE 0x108DDB40 @ RegisterMetaBehaviourCreator<HealthBehaviour>
// FUNCTION: ENGINE 0x108DDBE0 @ RegisterMetaBehaviourCreator<LightBehaviour>
// FUNCTION: ENGINE 0x108DE130 @ RegisterMetaBehaviourCreator<TriggerBehaviour>


namespace engine
{
	// 0x1065EF60 (the pure3d unit): registers the creators of its classes
	void RegisterPure3dMetaInstanceCreators();
	// 0x1067C2B0 (another pure3d unit): the same for more classes
	void RegisterPure3dMetaInstanceCreators2();

	// 0x1092B170 / 0x1092B450 (another unit): the registrations of more factories and of more behaviours' creators
	void RegisterMoreMetaObjectFactories();
	void RegisterMoreMetaBehaviourCreators();

	// The engine's start-up tables: the registrations of the classes' factories, in place
	// FUNCTION: ENGINE 0x108DE660
	void RegisterMetaObjectFactories()
	{
		content::RegisterMetaObjectFactory<engine::animation::AttachmentPhysicsProperties>();
		content::RegisterMetaObjectFactory<engine::ActorSpawner>();
		content::RegisterMetaObjectFactory<engine::ActorCrowdSpawner>();
		content::RegisterMetaObjectFactory<engine::camera::CameraLoader>();
		content::RegisterMetaObjectFactory<engine::CharacterIntentionInputMap>();
		content::RegisterMetaObjectFactory<engine::driving::CarPhysicsAttributes>();
		content::RegisterMetaObjectFactory<engine::driving::HelicopterPhysicsAttributes>();
		content::RegisterMetaObjectFactory<engine::driving::VehiclePhysicsAttributes>();
		content::RegisterMetaObjectFactory<engine::driving::WheelCollectionData>();
		content::RegisterMetaObjectFactory<engine::CharacterSolverProperties>();
		content::RegisterMetaObjectFactory<engine::ContentManager::ContentPackageDefinition>();
		content::RegisterMetaObjectFactory<engine::ContentManager::ContentPackageKey>();
		content::RegisterMetaObjectFactory<engine::ContentManager::ContentCementFileDefinition>();
		content::RegisterMetaObjectFactory<engine::GameObject>();
		content::RegisterMetaObjectFactory<engine::GameObjectTemplateBuilder>();
		content::RegisterMetaObjectFactory<engine::NamedInventoryCreator>();
		content::RegisterMetaObjectFactory<engine::PropSpawner>();
		content::RegisterMetaObjectFactory<ravenphysics::ColliderTypeNames>();
		content::RegisterMetaObjectFactory<ravenphysics::ConstraintAngularSpringSharedProperties>();
		content::RegisterMetaObjectFactory<ravenphysics::ConstraintAngularVelocitySharedProperties>();
		content::RegisterMetaObjectFactory<ravenphysics::ConstraintListFactory>();
		content::RegisterMetaObjectFactory<ravenphysics::ConstraintSpringAlongAxisSharedProperties>();
		content::RegisterMetaObjectFactory<ravenphysics::DeformableOrientationConstraintSharedProperties>();
		content::RegisterMetaObjectFactory<ravenphysics::DeformableSliderConstraintSharedProperties>();
		content::RegisterMetaObjectFactory<ravenphysics::IntersectionPropertiesLoader>();
		content::RegisterMetaObjectFactory<ravenphysics::MassProperties>();
		content::RegisterMetaObjectFactory<ravenphysics::MaterialLoader>();
		content::RegisterMetaObjectFactory<ravenphysics::PhysicsObjectFactory>();
		content::RegisterMetaObjectFactory<ravenphysics::PoweredConstraintSharedProperties>();
		content::RegisterMetaObjectFactory<ravenphysics::SimplePhysicsObjectFactory>();
		content::RegisterMetaObjectFactory<engine::RemoteCamera>();
		content::RegisterMetaObjectFactory<engine::SecondaryPhysicsProperties>();
		content::RegisterMetaObjectFactory<engine::SkuInfo>();
		content::RegisterMetaObjectFactory<engine::SplinePath>();
		content::RegisterMetaObjectFactory<engine::StreamPackage>();
		content::RegisterMetaObjectFactory<engine::StreamSlotGroup>();
		content::RegisterMetaObjectFactory<engine::StreamTrigger>();
		content::RegisterMetaObjectFactory<engine::SupportingLimbDefinition>();
		content::RegisterMetaObjectFactory<engine::SupportingLimbDefinitionList>();
		content::RegisterMetaObjectFactory<SurfaceDefinition>();
		content::RegisterMetaObjectFactory<engine::TrackedMotionToExpressionMap>();
		content::RegisterMetaObjectFactory<engine::world::Location>();
		content::RegisterMetaObjectFactory<engine::world::LocationRenderSettings>();
		content::RegisterMetaObjectFactory<engine::NIS>();
		content::RegisterMetaObjectFactory<engine::NISExclusionVolume>();
		content::RegisterMetaObjectFactory<engine::FmvSubtitleManager>();
		RegisterMoreMetaObjectFactories();
	}

	// FUNCTION: ENGINE 0x108DF1F0
	void RegisterMetaInstanceCreators()
	{
		content::RegisterMetaInstanceCreator<engine::AngularAccelerationExtractor>();
		content::RegisterMetaInstanceCreator<engine::AngularDisplacementExtractor>();
		content::RegisterMetaInstanceCreator<engine::AngularSpeedExtractor>();
		content::RegisterMetaInstanceCreator<engine::Attribute<bool>>();
		content::RegisterMetaInstanceCreator<engine::ConstAttribute<bool>>();
		content::RegisterMetaInstanceCreator<engine::Attribute<int>>();
		content::RegisterMetaInstanceCreator<engine::ConstAttribute<int>>();
		content::RegisterMetaInstanceCreator<engine::Attribute<float>>();
		content::RegisterMetaInstanceCreator<engine::ConstAttribute<float>>();
		content::RegisterMetaInstanceCreator<engine::Attribute<core::Name<core::CaseSensitiveKey> >>();
		content::RegisterMetaInstanceCreator<engine::ConstAttribute<core::Name<core::CaseSensitiveKey> >>();
		content::RegisterMetaInstanceCreator<engine::Attribute<pure3d::Pose *>>();
		content::RegisterMetaInstanceCreator<engine::ConstAttribute<pure3d::Pose *>>();
		content::RegisterMetaInstanceCreator<engine::Attribute<math::Matrix>>();
		content::RegisterMetaInstanceCreator<engine::ConstAttribute<math::Matrix>>();
		content::RegisterMetaInstanceCreator<engine::camera::Camera>();
		content::RegisterMetaInstanceCreator<engine::camera::Cinematographer>();
		content::RegisterMetaInstanceCreator<engine::camera::FPSCamera>();
		content::RegisterMetaInstanceCreator<engine::camera::OnFootCamera>();
		content::RegisterMetaInstanceCreator<engine::camera::ScriptedCamera>();
		content::RegisterMetaInstanceCreator<engine::ChangeLightColourMessage>();
		content::RegisterMetaInstanceCreator<engine::DampedAngularMotionTrackingFilter>();
		content::RegisterMetaInstanceCreator<engine::DampedLinearMotionTrackingFilter>();
		content::RegisterMetaInstanceCreator<engine::GameObject::DynamicAttributeList>();
		content::RegisterMetaInstanceCreator<engine::PatrolPoint>();
		content::RegisterMetaInstanceCreator<engine::SplineCV>();
		content::RegisterMetaInstanceCreator<engine::SplinePathCV>();
		content::RegisterMetaInstanceCreator<engine::EnableLightMessage>();
		content::RegisterMetaInstanceCreator<engine::EnterTriggerMessage>();
		content::RegisterMetaInstanceCreator<engine::ExitTriggerMessage>();
		content::RegisterMetaInstanceCreator<engine::LinearAccelerationExtractor>();
		content::RegisterMetaInstanceCreator<engine::LinearDisplacementExtractor>();
		content::RegisterMetaInstanceCreator<engine::LinearSpeedExtractor>();
		content::RegisterMetaInstanceCreator<math::AABB>();
		content::RegisterMetaInstanceCreator<math::OBB>();
		content::RegisterMetaInstanceCreator<math::Plane>();
		content::RegisterMetaInstanceCreator<math::Sphere>();
		content::RegisterMetaInstanceCreator<engine::RigidMotionTrackingFilter>();
		content::RegisterMetaInstanceCreator<engine::SecondaryPhysicsAmbientWind>();
		content::RegisterMetaInstanceCreator<engine::SecondaryPhysicsPinJoint>();
		content::RegisterMetaInstanceCreator<engine::SecondaryPhysicsPoweredJoint>();
		content::RegisterMetaInstanceCreator<engine::SpringBasedAngularMotionFilter>();
		content::RegisterMetaInstanceCreator<engine::SpringBasedLinearMotionFilter>();
		content::RegisterMetaInstanceCreator<engine::trigger::OBBVolume>();
		content::RegisterMetaInstanceCreator<engine::trigger::SphereVolume>();
		content::RegisterMetaInstanceCreator<engine::Attribute<math::Vector>>();
		content::RegisterMetaInstanceCreator<engine::ConstAttribute<math::Vector>>();
		content::RegisterMetaInstanceCreator<engine::Attribute<engine::GenericScriptValue>>();
		content::RegisterMetaInstanceCreator<engine::ConstAttribute<engine::GenericScriptValue>>();
		RegisterPure3dMetaInstanceCreators();
		RegisterPure3dMetaInstanceCreators2();
	}

	// FUNCTION: ENGINE 0x108DFE50
	void RegisterMetaBehaviourCreators()
	{
		engine::RegisterMetaBehaviourCreator<engine::AdvertisementBehaviour>();
		engine::RegisterMetaBehaviourCreator<engine::animation::AttachableBehaviour>();
		engine::RegisterMetaBehaviourCreator<engine::animation::JawFlapBehaviour>();
		engine::RegisterMetaBehaviourCreator<engine::animation::PuppetBehaviour>();
		engine::RegisterMetaBehaviourCreator<engine::BehaviourController>();
		engine::RegisterMetaBehaviourCreator<engine::camera::CameraBehaviour>();
		engine::RegisterMetaBehaviourCreator<engine::camera::CinematographerBehaviour>();
		engine::RegisterMetaBehaviourCreator<engine::CharacterIntentionBehaviour>();
		engine::RegisterMetaBehaviourCreator<engine::CharacterSolverBehaviour>();
		engine::RegisterMetaBehaviourCreator<engine::driving::CarIntentionBehaviour>();
		engine::RegisterMetaBehaviourCreator<engine::driving::CarPhysicsBehaviour>();
		engine::RegisterMetaBehaviourCreator<engine::driving::HelicopterIntentionBehaviour>();
		engine::RegisterMetaBehaviourCreator<engine::driving::HelicopterPhysicsBehaviour>();
		engine::RegisterMetaBehaviourCreator<engine::FirstPersonControlBehaviour>();
		engine::RegisterMetaBehaviourCreator<engine::HealthBehaviour>();
		engine::RegisterMetaBehaviourCreator<engine::KnockBehaviour>();
		engine::RegisterMetaBehaviourCreator<engine::LightBehaviour>();
		engine::RegisterMetaBehaviourCreator<engine::MotionTreeBehaviour>();
		engine::RegisterMetaBehaviourCreator<engine::NISPlayerBehaviour>();
		engine::RegisterMetaBehaviourCreator<engine::PatrolPathBehaviour>();
		engine::RegisterMetaBehaviourCreator<engine::PlaybackTreeBehaviour>();
		engine::RegisterMetaBehaviourCreator<engine::PoseAnimationBehaviour>();
		engine::RegisterMetaBehaviourCreator<engine::PropLogicTreeBehaviour>();
		engine::RegisterMetaBehaviourCreator<engine::PhysicsBehaviour>();
		engine::RegisterMetaBehaviourCreator<engine::PropBehaviour>();
		engine::RegisterMetaBehaviourCreator<engine::RagdollBehaviour>();
		engine::RegisterMetaBehaviourCreator<engine::RagdollLODBehaviour>();
		engine::RegisterMetaBehaviourCreator<engine::RenderBehaviour>();
		engine::RegisterMetaBehaviourCreator<engine::SecondaryPhysicsBehaviour>();
		engine::RegisterMetaBehaviourCreator<engine::SplineBehaviour>();
		engine::RegisterMetaBehaviourCreator<engine::TagBehaviour>();
		engine::RegisterMetaBehaviourCreator<engine::TouchBehaviour>();
		engine::RegisterMetaBehaviourCreator<engine::TrackedMotionToExpressionBehaviour>();
		engine::RegisterMetaBehaviourCreator<engine::TriggerBehaviour>();
		engine::RegisterMetaBehaviourCreator<engine::MovingTriggerBehaviour>();
		RegisterMoreMetaBehaviourCreators();
	}
}

// ---- annotations of the functions mapped in symbols.txt (generated) ----

// FUNCTION: ENGINE 0x108D75A0 @ content::ClassMetaType * content::GetClassMetaType<engine::ContentManager::ContentCementFileDefinition>(void)
// FUNCTION: ENGINE 0x108D75F0 @ content::MetaObjectFactory<engine::ContentManager::ContentCementFileDefinition,1>::MetaObjectFactory<engine::ContentManager::ContentCementFileDefinition,1>(char const *,u
// FUNCTION: ENGINE 0x108D7670 @ math::Plane::Plane(void) (name guess; identical copies)
// FUNCTION: ENGINE 0x108D78C0 @ content::ClassMetaType * content::GetClassMetaType<ravenphysics::ColliderTypeNames>(void)
// FUNCTION: ENGINE 0x108D7910 @ content::MetaObjectFactory<ravenphysics::ColliderTypeNames,1>::MetaObjectFactory<ravenphysics::ColliderTypeNames,1>(char const *,unsigned short,content::ClassMetaType *)
// FUNCTION: ENGINE 0x108D88E0 @ content::ClassMetaType * content::GetClassMetaType<engine::NIS>(void)
// FUNCTION: ENGINE 0x108D8930 @ content::MetaObjectFactory<engine::NIS,1>::MetaObjectFactory<engine::NIS,1>(char const *,unsigned short,content::ClassMetaType *)
// FUNCTION: ENGINE 0x108D8960 @ math::OBB::OBB(void) (name guess; identical copies)
// FUNCTION: ENGINE 0x108D8980 @ math::Colour128::Colour128(void) (name guess; identical copies)
// FUNCTION: ENGINE 0x108D8B60 @ content::ClassMetaType * content::GetClassMetaType<engine::AngularAccelerationExtractor>(void)
// FUNCTION: ENGINE 0x108D8BB0 @ content::MetaInstanceCreatorImpl<engine::AngularAccelerationExtractor,1>::MetaInstanceCreatorImpl<engine::AngularAccelerationExtractor,1>(char const *,unsigned short,cont
// FUNCTION: ENGINE 0x108D8C10 @ content::ClassMetaType * content::GetClassMetaType<engine::AngularDisplacementExtractor>(void)
// FUNCTION: ENGINE 0x108D8C60 @ content::MetaInstanceCreatorImpl<engine::AngularDisplacementExtractor,1>::MetaInstanceCreatorImpl<engine::AngularDisplacementExtractor,1>(char const *,unsigned short,cont
// FUNCTION: ENGINE 0x108D8C90 @ content::ClassMetaType * content::GetClassMetaType<engine::AngularSpeedExtractor>(void)
// FUNCTION: ENGINE 0x108D8CE0 @ content::MetaInstanceCreatorImpl<engine::AngularSpeedExtractor,1>::MetaInstanceCreatorImpl<engine::AngularSpeedExtractor,1>(char const *,unsigned short,content::ClassMeta
// FUNCTION: ENGINE 0x108D8D10 @ content::ClassMetaType * content::GetClassMetaType<engine::Attribute<bool> >(void)
// FUNCTION: ENGINE 0x108D8D60 @ content::MetaInstanceCreatorImpl<engine::Attribute<bool>,1>::MetaInstanceCreatorImpl<engine::Attribute<bool>,1>(char const *,unsigned short,content::ClassMetaType *)
// FUNCTION: ENGINE 0x108D8D90 @ content::MetaInstanceCreatorImpl<engine::ConstAttribute<bool>,1>::MetaInstanceCreatorImpl<engine::ConstAttribute<bool>,1>(char const *,unsigned short,content::ClassMetaTy
// FUNCTION: ENGINE 0x108D8DC0 @ content::ClassMetaType * content::GetClassMetaType<engine::Attribute<int> >(void)
// FUNCTION: ENGINE 0x108D8E10 @ content::MetaInstanceCreatorImpl<engine::Attribute<int>,1>::MetaInstanceCreatorImpl<engine::Attribute<int>,1>(char const *,unsigned short,content::ClassMetaType *)
// FUNCTION: ENGINE 0x108D8E40 @ content::MetaInstanceCreatorImpl<engine::ConstAttribute<int>,1>::MetaInstanceCreatorImpl<engine::ConstAttribute<int>,1>(char const *,unsigned short,content::ClassMetaType
// FUNCTION: ENGINE 0x108D8E70 @ content::ClassMetaType * content::GetClassMetaType<engine::Attribute<float> >(void)
// FUNCTION: ENGINE 0x108D8EC0 @ content::MetaInstanceCreatorImpl<engine::Attribute<float>,1>::MetaInstanceCreatorImpl<engine::Attribute<float>,1>(char const *,unsigned short,content::ClassMetaType *)
// FUNCTION: ENGINE 0x108D8EF0 @ content::MetaInstanceCreatorImpl<engine::ConstAttribute<float>,1>::MetaInstanceCreatorImpl<engine::ConstAttribute<float>,1>(char const *,unsigned short,content::ClassMeta
// FUNCTION: ENGINE 0x108D8F20 @ content::ClassMetaType * content::GetClassMetaType<engine::Attribute<core::Name<core::CaseSensitiveKey> > >(void)
// FUNCTION: ENGINE 0x108D8F70 @ content::MetaInstanceCreatorImpl<engine::Attribute<core::Name<core::CaseSensitiveKey> >,1>::MetaInstanceCreatorImpl<engine::Attribute<core::Name<core::CaseSensitiveKey> >
// FUNCTION: ENGINE 0x108D8FA0 @ content::MetaInstanceCreatorImpl<engine::ConstAttribute<core::Name<core::CaseSensitiveKey> >,1>::MetaInstanceCreatorImpl<engine::ConstAttribute<core::Name<core::CaseSensi
// FUNCTION: ENGINE 0x108D8FD0 @ content::ClassMetaType * content::GetClassMetaType<engine::Attribute<pure3d::Pose *> >(void)
// FUNCTION: ENGINE 0x108D9020 @ content::MetaInstanceCreatorImpl<engine::Attribute<pure3d::Pose *>,1>::MetaInstanceCreatorImpl<engine::Attribute<pure3d::Pose *>,1>(char const *,unsigned short,content::C
// FUNCTION: ENGINE 0x108D9050 @ content::MetaInstanceCreatorImpl<engine::ConstAttribute<pure3d::Pose *>,1>::MetaInstanceCreatorImpl<engine::ConstAttribute<pure3d::Pose *>,1>(char const *,unsigned short,
// FUNCTION: ENGINE 0x108D9080 @ content::ClassMetaType * content::GetClassMetaType<engine::Attribute<math::Matrix> >(void)
// FUNCTION: ENGINE 0x108D90D0 @ content::MetaInstanceCreatorImpl<engine::Attribute<math::Matrix>,1>::MetaInstanceCreatorImpl<engine::Attribute<math::Matrix>,1>(char const *,unsigned short,content::Class
// FUNCTION: ENGINE 0x108D9100 @ content::MetaInstanceCreatorImpl<engine::ConstAttribute<math::Matrix>,1>::MetaInstanceCreatorImpl<engine::ConstAttribute<math::Matrix>,1>(char const *,unsigned short,cont
// FUNCTION: ENGINE 0x108D93B0 @ content::ClassMetaType * content::GetClassMetaType<engine::ChangeLightColourMessage>(void)
// FUNCTION: ENGINE 0x108D9400 @ content::MetaInstanceCreatorImpl<engine::ChangeLightColourMessage,1>::MetaInstanceCreatorImpl<engine::ChangeLightColourMessage,1>(char const *,unsigned short,content::Cla
// FUNCTION: ENGINE 0x108D9430 @ engine::ChangeLightColourMessage::ChangeLightColourMessage(void)
// FUNCTION: ENGINE 0x108D9450 @ engine::IntrusiveMessage::~IntrusiveMessage(void) (name guess; identical copies)
// FUNCTION: ENGINE 0x108D9460 @ void * content::MetaInstanceCreatorImpl<engine::ChangeLightColourMessage,1>::Create(void)
// FUNCTION: ENGINE 0x108D95D0 @ content::MetaInstanceCreatorImpl<engine::GameObject::DynamicAttributeList,1>::MetaInstanceCreatorImpl<engine::GameObject::DynamicAttributeList,1>(char const *,unsigned sh
// FUNCTION: ENGINE 0x108D9740 @ content::ClassMetaType * content::GetClassMetaType<engine::EnableLightMessage>(void)
// FUNCTION: ENGINE 0x108D9790 @ content::MetaInstanceCreatorImpl<engine::EnableLightMessage,1>::MetaInstanceCreatorImpl<engine::EnableLightMessage,1>(char const *,unsigned short,content::ClassMetaType *
// FUNCTION: ENGINE 0x108D97C0 @ engine::EnableLightMessage::EnableLightMessage(void)
// FUNCTION: ENGINE 0x108D97E0 @ engine::ScenarioMessage::~ScenarioMessage(void) (name guess; identical copies)
// FUNCTION: ENGINE 0x108D97F0 @ void * content::MetaInstanceCreatorImpl<engine::EnableLightMessage,1>::Create(void)
// FUNCTION: ENGINE 0x108D9920 @ content::ClassMetaType * content::GetClassMetaType<engine::LinearAccelerationExtractor>(void)
// FUNCTION: ENGINE 0x108D9970 @ content::MetaInstanceCreatorImpl<engine::LinearAccelerationExtractor,1>::MetaInstanceCreatorImpl<engine::LinearAccelerationExtractor,1>(char const *,unsigned short,conten
// FUNCTION: ENGINE 0x108D99A0 @ content::ClassMetaType * content::GetClassMetaType<engine::LinearDisplacementExtractor>(void)
// FUNCTION: ENGINE 0x108D99F0 @ content::MetaInstanceCreatorImpl<engine::LinearDisplacementExtractor,1>::MetaInstanceCreatorImpl<engine::LinearDisplacementExtractor,1>(char const *,unsigned short,conten
// FUNCTION: ENGINE 0x108D9A20 @ content::ClassMetaType * content::GetClassMetaType<engine::LinearSpeedExtractor>(void)
// FUNCTION: ENGINE 0x108D9A70 @ content::MetaInstanceCreatorImpl<engine::LinearSpeedExtractor,1>::MetaInstanceCreatorImpl<engine::LinearSpeedExtractor,1>(char const *,unsigned short,content::ClassMetaTy
// FUNCTION: ENGINE 0x108D9B60 @ content::MetaInstanceCreatorImpl<math::Sphere,1>::MetaInstanceCreatorImpl<math::Sphere,1>(char const *,unsigned short,content::ClassMetaType *)
// FUNCTION: ENGINE 0x108D9BC0 @ content::ClassMetaType * content::GetClassMetaType<engine::RigidMotionTrackingFilter>(void)
// FUNCTION: ENGINE 0x108D9C10 @ content::MetaInstanceCreatorImpl<engine::RigidMotionTrackingFilter,1>::MetaInstanceCreatorImpl<engine::RigidMotionTrackingFilter,1>(char const *,unsigned short,content::C
// FUNCTION: ENGINE 0x108DA0A0 @ content::ClassMetaType * content::GetClassMetaType<engine::Attribute<math::Vector> >(void)
// FUNCTION: ENGINE 0x108DA0F0 @ content::MetaInstanceCreatorImpl<engine::Attribute<math::Vector>,1>::MetaInstanceCreatorImpl<engine::Attribute<math::Vector>,1>(char const *,unsigned short,content::Class
// FUNCTION: ENGINE 0x108DA120 @ content::MetaInstanceCreatorImpl<engine::ConstAttribute<math::Vector>,1>::MetaInstanceCreatorImpl<engine::ConstAttribute<math::Vector>,1>(char const *,unsigned short,cont
// FUNCTION: ENGINE 0x108DA150 @ content::ClassMetaType * content::GetClassMetaType<engine::Attribute<engine::GenericScriptValue> >(void)
// FUNCTION: ENGINE 0x108DA1A0 @ content::MetaInstanceCreatorImpl<engine::Attribute<engine::GenericScriptValue>,1>::MetaInstanceCreatorImpl<engine::Attribute<engine::GenericScriptValue>,1>(char const *,u
// FUNCTION: ENGINE 0x108DA1D0 @ content::MetaInstanceCreatorImpl<engine::ConstAttribute<engine::GenericScriptValue>,1>::MetaInstanceCreatorImpl<engine::ConstAttribute<engine::GenericScriptValue>,1>(char
// FUNCTION: ENGINE 0x108DB610 @ content::ClassMetaType * content::GetClassMetaType<engine::MovingTriggerBehaviour>(void)
// FUNCTION: ENGINE 0x108DB660 @ engine::MetaBehaviourCreatorImpl<engine::MovingTriggerBehaviour>::MetaBehaviourCreatorImpl<engine::MovingTriggerBehaviour>(char const *,unsigned short,content::ClassMetaT
// FUNCTION: ENGINE 0x108DB870 @ void * engine::EnableLightMessage::`scalar deleting destructor'(unsigned int)
// FUNCTION: ENGINE 0x108DB890 @ void * engine::ChangeLightColourMessage::`scalar deleting destructor'(unsigned int)
// FUNCTION: ENGINE 0x108DBCF0 @ void content::RegisterMetaObjectFactory<engine::ContentManager::ContentCementFileDefinition>(void)
// FUNCTION: ENGINE 0x108DBE80 @ void content::RegisterMetaObjectFactory<ravenphysics::ColliderTypeNames>(void)
// FUNCTION: ENGINE 0x108DC6A0 @ void content::RegisterMetaObjectFactory<engine::NIS>(void)
// FUNCTION: ENGINE 0x108DC790 @ void content::RegisterMetaInstanceCreator<engine::AngularAccelerationExtractor>(void)
// FUNCTION: ENGINE 0x108DC7E0 @ void content::RegisterMetaInstanceCreator<engine::AngularDisplacementExtractor>(void)
// FUNCTION: ENGINE 0x108DC830 @ void content::RegisterMetaInstanceCreator<engine::AngularSpeedExtractor>(void)
// FUNCTION: ENGINE 0x108DC880 @ void content::RegisterMetaInstanceCreator<engine::Attribute<bool> >(void)
// FUNCTION: ENGINE 0x108DC8D0 @ void content::RegisterMetaInstanceCreator<engine::ConstAttribute<bool> >(void)
// FUNCTION: ENGINE 0x108DC920 @ void content::RegisterMetaInstanceCreator<engine::Attribute<int> >(void)
// FUNCTION: ENGINE 0x108DC970 @ void content::RegisterMetaInstanceCreator<engine::ConstAttribute<int> >(void)
// FUNCTION: ENGINE 0x108DC9C0 @ void content::RegisterMetaInstanceCreator<engine::Attribute<float> >(void)
// FUNCTION: ENGINE 0x108DCA10 @ void content::RegisterMetaInstanceCreator<engine::ConstAttribute<float> >(void)
// FUNCTION: ENGINE 0x108DCA60 @ void content::RegisterMetaInstanceCreator<engine::Attribute<core::Name<core::CaseSensitiveKey> > >(void)
// FUNCTION: ENGINE 0x108DCAB0 @ void content::RegisterMetaInstanceCreator<engine::ConstAttribute<core::Name<core::CaseSensitiveKey> > >(void)
// FUNCTION: ENGINE 0x108DCB00 @ void content::RegisterMetaInstanceCreator<engine::Attribute<pure3d::Pose *> >(void)
// FUNCTION: ENGINE 0x108DCB50 @ void content::RegisterMetaInstanceCreator<engine::ConstAttribute<pure3d::Pose *> >(void)
// FUNCTION: ENGINE 0x108DCBA0 @ void content::RegisterMetaInstanceCreator<engine::Attribute<math::Matrix> >(void)
// FUNCTION: ENGINE 0x108DCBF0 @ void content::RegisterMetaInstanceCreator<engine::ConstAttribute<math::Matrix> >(void)
// FUNCTION: ENGINE 0x108DCDD0 @ void content::RegisterMetaInstanceCreator<engine::ChangeLightColourMessage>(void)
// FUNCTION: ENGINE 0x108DCEC0 @ void content::RegisterMetaInstanceCreator<engine::GameObject::DynamicAttributeList>(void)
// FUNCTION: ENGINE 0x108DD000 @ void content::RegisterMetaInstanceCreator<engine::EnableLightMessage>(void)
// FUNCTION: ENGINE 0x108DD0F0 @ void content::RegisterMetaInstanceCreator<engine::LinearAccelerationExtractor>(void)
// FUNCTION: ENGINE 0x108DD140 @ void content::RegisterMetaInstanceCreator<engine::LinearDisplacementExtractor>(void)
// FUNCTION: ENGINE 0x108DD190 @ void content::RegisterMetaInstanceCreator<engine::LinearSpeedExtractor>(void)
// FUNCTION: ENGINE 0x108DD2D0 @ void content::RegisterMetaInstanceCreator<math::Sphere>(void)
// FUNCTION: ENGINE 0x108DD320 @ void content::RegisterMetaInstanceCreator<engine::RigidMotionTrackingFilter>(void)
// FUNCTION: ENGINE 0x108DD5A0 @ void content::RegisterMetaInstanceCreator<engine::Attribute<math::Vector> >(void)
// FUNCTION: ENGINE 0x108DD5F0 @ void content::RegisterMetaInstanceCreator<engine::ConstAttribute<math::Vector> >(void)
// FUNCTION: ENGINE 0x108DD640 @ void content::RegisterMetaInstanceCreator<engine::Attribute<engine::GenericScriptValue> >(void)
// FUNCTION: ENGINE 0x108DD690 @ void content::RegisterMetaInstanceCreator<engine::ConstAttribute<engine::GenericScriptValue> >(void)
// FUNCTION: ENGINE 0x108DE180 @ void engine::RegisterMetaBehaviourCreator<engine::MovingTriggerBehaviour>(void)
