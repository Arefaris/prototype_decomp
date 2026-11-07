#include "code/proto/behaviours/addtoheightmapbehaviour.h"

namespace proto
{
#define PROTO_OFFSET(type, member) \
	content::MemberOffset(&((type*)0)->member, (int)&((type*)0)->member)

	// The heightmap functions of the AI system's unit (0x103C5730: adds the box; 0x103BA050: takes the behaviour's
	// box out)
	void Unknown103C5730(math::Vector* position, const math::Vector* center, float width, float length, float height,
		math::Matrix* transform, AddToHeightmapBehaviour* behaviour);
	void Unknown103BA050(math::Vector* position, AddToHeightmapBehaviour* behaviour);

	// FUNCTION: ENGINE 0x103C5D80
	content::ClassInfo* AddToHeightmapBehaviour::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "proto::AddToHeightmapBehaviour";
		sInfo.code = "pn";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x103C5DC0
	AddToHeightmapBehaviour::AddToHeightmapBehaviour(engine::GameObject* newOwner) : engine::Behaviour(newOwner)
	{
		registered = false;
		Listen(0x2b, true);
	}

	// FUNCTION: ENGINE 0x103C5E00
	void AddToHeightmapBehaviour::Slot1()
	{
		if (updateRequired)
		{
			Listen2(4, true);
		}
	}

	// FUNCTION: ENGINE 0x103C5EC0
	// NONMATCHING: scheduling, the engine loads localCenter.x after the translation's y (85.0 %)
#ifdef NONMATCHING
	void AddToHeightmapBehaviour::Remove()
	{
		if (updateRequired)
		{
			registered = false;
			math::Vector t;
			owner->transform->GetPointer()->GetTranslation(t);
			math::Vector position(localCenter.x + t.x, localCenter.y + t.y, localCenter.z + t.z);
			Unknown103BA050(&position, this);
		}
	}
#endif

	// FUNCTION: ENGINE 0x103C5F90
	void AddToHeightmapBehaviour::Update(float dt, unsigned short mask)
	{
		if (!registered && updateRequired)
		{
			math::Matrix* matrix = &owner->transform->Get();
			math::Matrix* current = owner->transform->GetPointer();
			math::Vector position(current->m[3][0], current->m[3][1], current->m[3][2]);
			Unknown103C5730(&position, &localCenter, width, length, height, matrix, this);
			registered = true;
			Listen2(4, false);
		}
	}

	// FUNCTION: ENGINE 0x103C62E0
	AddToHeightmapBehaviour::~AddToHeightmapBehaviour()
	{
		Remove();
	}

	// FUNCTION: ENGINE 0x103C6300
	void AddToHeightmapBehaviour::OnMessage(engine::Message* message)
	{
		if (message->type == 0x2b && message->id == 0x10)
		{
			Remove();
			registered = false;
			Listen2(4, true);
		}
	}

	// FUNCTION: ENGINE 0x103C6140
	content::MemberList* AddToHeightmapBehaviour::GetMembers()
	{
		static content::MemberList sList;
		sList.baseType = content::GetClassMetaType<engine::Behaviour>();
		static content::BaseClassCasterImpl<engine::Behaviour, AddToHeightmapBehaviour> sCaster;
		sList.baseCaster = &sCaster;
		static content::MemberInfo sMembers[] =
		{
			{ content::GetMemberVectorMetaType<AddToHeightmapBehaviour, 0>("p"), 0xC, "localCenter" },
			{ content::GetMemberPrimitiveMetaType<AddToHeightmapBehaviour, float, 0>("p"),
				PROTO_OFFSET(AddToHeightmapBehaviour, width), "width" },
			{ content::GetMemberPrimitiveMetaType<AddToHeightmapBehaviour, float, 1>("p"),
				PROTO_OFFSET(AddToHeightmapBehaviour, length), "length" },
			{ content::GetMemberPrimitiveMetaType<AddToHeightmapBehaviour, float, 2>("p"),
				PROTO_OFFSET(AddToHeightmapBehaviour, height), "height" },
			{ content::GetMemberPrimitiveMetaType<AddToHeightmapBehaviour, bool, 0>("p"),
				PROTO_OFFSET(AddToHeightmapBehaviour, updateRequired), "updateRequired" }
		};
		sList.members = sMembers;
		sList.count = 5;
		return &sList;
	}
}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x103C5E40
// FUNCTION: ENGINE 0x103C5E80
// FUNCTION: ENGINE 0x103C5E90
// FUNCTION: ENGINE 0x103C6040
// FUNCTION: ENGINE 0x103C6080
// FUNCTION: ENGINE 0x103C60C0
// FUNCTION: ENGINE 0x103C6100
// FUNCTION: ENGINE 0x103C64F0
