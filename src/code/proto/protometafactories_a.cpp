// The factories and creators the proto game registers for its reflected classes (content/metafactory.h): the class meta
// type, the factory or creator and the registration function of each class, in the order the engine has them
// (0x10290630 on; no assert path names the unit, the file names are guesses).
#include "code/content/metafactory.h"
#include "code/proto/behaviours/chargebehaviour.h"
#include "code/proto/behaviours/fightvariablesbehaviour.h"
#include "code/proto/behaviours/helicopterintentionbehaviour.h"
#include "code/proto/behaviours/hiteffectbehaviour.h"
#include "code/proto/behaviours/motiontrackingfilters.h"
#include "code/proto/behaviours/physicslodbehaviour.h"
#include "code/proto/behaviours/sensesinfobehaviour.h"
#include "code/proto/behaviours/tankintentionbehaviour.h"
#include "code/proto/behaviours/tendrilbehaviour.h"
#include "code/proto/behaviours/tunnelingbehaviour.h"
#include "code/proto/collectiblebehaviour.h"
#include "code/proto/powers/power.h"
#include "code/proto/powers/shieldpower.h"
#include "code/proto/render/blobshadowbehaviour.h"
#include "code/proto/render/collisionsqueezebehaviour.h"
#include "code/proto/render/decalbehaviour.h"
#include "code/proto/render/healthshaderbehaviour.h"
#include "code/proto/zonebehaviour.h"

namespace content
{
	template class MetaObjectFactory<proto::AnalyseCollisionParams, 1>;
	template ClassMetaType* GetClassMetaType<proto::AnalyseCollisionParams>();
	template void RegisterMetaObjectFactory<proto::AnalyseCollisionParams>();
	template class MetaObjectFactory<proto::MomentumDamageParams, 1>;
	template ClassMetaType* GetClassMetaType<proto::MomentumDamageParams>();
	template void RegisterMetaObjectFactory<proto::MomentumDamageParams>();
	template class MetaObjectFactory<proto::ShieldPower, 1>;
	template ClassMetaType* GetClassMetaType<proto::ShieldPower>();
	template void RegisterMetaObjectFactory<proto::ShieldPower>();
	template class MetaInstanceCreatorImpl<proto::DistanceAcceleratedMotionTrackingFilter, 1>;
	template ClassMetaType* GetClassMetaType<proto::DistanceAcceleratedMotionTrackingFilter>();
	template void RegisterMetaInstanceCreator<proto::DistanceAcceleratedMotionTrackingFilter>();
	template class MetaInstanceCreatorImpl<proto::LinearVelocityNoiseTrackingFilter, 1>;
	template ClassMetaType* GetClassMetaType<proto::LinearVelocityNoiseTrackingFilter>();
	template void RegisterMetaInstanceCreator<proto::LinearVelocityNoiseTrackingFilter>();
	template ClassMetaType* GetClassMetaType<proto::ChargeBehaviour>();
	template ClassMetaType* GetClassMetaType<proto::DecalBehaviour>();
	template ClassMetaType* GetClassMetaType<proto::FightVariablesBehaviour>();
	template ClassMetaType* GetClassMetaType<proto::HelicopterIntentionBehaviour>();
	template ClassMetaType* GetClassMetaType<proto::HitEffectBehaviour>();
	template ClassMetaType* GetClassMetaType<proto::BlobShadowBehaviour>();
	template ClassMetaType* GetClassMetaType<proto::PowerBehaviour>();
	template ClassMetaType* GetClassMetaType<proto::SensesInfoBehaviour>();
	template ClassMetaType* GetClassMetaType<proto::TankIntentionBehaviour>();
	template ClassMetaType* GetClassMetaType<proto::TendrilBehaviour>();
	template ClassMetaType* GetClassMetaType<proto::TunnelingBehaviour>();
	template ClassMetaType* GetClassMetaType<proto::PhysicsLODBehaviour>();
	template ClassMetaType* GetClassMetaType<proto::ZoneBehaviour>();
	template ClassMetaType* GetClassMetaType<proto::CollectibleBehaviour>();
	template ClassMetaType* GetClassMetaType<proto::HealthShaderBehaviour>();
	template ClassMetaType* GetClassMetaType<proto::CollisionSqueezeBehaviour>();
}

