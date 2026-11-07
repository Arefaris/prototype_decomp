// The instances of proto::Variant the AI helpers use (the tables of type discriminators with their statics, the
// discriminators' vftable slots and the constructors for each held type). No assert path names the unit; the file name
// is a guess.
#include "code/core/name.h"
#include "code/engine/gameobject/gameobjecthandle.h"
#include "code/math/obb.h"
#include "code/math/sphere.h"
#include "code/math/vector.h"
#include "code/proto/variant.h"

namespace
{
	typedef proto::Variant<float, math::OBB> FloatOBBVariant;
	typedef proto::Variant<math::Sphere, math::OBB> SphereOBBVariant;
	typedef proto::Variant<math::Vector, float, int, core::Name<core::CaseSensitiveKey>, engine::GameObjectHandle,
		bool> ValueVariant;
}

template class proto::Variant<float, math::OBB>;
template FloatOBBVariant::TypeDiscriminator* FloatOBBVariant::GetDiscriminator<float>();
template FloatOBBVariant::TypeDiscriminator* FloatOBBVariant::GetDiscriminator<math::OBB>();
template FloatOBBVariant::TypeDiscriminator* FloatOBBVariant::GetDiscriminator<proto::NilVariant>();
template void FloatOBBVariant::Construct<float>(const float&);
template void FloatOBBVariant::Construct<math::OBB>(const math::OBB&);

template class proto::Variant<math::Sphere, math::OBB>;
template SphereOBBVariant::TypeDiscriminator* SphereOBBVariant::GetDiscriminator<math::Sphere>();
template SphereOBBVariant::TypeDiscriminator* SphereOBBVariant::GetDiscriminator<math::OBB>();
template SphereOBBVariant::TypeDiscriminator* SphereOBBVariant::GetDiscriminator<proto::NilVariant>();
template void SphereOBBVariant::Construct<math::Sphere>(const math::Sphere&);
template void SphereOBBVariant::Construct<math::OBB>(const math::OBB&);

template class proto::Variant<math::Vector, float, int, core::Name<core::CaseSensitiveKey>, engine::GameObjectHandle,
	bool>;
