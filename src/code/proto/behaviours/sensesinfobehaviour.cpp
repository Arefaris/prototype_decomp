#include "code/proto/behaviours/sensesinfobehaviour.h"
#include "code/engine/gameobject/gameobject.h"
#include "code/proto/render/setdrawablevisionflags.h"
#include <math.h>

namespace content
{
	static const EnumValue sSensesTypeValues[] =
	{
		{ "None", 0 },
		{ "Prototype", 1 },
		{ "Infected0", 2 },
		{ "Infected1", 3 },
		{ "Infected2", 4 },
		{ "Brawler", 5 },
		{ "Stealth", 6 },
		{ "Leader", 7 },
		{ "Hydra", 8 },
		{ "Soldier", 9 },
		{ "Tank", 10 },
		{ "Helicopter", 11 },
		{ "UAV", 12 },
		{ "GenericMilitary", 13 },
		{ "HiveProp", 14 },
		{ "InfectedBoss", 15 },
		{ "Pedestrian", 16 }
	};

	// FUNCTION: ENGINE 0x10075A80
	template<> void EnumInfo<proto::SensesType>::Get(const char** name, const EnumValue** values, int* count,
		const char** code)
	{
		*name = "proto::SensesType";
		*code = "p";
		*values = sSensesTypeValues;
		*count = 0x11;
	}
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
	// 0x10D969FC / 0x10D96A04: 0.00001f and 0.1f in the pooled constants
	static const float kSensesEpsilon = 0.00001f;
	static const float kSensesFadeSpeed = 0.1f;

	float gSensesScale = 1.0f;
	float gSensesNearValues[17] =
	{
		0.0f, 0.75f, 0.6f, 0.7f, 0.75f, 0.75f, 0.9f, 1.0f, 0.9f, 0.45f, 0.5f, 0.6f, 0.55f, 0.45f, 0.8f, 1.0f, 0.25f
	};
	float gSensesFarValues[17] =
	{
		0.0f, 0.75f, 0.6f, 0.5f, 0.75f, 0.75f, 0.9f, 1.0f, 0.9f, 0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 0.8f, 1.0f, 0.0f
	};

	// FUNCTION: ENGINE 0x10075B90
	void SensesInfoBehaviour::SetGlobalScale(float newScale)
	{
		gSensesScale = newScale;
	}

	// FUNCTION: ENGINE 0x10075B00
	// EQUIVALENT: the vftable store and the load of the constant are scheduled differently (78.9 %)
	SensesInfoBehaviour::SensesInfoBehaviour(engine::GameObject* newOwner) : engine::Behaviour(newOwner), nearValue(0.0f),
		farValue(0.0f), scale(engine::driving::gOne), sensesType(SENSES_NONE), active(false), fading(false)
	{
		Listen(7, true);
		Listen(0x3d, true);
		Listen2(8, true);
	}

	SensesInfoBehaviour::~SensesInfoBehaviour()
	{
	}

	// FUNCTION: ENGINE 0x10075AC0
	content::ClassInfo* SensesInfoBehaviour::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "proto::SensesInfoBehaviour";
		sInfo.code = "pn";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x10075D10
	void SensesInfoBehaviour::ApplyVision(engine::render::Drawable drawable)
	{
		if (active && owner->behaviours.requested.Test(7))
		{
			SetDrawableVisionFlags* modifier = new SetDrawableVisionFlags(nearValue, scale * farValue, 0);
			drawable.ApplyModifier(modifier);
		}
	}

	// FUNCTION: ENGINE 0x10075E60
	void SensesInfoBehaviour::Refresh()
	{
		if (active)
		{
			engine::GetCurrentDrawable message;
			owner->SendMessage(&message);
			engine::render::Drawable drawable = message.drawable;
			if (drawable.IsValid())
			{
				ApplyVision(drawable);
			}
		}
	}

	// FUNCTION: ENGINE 0x10075EF0
	void SensesInfoBehaviour::SetNear(float value)
	{
		nearValue = value;
		Refresh();
	}

	// FUNCTION: ENGINE 0x10075F10
	void SensesInfoBehaviour::SetFar(float value)
	{
		farValue = value;
		Refresh();
	}

