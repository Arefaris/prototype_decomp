#include "code/proto/behaviours/spawnerbehaviour.h"
#include "code/content/vectormetatype.h"
#include "code/engine/fight/fightbranchref.h"
#include "code/engine/gameobject/gameobject.h"
#include "code/math/matrix.h"

namespace engine
{
	extern content::ObjectName gTransformName;
	namespace driving
	{
		extern const float gOne;
	}
}

namespace proto
{
#define PROTO_OFFSET(type, member) \
	content::MemberOffset(&((type*)0)->member, (int)&((type*)0)->member)

	// FUNCTION: ENGINE 0x10559CC0
	content::ClassInfo* SpawnerBehaviour::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "proto::SpawnerBehaviour";
		sInfo.code = "pn";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x1055AF80
	SpawnerBehaviour::SpawnerBehaviour(engine::GameObject* newOwner) : engine::Behaviour(newOwner), spawnRadius(engine::driving::gOne),
		spawnOffset(0.0f, 0.0f, 0.0f), branch(0), unknown34(0), totalSpawned(0), unknownE0(0)
	{
		owner->SetAttributeAndGet<math::Matrix>(engine::gTransformName, math::Matrix::IDENTITY, false);
		Listen(2, true);
		Listen(0x29, true);
		Listen(0x39, true);
		Listen2(4, true);
	}

	// FUNCTION: ENGINE 0x1055B060
	SpawnerBehaviour::~SpawnerBehaviour()
	{
	}

	// FUNCTION: ENGINE 0x10559D00
	void SpawnerBehaviour::Slot1()
	{
	}

	// FUNCTION: ENGINE 0x10559D10
	void SpawnerBehaviour::Update(float dt, unsigned short mask)
	{
	}

	// FUNCTION: ENGINE 0x1055A820
	void SpawnerBehaviour::Slot11()
	{
	}

	// FUNCTION: ENGINE 0x10559ED0
	void SpawnerBehaviour::SetBranch(fight::Branch* newBranch)
	{
		if (newBranch != branch.branch)
		{
			if (branch.branch != 0)
			{
				branch.branch->Unregister(&branch);
			}
			branch.branch = newBranch;
			if (newBranch != 0)
			{
				newBranch->Register(&branch);
			}
		}
	}

	// FUNCTION: ENGINE 0x10559F10
	fight::Branch* SpawnerBehaviour::GetBranch() const
	{
		return branch.branch;
	}

	// FUNCTION: ENGINE 0x1055A8B0
	content::MemberList* SpawnerBehaviour::GetMembers()
	{
		static content::MemberList sList;
		sList.baseType = content::GetClassMetaType<engine::Behaviour>();
		static content::BaseClassCasterImpl<engine::Behaviour, SpawnerBehaviour> sCaster;
		sList.baseCaster = &sCaster;
		static content::MemberInfo sMembers[] =
		{
			{ content::GetMemberNameMetaType<SpawnerBehaviour, 0>(true, true, "p"),
				PROTO_OFFSET(SpawnerBehaviour, templateName), "templateName" },
			{ content::GetMemberPrimitiveMetaType<SpawnerBehaviour, float, 0>("p"),
				PROTO_OFFSET(SpawnerBehaviour, spawnRadius), "spawnRadius" },
			{ content::GetMemberPrimitiveMetaType<SpawnerBehaviour, unsigned int, 0>("pn"),
				PROTO_OFFSET(SpawnerBehaviour, totalSpawned), "totalSpawned" },
			{ content::GetMemberVectorMetaType<SpawnerBehaviour, 0>("p"), 0x1c, "spawnOffset" },
			{ engine::GetFightBranchRefMetaType<SpawnerBehaviour>("GameObject", &SpawnerBehaviour::GetBranch,
				&SpawnerBehaviour::SetBranch, "p"), 0, "branch" }
		};
		sList.members = sMembers;
		sList.count = 5;
		return &sList;
	}
}

template class container::ArrayFixed<proto::SpawnedEntry, 50>;
template class container::ArrayFixed<proto::WeightedTemplate, 10>;

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x10559D20
// FUNCTION: ENGINE 0x10559D50
// FUNCTION: ENGINE 0x10559D70
// FUNCTION: ENGINE 0x10559DB0
// FUNCTION: ENGINE 0x10559DF0
// FUNCTION: ENGINE 0x10559E10
// FUNCTION: ENGINE 0x10559E90
// FUNCTION: ENGINE 0x10559EA0
// FUNCTION: ENGINE 0x1055A180
// FUNCTION: ENGINE 0x1055A1D0
// FUNCTION: ENGINE 0x1055A220
// FUNCTION: ENGINE 0x1055A260
// FUNCTION: ENGINE 0x1055A3D0
// FUNCTION: ENGINE 0x1055A3F0
// FUNCTION: ENGINE 0x1055A410
// FUNCTION: ENGINE 0x1055A830
// FUNCTION: ENGINE 0x1055A840
// FUNCTION: ENGINE 0x1055AEC0
// FUNCTION: ENGINE 0x1055B0E0
