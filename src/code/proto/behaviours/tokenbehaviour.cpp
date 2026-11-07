#include "code/proto/behaviours/tokenbehaviour.h"
#include "code/core/refptr.h"
#include "code/engine/gameobject/gameobject.h"
#include "code/engine/message.h"
#include "code/math/matrix.h"
#include "code/math/vector.h"
#include "code/proto/messages/airequestmessages.h"
#include "code/proto/messages/targetselectionmessages.h"

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
	}
}

namespace proto
{
	// The messages of type 0x2E whose classes are not declared elsewhere (RTTI proto::GetOwnersTokenMsg, RequestTokenMsg,
	// ReleaseTokenMsg, SetHunterTokenBoostTokenMsg, GetTokenScoreMsg; the members are guesses)
	struct GetOwnersTokenMsg : public TokenMessage
	{
		TokenBehaviour::TokenGroup* group;  // +0xC
		bool unknown10;
		int kind;  // +0x14
	};

	struct RequestTokenMsg : public TokenMessage
	{
		bool granted;  // +0xC
		int kind;  // +0x10
		unsigned int handle;  // +0x14
	};

	struct ReleaseTokenMsg : public TokenMessage
	{
		int kind;  // +0xC
		unsigned int handle;  // +0x10
	};

	struct SetHunterTokenBoostTokenMsg : public TokenMessage
	{
		int count;  // +0xC
		float time;  // +0x10
	};

	struct SetTokenWeightsBody : public TokenMessage
	{
		TokenWeights* weights;  // +0xC
	};

	// The messages whose first member is a single word
	struct TokenFloatMsg : public TokenMessage
	{
		float value;  // +0xC
	};

#define PROTO_OFFSET(type, member) \
	content::MemberOffset(&((type*)0)->member, (int)&((type*)0)->member)

	// FUNCTION: ENGINE 0x10403760
	content::ClassInfo* TokenBehaviour::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "proto::TokenBehaviour";
		sInfo.code = "pn";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x104037A0
	content::ClassInfo* TokenWeights::Weight::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "proto::TokenWeights::Weight";
		sInfo.code = "pn";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x104037E0
	content::ClassInfo* TokenWeights::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "proto::TokenWeights";
		sInfo.code = "pn";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x10403820
	void TokenBehaviour::Slot1()
	{
		Listen2(4, true);
		Remove(0xf);
	}

	// FUNCTION: ENGINE 0x10403AA0
	// NONMATCHING: the engine copies the weights pointer into a second register for the array reads (73.7 %)
#ifdef NONMATCHING
	float TokenBehaviour::GetClassnameWeight(const core::Name<core::CaseSensitiveKey>& name) const
	{
		TokenWeights* weights = tokenWeights;
		float result = 0.0f;
		if (weights != 0)
		{
			TokenWeights::Weight* item = weights->weights.Begin();
			result = weights->defaultWeight;
			TokenWeights::Weight* last = weights->weights.End();
			if (item != last)
			{
				do
				{
					if (item->classname == name)
					{
						result = item->weight;
						break;
					}
					item++;
				}
				while (item != last);
			}
		}
		return result;
	}
#endif

	// FUNCTION: ENGINE 0x10404000
	content::MemberList* TokenWeights::Weight::GetMembers()
	{
		static content::MemberList sList;
		static content::MemberInfo sMembers[] =
		{
			{ content::GetNameMetaType<Weight>(true, true, "p"), PROTO_OFFSET(Weight, classname), "classname" },
			{ content::GetMemberPrimitiveMetaType<Weight, float, 0>("p"), PROTO_OFFSET(Weight, weight), "weight" }
		};
		sList.members = sMembers;
		sList.count = 2;
		return &sList;
	}

	// FUNCTION: ENGINE 0x104040D0
	void TokenBehaviour::ClearTokens()
	{
		groups[0].holders.end = groups[0].holders.begin;
		groups[1].holders.end = groups[1].holders.begin;
		unknown48 = 0;
		unknown4C = 0.0f;
	}

	// FUNCTION: ENGINE 0x10404220
	bool TokenBehaviour::AcquireToken(int kind, unsigned int handle)
	{
		TokenGroup::Holder* item = groups[kind].holders.begin;
		TokenGroup::Holder* last = groups[kind].holders.end;
		for (; item != last; item++)
		{
			if (item->handle == handle)
			{
				return true;
			}
		}
		if (last != groups[kind].holders.capacity)
		{
			TokenGroup::Holder entry;
			entry.handle = handle;
			entry.score = choreo::gMinusOne;
			groups[kind].holders.PushBack(entry);
			return true;
		}
		return false;
	}

	// FUNCTION: ENGINE 0x104042B0
	bool TokenBehaviour::ReleaseToken(int kind, unsigned int handle)
	{
		TokenGroup& group = groups[kind];
		TokenGroup::Holder* item = group.holders.begin;
		while (true)
		{
			if (item == groups[kind].holders.end)
			{
				return false;
			}
			if (item->handle == handle)
			{
				break;
			}
			item++;
		}
		group.holders.end--;
		TokenGroup::Holder* last = group.holders.end;
		if (item < last)
		{
			*item = *last;
		}
		return true;
	}

