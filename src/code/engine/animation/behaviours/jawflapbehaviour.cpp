#include "code/engine/animation/behaviours/jawflapbehaviour.h"
#include "code/content/vectormetatype.h"
#include "code/engine/attributemessage.h"
#include "code/engine/fight/expressionactions.h"

namespace engine
{
	// The name of the puppet attribute of a game object (0x112834F0)
	extern content::ObjectName gPuppetAttributeName;

	namespace animation
	{
		// FUNCTION: ENGINE 0x10919F50
		content::ClassInfo* JawFlapBehaviour::GetClassInfo()
		{
			static content::ClassInfo sInfo;
			sInfo.version = 1;
			sInfo.name = "engine::animation::JawFlapBehaviour";
			sInfo.code = "p";
			return &sInfo;
		}

		// FUNCTION: ENGINE 0x10919F90
		void JawFlapBehaviour::OnPostedMessage(Message* message)
		{
		}

		// FUNCTION: ENGINE 0x10919FA0
		float JawFlapBehaviour::GetThresholdMin() const
		{
			return thresholdMin;
		}

		// FUNCTION: ENGINE 0x10919FB0
		void JawFlapBehaviour::SetThresholdMin(float value)
		{
			thresholdMin = value;
		}

		// FUNCTION: ENGINE 0x10919FC0
		float JawFlapBehaviour::GetThresholdMax() const
		{
			return thresholdMax;
		}

		// FUNCTION: ENGINE 0x10919FD0
		void JawFlapBehaviour::SetThresholdMax(float value)
		{
			thresholdMax = value;
		}

		// FUNCTION: ENGINE 0x10919FE0
		float JawFlapBehaviour::GetAngleMin() const
		{
			return angleMin;
		}

		// FUNCTION: ENGINE 0x10919FF0
		void JawFlapBehaviour::SetAngleMin(float value)
		{
			angleMin = value;
		}

		// FUNCTION: ENGINE 0x1091A000
		float JawFlapBehaviour::GetAngleMax() const
		{
			return angleMax;
		}

		// FUNCTION: ENGINE 0x1091A010
		void JawFlapBehaviour::SetAngleMax(float value)
		{
			angleMax = value;
		}

		// FUNCTION: ENGINE 0x1091A020
		int JawFlapBehaviour::GetPriority() const
		{
			return priority;
		}

		// FUNCTION: ENGINE 0x1091A030
		void JawFlapBehaviour::SetPriority(int value)
		{
		}

		// FUNCTION: ENGINE 0x1091A040
		float JawFlapBehaviour::GetBlendInTime() const
		{
			return blendInTime;
		}

		// FUNCTION: ENGINE 0x1091A050
		void JawFlapBehaviour::SetBlendInTime(float value)
		{
			blendInTime = value;
		}

		// FUNCTION: ENGINE 0x1091A060
		float JawFlapBehaviour::GetBlendOutTime() const
		{
			return blendOutTime;
		}

		// FUNCTION: ENGINE 0x1091A070
		void JawFlapBehaviour::SetBlendOutTime(float value)
		{
			blendOutTime = value;
		}

		// FUNCTION: ENGINE 0x1091A080
		const math::Vector* JawFlapBehaviour::GetAxis() const
		{
			return &axis;
		}

		// FUNCTION: ENGINE 0x1091A090
		void JawFlapBehaviour::SetAxis(const math::Vector* value)
		{
			axis.x = value->x;
			axis.y = value->y;
			axis.z = value->z;
		}

		// FUNCTION: ENGINE 0x1091A290
		JawFlapBehaviour::JawFlapBehaviour(GameObject* newOwner) :
			Behaviour(newOwner),
			loudness(0.0f),
			jaw(0),
			thresholdMin(0.0f),
			thresholdMax(0.1f),
			angleMin(0.0f),
			angleMax(15.0f),
			priority(-1111),
			blendInTime(0.1f),
			blendOutTime(0.1f)
		{
			Listen(0x15, true);
			Listen(1, true);
			Listen2(0x100, true);
			axis.x = 0.0f;
			axis.y = 0.0f;
			axis.z = -1.0f;
		}

		// FUNCTION: ENGINE 0x1091A380
		JawFlapBehaviour::~JawFlapBehaviour()
		{
		}

		// FUNCTION: ENGINE 0x1091A3D0
		void JawFlapBehaviour::FindPuppet()
		{
			puppet = GetPuppet(owner);
		}

		// FUNCTION: ENGINE 0x1091A410
		void JawFlapBehaviour::ReleaseAll()
		{
			if (puppet.p != 0)
			{
				choreo::Puppet* held = puppet.p;
				puppet.p = 0;
				held->Release();
			}
			if (parts.p != 0)
			{
				core::IRefCount* held = parts.p;
				parts.p = 0;
				held->Release();
			}
			if (driver.p != 0)
			{
				choreo::Driver* held = driver.p;
				driver.p = 0;
				held->Release();
			}
			jaw = 0xffff;
			loudness = 0.0f;
		}

