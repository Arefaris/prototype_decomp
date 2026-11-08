#include "code/proto/webofintrigue/webofintriguemanager.h"

namespace proto
{
	// FUNCTION: ENGINE 0x10563080
	content::ClassInfo* WOIEpisode::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "proto::WOIEpisode";
		sInfo.code = "p";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x10563140
	content::MemberList* WOIEpisode::GetMembers()
	{
		static content::MemberList sList;
		static content::MemberInfo sMembers[] =
		{
			{ content::GetMemberPrimitiveMetaType<WOIEpisode, unsigned int, 0>("p"),
				content::MemberOffset((unsigned int*)&((WOIEpisode*)0)->total, (int)&((WOIEpisode*)0)->total), "numberOfNodes" }
		};
		sList.members = sMembers;
		sList.count = 1;
		return &sList;
	}

	// FUNCTION: ENGINE 0x105631E0
	WOIEpisode::WOIEpisode() : done(0), total(0)
	{
	}

	// FUNCTION: ENGINE 0x105630C0
	void WOIEpisode::Slot3(int unused)
	{
		gWebOfIntrigueManager->AddVisible(this);
	}

	// FUNCTION: ENGINE 0x105630E0
	bool WOIEpisode::IsReady()
	{
		return true;
	}

	// FUNCTION: ENGINE 0x105630F0
	void WOIEpisode::ResetDone()
	{
		done = 0;
	}
}

// Kept copies (template instances and wrappers of this unit):
// FUNCTION: ENGINE 0x10563100
// FUNCTION: ENGINE 0x10563200
// FUNCTION: ENGINE 0x10563210