namespace engine
{
	template class MetaBehaviourCreatorImpl<proto::ChargeBehaviour>;
	template void RegisterMetaBehaviourCreator<proto::ChargeBehaviour>();
	template class MetaBehaviourCreatorImpl<proto::DecalBehaviour>;
	template void RegisterMetaBehaviourCreator<proto::DecalBehaviour>();
	template class MetaBehaviourCreatorImpl<proto::FightVariablesBehaviour>;
	template void RegisterMetaBehaviourCreator<proto::FightVariablesBehaviour>();
	template class MetaBehaviourCreatorImpl<proto::HelicopterIntentionBehaviour>;
	template void RegisterMetaBehaviourCreator<proto::HelicopterIntentionBehaviour>();
	template class MetaBehaviourCreatorImpl<proto::HitEffectBehaviour>;
	template void RegisterMetaBehaviourCreator<proto::HitEffectBehaviour>();
	template class MetaBehaviourCreatorImpl<proto::BlobShadowBehaviour>;
	template void RegisterMetaBehaviourCreator<proto::BlobShadowBehaviour>();
	template class MetaBehaviourCreatorImpl<proto::PowerBehaviour>;
	template void RegisterMetaBehaviourCreator<proto::PowerBehaviour>();
	template class MetaBehaviourCreatorImpl<proto::SensesInfoBehaviour>;
	template void RegisterMetaBehaviourCreator<proto::SensesInfoBehaviour>();
	template class MetaBehaviourCreatorImpl<proto::TankIntentionBehaviour>;
	template void RegisterMetaBehaviourCreator<proto::TankIntentionBehaviour>();
	template class MetaBehaviourCreatorImpl<proto::TendrilBehaviour>;
	template void RegisterMetaBehaviourCreator<proto::TendrilBehaviour>();
	template class MetaBehaviourCreatorImpl<proto::TunnelingBehaviour>;
	template void RegisterMetaBehaviourCreator<proto::TunnelingBehaviour>();
	template class MetaBehaviourCreatorImpl<proto::PhysicsLODBehaviour>;
	template void RegisterMetaBehaviourCreator<proto::PhysicsLODBehaviour>();
	template class MetaBehaviourCreatorImpl<proto::ZoneBehaviour>;
	template void RegisterMetaBehaviourCreator<proto::ZoneBehaviour>();
	template class MetaBehaviourCreatorImpl<proto::CollectibleBehaviour>;
	template void RegisterMetaBehaviourCreator<proto::CollectibleBehaviour>();
	template class MetaBehaviourCreatorImpl<proto::HealthShaderBehaviour>;
	template void RegisterMetaBehaviourCreator<proto::HealthShaderBehaviour>();
	template class MetaBehaviourCreatorImpl<proto::CollisionSqueezeBehaviour>;
	template void RegisterMetaBehaviourCreator<proto::CollisionSqueezeBehaviour>();
}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x10290630
// FUNCTION: ENGINE 0x10290690
// FUNCTION: ENGINE 0x102906C0
// FUNCTION: ENGINE 0x10290770
// FUNCTION: ENGINE 0x102907D0
// FUNCTION: ENGINE 0x10290800
// FUNCTION: ENGINE 0x10291BA0
// FUNCTION: ENGINE 0x10291C00
// FUNCTION: ENGINE 0x10291C30
// FUNCTION: ENGINE 0x10293450
// FUNCTION: ENGINE 0x102934B0
// FUNCTION: ENGINE 0x102934E0
// FUNCTION: ENGINE 0x10293500
// FUNCTION: ENGINE 0x10293560
// FUNCTION: ENGINE 0x10293590
// FUNCTION: ENGINE 0x10293F60
// FUNCTION: ENGINE 0x10293FC0
// FUNCTION: ENGINE 0x10293FF0
// FUNCTION: ENGINE 0x102943A0
// FUNCTION: ENGINE 0x10294400
// FUNCTION: ENGINE 0x10294430
// FUNCTION: ENGINE 0x102947F0
// FUNCTION: ENGINE 0x10294850
// FUNCTION: ENGINE 0x10294880
// FUNCTION: ENGINE 0x10294F80
// FUNCTION: ENGINE 0x10294FE0
// FUNCTION: ENGINE 0x10295010
// FUNCTION: ENGINE 0x102950F0
// FUNCTION: ENGINE 0x10295150
// FUNCTION: ENGINE 0x10295180
// FUNCTION: ENGINE 0x10295A60
// FUNCTION: ENGINE 0x10295AC0
// FUNCTION: ENGINE 0x10295AF0
// FUNCTION: ENGINE 0x10296490
// FUNCTION: ENGINE 0x102964F0
// FUNCTION: ENGINE 0x10296520
// FUNCTION: ENGINE 0x10296760
// FUNCTION: ENGINE 0x102967C0
// FUNCTION: ENGINE 0x102967F0
// FUNCTION: ENGINE 0x10296AF0
// FUNCTION: ENGINE 0x10296B50
// FUNCTION: ENGINE 0x10296B80
// FUNCTION: ENGINE 0x10296E80
// FUNCTION: ENGINE 0x10296EE0
// FUNCTION: ENGINE 0x10296F10
// FUNCTION: ENGINE 0x10297B70
// FUNCTION: ENGINE 0x10297BD0
// FUNCTION: ENGINE 0x10297C00
// FUNCTION: ENGINE 0x10297CD0
// FUNCTION: ENGINE 0x10297D30
// FUNCTION: ENGINE 0x10297D60
// FUNCTION: ENGINE 0x10298040
// FUNCTION: ENGINE 0x102980A0
// FUNCTION: ENGINE 0x102980D0
// FUNCTION: ENGINE 0x102986B0
// FUNCTION: ENGINE 0x10298710
// FUNCTION: ENGINE 0x10298740
// FUNCTION: ENGINE 0x10299100
// FUNCTION: ENGINE 0x10299160
// FUNCTION: ENGINE 0x10299190
// FUNCTION: ENGINE 0x10299330
// FUNCTION: ENGINE 0x10299390
// FUNCTION: ENGINE 0x102993C0
// FUNCTION: ENGINE 0x10299AE0
// FUNCTION: ENGINE 0x10299BA0
// FUNCTION: ENGINE 0x1029A620
// FUNCTION: ENGINE 0x1029B2E0
// FUNCTION: ENGINE 0x1029B340
// FUNCTION: ENGINE 0x1029B880
// FUNCTION: ENGINE 0x1029BAC0
// FUNCTION: ENGINE 0x1029BD00
// FUNCTION: ENGINE 0x1029C120
// FUNCTION: ENGINE 0x1029C1E0
// FUNCTION: ENGINE 0x1029C6C0
// FUNCTION: ENGINE 0x1029CC00
// FUNCTION: ENGINE 0x1029CD80
// FUNCTION: ENGINE 0x1029CF60
// FUNCTION: ENGINE 0x1029D140
// FUNCTION: ENGINE 0x1029D800
// FUNCTION: ENGINE 0x1029D8C0
// FUNCTION: ENGINE 0x1029DAA0
// FUNCTION: ENGINE 0x1029DE00
// FUNCTION: ENGINE 0x1029E3A0
// FUNCTION: ENGINE 0x1029E4C0
