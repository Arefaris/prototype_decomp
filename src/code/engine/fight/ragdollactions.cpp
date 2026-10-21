// The actions of the ragdoll tracks (the code sits in 0x1092DD60 - 0x1092FDF0, no assert path; file name guessed). The
// tracks and the conditions are in ragdoll.cpp.
#include "code/engine/fight/ragdollactions.h"
#include "code/engine/physics/physicsmessages.h"
#include "code/engine/physics/ragdollmessages.h"

namespace engine
{
	// FUNCTION: ENGINE 0x1092E030
	RagdollStoreJointVelocitiesAction::RagdollStoreJointVelocitiesAction(GameObjectHandle newTarget)
		: fight::Action(0x600), target(newTarget)
	{
	}

	// FUNCTION: ENGINE 0x1092E050
	RagdollStoreJointVelocitiesAction::~RagdollStoreJointVelocitiesAction()
	{
	}

	// FUNCTION: ENGINE 0x1092E980
	bool RagdollStoreJointVelocitiesAction::Slot5(int arg, float value)
	{
		GameObject* object = target.Get();
		if (object == 0)
		{
			return false;
		}
		RagdollStoreJointVelocitiesMessage message(true);
		object->SendMessage(&message);
		return true;
	}

	// FUNCTION: ENGINE 0x1092E9F0
	void RagdollStoreJointVelocitiesAction::Slot6()
	{
		GameObject* object = target.Get();
		if (object != 0)
		{
			RagdollStoreJointVelocitiesMessage message(false);
			object->SendMessage(&message);
		}
	}

