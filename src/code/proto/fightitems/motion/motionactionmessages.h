// The messages the action half of the motion fight items of the consume, collision, death, decal, detect, devastator and edge units
// send to game objects. The messages are declared by other units of the engine (RTTI names; the constructors are inline there and
// expanded in every user), the member names and the argument lists are guesses from the users.
#ifndef PROTO_FIGHTITEMS_MOTION_MOTIONACTIONMESSAGES_H
#define PROTO_FIGHTITEMS_MOTION_MOTIONACTIONMESSAGES_H

#include "code/engine/message.h"
#include "code/engine/gameobject/gameobjecthandle.h"
#include "code/core/name.h"
#include "code/container/string.h"
#include "code/proto/fightitems/ai/aicodemessages.h"
#include "code/proto/fightitems/motion/motionmessages.h"

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

	// The parameters of a button hint (0x78 bytes, no RTTI): the part of an AddButtonHintMessage behind its header
	struct ButtonHintParams
	{
		// 0x100A01E0 (the engine's constructor is out of line)
		ButtonHintParams(int newButton, int newPressType, const char* newText, const core::Name<core::CaseSensitiveKey>& newScenarioMessage, int newPriority,
			bool newPersistent, bool new5D, bool new5E, bool new5F, const core::Name<core::CaseSensitiveKey>& new68);

		int button;  // +0x0
		int unknown4;  // +0x4
		int pressType;  // +0x8
		container::StringC<64> text;  // +0xC
		core::Name<core::CaseSensitiveKey> scenarioMessage;  // +0x50
		int priority;  // +0x58
		bool persistent;  // +0x5C
		bool unknown5D;  // +0x5D
		bool unknown5E;  // +0x5E
		bool unknown5F;  // +0x5F
		bool unknown60;  // +0x60
		unsigned char unknown61[0x7];
		core::Name<core::CaseSensitiveKey> unknown68;  // +0x68
	};

	// RTTI: proto::AddButtonHintMessage: shows a button hint on the object
	struct AddButtonHintMessage : public ButtonHintMessage
	{
		// 0x100A02A0 (out of line in the engine)
		AddButtonHintMessage(int newButton, int newPressType, const char* newText, const core::Name<core::CaseSensitiveKey>& newScenarioMessage, int newPriority,
			bool newPersistent, bool new5D, bool new5E, bool new5F, const core::Name<core::CaseSensitiveKey>& new68);
		virtual ~AddButtonHintMessage()
		{
		}

		int unknownC;  // +0xC
		ButtonHintParams params;  // +0x10
	};

	// RTTI: proto::RemoveButtonHintMessage: removes the button hint of a scenario message from the object
	struct RemoveButtonHintMessage : public ButtonHintMessage
	{
		// 0x1009FFB0 (out of line in the engine)
		explicit RemoveButtonHintMessage(const core::Name<core::CaseSensitiveKey>& newScenarioMessage);
		virtual ~RemoveButtonHintMessage()
		{
		}

		int unknownC;  // +0xC
		core::Name<core::CaseSensitiveKey> scenarioMessage;  // +0x10
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

	// RTTI: proto::AttemptGrabMessage: asks an object whether it can be grabbed by another (the object answers in grabbed)
	class AttemptGrabMessage : public GrabbableMessage
	{
	public:
		AttemptGrabMessage(engine::GameObjectHandle newGrabber, bool newDevastatorGrab) : GrabbableMessage(0), grabber(newGrabber), victim(), allowed(true), grabbed(false), devastatorGrab(newDevastatorGrab)
		{
		}
		virtual ~AttemptGrabMessage()
		{
		}

		engine::GameObjectHandle grabber;  // +0xC
		engine::GameObjectHandle victim;  // +0x10
		bool allowed;  // +0x14
		bool grabbed;  // +0x15
		bool devastatorGrab;  // +0x16
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
