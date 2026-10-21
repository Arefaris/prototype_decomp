#include "code/engine/remotecamera.h"

namespace engine
{
#define ENGINE_OFFSET(type, member) \
	content::MemberOffset(&((type*)0)->member, (int)&((type*)0)->member)

	// FUNCTION: ENGINE 0x1090DA00
	content::ClassInfo* RemoteCamera::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "engine::RemoteCamera";
		sInfo.code = "p";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x1090DBD0
	content::MemberList* RemoteCamera::GetMembers()
	{
		static content::MemberList sList;
		static content::MemberInfo sMembers[] =
		{
			{ content::GetMemberVectorMetaType<RemoteCamera, 0>("p"), 8, "Position" },
			{ content::GetMemberVectorMetaType<RemoteCamera, 1>("p"), 0x14, "Target" },
			{ content::GetMemberVectorMetaType<RemoteCamera, 2>("p"), 0x20, "Up" },
			{ content::GetMemberPrimitiveMetaType<RemoteCamera, float, 0>("p"), ENGINE_OFFSET(RemoteCamera, fov), "FOV" },
			{ content::GetMemberPrimitiveMetaType<RemoteCamera, float, 1>("p"),
				ENGINE_OFFSET(RemoteCamera, nearPlane), "NearPlane" },
			{ content::GetMemberPrimitiveMetaType<RemoteCamera, float, 2>("p"),
				ENGINE_OFFSET(RemoteCamera, farPlane), "FarPlane" },
			{ content::GetMemberPrimitiveMetaType<RemoteCamera, bool, 0>("p"), ENGINE_OFFSET(RemoteCamera, active),
				"Active" }
		};
		sList.members = sMembers;
		sList.count = 7;
		return &sList;
	}

	// FUNCTION: ENGINE 0x1090DD30
	// EQUIVALENT: the engine stores the vftable and the reference count before the members, ours after them, 71.6 %
	RemoteCamera::RemoteCamera() : fov(1.0f), nearPlane(1.0f), farPlane(500.0f), active(false)
	{
		position.x = 0.0f;
		position.y = 0.0f;
		position.z = 0.0f;
		target.x = 0.0f;
		target.y = 0.0f;
		target.z = 0.0f;
		up.x = 0.0f;
		up.y = 0.0f;
		up.z = 0.0f;
	}
}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x1090DA40
// FUNCTION: ENGINE 0x1090DA70
// FUNCTION: ENGINE 0x1090DAA0
// FUNCTION: ENGINE 0x1090DAD0
// FUNCTION: ENGINE 0x1090DB10
// FUNCTION: ENGINE 0x1090DB50
// FUNCTION: ENGINE 0x1090DB90
// FUNCTION: ENGINE 0x1090DDA0
