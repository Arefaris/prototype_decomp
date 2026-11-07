#include "code/proto/render/protocolourvariationbehaviour.h"
#include "code/core/refptr.h"

namespace proto
{
#define PROTO_OFFSET(type, member) \
	content::MemberOffset(&((type*)0)->member, (int)&((type*)0)->member)

	// FUNCTION: ENGINE 0x102DE540
	ProtoColourVariationBehaviour::ProtoColourVariationBehaviour(engine::GameObject* newOwner)
		: engine::Behaviour(newOwner), shaderPalette(0), paletteIndex(0), createPatchForNewDrawable(false)
	{
		Listen(7, true);
		Listen(0x3d, true);
		Listen(2, true);
	}

	// FUNCTION: ENGINE 0x102DE610
	ProtoColourVariationBehaviour::~ProtoColourVariationBehaviour()
	{
		core::SafeRelease(shaderPalette);
	}

	// FUNCTION: ENGINE 0x102DE500
	content::ClassInfo* ProtoColourVariationBehaviour::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "proto::ProtoColourVariationBehaviour";
		sInfo.code = "p";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x102DEA40
	content::MemberList* ProtoColourVariationBehaviour::GetMembers()
	{
		static content::MemberList sList;
		sList.baseType = content::GetClassMetaType<engine::Behaviour>();
		static content::BaseClassCasterImpl<engine::Behaviour, ProtoColourVariationBehaviour> sCaster;
		sList.baseCaster = &sCaster;
		static content::MemberInfo sMembers[] =
		{
			{ content::GetReferenceMetaType<ProtoColourVariationBehaviour, ShaderPalette>("p"),
				PROTO_OFFSET(ProtoColourVariationBehaviour, shaderPalette), "shaderPalette" },
			{ content::GetMemberPrimitiveMetaType<ProtoColourVariationBehaviour, bool, 0>("p"),
				PROTO_OFFSET(ProtoColourVariationBehaviour, createPatchForNewDrawable),
				"createPatchForNewDrawable" }
		};
		sList.members = sMembers;
		sList.count = 2;
		return &sList;
	}
}
