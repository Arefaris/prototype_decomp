// The factories the content library loads the engine's reflected classes through (see content/metafactory.h): the
// class meta type, the factory (or instance creator) and its registration of each class, in the order the engine has
// them (0x108D6E20 on).
#include "code/content/metafactory.h"
#include "code/engine/reflectedclasses.h"
#include "code/engine/fmv/fmvsubtitlemanager.h"
#include "code/engine/gameobject/gameobject.h"
#include "code/engine/motiontrackingfilter.h"
#include "code/engine/scenariomessage.h"

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
// FUNCTION: ENGINE 0x108DE1D0 @ MetaObjectFactory<NISExclusionVolume,1>::Create
// FUNCTION: ENGINE 0x108DE1F0 @ MetaInstanceCreatorImpl<EnterTriggerMessage,1>::Create
// FUNCTION: ENGINE 0x108DE220 @ MetaInstanceCreatorImpl<ExitTriggerMessage,1>::Create
