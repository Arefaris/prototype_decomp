// The Create members of the content library's factories and instance creators that the engine emits out of line in one unit (0x108E0720 - 0x108E1260). The
// factories and their registrations are in metafactories.cpp, which declares these members.
#include "code/content/metafactory.h"
#include "code/engine/reflectedclasses.h"
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
#include "code/engine/camera/cameraloader.h"
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
	template LoadObject* MetaObjectFactory<engine::NIS, 1>::Create();
	template void* MetaInstanceCreatorImpl<engine::AngularAccelerationExtractor, 1>::Create();
	template void* MetaInstanceCreatorImpl<engine::AngularDisplacementExtractor, 1>::Create();
	template void* MetaInstanceCreatorImpl<engine::AngularSpeedExtractor, 1>::Create();
	template void* MetaInstanceCreatorImpl<engine::Attribute<math::Matrix>, 1>::Create();
	template void* MetaInstanceCreatorImpl<engine::GameObject::DynamicAttributeList, 1>::Create();
	template void* MetaInstanceCreatorImpl<engine::LinearAccelerationExtractor, 1>::Create();
	template void* MetaInstanceCreatorImpl<engine::LinearDisplacementExtractor, 1>::Create();
	template void* MetaInstanceCreatorImpl<engine::LinearSpeedExtractor, 1>::Create();
	template void* MetaInstanceCreatorImpl<engine::RigidMotionTrackingFilter, 1>::Create();
}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x108E0760
// FUNCTION: ENGINE 0x108E0790
// FUNCTION: ENGINE 0x108E07C0
// FUNCTION: ENGINE 0x108E0970
// FUNCTION: ENGINE 0x108E09A0
// FUNCTION: ENGINE 0x108E09D0
// FUNCTION: ENGINE 0x108E0A00
// FUNCTION: ENGINE 0x108E0BF0
// FUNCTION: ENGINE 0x108E0F10
// FUNCTION: ENGINE 0x108E10E0