		// FUNCTION: ENGINE 0x1091B090
		void JawFlapBehaviour::Setup()
		{
			FindJaw();
			FindPuppet();
		}

		// FUNCTION: ENGINE 0x1091B0A0
		void JawFlapBehaviour::Slot1()
		{
			if (requested.Test(7))
			{
				Setup();
			}
		}

		// FUNCTION: ENGINE 0x1091B0C0
		void JawFlapBehaviour::OnActiveChanged(bool active)
		{
			Behaviour::OnActiveChanged(active);
			if (active)
			{
				Setup();
				return;
			}
			ReleaseAll();
		}

		// FUNCTION: ENGINE 0x1091AAC0
		void JawFlapBehaviour::OnMessage(Message* message)
		{
			switch (message->type)
			{
			case 1:
				{
					AttributeUpdatedMessage* update = (AttributeUpdatedMessage*)message;
					if (proto::gDrawableAttributeName == update->name)
					{
						FindJaw();
						return;
					}
					if (gPuppetAttributeName == update->name)
					{
						FindPuppet();
					}
				}
				break;
			case 0x15:
				switch ((unsigned short)message->id)
				{
				case 2:
					loudness = ((VoiceMessage*)message)->loudness;
					break;
				}
				break;
			}
		}

		// FUNCTION: ENGINE 0x1091AEB0
		content::MemberList* JawFlapBehaviour::GetMembers()
		{
			static content::MemberList sList;
			sList.baseType = content::GetClassMetaType<Behaviour>();
			static content::BaseClassCasterImpl<Behaviour, JawFlapBehaviour> sCaster;
			sList.baseCaster = &sCaster;
			static content::MemberInfo sMembers[] =
			{
				{ content::GetMemberMetaType<JawFlapBehaviour, float, 0>(&JawFlapBehaviour::GetThresholdMin,
					&JawFlapBehaviour::SetThresholdMin, "p"), 0, "thresholdMin" },
				{ content::GetMemberMetaType<JawFlapBehaviour, float, 1>(&JawFlapBehaviour::GetThresholdMax,
					&JawFlapBehaviour::SetThresholdMax, "p"), 0, "thresholdMax" },
				{ content::GetMemberMetaType<JawFlapBehaviour, float, 2>(&JawFlapBehaviour::GetAngleMin,
					&JawFlapBehaviour::SetAngleMin, "p"), 0, "angleMin" },
				{ content::GetMemberMetaType<JawFlapBehaviour, float, 3>(&JawFlapBehaviour::GetAngleMax,
					&JawFlapBehaviour::SetAngleMax, "p"), 0, "angleMax" },
				{ content::GetMemberMetaType<JawFlapBehaviour, int, 0>(&JawFlapBehaviour::GetPriority,
					&JawFlapBehaviour::SetPriority, "p"), 0, "priority" },
				{ content::GetMemberMetaType<JawFlapBehaviour, float, 4>(&JawFlapBehaviour::GetBlendInTime,
					&JawFlapBehaviour::SetBlendInTime, "p"), 0, "blendInTime" },
				{ content::GetMemberMetaType<JawFlapBehaviour, float, 5>(&JawFlapBehaviour::GetBlendOutTime,
					&JawFlapBehaviour::SetBlendOutTime, "p"), 0, "blendOutTime" },
				{ content::GetMemberVectorMetaType<JawFlapBehaviour, 0>(&JawFlapBehaviour::GetAxis,
					&JawFlapBehaviour::SetAxis, "p"), 0, "axis" }
			};
			sList.members = sMembers;
			sList.count = 8;
			return &sList;
		}
	}
}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x1091A250
// FUNCTION: ENGINE 0x1091A340
// FUNCTION: ENGINE 0x1091A350
// FUNCTION: ENGINE 0x1091A460
// FUNCTION: ENGINE 0x1091A480
// FUNCTION: ENGINE 0x1091A490
// FUNCTION: ENGINE 0x1091A4B0
// FUNCTION: ENGINE 0x1091A4D0
// FUNCTION: ENGINE 0x1091A4E0
// FUNCTION: ENGINE 0x1091A500
// FUNCTION: ENGINE 0x1091A590
// FUNCTION: ENGINE 0x1091A5B0
// FUNCTION: ENGINE 0x1091A5C0
// FUNCTION: ENGINE 0x1091AB30
// FUNCTION: ENGINE 0x1091ABA0
// FUNCTION: ENGINE 0x1091AC10
// FUNCTION: ENGINE 0x1091AC80
// FUNCTION: ENGINE 0x1091ACF0
// FUNCTION: ENGINE 0x1091AD60
// FUNCTION: ENGINE 0x1091ADD0
// FUNCTION: ENGINE 0x1091AE40
