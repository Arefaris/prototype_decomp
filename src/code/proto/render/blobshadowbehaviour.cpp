#include "code/proto/render/blobshadowbehaviour.h"
#include "code/core/heap.h"
#include "code/core/refptr.h"
#include "code/pure3d/pddi/dx9/dxcontext.h"

namespace proto
{
#define PROTO_OFFSET(type, member) \
	content::MemberOffset(&((type*)0)->member, (int)&((type*)0)->member)

	// FUNCTION: ENGINE 0x102EDD90
	BlobShadowBehaviour::BlobShadowBehaviour(engine::GameObject* newOwner) : engine::Behaviour(newOwner), position(-10000.0f, -10000.0f, -10000.0f), radius(engine::driving::gOne)
	{
		blobTexture = 0;
		shader = 0;
	}

	// FUNCTION: ENGINE 0x102EDD50
	content::ClassInfo* BlobShadowBehaviour::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "proto::BlobShadowBehaviour";
		sInfo.code = "p";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x102EDDF0
	void BlobShadowBehaviour::DestroyDrawable()
	{
		core::HeapScope scope(0xb2);
		if (drawable.IsValid())
		{
			engine::render::Drawable::Destroy(&drawable, 0);
		}
	}

	// FUNCTION: ENGINE 0x102EDE40
	void BlobShadowBehaviour::OnActiveChanged(bool active)
	{
		engine::Behaviour::OnActiveChanged(active);
		if (drawable.IsValid())
		{
			drawable.SetPartsUnknown(active);
		}
	}

	// FUNCTION: ENGINE 0x102EDE80
	void BlobShadowBehaviour::OnMessage(engine::Message* message)
	{
	}

	// FUNCTION: ENGINE 0x102EDF00
	BlobShadowBehaviour::~BlobShadowBehaviour()
	{
		core::HeapScope scope(0xb2);
		DestroyDrawable();
		core::SafeRelease(blobTexture);
		core::SafeRelease(shader);
	}

	// FUNCTION: ENGINE 0x102EDF60
	void BlobShadowBehaviour::Slot1()
	{
		core::HeapScope scope(0xb2);
		Listen2(4, true);
		core::RefAssign(shader, new pure3d::Shader("env_blobshadow"));
		core::Name<core::CaseInsensitiveKey32> name("blobTexture", 1);
		pure3d::Shader* current = shader;
		pure3d::dxTexture* texture = blobTexture != 0 ? blobTexture->info : 0;
		current->shader->SetTexture(name, texture);
	}

	// FUNCTION: ENGINE 0x102EE680
	content::MemberList* BlobShadowBehaviour::GetMembers()
	{
		static content::MemberList sList;
		sList.baseType = content::GetClassMetaType<engine::Behaviour>();
		static content::BaseClassCasterImpl<engine::Behaviour, BlobShadowBehaviour> sCaster;
		sList.baseCaster = &sCaster;
		static content::MemberInfo sMembers[] =
		{
			{ content::GetReferenceMetaType<BlobShadowBehaviour, pure3d::Texture>("p"),
				PROTO_OFFSET(BlobShadowBehaviour, blobTexture), "blobTexture" },
			{ content::GetMemberPrimitiveMetaType<BlobShadowBehaviour, float, 0>("p"),
				PROTO_OFFSET(BlobShadowBehaviour, radius), "radius" }
		};
		sList.members = sMembers;
		sList.count = 2;
		return &sList;
	}
}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x102EDE90
// FUNCTION: ENGINE 0x102EDEA0
// FUNCTION: ENGINE 0x102EDEC0
// FUNCTION: ENGINE 0x102EDED0
// FUNCTION: ENGINE 0x102EE1C0
// FUNCTION: ENGINE 0x102EE200
// FUNCTION: ENGINE 0x102EE620

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x102CD490
// FUNCTION: ENGINE 0x102CD4B0