	// FUNCTION: ENGINE 0x10075F30
	void SensesInfoBehaviour::OnActiveChanged(bool newActive)
	{
		engine::Behaviour::OnActiveChanged(newActive);
		if (newActive)
		{
			Refresh();
		}
		Listen2(8, newActive);
	}

	// FUNCTION: ENGINE 0x10075F70
	void SensesInfoBehaviour::Slot1()
	{
		active = true;
		nearValue = gSensesNearValues[sensesType];
		farValue = gSensesFarValues[sensesType];
		scale = gSensesScale;
		Refresh();
	}

	// FUNCTION: ENGINE 0x10075FB0
	void SensesInfoBehaviour::Update(float dt, unsigned short mask)
	{
		if (scale != gSensesScale)
		{
			scale = gSensesScale;
			Refresh();
		}
		if (fading)
		{
			float step = dt * kSensesFadeSpeed;
			float value = nearValue - step;
			if (!(value >= 0.0f))
			{
				value = 0.0f;
			}
			float one = engine::driving::gOne;
			if (value - one >= 0.0f)
			{
				value = one;
			}
			nearValue = value;
			float other = farValue - step;
			if (!(other >= 0.0f))
			{
				other = 0.0f;
			}
			if (other - one >= 0.0f)
			{
				other = one;
			}
			farValue = other;
			Refresh();
			if ((float)fabs((double)nearValue) <= kSensesEpsilon && (float)fabs((double)farValue) <= kSensesEpsilon)
			{
				fading = false;
			}
		}
	}

	// FUNCTION: ENGINE 0x100760B0
	// NONMATCHING: shrink-wrap (the engine saves edi in the entry block), and the engine builds the by-value drawable of the id 3 case in the argument area (20 %)
#ifdef NONMATCHING
	void SensesInfoBehaviour::OnMessage(engine::Message* message)
	{
		switch (message->type)
		{
		case 7:
			switch ((unsigned short)message->id)
			{
			case 3:
			{
				engine::render::Drawable drawable;
				drawable = static_cast<engine::SetCurrentDrawable*>(message)->drawable;
				ApplyVision(drawable);
				break;
			}
			case 9:
				Refresh();
				break;
			}
			break;
		case 0x3d:
			switch ((unsigned short)message->id)
			{
			case 0xe:
			{
				ConfigureSensesInfoMessage* configure = static_cast<ConfigureSensesInfoMessage*>(message);
				if (configure->nearValue >= 0.0f)
				{
					nearValue = configure->nearValue;
				}
				if (configure->farValue >= 0.0f)
				{
					farValue = configure->farValue;
				}
				if (configure->fade)
				{
					fading = true;
				}
				if (configure->drawable.IsValid())
				{
					ApplyVision(configure->drawable);
				}
				else
				{
					Refresh();
				}
				break;
			}
			case 0xf:
			{
				GetSensesInfoMessage* get = static_cast<GetSensesInfoMessage*>(message);
				get->nearValue = nearValue;
				float value = farValue;
				get->farValue = value;
				if (get->scaled)
				{
					get->farValue = scale * value;
				}
				break;
			}
			case 0x10:
				nearValue = gSensesNearValues[sensesType];
				farValue = gSensesFarValues[sensesType];
				break;
			}
			break;
		}
	}
#endif

	// FUNCTION: ENGINE 0x10075DA0
	content::MemberList* SensesInfoBehaviour::GetMembers()
	{
		static content::MemberList sList;
		sList.baseType = content::GetClassMetaType<engine::Behaviour>();
		static content::BaseClassCasterImpl<engine::Behaviour, SensesInfoBehaviour> sCaster;
		sList.baseCaster = &sCaster;
		static content::MemberInfo sMembers[] =
		{
			{ content::GetEnumMetaType<SensesType>(), 0x18, "sensesType" }
		};
		sList.members = sMembers;
		sList.count = 1;
		return &sList;
	}
}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x10075BD0
// FUNCTION: ENGINE 0x10075CA0
// FUNCTION: ENGINE 0x10075CB0

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x10075B80
// FUNCTION: ENGINE 0x10075CE0

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x10075C50
