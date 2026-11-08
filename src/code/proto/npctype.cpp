#include "code/proto/npctype.h"
#include "code/core/refptr.h"

namespace proto
{
#define PROTO_OFFSET(type, member) 	content::MemberOffset(&((type*)0)->member, (int)&((type*)0)->member)

#define PROTO_NAME_OFFSET(type, member) 	content::MemberOffset((core::Name<core::CaseSensitiveKey>*)&((type*)0)->member, (int)&((type*)0)->member)

	// FUNCTION: ENGINE 0x1047AFE0
	content::ClassInfo* NPCRender::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "proto::NPCRender";
		sInfo.code = "pn";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x1047B020
	content::ClassInfo* NPCType::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "proto::NPCType";
		sInfo.code = "pn";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x1047B060
	NPCDrawable* NPCRender::GetLod(int level) const
	{
		return lods[level];
	}

	// FUNCTION: ENGINE 0x1047B190
	NPCRender::NPCRender() : shaderPalette(0)
	{
		lods[0] = 0;
		lods[1] = 0;
	}

	// FUNCTION: ENGINE 0x1047B200
	NPCRender::~NPCRender()
	{
		for (int i = 0; i < 2; i++)
		{
			if (lods[i] != 0)
			{
				core::SafeRelease(lods[i]);
			}
		}
		core::SafeRelease(shaderPalette);
	}

	// FUNCTION: ENGINE 0x1047B250
	NPCType::NPCType() : lodCharacter(0), gender("male", 1), characterTemplate(0), instancePool(0), voice("p_ctf", 1)
	{
	}

	// FUNCTION: ENGINE 0x1047B2B0
	NPCType::~NPCType()
	{
		core::SafeRelease(instancePool);
		core::SafeRelease(characterTemplate);
		core::SafeRelease((core::IRefCount*&)lodCharacter);
	}

	// FUNCTION: ENGINE 0x1047B2F0
	void NPCType::SetName(const content::ObjectName& newName)
	{
		name = newName;
	}

	// FUNCTION: ENGINE 0x1047B620
	content::MemberList* NPCRender::GetMembers()
	{
		static content::MemberList sList;
		static content::MemberInfo sMembers[] =
		{
			{ content::GetMemberReferenceMetaType<NPCRender, NPCDrawable, 0>("p"),
				PROTO_OFFSET(NPCRender, lods[0]), "lod_Medium" },
			{ content::GetMemberReferenceMetaType<NPCRender, NPCDrawable, 1>("p"),
				PROTO_OFFSET(NPCRender, lods[1]), "lod_Low" },
			{ content::GetReferenceMetaType<NPCRender, ShaderPalette>("p"),
				PROTO_OFFSET(NPCRender, shaderPalette), "shaderPalette" }
		};
		sList.members = sMembers;
		sList.count = 3;
		return &sList;
	}

	// FUNCTION: ENGINE 0x1047B720
	content::MemberList* NPCType::GetMembers()
	{
		static content::MemberList sList;
		sList.baseType = content::GetClassMetaType<NPCRender>();
		static content::BaseClassCasterImpl<NPCRender, NPCType> sCaster;
		sList.baseCaster = &sCaster;
		static content::MemberInfo sMembers[] =
		{
			{ content::GetReferenceMetaType<NPCType, content::MetaObjectTemplate>("p"),
				PROTO_OFFSET(NPCType, characterTemplate), "characterTemplate" },
			{ content::GetReferenceMetaType<NPCType, NPCInstancePool>("p"),
				PROTO_OFFSET(NPCType, instancePool), "instancePool" },
			{ content::GetMemberNameMetaType<NPCType, 0>(true, true, "pn"),
				PROTO_NAME_OFFSET(NPCType, gender), "gender" },
			{ content::GetMemberNameMetaType<NPCType, 1>(true, true, "pn"),
				PROTO_NAME_OFFSET(NPCType, voice), "voice" },
			{ content::GetReferenceMetaType<NPCType, engine::render::DrawableArchetype>("p"),
				PROTO_OFFSET(NPCType, lodCharacter), "lod_Character" }
		};
		sList.members = sMembers;
		sList.count = 5;
		return &sList;
	}
}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x1047B0B0
// FUNCTION: ENGINE 0x1047B0C0
// FUNCTION: ENGINE 0x1047B0D0
// FUNCTION: ENGINE 0x1047B110
// FUNCTION: ENGINE 0x1047B150
// FUNCTION: ENGINE 0x1047B170
// FUNCTION: ENGINE 0x1047B1C0
// FUNCTION: ENGINE 0x1047B1D0
// FUNCTION: ENGINE 0x1047B300
// FUNCTION: ENGINE 0x1047B310
// FUNCTION: ENGINE 0x1047B340
// FUNCTION: ENGINE 0x1047B350
// FUNCTION: ENGINE 0x1047B380
// FUNCTION: ENGINE 0x1047B3B0
// FUNCTION: ENGINE 0x1047B3E0
// FUNCTION: ENGINE 0x1047B440
// FUNCTION: ENGINE 0x1047B4A0
// FUNCTION: ENGINE 0x1047B500
// FUNCTION: ENGINE 0x1047B560
// FUNCTION: ENGINE 0x1047B5C0
