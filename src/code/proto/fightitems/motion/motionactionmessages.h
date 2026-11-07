// The messages the action half of the motion fight items of the consume, collision, death, decal, detect, devastator and edge units
// send to game objects. The messages are declared by other units of the engine (RTTI names; the constructors are inline there and
// expanded in every user), the member names and the argument lists are guesses from the users.
#ifndef PROTO_FIGHTITEMS_MOTION_MOTIONACTIONMESSAGES_H
#define PROTO_FIGHTITEMS_MOTION_MOTIONACTIONMESSAGES_H

#include "code/engine/message.h"
#include "code/engine/gameobject/gameobjecthandle.h"
#include "code/core/name.h"
#include "code/proto/fightitems/ai/aicodemessages.h"

namespace engine
{
	// 0x11283540: the name of the attribute that holds the handle of the object an object is attached to
	extern core::Name<core::CaseSensitiveKey> gAttachmentState;

	// RTTI: engine::AttachmentGetAttachmentStateMessage: the object answers with the handle of the object it is attached to (a
	// pointer to the handle, or null)
	struct AttachmentGetAttachmentStateMessage : public NonintrusiveMessage
	{
		AttachmentGetAttachmentStateMessage() : NonintrusiveMessage(0xf, 6), parent(0)
		{
		}
		virtual ~AttachmentGetAttachmentStateMessage()
		{
		}

		GameObjectHandle* parent;  // +0xC
	};
}

namespace proto
{
	// RTTI: proto::ReleaseGrabbedObjectMessage: the object lets go of the grabbed object
	class ReleaseGrabbedObjectMessage : public GrabMessage
	{
	public:
		explicit ReleaseGrabbedObjectMessage(engine::GameObjectHandle newObject) : GrabMessage(2), object(newObject)
		{
		}
		virtual ~ReleaseGrabbedObjectMessage()
		{
		}

		engine::GameObjectHandle object;  // +0xC
	};

	// RTTI: proto::GrabbableMessage: the base of the messages about grabbable and consumable objects (message type 0x3C)
	class GrabbableMessage : public engine::IntrusiveMessage
	{
	public:
		explicit GrabbableMessage(short newId) : engine::IntrusiveMessage(0x3c, newId)
		{
		}
		virtual ~GrabbableMessage()
		{
		}
	};

	// RTTI: proto::QueryConsumeAnimationFinishedMessage: the object answers whether its consume animation has finished
	struct QueryConsumeAnimationFinishedMessage : public GrabbableMessage
	{
		QueryConsumeAnimationFinishedMessage() : GrabbableMessage(9), finished(false)
		{
		}
		virtual ~QueryConsumeAnimationFinishedMessage()
		{
		}

		bool finished;  // +0xC
	};

	// RTTI: proto::ScaleJointForConsumeMessage: scales a joint of the object to a size at a rate
	struct ScaleJointForConsumeMessage : public GrabbableMessage
	{
		ScaleJointForConsumeMessage(int newJoint, float newRate, float newScale) : GrabbableMessage(10), joint(newJoint), scale(newScale), rate(newRate)
		{
		}
		virtual ~ScaleJointForConsumeMessage()
		{
		}

		int joint;  // +0xC
		float scale;  // +0x10
		float rate;  // +0x14
	};

	// RTTI: proto::StopScalingJointForConsumeMessage: stops the scaling of a joint
	struct StopScalingJointForConsumeMessage : public GrabbableMessage
	{
		explicit StopScalingJointForConsumeMessage(int newJoint) : GrabbableMessage(0xb), joint(newJoint)
		{
		}
		virtual ~StopScalingJointForConsumeMessage()
		{
		}

		int joint;  // +0xC
	};
}

#endif
