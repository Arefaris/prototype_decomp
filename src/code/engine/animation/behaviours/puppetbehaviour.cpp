#include "code/engine/animation/behaviours/puppetbehaviour.h"
#include "code/engine/attributemessage.h"
#include "code/engine/driving/carattributes.h"
#include "code/engine/gameobject/gameobject.h"
#include "code/engine/gameobject/gameobjectsystem.h"
#include "code/engine/rendermessages.h"

namespace choreo
{
	extern const float gMinusOne;
}

namespace proto
{
	// The lookup of the parts of a drawable (effecttrack.h) and the name of the attribute that holds it (0x112834C8)
	struct PartLookup;
	extern content::ObjectName gDrawableAttributeName;
}

namespace engine
{
	// The name of the puppet attribute of a game object (0x112834F0)
	extern content::ObjectName gPuppetAttributeName;

	namespace animation
	{
		// FUNCTION: ENGINE 0x1091B180
		content::ClassInfo* PuppetBehaviour::GetClassInfo()
		{
			static content::ClassInfo sInfo;
			sInfo.version = 1;
			sInfo.name = "PuppetBehaviour";
			sInfo.code = "p";
			return &sInfo;
		}

		// FUNCTION: ENGINE 0x1091B1D0
		bool PuppetBehaviour::GetIkLimbsEnabled() const
		{
			if (puppet == 0)
			{
				return ikLimbsEnabled;
			}
			return puppet->mUnknown40;
		}

		// FUNCTION: ENGINE 0x1091B1E0
		void PuppetBehaviour::SetIkLimbsEnabled(bool value)
		{
			ikLimbsEnabled = value;
			if (puppet != 0)
			{
				puppet->mUnknown40 = value;
			}
		}

		// FUNCTION: ENGINE 0x1091B200
		bool PuppetBehaviour::GetAutoUpdateLocomotionPhase() const
		{
			if (puppet == 0)
			{
				return autoUpdateLocomotionPhase;
			}
			return puppet->mUnknown15C;
		}

		// FUNCTION: ENGINE 0x1091B220
		void PuppetBehaviour::SetAutoUpdateLocomotionPhase(bool value)
		{
			autoUpdateLocomotionPhase = value;
			if (puppet != 0)
			{
				puppet->mUnknown15C = value;
			}
		}

		// FUNCTION: ENGINE 0x1091B240
		bool PuppetBehaviour::GetDeferredUpdate() const
		{
			return deferredUpdate;
		}

		// FUNCTION: ENGINE 0x1091C400
		PuppetBehaviour::PuppetBehaviour(GameObject* newOwner) : Behaviour(newOwner), puppet(0), unknown14(false),
			ikLimbsEnabled(false), autoUpdateLocomotionPhase(false), deferredUpdate(false),
			unknown20(choreo::gMinusOne), suppressErrorOnDisableBatching(false)
		{
			Listen(10, true);
			Listen(1, true);
			Listen(0x17, true);
			Listen(2, true);
			Listen(0x11, true);
			Listen(0x19, true);
			Listen2(4, true);
			Listen2(0x10, true);
			owner->SetAttributeAndGet<choreo::Puppet*>(gPuppetAttributeName, 0, false);
			owner->SetAttributeAndGet<proto::PartLookup*>(proto::gDrawableAttributeName, 0, false);
		}

		// FUNCTION: ENGINE 0x1091B360
		PuppetBehaviour::~PuppetBehaviour()
		{
			core::SafeRelease(puppet);
		}

		// FUNCTION: ENGINE 0x1091B250
		void PuppetBehaviour::UpdateTimeScale(bool enable)
		{
			bool valid = handle.IsValid();
			if (enable)
			{
				if (!valid)
				{
					handle = choreo::CreatePuppetHandle(puppet);
				}
				puppet->mTimeScale = owner->behaviours.updateTimeScalar;
				return;
			}
			if (valid)
			{
				choreo::DestroyPuppetHandle(handle);
				handle = choreo::PuppetHandle();
			}
			puppet->mTimeScale = driving::gOne;
		}