	// FUNCTION: ENGINE 0x10404550
	content::MemberList* TokenBehaviour::GetMembers()
	{
		static content::MemberList sList;
		sList.baseType = content::GetClassMetaType<engine::Behaviour>();
		static content::BaseClassCasterImpl<engine::Behaviour, TokenBehaviour> sCaster;
		sList.baseCaster = &sCaster;
		static content::MemberInfo sMembers[] =
		{
			{ content::GetReferenceMetaType<TokenBehaviour, TokenWeights>("p"), PROTO_OFFSET(TokenBehaviour, tokenWeights),
				"tokenWeights" },
			{ content::GetMemberPrimitiveMetaType<TokenBehaviour, float, 0>("p"), PROTO_OFFSET(TokenBehaviour, tooFar),
				"tooFar" },
			{ content::GetMemberPrimitiveMetaType<TokenBehaviour, float, 1>("p"),
				PROTO_OFFSET(TokenBehaviour, distanceWeight), "distanceWeight" },
			{ content::GetMemberPrimitiveMetaType<TokenBehaviour, float, 2>("p"),
				PROTO_OFFSET(TokenBehaviour, classnameWeight), "classnameWeight" },
			{ content::GetMemberPrimitiveMetaType<TokenBehaviour, float, 3>("p"),
				PROTO_OFFSET(TokenBehaviour, consumeProbability), "consumeProbability" }
		};
		sList.members = sMembers;
		sList.count = 5;
		return &sList;
	}

	// FUNCTION: ENGINE 0x104046F0
	content::MemberList* TokenWeights::GetMembers()
	{
		static content::MemberList sList;
		static content::MemberInfo sMembers[] =
		{
			{ content::GetArrayDynamicMetaType<TokenWeights, WeightArray>(content::GetClassMetaType<Weight>(), "p"),
				PROTO_OFFSET(TokenWeights, weights), "weights" },
			{ content::GetMemberPrimitiveMetaType<TokenWeights, float, 0>("p"),
				PROTO_OFFSET(TokenWeights, defaultWeight), "defaultWeight" }
		};
		sList.members = sMembers;
		sList.count = 2;
		return &sList;
	}

	// FUNCTION: ENGINE 0x104047D0
	TokenBehaviour::TokenBehaviour(engine::GameObject* newOwner) : engine::Behaviour(newOwner)
	{
		unknown34 = 0.0f;
		tooFar = 40.0f;
		distanceWeight = 1.5f;
		float one = engine::driving::gOne;
		classnameWeight = one;
		tokenWeights = 0;
		consumeProbability = one;
		unknown54 = false;
		unknown55 = false;
		ClearTokens();
		Listen(2, true);
		Listen(0x2e, true);
		for (int i = 0; i < 2; i++)
		{
			groups[i].holders.Create(10);
			maxTokens[i] = 2;
		}
	}

	// FUNCTION: ENGINE 0x104048D0
	TokenBehaviour::~TokenBehaviour()
	{
		core::SafeRelease(tokenWeights);
	}

	// FUNCTION: ENGINE 0x10404930
	void TokenBehaviour::OnMessage(engine::Message* message)
	{
		switch (message->type)
		{
		case 2:
			ClearTokens();
			break;
		case 0x2e:
			{
			switch ((unsigned short)message->id)
			{
			case 0:
				{
					GetOwnersTokenMsg* query = (GetOwnersTokenMsg*)message;
					if (query->kind < 2)
					{
						query->group = &groups[query->kind];
						query->unknown10 = false;
					}
				}
				break;
			case 1:
				((TokenFloatMsg*)message)->value = unknown34;
				break;
			case 2:
				unknown34 = ((TokenFloatMsg*)message)->value;
				break;
			case 3:
				{
					SetMaxTokensMsg* set = (SetMaxTokensMsg*)message;
					if (set->unknown10 < 2)
					{
						maxTokens[set->unknown10] = set->unknownC;
					}
				}
				break;
			case 4:
				{
					GetMaxTokensMsg* get = (GetMaxTokensMsg*)message;
					if (get->unknown10 < 2)
					{
						get->unknownC = maxTokens[get->unknown10];
					}
				}
				break;
			case 5:
				{
					RequestTokenMsg* request = (RequestTokenMsg*)message;
					if (request->kind < 2)
					{
						request->granted = AcquireToken(request->kind, request->handle);
					}
				}
				break;
			case 6:
				{
					ReleaseTokenMsg* release = (ReleaseTokenMsg*)message;
					if (release->kind < 2)
					{
						ReleaseToken(release->kind, release->handle);
					}
				}
				break;
			case 7:
				{
					SetHunterTokenBoostTokenMsg* boost = (SetHunterTokenBoostTokenMsg*)message;
					unknown48 = boost->count;
					unknown4C = boost->time;
				}
				break;
			case 8:
				core::RefAssign(tokenWeights, ((SetTokenWeightsBody*)message)->weights);
				break;
			case 9:
				{
					GetTokenScoreMsg* query = (GetTokenScoreMsg*)message;
					const math::Matrix& matrix = owner->transform->value;
					math::Vector position;
					position.x = matrix.m[3][0];
					position.y = matrix.m[3][1];
					position.z = matrix.m[3][2];
					float score = ScoreTarget(&position, query->handle.Get());
					query->score = score;
					query->normalized = score / (classnameWeight + distanceWeight);
				}
				break;
			}
			}
			break;
		}
	}

