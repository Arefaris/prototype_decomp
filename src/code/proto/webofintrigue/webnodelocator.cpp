#include "code/proto/webofintrigue/webnodelocator.h"
#include "code/proto/webofintrigue/webofintriguemanager.h"

namespace proto
{
#define PROTO_OFFSET(type, member) \
	content::MemberOffset(&((type*)0)->member, (int)&((type*)0)->member)

	// FUNCTION: ENGINE 0x1055B1E0
	content::ClassInfo* WebNodeLocator::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "proto::WebNodeLocator";
		sInfo.code = "p";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x1055B2F0
	content::MemberList* WebNodeLocator::GetMembers()
	{
		static content::MemberList sList;
		static content::MemberInfo sMembers[] =
		{
			{ content::GetMatrixMetaType<WebNodeLocator>(false, false, "p"),
				PROTO_OFFSET(WebNodeLocator, transform), "transform" },
			{ content::GetMemberPrimitiveMetaType<WebNodeLocator, int, 0>("p"),
				PROTO_OFFSET(WebNodeLocator, nodeID), "nodeID" }
		};
		sList.members = sMembers;
		sList.count = 2;
		return &sList;
	}

	// FUNCTION: ENGINE 0x1055B3C0
	WebNodeLocator::WebNodeLocator() : transform(math::Matrix::IDENTITY), nodeID(-1)
	{
	}

	WebNodeLocator::~WebNodeLocator()
	{
	}

	// FUNCTION: ENGINE 0x1055B230
	void WebNodeLocator::Slot3(int unused)
	{
		gWebOfIntrigueManager->SetNodeTransform(nodeID, &transform);
	}

	// FUNCTION: ENGINE 0x1055B250
	bool WebNodeLocator::IsReady()
	{
		gWebOfIntrigueManager->NodeLocatorLoaded(nodeID);
		return true;
	}
}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x1055B220
// FUNCTION: ENGINE 0x1055B270
// FUNCTION: ENGINE 0x1055B2B0
// FUNCTION: ENGINE 0x1055B4F0