		// FUNCTION: ENGINE 0x1091BC50
		void PuppetBehaviour::CreatePuppet()
		{
			if (puppet == 0)
			{
				Attribute<proto::PartLookup*>* drawable =
					(Attribute<proto::PartLookup*>*)owner->FindAttribute(proto::gDrawableAttributeName);
				pure3d::Pose* pose = (pure3d::Pose*)drawable->value;
				if (pose != 0)
				{
					core::RefAssign(puppet, new choreo::Puppet(pose));
					puppet->SetUserData((int)(choreo::Puppet::ValidationFailedCallback*)this);
					Attribute<choreo::Puppet*>* attribute =
						(Attribute<choreo::Puppet*>*)owner->FindAttribute(gPuppetAttributeName);
					attribute->value = puppet;
					puppet->mUnknown40 = ikLimbsEnabled;
					puppet->mUnknown15C = autoUpdateLocomotionPhase;
					SetDeferredUpdate(deferredUpdate);
					RenderEvaluatePoseMessage message(false);
					owner->SendMessage(&message);
				}
			}
		}

		// FUNCTION: ENGINE 0x1091BD20
		void PuppetBehaviour::DestroyPuppet()
		{
			if (puppet != 0)
			{
				ikLimbsEnabled = puppet->mUnknown40;
			}
			bool deferred = deferredUpdate;
			SetDeferredUpdate(false);
			deferredUpdate = deferred;
			core::SafeRelease(puppet);
			Attribute<choreo::Puppet*>* attribute = (Attribute<choreo::Puppet*>*)owner->FindAttribute(gPuppetAttributeName);
			attribute->value = puppet;
			RenderEvaluatePoseMessage message(true);
			owner->SendMessage(&message);
		}

		// FUNCTION: ENGINE 0x1091B430
		void PuppetBehaviour::Suspend(Message* message)
		{
			if (requested.Test(7))
			{
				OnActiveChanged(false);
				SetState(STATE_DIRTY);
			}
		}

		// FUNCTION: ENGINE 0x1091B460
		void PuppetBehaviour::Resume(Message* message)
		{
			if (!requested.Test(7) && (state & STATE_DIRTY) != 0)
			{
				ClearState(STATE_DIRTY);
				OnActiveChanged(true);
			}
		}

		// FUNCTION: ENGINE 0x1091B390
		void PuppetBehaviour::OnPostedMessage(Message* message)
		{
			switch (message->type)
			{
			case 10:
				if (message->id == 5)
				{
					GetLocomotionMessage* locomotion = (GetLocomotionMessage*)message;
					locomotion->linearVelocity[0] = locomotionState.linearVelocity[0];
					locomotion->linearVelocity[1] = locomotionState.linearVelocity[1];
					locomotion->linearVelocity[2] = locomotionState.linearVelocity[2];
					locomotion->angularVelocity[0] = locomotionState.angularVelocity[0];
					locomotion->angularVelocity[1] = locomotionState.angularVelocity[1];
					locomotion->angularVelocity[2] = locomotionState.angularVelocity[2];
				}
				break;
			case 0x11:
				if (message->id == 8)
				{
					((GetIkLimbsMessage*)message)->ikLimbsEnabled = GetIkLimbsEnabled();
				}
				break;
			}
		}

		// FUNCTION: ENGINE 0x1091C0E0
		void PuppetBehaviour::Slot1()
		{
			if (requested.Test(7))
			{
				CreatePuppet();
			}
			unknown14 = true;
		}

		// FUNCTION: ENGINE 0x1091C070
		void PuppetBehaviour::OnActiveChanged(bool active)
		{
			if (GetHandle(owner).Get() != 0)
			{
				if (active)
				{
					CreatePuppet();
				}
				else
				{
					DestroyPuppet();
				}
			}
			Behaviour::OnActiveChanged(active);
		}

