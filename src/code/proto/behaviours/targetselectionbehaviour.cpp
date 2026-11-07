#include "code/proto/behaviours/targetselectionbehaviour.h"
#include "code/core/refptr.h"
#include "code/engine/gameobject/gameobject.h"
#include "code/engine/message.h"
#include "code/proto/fightitems/ai/aicodemessages.h"

namespace choreo
{
	// 0x10D94FF8
	extern const float gMinusOne;
}

namespace engine
{
	namespace driving
	{
		extern const float gOne;
		extern const float gHalf;
		extern const float gTwo;
	}
}

namespace proto
{
	// 0x10DA3664
	extern const float gFifty;

#define PROTO_OFFSET(type, member) \
	content::MemberOffset(&((type*)0)->member, (int)&((type*)0)->member)

	// FUNCTION: ENGINE 0x103FEDF0
	content::ClassInfo* TargetSelectionBehaviour::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "TargetSelectionBehaviour";
		sInfo.code = "pn";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x103FEE30
	content::ClassInfo* TargetSelectionWeights::Pair::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "proto::TargetSelectionWeights::Pair";
		sInfo.code = "pn";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x103FEE70
	content::ClassInfo* TargetSelectionWeights::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "proto::TargetSelectionWeights";
		sInfo.code = "pn";
		return &sInfo;
	}

	// RTTI proto::AddTargetLockMessage and RemoveTargetLockMessage (type 0x3B, ids 7 and 8): an object is told that the selection
	// of another one locks onto it (or no longer does); the message carries the place the lock is kept at
	struct AddTargetLockMessage : public TargetableMessage
	{
		explicit AddTargetLockMessage(engine::GameObject** newLock) : TargetableMessage(7), lock(newLock), flag(false)
		{
		}
		virtual ~AddTargetLockMessage()
		{
		}

		engine::GameObject** lock;  // +0xC
		bool flag;  // +0x10
	};

	struct RemoveTargetLockMessage : public TargetableMessage
	{
		explicit RemoveTargetLockMessage(engine::GameObject** newLock) : TargetableMessage(8), lock(newLock)
		{
		}
		virtual ~RemoveTargetLockMessage()
		{
		}

		engine::GameObject** lock;  // +0xC
	};

	// FUNCTION: ENGINE 0x104009A0
	void TargetSelectionBehaviour::SetCurrent(engine::HandleBase handle)
	{
		engine::GameObject* object;
		if (handle.index == 0xffff || engine::GetGameObjectEntries()[handle.index].serial != handle.serial)
		{
			object = 0;
		}
		else
		{
			object = engine::GetGameObjectEntries()[handle.index].object;
		}
		engine::GameObject** lock = &current;
		engine::GameObject* old = *lock;
		if (old != object)
		{
			if (old != 0)
			{
				RemoveTargetLockMessage remove(lock);
				old->SendMessage(&remove);
			}
			if (object != 0)
			{
				AddTargetLockMessage add(lock);
				object->SendMessage(&add);
			}
		}
	}

	// FUNCTION: ENGINE 0x10401A50
	void TargetSelectionBehaviour::Reset()
	{
		{
			engine::HandleBase handle;
			SetCurrent(handle);
		}
		{
			engine::HandleBase handle;
			unknown24 = choreo::gMinusOne;
			unknown20 = handle;
		}
		{
			engine::HandleBase handle;
			unknown10 = handle;
			unknown14 = false;
			unknown15 = false;
			unknown28 = false;
		}
		{
			engine::HandleBase handle;
			unknown34 = false;
			unknown2C = handle;
		}
	}

	// FUNCTION: ENGINE 0x10401680
	TargetSelectionBehaviour::~TargetSelectionBehaviour()
	{
		SetRegistered(false);
		engine::HandleBase none;
		SetCurrent(none);
		core::SafeRelease(weights);
		candidates.Reset();
	}

	// FUNCTION: ENGINE 0x104025A0
	void TargetSelectionBehaviour::OnActiveChanged(bool active)
	{
		if (!active)
		{
			Reset();
		}
		engine::Behaviour::OnActiveChanged(active);
	}

	// FUNCTION: ENGINE 0x10402150
	// NONMATCHING: the engine loads the first three constants ahead of the byte stores and keeps the order of the float stores of
	// its own (48.6 %)
