#include "code/engine/camera/cameraloader.h"
#include "code/engine/camera/cinematographer.h"

namespace engine
{
	namespace camera
	{
#define ENGINE_OFFSET(type, member) \
	content::MemberOffset(&((type*)0)->member, (int)&((type*)0)->member)
#define ENGINE_NAME_OFFSET(type, member) \
	content::MemberOffset((core::Name<core::CaseSensitiveKey>*)&((type*)0)->member, (int)&((type*)0)->member)

		// FUNCTION: ENGINE 0x109067F0
		content::ClassInfo* CameraLoader::GetClassInfo()
		{
			static content::ClassInfo sInfo;
			sInfo.version = 1;
			sInfo.name = "engine::camera::CameraLoader";
			sInfo.code = "pn";
			return &sInfo;
		}

		// FUNCTION: ENGINE 0x10906830
		bool CameraLoader::IsReady()
		{
			return true;
		}

		// FUNCTION: ENGINE 0x109068C0
		core::Name<core::CaseSensitiveKey> CameraLoader::GetAvatarName() const
		{
			return avatarName;
		}

		// FUNCTION: ENGINE 0x109068E0
		CameraLoader::~CameraLoader()
		{
			if (camera != 0)
			{
				delete camera;
			}
		}

		// FUNCTION: ENGINE 0x10906940
		// EQUIVALENT: the engine's lea of the first name member sits behind the reference count store, ours before it, 88.2 %
		CameraLoader::CameraLoader() : camera(0), spawnActive(false), type(0)
		{
		}

		// FUNCTION: ENGINE 0x10906B20
		content::MemberList* CameraLoader::GetMembers()
		{
			static content::MemberList sList;
			static content::MemberInfo sMembers[] =
			{
				{ content::GetObjectMetaType<Camera>("pn"), ENGINE_OFFSET(CameraLoader, camera), "camera" },
				{ content::GetMemberPrimitiveMetaType<CameraLoader, bool, 0>("pn"),
					ENGINE_OFFSET(CameraLoader, spawnActive), "spawnActive" },
				{ content::GetNameMetaType<CameraLoader>(true, true, "pn"),
					ENGINE_NAME_OFFSET(CameraLoader, avatarName), "avatarName" },
				{ content::GetNameMetaType<Cinematographer>(true, true, "pn"),
					ENGINE_NAME_OFFSET(CameraLoader, cinematographerName), "cinematographerName" },
				{ content::GetEnumMetaType<CinematographerType>(), 0x24, "type" }
			};
			sList.members = sMembers;
			sList.count = 5;
			return &sList;
		}
	}
}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x10906840
// FUNCTION: ENGINE 0x10906900
// FUNCTION: ENGINE 0x10906980
// FUNCTION: ENGINE 0x10906AD0