		// FUNCTION: ENGINE 0x1091C100
		void PuppetBehaviour::OnMessage(Message* message)
		{
			switch (message->type)
			{
			case 2:
				if (puppet != 0)
				{
					puppet->RemoveAll(true);
					locomotionState.Reset();
					return;
				}
				locomotionState.Reset();
				break;
			case 1:
				{
					AttributeUpdatedMessage* update = (AttributeUpdatedMessage*)message;
					core::Name<core::CaseSensitiveKey> name(update->name);
					if (name == proto::gDrawableAttributeName)
					{
						if (puppet != 0)
						{
							Attribute<proto::PartLookup*>* drawable =
								(Attribute<proto::PartLookup*>*)owner->FindAttribute(proto::gDrawableAttributeName);
							puppet->SetPose((pure3d::Pose*)drawable->value);
							return;
						}
						if (unknown14 && requested.Test(7))
						{
							CreatePuppet();
							return;
						}
					}
				}
				break;
			case 0x17:
				switch ((unsigned short)message->id)
				{
				case 4:
					Suspend(message);
					return;
				case 6:
					Resume(message);
					return;
				}
				break;
			case 0x11:
				if (message->id == 9)
				{
					SetIkLimbsEnabled(((SetIkLimbsMessage*)message)->ikLimbsEnabled);
					return;
				}
				break;
			case 0x19:
				switch ((unsigned short)message->id)
				{
				case 0:
					if (puppet != 0)
					{
						puppet->mTimeScale = driving::gOne;
						return;
					}
					break;
				case 1:
					if (puppet != 0)
					{
						if (deferredUpdate && unknown20 <= -0.00001f)
						{
							puppet->mTimeScale = ((PuppetTimeScaleMessage*)message)->timeScale;
							return;
						}
						puppet->mTimeScale = driving::gOne;
						return;
					}
					break;
				}
				break;
			case 10:
				if (message->id != 6)
				{
					return;
				}
				locomotionState.Reset();
				break;
			}
		}

		// FUNCTION: ENGINE 0x1091B2E0
		int PuppetBehaviour::OnValidationFailed(int unknown4, bool disableBatching, int unknown12)
		{
			if (disableBatching && suppressErrorOnDisableBatching)
			{
				return 0;
			}
			return 1;
		}

		// FUNCTION: ENGINE 0x1091B3F0
		void PuppetBehaviour::SetDeferredUpdate(bool value)
		{
			deferredUpdate = value;
			if (puppet == 0)
			{
				return;
			}
			UpdateTimeScale(value && unknown20 <= -0.00001f);
		}

		// FUNCTION: ENGINE 0x1091BF20
		content::MemberList* PuppetBehaviour::GetMembers()
		{
			static content::MemberList sList;
			sList.baseType = content::GetClassMetaType<Behaviour>();
			static content::BaseClassCasterImpl<Behaviour, PuppetBehaviour> sCaster;
			sList.baseCaster = &sCaster;
			static content::MemberInfo sMembers[] =
			{
				{ content::GetMemberMetaType<PuppetBehaviour, bool, 0>(&PuppetBehaviour::GetIkLimbsEnabled,
					&PuppetBehaviour::SetIkLimbsEnabled, "p"), 0, "ikLimbsEnabled" },
				{ content::GetMemberMetaType<PuppetBehaviour, bool, 1>(&PuppetBehaviour::GetAutoUpdateLocomotionPhase,
					&PuppetBehaviour::SetAutoUpdateLocomotionPhase, "p"), 0, "autoUpdateLocomotionPhase" },
				{ content::GetMemberMetaType<PuppetBehaviour, bool, 2>(&PuppetBehaviour::GetDeferredUpdate,
					&PuppetBehaviour::SetDeferredUpdate, "p"), 0, "deferredUpdate" },
				{ content::GetMemberPrimitiveMetaType<PuppetBehaviour, bool, 0>("p"),
					content::MemberOffset(&((PuppetBehaviour*)0)->suppressErrorOnDisableBatching,
					(int)&((PuppetBehaviour*)0)->suppressErrorOnDisableBatching), "suppressErrorOnDisableBatching" }
			};
			sList.members = sMembers;
			sList.count = 4;
			return &sList;
		}
	}
}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x1091B320
// FUNCTION: ENGINE 0x1091B330
// FUNCTION: ENGINE 0x1091B870
// FUNCTION: ENGINE 0x1091B8B0
// FUNCTION: ENGINE 0x1091B8E0
// FUNCTION: ENGINE 0x1091B900
// FUNCTION: ENGINE 0x1091BDA0
// FUNCTION: ENGINE 0x1091BE20
// FUNCTION: ENGINE 0x1091BEA0
// FUNCTION: ENGINE 0x1091B300
// FUNCTION: ENGINE 0x1091B920