#ifdef NONMATCHING
	TargetSelectionBehaviour::TargetSelectionBehaviour(engine::GameObject* newOwner) : TargetingBehaviour(newOwner),
		unknown14(false), unknown15(false), unknown16(false), unknown17(false), current(0), unknown1C(0),
		unknown24(choreo::gMinusOne), unknown29(false), unknown2A(true), registered(false), ignorePatsy(false),
		unknown37(0xfe), weights(0), forgetTime(5.0f), tooFar(proto::gFifty), weightDistance(engine::driving::gTwo),
		weightHysteresis(engine::driving::gOne), weightCanSee(engine::driving::gOne), weightTargetingMe(0.4f),
		weightLastDamager(engine::driving::gHalf), weightHaveToken(engine::driving::gHalf),
		weightIsNotAlly(engine::driving::gTwo), acquireOnIdleTime(0.0f), unknownA8(0.0f), unknownAC(5.0f),
		unknownB0(false), unknownB4(choreo::gMinusOne), unknownD0(1), unknownD4(-1), unknownD8(0.0f), unknownDC(0.0f),
		unknownE0(-1), gameIntensityContribution(engine::driving::gOne)
	{
		Reset();
		Listen(0x20, true);
		Listen(2, true);
		Listen(0x2f, true);
		Listen(0x25, true);
		Listen(0x14, true);
		Listen(0x28, true);
		Listen(0x39, true);
	}
#endif

	// FUNCTION: ENGINE 0x104000C0
	content::MemberList* TargetSelectionWeights::Pair::GetMembers()
	{
		static content::MemberList sList;
		static content::MemberInfo sMembers[] =
		{
			{ content::GetEnumMetaType<TargetClass>(), 0, "class" },
			{ content::GetMemberPrimitiveMetaType<Pair, float, 0>("p"), PROTO_OFFSET(Pair, weight), "weight" }
		};
		sList.members = sMembers;
		sList.count = 2;
		return &sList;
	}

	// FUNCTION: ENGINE 0x104015D0
	content::MemberList* TargetSelectionWeights::GetMembers()
	{
		static content::MemberList sList;
		static content::MemberInfo sMembers[] =
		{
			{ content::GetArrayDynamicMetaType<TargetSelectionWeights, PairArray>(content::GetClassMetaType<Pair>(), "p"),
				PROTO_OFFSET(TargetSelectionWeights, weights), "weights" }
		};
		sList.members = sMembers;
		sList.count = 1;
		return &sList;
	}

	// FUNCTION: ENGINE 0x10401250
	content::MemberList* TargetSelectionBehaviour::GetMembers()
	{
		static content::MemberList sList;
		sList.baseType = content::GetClassMetaType<TargetingBehaviour>();
		static content::BaseClassCasterImpl<TargetingBehaviour, TargetSelectionBehaviour> sCaster;
		sList.baseCaster = &sCaster;
		static content::MemberInfo sMembers[] =
		{
			{ content::GetMemberPrimitiveMetaType<TargetSelectionBehaviour, float, 0>("p"),
				PROTO_OFFSET(TargetSelectionBehaviour, forgetTime), "forgetTime" },
			{ content::GetMemberPrimitiveMetaType<TargetSelectionBehaviour, float, 1>("p"),
				PROTO_OFFSET(TargetSelectionBehaviour, tooFar), "tooFar" },
			{ content::GetMemberPrimitiveMetaType<TargetSelectionBehaviour, float, 2>("p"),
				PROTO_OFFSET(TargetSelectionBehaviour, weightDistance), "weightDistance" },
			{ content::GetMemberPrimitiveMetaType<TargetSelectionBehaviour, float, 3>("p"),
				PROTO_OFFSET(TargetSelectionBehaviour, weightHysteresis), "weightHysteresis" },
			{ content::GetMemberPrimitiveMetaType<TargetSelectionBehaviour, float, 4>("p"),
				PROTO_OFFSET(TargetSelectionBehaviour, weightCanSee), "weightCanSee" },
			{ content::GetMemberPrimitiveMetaType<TargetSelectionBehaviour, float, 5>("p"),
				PROTO_OFFSET(TargetSelectionBehaviour, weightTargetingMe), "weightTargetingMe" },
			{ content::GetMemberPrimitiveMetaType<TargetSelectionBehaviour, float, 6>("p"),
				PROTO_OFFSET(TargetSelectionBehaviour, weightLastDamager), "weightLastDamager" },
			{ content::GetMemberPrimitiveMetaType<TargetSelectionBehaviour, float, 7>("p"),
				PROTO_OFFSET(TargetSelectionBehaviour, weightHaveToken), "weightHaveToken" },
			{ content::GetMemberPrimitiveMetaType<TargetSelectionBehaviour, float, 8>("p"),
				PROTO_OFFSET(TargetSelectionBehaviour, weightIsNotAlly), "weightIsNotAlly" },
			{ content::GetMemberPrimitiveMetaType<TargetSelectionBehaviour, float, 9>("p"),
				PROTO_OFFSET(TargetSelectionBehaviour, acquireOnIdleTime), "acquireOnIdleTime" },
			{ content::GetReferenceMetaType<TargetSelectionBehaviour, TargetSelectionWeights>("p"),
				PROTO_OFFSET(TargetSelectionBehaviour, weights), "weights" },
			{ content::GetMemberPrimitiveMetaType<TargetSelectionBehaviour, bool, 0>("p"),
				PROTO_OFFSET(TargetSelectionBehaviour, ignorePatsy), "ignorePatsy" },
			{ content::GetMemberPrimitiveMetaType<TargetSelectionBehaviour, float, 10>("p"),
				PROTO_OFFSET(TargetSelectionBehaviour, gameIntensityContribution), "gameIntensityContribution" }
		};
		sList.members = sMembers;
		sList.count = 13;
		return &sList;
	}
}

