// The actions of the supporting limb tracks (the code sits in 0x1092FDC0 - 0x10930870, no assert path; file name
// guessed). The tracks are in supportinglimb.cpp and supportingstick.cpp.
#include "code/engine/fight/supportinglimbactions.h"
#include "code/engine/gameobject/gameobjectmessages.h"
#include "code/engine/physics/supportinglimb.h"
#include "code/engine/physics/supportinglimbmessages.h"

namespace engine
{
	// FUNCTION: ENGINE 0x10930240
	SupportingLimbAction::SupportingLimbAction(SupportingLimbTrack* newTrack, GameObjectHandle newTarget)
		: fight::Action(0x200), link(newTrack), target(newTarget)
	{
	}

	// FUNCTION: ENGINE 0x1092FFD0
	SupportingLimbAction::~SupportingLimbAction()
	{
	}

	// FUNCTION: ENGINE 0x109302D0
	// EQUIVALENT: register allocation and shrink-wrap; the engine loads the direction's components into xmm2, xmm1 and xmm0 (z, y, x) and saves edi in the entry block, ours uses other registers; the arithmetic, calls and memory accesses are the engine's
	bool SupportingLimbAction::Slot5(int arg, float value)
	{
		if (link.object != 0)
		{
			GameObject* object = target.Get();
			if (object != 0)
			{
				FindSupportingLimbMessage find(link.object->supportingLimb);
				object->SendMessage(&find);
				SupportingLimb* limb = find.limb;
				SupportingLimbSetActiveMessage setActive(limb);
				object->SendMessage(&setActive);
				if (limb != 0)
				{
					SupportingLimbTrack* track = link.object;
					if (track->direction.z * track->direction.z + track->direction.y * track->direction.y + track->direction.x * track->direction.x > 0.0f)
					{
						math::Vector rotated(0.0f, 0.0f, 0.0f);
						math::Vector direction;
						direction.x = track->direction.x;
						direction.y = track->direction.y;
						direction.z = track->direction.z;
						object->transform->value.Rotate(direction, rotated);
						rotated.Normalize();
						limb->castDirection.x = rotated.x;
						limb->castDirection.y = rotated.y;
						limb->castDirection.z = rotated.z;
					}
				}
			}
		}
		return false;
	}

	// FUNCTION: ENGINE 0x109307B0
	fight::Action* SupportingLimbTrack::CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner)
	{
		GameObjectHandle handle = GetObjectHandle(owner);
		return new SupportingLimbAction(this, handle);
	}

	// FUNCTION: ENGINE 0x10930440
	SupportingSurfaceStickAction::SupportingSurfaceStickAction(SupportingSurfaceStickTrack* newTrack, GameObjectHandle newTarget)
		: fight::Action(0x200), link(newTrack), target(newTarget)
	{
		if (newTrack->restoreOnEnd)
		{
			SetFlag(0x400, true);
		}
	}

	// FUNCTION: ENGINE 0x10930010
	SupportingSurfaceStickAction::~SupportingSurfaceStickAction()
	{
	}

	// FUNCTION: ENGINE 0x109304D0
	// EQUIVALENT: register allocation; the engine keeps this in esi and the object in edi, ours the other way round; every other instruction is the engine's
	bool SupportingSurfaceStickAction::Slot5(int arg, float value)
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
		StickToSupportingSurfaceMessage message(link.object->stickToSupportingSurface);
		object->SendMessage(&message);
		previousStick = message.previous;
		SupportingLimbGetActiveMessage query;
		object->SendMessage(&query);
		SupportingLimb* limb = (SupportingLimb*)query.limb;
		if (limb != 0)
		{
			if (link.object->resetOrientationDelta)
			{
				limb->transform = math::Matrix::IDENTITY;
			}
			if (link.object->resetLimbSmoothing)
			{
				limb->unknown70 = true;
			}
		}
		return Notifies();
	}

	// FUNCTION: ENGINE 0x109305C0
	void SupportingSurfaceStickAction::Slot6()
	{
		if (link.object != 0)
		{
			GameObject* object = target.Get();
			if (object != 0)
			{
				StickToSupportingSurfaceMessage message(previousStick);
				object->SendMessage(&message);
			}
		}
	}

	// FUNCTION: ENGINE 0x109307F0
	fight::Action* SupportingSurfaceStickTrack::CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner)
	{
		GameObjectHandle handle = GetObjectHandle(owner);
		return new SupportingSurfaceStickAction(this, handle);
	}

	// FUNCTION: ENGINE 0x10930630
	SupportingLimbExtraLengthAction::SupportingLimbExtraLengthAction(SupportingLimbExtraLengthTrack* newTrack, GameObjectHandle newTarget)
		: fight::Action(0x600), link(newTrack), target(newTarget), limb(0), appliedLength(0.0f)
	{
	}

	// FUNCTION: ENGINE 0x10930050
	SupportingLimbExtraLengthAction::~SupportingLimbExtraLengthAction()
	{
	}

	// FUNCTION: ENGINE 0x109306B0
	bool SupportingLimbExtraLengthAction::Slot5(int arg, float value)
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
		limbName = link.object->supportingLimb;
		if (limbName.IsEmpty())
		{
			SupportingLimbGetActiveMessage query;
			object->SendMessage(&query);
			limb = (SupportingLimb*)query.limb;
			limbName = (*query.limb)->name;
		}
		else
		{
			FindSupportingLimbMessage find(limbName);
			object->SendMessage(&find);
			limb = find.limb;
		}
		if (limb == 0)
		{
			return false;
		}
		appliedLength = link.object->extraLength;
		limb->unknown6C = appliedLength + limb->unknown6C;
		return true;
	}

	// FUNCTION: ENGINE 0x10930080
	void SupportingLimbExtraLengthAction::Slot6()
	{
		GameObject* object = target.Get();
		if (object != 0 && limb != 0)
		{
			FindSupportingLimbMessage find(limbName);
			object->SendMessage(&find);
			if (limb == find.limb)
			{
				limb->unknown6C = limb->unknown6C - appliedLength;
			}
		}
	}

	// FUNCTION: ENGINE 0x10930830
	fight::Action* SupportingLimbExtraLengthTrack::CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner)
	{
		GameObjectHandle handle = GetObjectHandle(owner);
		return new SupportingLimbExtraLengthAction(this, handle);
	}
}
