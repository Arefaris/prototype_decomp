// engine::FmvSubtitleManager (code/engine/fmv/fmvsubtitlemanager.cpp): the subtitles of a full-motion video. The
// manager is a content library object: it reflects itself (the class info, the three members of a SubTitleEnty and
// the element array they live in) and is created from a .fmv description through content::MetaObjectFactory. The
// element array is a container::ArrayDynamic over operator new[]; the members of the array and of its reflection
// helper are the ones this unit instantiates.
#include "code/container/arraydynamicallocatornew.h"
#include "code/container/arraydynamicstatic.h"
#include "code/engine/fmv/fmvsubtitlemanager.h"

namespace container
{
	template class ArrayDynamic<engine::FmvSubtitleManager::SubTitleEnty, AllocatorNew>;
}

namespace engine
{
	// FUNCTION: ENGINE 0x108C07F0
	FmvSubtitleManager::SubTitleEnty::SubTitleEnty()
		: startTime(-1.0f), endTime(-1.0f), unknown108(0)
	{
		subtitleId[0] = 0;
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

// The members of the element array and of the template functions it uses, which the header defines and this unit
// instantiates (the array's own copies, in address order):
// FUNCTION: ENGINE 0x108C0580 operator[]
// FUNCTION: ENGINE 0x108C05E0 Create
// FUNCTION: ENGINE 0x108C0630 Size
// FUNCTION: ENGINE 0x108C06A0 content::MemberOffset<char [256]>
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