// The array of the weights and the list of the candidates: the engine keeps its out-of-line copies of their members
template class container::ArrayDynamic<proto::TargetSelectionWeights::Pair, container::AllocatorNew>;
template class container::ArrayFixed<proto::TargetSelectionBehaviour::Candidate, 8>;

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x103FF2F0
// FUNCTION: ENGINE 0x103FF3C0
// FUNCTION: ENGINE 0x103FF3D0
// FUNCTION: ENGINE 0x103FF3E0
// FUNCTION: ENGINE 0x103FF440
// FUNCTION: ENGINE 0x103FF450
// FUNCTION: ENGINE 0x103FF490
// FUNCTION: ENGINE 0x103FF540
// FUNCTION: ENGINE 0x103FF550
// FUNCTION: ENGINE 0x103FFA20
// FUNCTION: ENGINE 0x103FFAB0
// FUNCTION: ENGINE 0x103FFAF0
// FUNCTION: ENGINE 0x103FFB30
// FUNCTION: ENGINE 0x103FFB70
// FUNCTION: ENGINE 0x103FFBB0
// FUNCTION: ENGINE 0x103FFBF0
// FUNCTION: ENGINE 0x103FFC30
// FUNCTION: ENGINE 0x103FFC70
// FUNCTION: ENGINE 0x103FFCB0
// FUNCTION: ENGINE 0x103FFCF0
// FUNCTION: ENGINE 0x103FFD30
// FUNCTION: ENGINE 0x103FFD70
// FUNCTION: ENGINE 0x103FFDB0
// FUNCTION: ENGINE 0x103FFE30
// FUNCTION: ENGINE 0x103FFE40
// FUNCTION: ENGINE 0x103FFE50
// FUNCTION: ENGINE 0x103FFF20
// FUNCTION: ENGINE 0x103FFF40
// FUNCTION: ENGINE 0x103FFF60
// FUNCTION: ENGINE 0x103FFF80
// FUNCTION: ENGINE 0x103FFFA0
// FUNCTION: ENGINE 0x10400ED0
// FUNCTION: ENGINE 0x10400EE0
// FUNCTION: ENGINE 0x10401020
// FUNCTION: ENGINE 0x10401080
// FUNCTION: ENGINE 0x104020E0
// FUNCTION: ENGINE 0x10402380

// Kept copies (inline members, template instances and compiler-generated functions of this unit):

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x103FED50
// FUNCTION: ENGINE 0x103FF2C0
// FUNCTION: ENGINE 0x103FF2D0
// FUNCTION: ENGINE 0x103FF2E0
// FUNCTION: ENGINE 0x103FF300
// FUNCTION: ENGINE 0x103FF310
// FUNCTION: ENGINE 0x103FF330
// FUNCTION: ENGINE 0x103FF340
// FUNCTION: ENGINE 0x103FF350
// FUNCTION: ENGINE 0x103FF370
// FUNCTION: ENGINE 0x103FF390
// FUNCTION: ENGINE 0x103FF460
// FUNCTION: ENGINE 0x103FFDF0
// FUNCTION: ENGINE 0x103FFE60
// FUNCTION: ENGINE 0x103FFE70
// FUNCTION: ENGINE 0x103FFE90
// FUNCTION: ENGINE 0x103FFEB0