	// FUNCTION: ENGINE 0x1092E2A0
	fight::Action* RagdollStoreJointVelocitiesTrack::CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner)
	{
		GameObjectHandle handle = GetObjectHandle(owner);
		return new RagdollStoreJointVelocitiesAction(handle);
	}

	// FUNCTION: ENGINE 0x1092E120
	UnpowerRagdollAction::UnpowerRagdollAction(GameObjectHandle newTarget)
		: fight::Action(0xE00), target(newTarget)
	{
	}

	// FUNCTION: ENGINE 0x1092E140
	UnpowerRagdollAction::~UnpowerRagdollAction()
	{
	}

	// FUNCTION: ENGINE 0x1092E150
	bool UnpowerRagdollAction::Slot7(int arg, float value)
	{
		return false;
	}

	// FUNCTION: ENGINE 0x1092E160
	void UnpowerRagdollAction::Slot6()
	{
	}

	// FUNCTION: ENGINE 0x1092EB30
	// EQUIVALENT: shrink-wrap; the engine saves ebx in the entry block, before the handle's table lookup, ours after it; every other instruction is the engine's
	bool UnpowerRagdollAction::Slot5(int arg, float value)
	{
		GameObject* object = target.Get();
		if (object != 0)
		{
			RagdollSetPoweredByPoseMessage message(0, 0, false);
			object->SendMessage(&message);
		}
		return false;
	}

	// FUNCTION: ENGINE 0x1092E3C0
	fight::Action* UnpowerRagdollTrack::CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner)
	{
		GameObjectHandle handle = GetObjectHandle(owner);
		return new UnpowerRagdollAction(handle);
	}

	// FUNCTION: ENGINE 0x1092EF40
	EnableRagdollAction::EnableRagdollAction(EnableRagdollTrack* newTrack, GameObjectHandle newTarget)
		: fight::Action(0x200), link(newTrack), target(newTarget)
	{
	}

	// FUNCTION: ENGINE 0x1092E840
	EnableRagdollAction::~EnableRagdollAction()
	{
	}

	// FUNCTION: ENGINE 0x1092EFD0
	// EQUIVALENT: register allocation and shrink-wrap; the engine keeps the track in ebp and the object in ebx and saves its registers in the entry block, ours the other way round; the message fields, calls and branches are the engine's
	bool EnableRagdollAction::Slot5(int arg, float value)
	{
		EnableRagdollTrack* track = link.object;
		if (track != 0)
		{
			GameObject* object = target.Get();
			if (object != 0)
			{
				int rootJoint = 0xffff;
				if (track->rootJoint.GetHash() != 0)
				{
					Attribute<proto::PartLookup*>* attribute = (Attribute<proto::PartLookup*>*)object->FindAttribute(proto::gDrawableAttributeName);
					if (attribute != 0)
					{
						proto::PartLookup** lookup = &attribute->value;
						if (lookup != 0 && *lookup != 0)
						{
							rootJoint = (*lookup)->FindPart(track->rootJoint);
						}
					}
				}
				RagdollSetEnabledMessage message(true, link.object->disableSupportingLimb, link.object->inheritJointVelocities, -1, 0xffff, true);
				message.rootJoint = rootJoint;
				message.includeRootJoint = link.object->includeRootJoint;
				if (link.object->useNormalPhysicsObjectAsRagdoll)
				{
					GetPhysicsObjectMessage query;
					object->PostMessage(&query);
					message.physicsObject = query.handle.value;
				}
				object->SendMessage(&message);
				SetPhysicsToPoseBlendFactorMessage poseMessage(1.0f, link.object->physicsTransitionDuration);
				object->SendMessage(&poseMessage);
			}
		}
		return false;
	}

	// FUNCTION: ENGINE 0x1092FC00
	fight::Action* EnableRagdollTrack::CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner)
	{
		GameObjectHandle handle = GetObjectHandle(owner);
		return new EnableRagdollAction(this, handle);
	}

	// FUNCTION: ENGINE 0x1092F140
	DisableRagdollAction::DisableRagdollAction(DisableRagdollTrack* newTrack, GameObjectHandle newTarget)
		: fight::Action(0x200), link(newTrack), target(newTarget)
	{
		if (newTrack->physicsBlendTime > 0.00001f)
		{
			SetFlag(0x400, true);
		}
	}

	// FUNCTION: ENGINE 0x1092E880
	DisableRagdollAction::~DisableRagdollAction()
	{
	}

	// FUNCTION: ENGINE 0x1092F1E0
	// EQUIVALENT: instruction selection; the engine pushes the -1 through eax (or eax, -1), ours pushes the immediate; every other instruction is the engine's
	bool DisableRagdollAction::Slot5(int arg, float value)
	{
		DisableRagdollTrack* track = link.object;
		if (track == 0)
		{
			return false;
		}
		GameObject* object = target.Get();
		if (object == 0)
		{
			return false;
		}
		bool notifies = Notifies();
		if (notifies)
		{
			float duration = track->Slot10();
			SetPhysicsToPoseBlendFactorMessage message(0.0f, duration);
			object->SendMessage(&message);
		}
		else
		{
			RagdollSetEnabledMessage message(false, false, true, -1);
			object->SendMessage(&message);
		}
		return notifies;
	}

	// FUNCTION: ENGINE 0x1092E8B0
	void DisableRagdollAction::Slot6()
	{
		GameObject* object = target.Get();
		if (object != 0)
		{
			SetPhysicsToPoseBlendFactorMessage poseMessage(1.0f, 0.0f);
			object->SendMessage(&poseMessage);
			RagdollSetEnabledMessage enabledMessage(false, false, true, -1, 0xffff, true);
			object->SendMessage(&enabledMessage);
		}
	}

	// FUNCTION: ENGINE 0x1092FC40
	fight::Action* DisableRagdollTrack::CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner)
	{
		GameObjectHandle handle = GetObjectHandle(owner);
		return new DisableRagdollAction(this, handle);
	}

	// FUNCTION: ENGINE 0x1092F970
	DeactivateRagdollAction::DeactivateRagdollAction(DeactivateRagdollTrack* newTrack, GameObjectHandle newTarget)
		: fight::Action(0x600), link(newTrack), target(newTarget)
	{
	}

	// FUNCTION: ENGINE 0x1092EBC0
	DeactivateRagdollAction::~DeactivateRagdollAction()
	{
	}

	// FUNCTION: ENGINE 0x1092FA00
	bool DeactivateRagdollAction::Slot5(int arg, float value)
	{
		if (link.object == 0)
		{
			return false;
		}
		GameObject* object = target.Get();
		if (object == 0)
		{
			return false;
		}
		RagdollSetBehaviourActiveMessage message(false);
		object->SendMessage(&message);
		return true;
	}

	// FUNCTION: ENGINE 0x1092EBF0
	void DeactivateRagdollAction::Slot6()
	{
		GameObject* object = target.Get();
		if (object != 0)
		{
			RagdollSetBehaviourActiveMessage message(true);
			object->SendMessage(&message);
		}
	}

	// FUNCTION: ENGINE 0x1092FD40
	fight::Action* DeactivateRagdollTrack::CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner)
	{
		GameObjectHandle handle = GetObjectHandle(owner);
		return new DeactivateRagdollAction(this, handle);
	}

	// FUNCTION: ENGINE 0x1092FA70
	RagdollSetKeyframeUpdatedAction::RagdollSetKeyframeUpdatedAction(RagdollSetKeyframeUpdatedTrack* newTrack, GameObjectHandle newTarget)
		: fight::Action(0x600), link(newTrack), target(newTarget)
	{
	}

	// FUNCTION: ENGINE 0x1092EC60
	RagdollSetKeyframeUpdatedAction::~RagdollSetKeyframeUpdatedAction()
	{
	}

	// FUNCTION: ENGINE 0x1092FB00
	// EQUIVALENT: scheduling; the engine takes the address of the message after storing the flag, ours before; every other instruction is the engine's
	bool RagdollSetKeyframeUpdatedAction::Slot5(int arg, float value)
	{
		RagdollSetKeyframeUpdatedTrack* track = link.object;
		if (track != 0)
		{
			GameObject* object = target.Get();
			if (object != 0)
			{
				RagdollSetKeyframeUpdatedMessage message(track->keyframeUpdated);
				object->SendMessage(&message);
				if (!message.handled)
				{
					SetFlag(0x400, false);
					return false;
				}
				return true;
			}
		}
		return false;
	}

	// FUNCTION: ENGINE 0x1092FB90
	// EQUIVALENT: instruction selection; the engine loads the track's flag into cl and tests it before sete, ours compares the byte in memory; every other instruction is the engine's
	void RagdollSetKeyframeUpdatedAction::Slot6()
	{
		RagdollSetKeyframeUpdatedTrack* track = link.object;
		if (track != 0)
		{
			GameObject* object = target.Get();
			if (object != 0)
			{
				bool updated = track->keyframeUpdated;
				RagdollSetKeyframeUpdatedMessage message(!updated);
				object->SendMessage(&message);
			}
		}
	}

	// FUNCTION: ENGINE 0x1092FD80
	fight::Action* RagdollSetKeyframeUpdatedTrack::CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner)
	{
		GameObjectHandle handle = GetObjectHandle(owner);
		return new RagdollSetKeyframeUpdatedAction(this, handle);
	}

	// FUNCTION: ENGINE 0x1092F800
	PowerRagdollByPuppetAction::PowerRagdollByPuppetAction(PowerRagdollByPuppetTrack* newTrack, GameObjectHandle newTarget)
		: fight::Action(0xE00), link(newTrack), target(newTarget)
	{
	}

	// FUNCTION: ENGINE 0x1092EB00
	PowerRagdollByPuppetAction::~PowerRagdollByPuppetAction()
	{
	}

	// FUNCTION: ENGINE 0x1092E100
	bool PowerRagdollByPuppetAction::Slot7(int arg, float value)
	{
		return false;
	}

	// FUNCTION: ENGINE 0x1092E110
	void PowerRagdollByPuppetAction::Slot6()
	{
	}

	// FUNCTION: ENGINE 0x1092FD00
	fight::Action* PowerRagdollByPuppetTrack::CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner)
	{
		GameObjectHandle handle = GetObjectHandle(owner);
		return new PowerRagdollByPuppetAction(this, handle);
	}
}