	// FUNCTION: ENGINE 0x104051B0
	void TokenBehaviour::Update(float dt, unsigned short mask)
	{
		if (dt != 0.0f)
		{
			if (0.0f < unknown34)
			{
				float value = unknown34 - dt;
				if (!(value > 0.0f))
				{
					value = 0.0f;
				}
				unknown34 = value;
			}
			if (0.0f < unknown4C)
			{
				float value = unknown4C - dt;
				float result = 0.0f;
				if (0.0f < value)
				{
					result = value;
				}
				unknown4C = result;
			}
			DistributeTokens();
		}
	}
}

// The arrays of the token holders and of the weights: the engine keeps its out-of-line copies of their members
template class container::ArrayDynamic<proto::TokenBehaviour::TokenGroup::Holder, container::AllocatorNew>;
template class container::ArrayDynamic<proto::TokenWeights::Weight, container::AllocatorNew>;

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x104038E0
// FUNCTION: ENGINE 0x10403960
// FUNCTION: ENGINE 0x10403970
// FUNCTION: ENGINE 0x104039B0
// FUNCTION: ENGINE 0x104039C0
// FUNCTION: ENGINE 0x104039E0
// FUNCTION: ENGINE 0x10403A50
// FUNCTION: ENGINE 0x10403A60
// FUNCTION: ENGINE 0x10403A70
// FUNCTION: ENGINE 0x10403B20
// FUNCTION: ENGINE 0x10403B90
// FUNCTION: ENGINE 0x10403C10
// FUNCTION: ENGINE 0x10403C50
// FUNCTION: ENGINE 0x10403C90
// FUNCTION: ENGINE 0x10403CD0
// FUNCTION: ENGINE 0x10403D10
// FUNCTION: ENGINE 0x10403D50
// FUNCTION: ENGINE 0x10403D90
// FUNCTION: ENGINE 0x10403DA0
// FUNCTION: ENGINE 0x10403E00
// FUNCTION: ENGINE 0x10403E10
// FUNCTION: ENGINE 0x10403E50
// FUNCTION: ENGINE 0x10403E80
// FUNCTION: ENGINE 0x10403EB0
// FUNCTION: ENGINE 0x10403ED0
// FUNCTION: ENGINE 0x10403EF0
// FUNCTION: ENGINE 0x10403F10
// FUNCTION: ENGINE 0x10403F30
// FUNCTION: ENGINE 0x10403F60
// FUNCTION: ENGINE 0x10404310
// FUNCTION: ENGINE 0x10404330
// FUNCTION: ENGINE 0x10404390
// FUNCTION: ENGINE 0x104043F0
// FUNCTION: ENGINE 0x10404450
// FUNCTION: ENGINE 0x10404500
// FUNCTION: ENGINE 0x10405000
// FUNCTION: ENGINE 0x10405030
// FUNCTION: ENGINE 0x10405180
// FUNCTION: ENGINE 0x10405220
// FUNCTION: ENGINE 0x104052C0
// FUNCTION: ENGINE 0x10405380
// FUNCTION: ENGINE 0x1040A6E0
// FUNCTION: ENGINE 0x1040B290
// FUNCTION: ENGINE 0x1040B320
// FUNCTION: ENGINE 0x1040B3B0
// FUNCTION: ENGINE 0x10411840
// FUNCTION: ENGINE 0x104154E0

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x10403E40
// FUNCTION: ENGINE 0x10405270

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x10400040
// FUNCTION: ENGINE 0x10401130
// FUNCTION: ENGINE 0x10403840
// FUNCTION: ENGINE 0x10403850
// FUNCTION: ENGINE 0x10403B30
// FUNCTION: ENGINE 0x10403E20
// FUNCTION: ENGINE 0x10403E30
// FUNCTION: ENGINE 0x10403FB0
// FUNCTION: ENGINE 0x104044C0
// FUNCTION: ENGINE 0x10405130
// FUNCTION: ENGINE 0x104091A0
// FUNCTION: ENGINE 0x10409360
// FUNCTION: ENGINE 0x1040ACE0
// FUNCTION: ENGINE 0x1040AD10
// FUNCTION: ENGINE 0x1040BDE0
// FUNCTION: ENGINE 0x10410960
// FUNCTION: ENGINE 0x10410BA0
// FUNCTION: ENGINE 0x10415050
// FUNCTION: ENGINE 0x1041CAD0