template ValueVariant::TypeDiscriminator* ValueVariant::GetDiscriminator<math::Vector>();
template ValueVariant::TypeDiscriminator* ValueVariant::GetDiscriminator<float>();
template ValueVariant::TypeDiscriminator* ValueVariant::GetDiscriminator<int>();
template ValueVariant::TypeDiscriminator* ValueVariant::GetDiscriminator<core::Name<core::CaseSensitiveKey> >();
template ValueVariant::TypeDiscriminator* ValueVariant::GetDiscriminator<engine::GameObjectHandle>();
template ValueVariant::TypeDiscriminator* ValueVariant::GetDiscriminator<bool>();
template ValueVariant::TypeDiscriminator* ValueVariant::GetDiscriminator<proto::NilVariant>();
template void ValueVariant::Construct<math::Vector>(const math::Vector&);
template void ValueVariant::Construct<float>(const float&);
template void ValueVariant::Construct<core::Name<core::CaseSensitiveKey> >(const core::Name<core::CaseSensitiveKey>&);
template void ValueVariant::Construct<engine::GameObjectHandle>(const engine::GameObjectHandle&);
template void ValueVariant::Construct<bool>(const bool&);

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x10367C50
// FUNCTION: ENGINE 0x10367CC0
// FUNCTION: ENGINE 0x10369460
// FUNCTION: ENGINE 0x10369470
// FUNCTION: ENGINE 0x10369480
// FUNCTION: ENGINE 0x10369490
// FUNCTION: ENGINE 0x103694B0
// FUNCTION: ENGINE 0x103694C0
// FUNCTION: ENGINE 0x103694D0
// FUNCTION: ENGINE 0x103694E0
// FUNCTION: ENGINE 0x10369500
// FUNCTION: ENGINE 0x10369510
// FUNCTION: ENGINE 0x10369520
// FUNCTION: ENGINE 0x10369530
// FUNCTION: ENGINE 0x103745C0
// FUNCTION: ENGINE 0x103745F0
// FUNCTION: ENGINE 0x10374620
// FUNCTION: ENGINE 0x103768A0
// FUNCTION: ENGINE 0x10376AB0
// FUNCTION: ENGINE 0x10377620
// FUNCTION: ENGINE 0x10377680
// FUNCTION: ENGINE 0x10377C50
// FUNCTION: ENGINE 0x1037BF70
// FUNCTION: ENGINE 0x1037D0F0
// FUNCTION: ENGINE 0x1037D100
// FUNCTION: ENGINE 0x1037D110
// FUNCTION: ENGINE 0x1037D120
// FUNCTION: ENGINE 0x1037D150
// FUNCTION: ENGINE 0x1037D160
// FUNCTION: ENGINE 0x1037D170
// FUNCTION: ENGINE 0x1037D180
// FUNCTION: ENGINE 0x1037D190
// FUNCTION: ENGINE 0x1037D1A0
// FUNCTION: ENGINE 0x1037D1B0
// FUNCTION: ENGINE 0x1037D220
// FUNCTION: ENGINE 0x1037EA60
// FUNCTION: ENGINE 0x1037EA90
// FUNCTION: ENGINE 0x1037EAC0
// FUNCTION: ENGINE 0x1037EAE0
// FUNCTION: ENGINE 0x1037FB50
// FUNCTION: ENGINE 0x1037FD70
// FUNCTION: ENGINE 0x1037FFA0
// FUNCTION: ENGINE 0x10380010
// FUNCTION: ENGINE 0x103806C0
// FUNCTION: ENGINE 0x10381FE0
// FUNCTION: ENGINE 0x1038AD10
// FUNCTION: ENGINE 0x1038AE40
// FUNCTION: ENGINE 0x1038AF70
// FUNCTION: ENGINE 0x1038AF80
// FUNCTION: ENGINE 0x1038AF90
// FUNCTION: ENGINE 0x1038AFA0
// FUNCTION: ENGINE 0x1038AFD0
// FUNCTION: ENGINE 0x1038AFE0
// FUNCTION: ENGINE 0x1038AFF0
// FUNCTION: ENGINE 0x1038B000
// FUNCTION: ENGINE 0x1038B020
// FUNCTION: ENGINE 0x1038B030
// FUNCTION: ENGINE 0x1038B040
// FUNCTION: ENGINE 0x1038B050
// FUNCTION: ENGINE 0x1038B070
// FUNCTION: ENGINE 0x1038B080
// FUNCTION: ENGINE 0x1038B090
// FUNCTION: ENGINE 0x1038B0B0
// FUNCTION: ENGINE 0x1038B0C0
// FUNCTION: ENGINE 0x1038B0D0
// FUNCTION: ENGINE 0x1038B0E0
// FUNCTION: ENGINE 0x1038B100
// FUNCTION: ENGINE 0x1038B110
// FUNCTION: ENGINE 0x1038B120
// FUNCTION: ENGINE 0x1038B130
// FUNCTION: ENGINE 0x1038B150
// FUNCTION: ENGINE 0x1038B160
// FUNCTION: ENGINE 0x1038B170
// FUNCTION: ENGINE 0x1038B180
// FUNCTION: ENGINE 0x1038B190
// FUNCTION: ENGINE 0x1038B1C0
// FUNCTION: ENGINE 0x1038B1F0
// FUNCTION: ENGINE 0x1038B220
// FUNCTION: ENGINE 0x1038B250
// FUNCTION: ENGINE 0x1038B260
// FUNCTION: ENGINE 0x1038B290
// FUNCTION: ENGINE 0x1038B2C0
// FUNCTION: ENGINE 0x1038B2F0
// FUNCTION: ENGINE 0x1038B530
// FUNCTION: ENGINE 0x1038B580
// FUNCTION: ENGINE 0x1038B5E0
// FUNCTION: ENGINE 0x1038B640
// FUNCTION: ENGINE 0x1038B6A0
// FUNCTION: ENGINE 0x1038B700
