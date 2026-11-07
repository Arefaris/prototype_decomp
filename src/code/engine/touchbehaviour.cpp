#include "code/engine/touchbehaviour.h"
#include "code/engine/gameobject/gameobject.h"
#include "code/engine/gameobject/gameobjectsystem.h"
#include "code/ravenphysics/physicsobject.h"
#include <new>

namespace engine
{
	extern core::Name<core::CaseSensitiveKey> gTransformName;

	namespace camera
	{
		extern const float gThousandth;
	}

	namespace trigger
	{
		// 0x10899FB0 / 0x1089A030 (another unit; name guesses): put the volume into the world's list / take it out
		void AddVolume(Volume* volume);
		void RemoveVolume(Volume* volume);
	}

	// The sphere of a volume nobody sized, built where the volume is made
	struct SmallSphere : public math::Sphere
	{
		SmallSphere()
		{
			centre.x = 0.0f;
			centre.y = 0.0f;
			centre.z = 0.0f;
			radius = camera::gThousandth;
		}
	};

#define ENGINE_OFFSET(type, member) \
	content::MemberOffset(&((type*)0)->member, (int)&((type*)0)->member)

	// FUNCTION: ENGINE 0x10929FF0
	content::ClassInfo* TouchBehaviour::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "engine::TouchBehaviour";
		sInfo.code = "pn";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x1092A030
	TouchBehaviour::TouchBehaviour(GameObject* newOwner) : Behaviour(newOwner)
	{
		volume = 0;
		Listen(0x1a, true);
		Listen(0x17, true);
	}

	// FUNCTION: ENGINE 0x1092A070
	void TouchBehaviour::Slot0()
	{
		Listen2(4, true);
		if (volume == 0)
		{
			volume = new trigger::SphereVolume(SmallSphere());
		}
	}

	// FUNCTION: ENGINE 0x1092A140
	void TouchBehaviour::Slot1()
	{
		volume->SetKind(1);
		BaseAttribute* attribute = owner->FindAttribute(gTransformName);
		if (attribute != 0)
		{
			volume->SetObjectTransform(((Attribute<math::Matrix>*)attribute)->value);
		}
		OnActiveChanged(requested.Test(7));
		volume->SetOwner(GetHandle(owner));
	}

	// FUNCTION: ENGINE 0x1092A1A0
	void TouchBehaviour::OnActiveChanged(bool active)
	{
		Behaviour::OnActiveChanged(active);
		if (volume != 0 && volume->GetHandle()->IsValid())
		{
			bool asleep = volume->GetHandle()->GetObjectSecond()->asleep == 1;
			if (active)
			{
				if (!asleep)
				{
					trigger::AddVolume(volume);
				}
			}
			else if (asleep)
			{
				trigger::RemoveVolume(volume);
			}
		}
	}

	// FUNCTION: ENGINE 0x1092A230
	void TouchBehaviour::Update(float dt, unsigned short mask)
	{
		volume->SetObjectTransform(owner->transform->value);
	}

	// FUNCTION: ENGINE 0x1092A250
	void TouchBehaviour::OnMessage(Message* message)
	{
		switch (message->type)
		{
		case 0x17:
			if ((unsigned short)message->id == 3)
			{
				if (requested.Test(7))
				{
					Behaviour::OnActiveChanged(false);
					SetState(2);
				}
			}
			else if ((unsigned short)message->id == 7)
			{
				if (!requested.Test(7) && (state & 2) != 0)
				{
					ClearState(2);
					Behaviour::OnActiveChanged(true);
				}
			}
			break;
		case 0x1a:
			volume->SetObjectTransform(owner->transform->value);
			Listen(0x1a, false);
			break;
		}
	}

	// FUNCTION: ENGINE 0x1092A2F0
	TouchBehaviour::~TouchBehaviour()
	{
		TouchBehaviour::OnActiveChanged(false);
		delete volume;
	}

	// FUNCTION: ENGINE 0x1092A370
	content::MemberList* TouchBehaviour::GetMembers()
	{
		static content::MemberList sList;
		sList.baseType = content::GetClassMetaType<Behaviour>();
		static content::BaseClassCasterImpl<Behaviour, TouchBehaviour> sCaster;
		sList.baseCaster = &sCaster;
		static content::MemberInfo sMembers[] =
		{
			{ content::GetObjectMetaType<trigger::Volume>("pnr"), ENGINE_OFFSET(TouchBehaviour, volume), "volume" }
		};
		sList.members = sMembers;
		sList.count = 1;
		return &sList;
	}
}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x1092A100
// FUNCTION: ENGINE 0x1092A110
// FUNCTION: ENGINE 0x1092A320
// FUNCTION: ENGINE 0x1092A420
