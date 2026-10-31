// The names of the game object attributes (asleep, drawable name, puppet, physics object, ...) that the behaviours
// look up by name (unit name guess: the engine's static initialisers 0x10D73C10 - 0x10D73EB0 construct them in one run).
#include "code/core/name.h"

namespace engine
{
	core::Name<core::CaseSensitiveKey> gProtoVolatileIsInVehicle("Proto_Volatile_IsInVehicle", 0);
	core::Name<core::CaseSensitiveKey> gAnimationFinished("animation finished", 0);
	core::Name<core::CaseSensitiveKey> gAttachmentState("attachmentState", 0);
	core::Name<core::CaseSensitiveKey> gAsleepName("asleep", 0);
	core::Name<core::CaseSensitiveKey> gBoundingBox("boundingBox", 0);
	core::Name<core::CaseSensitiveKey> gEffectsPropData("effectsPropData", 0);
	core::Name<core::CaseSensitiveKey> gEffectsPropType("effectsPropType", 0);
	core::Name<core::CaseSensitiveKey> gExpressionPose("expressionPose", 0);
	core::Name<core::CaseSensitiveKey> gLodValue("lodValue", 0);
	core::Name<core::CaseSensitiveKey> gPoseAnimationControllerName("pose animation controller", 0);
	core::Name<core::CaseSensitiveKey> gPropSpawnerName("prop spawner", 0);
	core::Name<core::CaseSensitiveKey> gPuppetAttributeName("puppet", 0);
	core::Name<core::CaseSensitiveKey> gScaleName("scale", 0);
	core::Name<core::CaseSensitiveKey> gState("state", 0);
	core::Name<core::CaseSensitiveKey> gMetaObjectTemplateName("meta object template", 0);
	core::Name<core::CaseSensitiveKey> gTransformName("transform", 0);
	core::Name<core::CaseSensitiveKey> gRandom("random", 0);
}

namespace proto
{
	core::Name<core::CaseSensitiveKey> gDrawableHandleAttributeName("drawableObject", 0);
	core::Name<core::CaseSensitiveKey> gDrawableAttributeName("pose", 0);
}

// The dynamic initialisers and atexit stubs of the unit's names:
// FUNCTION: ENGINE 0x10D73C10
// FUNCTION: ENGINE 0x10D73C30
// FUNCTION: ENGINE 0x10D73C50
// FUNCTION: ENGINE 0x10D73C70
// FUNCTION: ENGINE 0x10D73C90
// FUNCTION: ENGINE 0x10D73CB0
// FUNCTION: ENGINE 0x10D73CF0
// FUNCTION: ENGINE 0x10D73D10
// FUNCTION: ENGINE 0x10D73D30
// FUNCTION: ENGINE 0x10D73D50
// FUNCTION: ENGINE 0x10D73DB0
// FUNCTION: ENGINE 0x10D73DD0
// FUNCTION: ENGINE 0x10D73DF0
// FUNCTION: ENGINE 0x10D73E10
// FUNCTION: ENGINE 0x10D73E30
// FUNCTION: ENGINE 0x10D73E50
// FUNCTION: ENGINE 0x10D73E70
// FUNCTION: ENGINE 0x10D73E90
// FUNCTION: ENGINE 0x10D73EB0
// FUNCTION: ENGINE 0x10D89A90
// FUNCTION: ENGINE 0x10D89AD0
// FUNCTION: ENGINE 0x10D89AE0
// FUNCTION: ENGINE 0x10D89AF0
// FUNCTION: ENGINE 0x10D89B00
// FUNCTION: ENGINE 0x10D89B10
// FUNCTION: ENGINE 0x10D89B20
// FUNCTION: ENGINE 0x10D89B30
// FUNCTION: ENGINE 0x10D89B40
// FUNCTION: ENGINE 0x10D89B50
// FUNCTION: ENGINE 0x10D89B80
// FUNCTION: ENGINE 0x10D89B90
// FUNCTION: ENGINE 0x10D89BA0
// FUNCTION: ENGINE 0x10D89BB0
// FUNCTION: ENGINE 0x10D89BD0
// FUNCTION: ENGINE 0x10D89BE0
// FUNCTION: ENGINE 0x10D89BF0
// FUNCTION: ENGINE 0x10D89C00
// FUNCTION: ENGINE 0x10D89C10
