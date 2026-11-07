// The messages the action halves of the motion fight items send, whose classes no other unit of this source tree declares (RTTI names; the constructors are
// inline in the engine and expanded in every user, so the argument lists and member names are guesses from the users).
#ifndef PROTO_FIGHTITEMS_MOTION_MOTIONMESSAGES3_H
#define PROTO_FIGHTITEMS_MOTION_MOTIONMESSAGES3_H

#include "code/engine/message.h"
#include "code/engine/gameobject/gameobjecthandle.h"
#include "code/core/name.h"
#include "code/proto/fightitems/ai/aicodemessages.h"
#include "code/proto/fightitems/motion/motionmessages.h"
#include "code/proto/fightitems/motion/motionmessages2.h"

namespace proto
{
	// RTTI: proto::SetGrabbingTimerGrabMessage
	struct SetGrabbingTimerGrabMessage : public proto::GrabMessage
	{
	public:
		SetGrabbingTimerGrabMessage(float vC, bool v10) : GrabMessage(11), unknownC(vC), unknown10(v10)
		{
		}
		virtual ~SetGrabbingTimerGrabMessage()
		{
		}

		float unknownC;  // +0xC
		bool unknown10;  // +0x10
	};

}
namespace proto
{
	// RTTI: proto::SetGrabTargetGrabMessage
	struct SetGrabTargetGrabMessage : public proto::GrabMessage
	{
	public:
		explicit SetGrabTargetGrabMessage(engine::GameObjectHandle vC) : GrabMessage(8), unknownC(vC)
		{
		}
		virtual ~SetGrabTargetGrabMessage()
		{
		}

		engine::GameObjectHandle unknownC;  // +0xC
	};

}
namespace proto
{
	// RTTI: proto::GroundSpikeMessage: the base of a family of messages (message type 0x30)
	class GroundSpikeMessage : public engine::IntrusiveMessage
	{
	public:
		explicit GroundSpikeMessage(short newId) : engine::IntrusiveMessage(0x30, newId)
		{
		}
		virtual ~GroundSpikeMessage()
		{
		}
	};

}
namespace proto
{
	// RTTI: proto::GroundSpikeShardInitializeForDescendMessage
	class GroundSpikeShardInitializeForDescendMessage : public proto::GroundSpikeMessage
	{
	public:
		GroundSpikeShardInitializeForDescendMessage(bool vC, float v18, float v14, float v10) : GroundSpikeMessage(8), unknownC(vC), unknown10(v10), unknown14(v14), unknown18(v18)
		{
		}
		virtual ~GroundSpikeShardInitializeForDescendMessage()
		{
		}

		bool unknownC;  // +0xC
		float unknown10;  // +0x10
		float unknown14;  // +0x14
		float unknown18;  // +0x18
	};

}
namespace proto
{
	// RTTI: proto::SetTimeWithNoDamageCounterEnabledMessage
	struct SetTimeWithNoDamageCounterEnabledMessage : public engine::IntrusiveMessage
	{
	public:
		explicit SetTimeWithNoDamageCounterEnabledMessage(bool vC) : engine::IntrusiveMessage(20, 50), unknownC(vC)
		{
		}
		virtual ~SetTimeWithNoDamageCounterEnabledMessage()
		{
		}

		bool unknownC;  // +0xC
	};

}
namespace proto
{
	// RTTI: proto::TemporaryRegenerationDamageMessage
	struct TemporaryRegenerationDamageMessage : public engine::IntrusiveMessage
	{
	public:
		TemporaryRegenerationDamageMessage(float newExpiry, float newRegenMaxHealthPercentage, float newRegenRate) : engine::IntrusiveMessage(20, 27), regenRate(newRegenRate), regenMaxHealthPercentage(newRegenMaxHealthPercentage), expiry(newExpiry)
		{
		}
		virtual ~TemporaryRegenerationDamageMessage()
		{
		}

		float regenRate;  // +0xC
		float regenMaxHealthPercentage;  // +0x10
		float expiry;  // +0x14
	};

}
namespace proto
{
	// RTTI: proto::IKMessage: the base of a family of messages (message type 0x2C)
	struct IKMessage : public engine::IntrusiveMessage
	{
	public:
		explicit IKMessage(short newId) : engine::IntrusiveMessage(0x2C, newId)
		{
		}
		virtual ~IKMessage()
		{
		}
	};

}
namespace proto
{
	// RTTI: proto::SetIKSurfaceFixupEnabledMessage
	struct SetIKSurfaceFixupEnabledMessage : public proto::IKMessage
	{
	public:
		explicit SetIKSurfaceFixupEnabledMessage(bool vC) : IKMessage(1), unknownC(vC)
		{
		}
		virtual ~SetIKSurfaceFixupEnabledMessage()
		{
		}

		bool unknownC;  // +0xC
	};

}
namespace proto
{
	// RTTI: proto::SetShoulderConFixupEnabledMessage
	struct SetShoulderConFixupEnabledMessage : public proto::IKMessage
	{
	public:
		explicit SetShoulderConFixupEnabledMessage(bool vC) : IKMessage(2), unknownC(vC)
		{
		}
		virtual ~SetShoulderConFixupEnabledMessage()
		{
		}

		bool unknownC;  // +0xC
	};

}
namespace proto
{
	// RTTI: proto::MagneticBootsGetSteerInfoMessage
	struct MagneticBootsGetSteerInfoMessage : public proto::MovementMessage
	{
	public:
		explicit MagneticBootsGetSteerInfoMessage(int vC) : MovementMessage(45), unknownC(vC)
		{
		}
		virtual ~MagneticBootsGetSteerInfoMessage()
		{
		}

		int unknownC;  // +0xC
	};

}
#endif
