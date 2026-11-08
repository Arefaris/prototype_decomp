#include "code/proto/timeofday/globalshaderrig.h"

namespace proto
{
#define PROTO_OFFSET(type, member) \
	content::MemberOffset(&((type*)0)->member, (int)&((type*)0)->member)
#define PROTO_NAME_OFFSET(type, member) \
	content::MemberOffset((core::Name<core::CaseSensitiveKey>*)&((type*)0)->member, (int)&((type*)0)->member)

	// FUNCTION: ENGINE 0x1054D580
	template<> content::ClassInfo* GlobalShaderRig::Param<float>::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "proto::GlobalShaderRig::Param<float>";
		sInfo.code = "p";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x1054D5C0
	template<> content::ClassInfo* GlobalShaderRig::Param<math::Vector>::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "proto::GlobalShaderRig::Param<math::Vector>";
		sInfo.code = "p";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x1054D600
	template<> content::ClassInfo* GlobalShaderRig::Param<math::Colour128>::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "proto::GlobalShaderRig::Param<math::Colour>";
		sInfo.code = "p";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x1054D640
	content::ClassInfo* GlobalShaderRig::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "proto::GlobalShaderRig";
		sInfo.code = "p";
		return &sInfo;
	}

	// Left to the engine (it calls another copy of MemberOffset<Name> than the one mapped for the other units)
	template<> content::MemberList* GlobalShaderRig::Param<float>::GetMembers()
	{
		static content::MemberList sList;
		static content::MemberInfo sMembers[] =
		{
			{ content::GetNameMetaType<Param<float> >(false, false, "p"), PROTO_NAME_OFFSET(Param<float>, name), "name" },
			{ content::GetClassMetaType<TimeOfDayVarChannel<float> >(), PROTO_OFFSET(Param<float>, values), "values" }
		};
		sList.members = sMembers;
		sList.count = 2;
		return &sList;
	}

	// Left to the engine (it calls another copy of MemberOffset<Name> than the one mapped for the other units)
	template<> content::MemberList* GlobalShaderRig::Param<math::Vector>::GetMembers()
	{
		static content::MemberList sList;
		static content::MemberInfo sMembers[] =
		{
			{ content::GetNameMetaType<Param<math::Vector> >(false, false, "p"), PROTO_NAME_OFFSET(Param<math::Vector>, name), "name" },
			{ content::GetClassMetaType<TimeOfDayVarChannel<math::Vector> >(), PROTO_OFFSET(Param<math::Vector>, values), "values" }
		};
		sList.members = sMembers;
		sList.count = 2;
		return &sList;
	}

	// Left to the engine (it calls another copy of MemberOffset<Name> than the one mapped for the other units)
	template<> content::MemberList* GlobalShaderRig::Param<math::Colour128>::GetMembers()
	{
		static content::MemberList sList;
		static content::MemberInfo sMembers[] =
		{
			{ content::GetNameMetaType<Param<math::Colour128> >(false, false, "p"), PROTO_NAME_OFFSET(Param<math::Colour128>, name), "name" },
			{ content::GetClassMetaType<TimeOfDayVarChannel<math::Colour128> >(), PROTO_OFFSET(Param<math::Colour128>, values), "values" }
		};
		sList.members = sMembers;
		sList.count = 2;
		return &sList;
	}

	// FUNCTION: ENGINE 0x1054E920
	content::MemberList* GlobalShaderRig::GetMembers()
	{
		static content::MemberList sList;
		static content::MemberInfo sMembers[] =
		{
			{ content::GetArrayDynamicMetaType<GlobalShaderRig, container::ArrayDynamic<Param<float>, container::AllocatorNew> >(
				content::GetClassMetaType<Param<float> >(), "p"), PROTO_OFFSET(GlobalShaderRig, float1s), "float1s" },
			{ content::GetArrayDynamicMetaType<GlobalShaderRig, container::ArrayDynamic<Param<math::Vector>, container::AllocatorNew> >(
				content::GetClassMetaType<Param<math::Vector> >(), "p"), PROTO_OFFSET(GlobalShaderRig, float3s), "float3s" },
			{ content::GetArrayDynamicMetaType<GlobalShaderRig, container::ArrayDynamic<Param<math::Colour128>, container::AllocatorNew> >(
				content::GetClassMetaType<Param<math::Colour128> >(), "p"), PROTO_OFFSET(GlobalShaderRig, float4s), "float4s" }
		};
		sList.members = sMembers;
		sList.count = 3;
		return &sList;
	}

	template class GlobalShaderRig::Param<float>;
	template class GlobalShaderRig::Param<math::Vector2>;
	template class GlobalShaderRig::Param<math::Vector>;
	template class GlobalShaderRig::Param<math::Colour128>;
}

namespace container
{
	template class ArrayDynamic<proto::GlobalShaderRig::Param<float>, AllocatorNew>;
	template class ArrayDynamic<proto::GlobalShaderRig::Param<math::Vector2>, AllocatorNew>;
	template class ArrayDynamic<proto::GlobalShaderRig::Param<math::Vector>, AllocatorNew>;
	template class ArrayDynamic<proto::GlobalShaderRig::Param<math::Colour128>, AllocatorNew>;
}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x1054D740
// FUNCTION: ENGINE 0x1054D7A0
// FUNCTION: ENGINE 0x1054D800
// FUNCTION: ENGINE 0x1054D990
// FUNCTION: ENGINE 0x1054D9D0
// FUNCTION: ENGINE 0x1054D9E0
// FUNCTION: ENGINE 0x1054DA20
// FUNCTION: ENGINE 0x1054DA30
// FUNCTION: ENGINE 0x1054DA70
// FUNCTION: ENGINE 0x1054DA80
// FUNCTION: ENGINE 0x1054DA90
// FUNCTION: ENGINE 0x1054DAA0
// FUNCTION: ENGINE 0x1054E0C0
// FUNCTION: ENGINE 0x1054E120
// FUNCTION: ENGINE 0x1054E180
// FUNCTION: ENGINE 0x1054E2B0
// FUNCTION: ENGINE 0x1054E2C0
// FUNCTION: ENGINE 0x1054E2E0
// FUNCTION: ENGINE 0x1054E300
// FUNCTION: ENGINE 0x1054E320
// FUNCTION: ENGINE 0x1054E340
// FUNCTION: ENGINE 0x1054E3B0
// FUNCTION: ENGINE 0x1054E3C0
// FUNCTION: ENGINE 0x1054E3E0
// FUNCTION: ENGINE 0x1054E400
// FUNCTION: ENGINE 0x1054E420
// FUNCTION: ENGINE 0x1054E440
// FUNCTION: ENGINE 0x1054E4B0
// FUNCTION: ENGINE 0x1054E4C0
// FUNCTION: ENGINE 0x1054E4E0
// FUNCTION: ENGINE 0x1054E500
// FUNCTION: ENGINE 0x1054E520
// FUNCTION: ENGINE 0x1054E540
// FUNCTION: ENGINE 0x1054E800
// FUNCTION: ENGINE 0x1054E860
// FUNCTION: ENGINE 0x1054E8C0
// FUNCTION: ENGINE 0x1054F070
// FUNCTION: ENGINE 0x1054F090
// FUNCTION: ENGINE 0x1054F0B0
// FUNCTION: ENGINE 0x10550070
// FUNCTION: ENGINE 0x105500C0
// FUNCTION: ENGINE 0x10550130
// FUNCTION: ENGINE 0x10550280
// FUNCTION: ENGINE 0x10550300
// FUNCTION: ENGINE 0x10550500
