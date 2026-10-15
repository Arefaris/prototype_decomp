// engine::FmvSubtitleManager (code/engine/fmv/fmvsubtitlemanager.cpp): the subtitles of a full-motion video. The
// manager is a content library object: it reflects itself (the class info, the three members of a SubTitleEnty and
// the element array they live in) and is created from a .fmv description through content::MetaObjectFactory. The
// element array is a container::ArrayDynamic over operator new[]; the members of the array and of its reflection
// helper are the ones this unit instantiates.
#include "code/container/arraydynamicallocatornew.h"
#include "code/container/arraydynamicstatic.h"
#include "code/engine/fmv/fmvsubtitlemanager.h"
#include "code/engine/system/streampackage.h"

namespace container
{
	template class ArrayDynamic<engine::FmvSubtitleManager::SubTitleEnty, AllocatorNew>;
}

namespace engine
{
	// FUNCTION: ENGINE 0x108C0500
	const content::ClassInfo* FmvSubtitleManager::SubTitleEnty::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "engine::FmvSubtitleManager::SubTitleEnty";
		sInfo.code = "";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x108C0540
	const content::ClassInfo* FmvSubtitleManager::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "engine::FmvSubtitleManager";
		sInfo.code = "";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x108C0AD0
	const content::MemberList* FmvSubtitleManager::SubTitleEnty::GetMembers()
	{
		static content::MemberList sList;
		// The tag of each member's meta type only tells the two float members' instances apart
		static content::MemberInfo sMembers[3] = {
			{ content::GetStringMetaType(STRING_CAPACITY, ""),
				content::MemberOffset(&((SubTitleEnty*)0)->subtitleId, 0), "subtitleId" },
			{ content::GetMemberPrimitiveMetaType<SubTitleEnty, float, 32>(""),
				content::MemberOffset(&((SubTitleEnty*)0)->startTime, 0x100), "startTime" },
			{ content::GetMemberPrimitiveMetaType<SubTitleEnty, float, 35>(""),
				content::MemberOffset(&((SubTitleEnty*)0)->endTime, 0x104), "endTime" },
		};
		sList.members = sMembers;
		sList.count = 3;
		return &sList;
	}
}

namespace content
{
	// FUNCTION: ENGINE 0x108C0670
	StringMetaType* GetStringMetaType(int capacity, const char* code)
	{
		static StringMetaType sType(capacity, code);
		return &sType;
	}
}

namespace content
{
	// The class meta type of a subtitle and the meta type of the array the subtitles live in, which the manager's
	// reflection is built from (the copies also come out of the classes' own reflection units)
	template ClassMetaType* GetClassMetaType<engine::FmvSubtitleManager::SubTitleEnty>();
	template ArrayDynamicMetaType* GetArrayDynamicMetaType<engine::FmvSubtitleManager,
		engine::FmvSubtitleManager::SubTitleArray>(MetaType*, const char*);
	// The lookups the unit makes in the inventory
	template engine::FmvSubtitleManager* LoadInventory::Find<engine::FmvSubtitleManager>(const char*);
	template engine::StreamPackage* LoadInventory::Find<engine::StreamPackage>(const char*);
}

namespace content
{
	// The offset of the subtitles member in the manager, which the manager's own member list holds
	template int MemberOffset<engine::FmvSubtitleManager::SubTitleArray>(
		engine::FmvSubtitleManager::SubTitleArray*, int);
}

namespace container
{
	// The range copies the array's elements with
	template engine::FmvSubtitleManager::SubTitleEnty* AssignRange(
		const engine::FmvSubtitleManager::SubTitleEnty* first,
		const engine::FmvSubtitleManager::SubTitleEnty* last,
		engine::FmvSubtitleManager::SubTitleEnty* dest);
}

namespace content
{
	// the default element the reflection inserts (Insert is the engine's copy, which calls this one)
	ArrayDynamicHelper<engine::FmvSubtitleManager::SubTitleArray>::T& ArrayDynamicHelper<engine::FmvSubtitleManager::SubTitleArray>::Default()
	{
		static T sDefault;
		return sDefault;
	}
}

// The headers' members this unit instantiates, in address order:
// FUNCTION: ENGINE 0x108C07F0 the element's constructor
// The element array's members and the template functions it uses:
// FUNCTION: ENGINE 0x108C0580 operator[]
// FUNCTION: ENGINE 0x108C05E0 Create
// FUNCTION: ENGINE 0x108C0630 Size
// FUNCTION: ENGINE 0x108C06A0 content::MemberOffset<char [256]>
// FUNCTION: ENGINE 0x108C06B0 content::MemberOffset<SubTitleEnty array>
// FUNCTION: ENGINE 0x108C06D0 the constructor
// FUNCTION: ENGINE 0x108C06E0 Allocate
// FUNCTION: ENGINE 0x108C0750 content::GetMemberPrimitiveMetaType (startTime)
// FUNCTION: ENGINE 0x108C0790 content::GetMemberPrimitiveMetaType (endTime)
// FUNCTION: ENGINE 0x108C0860 Capacity
// FUNCTION: ENGINE 0x108C0890 operator[] const
// FUNCTION: ENGINE 0x108C08E0 container::ConstructCopyAt
// FUNCTION: ENGINE 0x108C0940 container::ConstructFill
// FUNCTION: ENGINE 0x108C09F0 Erase
// FUNCTION: ENGINE 0x108C0A50 Free
// FUNCTION: ENGINE 0x108C0A80 ShiftUp
// FUNCTION: ENGINE 0x108C0F00 Reserve
// FUNCTION: ENGINE 0x108C0FE0 Insert (count copies)
// FUNCTION: ENGINE 0x108C07E0 the array helper's constructor
// FUNCTION: ENGINE 0x108C0820 the array helper's Size
// FUNCTION: ENGINE 0x108C0840 the array helper's Get
// FUNCTION: ENGINE 0x108C08A0 the array helper's Default
// FUNCTION: ENGINE 0x108C0900 container::AssignRange
// FUNCTION: ENGINE 0x108C0980 the caster's constructor
// FUNCTION: ENGINE 0x108C0990 the caster's Cast
// FUNCTION: ENGINE 0x108C09B0 the array helper's GetConst
// FUNCTION: ENGINE 0x108C09D0 the array helper's Capacity
// FUNCTION: ENGINE 0x108C0DB0 Clear
// FUNCTION: ENGINE 0x108C0DC0 content::GetClassMetaType<SubTitleEnty>
// FUNCTION: ENGINE 0x108C0E10 content::GetArrayDynamicMetaType (the subtitles member)
// FUNCTION: ENGINE 0x108C0E60 content::LoadInventory::Find<FmvSubtitleManager>
// FUNCTION: ENGINE 0x108C0EA0 content::LoadInventory::Find<StreamPackage>
// FUNCTION: ENGINE 0x108C0EE0 the array helper's Erase
