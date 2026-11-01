// The volume of a scene that excludes the NIS from playing (engine::NISExclusionVolume; code/engine/nis/nisexclusionvolume.cpp,
// the file name is a guess): its reflection.
#include "code/engine/reflectedclasses.h"

namespace engine
{
#define ENGINE_OFFSET(type, member) 	content::MemberOffset(&((type*)0)->member, (int)&((type*)0)->member)

	// FUNCTION: ENGINE 0x1088B8A0
	content::ClassInfo* NISExclusionVolume::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "engine::NISExclusionVolume";
		sInfo.code = "p";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x1088C180
	content::MemberList* NISExclusionVolume::GetMembers()
	{
		static content::MemberList sList;
		static content::MemberInfo sMembers[] =
		{
			{ content::GetClassMetaType<math::OBB>(), ENGINE_OFFSET(NISExclusionVolume, obb), "obb" }
		};
		sList.members = sMembers;
		sList.count = 1;
		return &sList;
	}
}
