#include "code/proto/tunnelvolume.h"
#include "code/math/matrix3.h"

namespace engine
{
	namespace driving
	{
		extern const float gOne;
	}
}

namespace proto
{
#define PROTO_OFFSET(type, member) \
	content::MemberOffset(&((type*)0)->member, (int)&((type*)0)->member)

	// FUNCTION: ENGINE 0x103B2590
	content::ClassInfo* TunnelVolume::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "proto::TunnelVolume";
		sInfo.code = "pn";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x103B28D0
	content::MemberList* TunnelVolume::GetMembers()
	{
		static content::MemberList sList;
		static content::MemberInfo sMembers[] =
		{
			{ content::GetClassMetaType<math::OBB>(), PROTO_OFFSET(TunnelVolume, box), "box" },
			{ content::GetMemberVectorMetaType<TunnelVolume, 0>("p"), 0x44, "entrance1" },
			{ content::GetMemberVectorMetaType<TunnelVolume, 1>("p"), 0x50, "entrance2" }
		};
		sList.members = sMembers;
		sList.count = 3;
		return &sList;
	}

	// FUNCTION: ENGINE 0x103B2C70
	// NONMATCHING: scheduling, the engine stores the address of the Matrix3 temporary after the reference count (95.8 %)
#ifdef NONMATCHING
	TunnelVolume::TunnelVolume()
	{
		math::Matrix3 identity;
		identity.Identity();
		box.centre.x = 0.0f;
		box.centre.y = 0.0f;
		box.centre.z = 0.0f;
		box.axis[0].x = identity.m[0][0];
		box.axis[0].y = identity.m[0][1];
		box.axis[0].z = identity.m[0][2];
		box.axis[1].x = identity.m[1][0];
		box.axis[1].y = identity.m[1][1];
		box.axis[1].z = identity.m[1][2];
		box.axis[2].x = identity.m[2][0];
		box.axis[2].y = identity.m[2][1];
		box.axis[2].z = identity.m[2][2];
		box.extents.x = 1.0f;
		box.extents.y = 1.0f;
		box.extents.z = 1.0f;
		entrance1.x = math::kZeroVector.x;
		entrance1.y = math::kZeroVector.y;
		entrance1.z = math::kZeroVector.z;
		entrance2.x = math::kZeroVector.x;
		entrance2.y = math::kZeroVector.y;
		entrance2.z = math::kZeroVector.z;
	}
#endif

	TunnelVolume::~TunnelVolume()
	{
	}
}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x103B2750
// FUNCTION: ENGINE 0x103B2820

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x103B25D0

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x103B2830
// FUNCTION: ENGINE 0x103B2870
